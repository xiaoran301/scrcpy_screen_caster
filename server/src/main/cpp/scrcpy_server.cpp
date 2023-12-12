// Write C++ code here.
//
// Do not forget to dynamically load the C++ library into your application.
//
// For instance,
//
// In MainActivity.java:
//    static {
//       System.loadLibrary("scrcpy");
//    }
//
// Or, in MainActivity.kt:
//    companion object {
//      init {
//         System.loadLibrary("scrcpy")
//      }
//    }
#include <dlfcn.h>

#include "tracking_pose.h"
#include "log_util.h"
#include "quater.h"
#include "custom_math.h"

// tracking client 接口
#define TRACKINGCLIENT_NAME "libtrackingclient.pxr.so"
struct client_interface_t {
    void *(*CreateClient)();
    int (*DestroyClient)(void *client);
    int (*setFakePoseMode)(void *client, int enable);
    int (*injectHMDPose)(void *client, algo_result_t *pose);
    int (*injectControllerPose)(void *client, algo_result_t *left, algo_result_t *right);
};

// global var
client_interface_t g_client_interface{};
void *g_pTrackingclient = nullptr;

// 用于头戴的位姿
algo_result_t g_fakepose;

// 是否开启pico的inject
bool g_openHook = false;

// 当前旋转比例
Vector3 g_rotate_ratio = {0, 0, 0};


void reset_trackpose(algo_result_t *trackpose){
    trackpose->pose.x = 0;
    trackpose->pose.y = 0;
    trackpose->pose.z = 0;
    trackpose->pose.rw = 1;
    trackpose->pose.rx = 0;
    trackpose->pose.ry = 0;
}

// 初始化
int init_trackingservice_client(){
    LOGI("init_trackingservice_client");
    void *handle = dlopen(TRACKINGCLIENT_NAME, RTLD_NOW | RTLD_NODELETE);
    if (!handle) {
        LOGE("Error opening %s %s\n", TRACKINGCLIENT_NAME, dlerror());
        return -1;
    }
    
    // 连接结构体中的函数指针到动态库中对应的函数
    *(void**) &(g_client_interface.CreateClient) = dlsym(handle, "CreateClient");
    *(void**) &(g_client_interface.DestroyClient) = dlsym(handle, "DestroyClient");
    *(void**) &(g_client_interface.setFakePoseMode) = dlsym(handle, "setFakePoseMode");
    *(void**) &(g_client_interface.injectHMDPose) = dlsym(handle, "injectHMDPose");
    *(void**) &(g_client_interface.injectControllerPose) = dlsym(handle, "injectControllerPose");
   
    // 调用函数获取client对象
    g_pTrackingclient = g_client_interface.CreateClient();
    if(g_pTrackingclient == nullptr){
        LOGE("Error CreateClient \n");
        return -1;
    }
    
    
    reset_trackpose(&g_fakepose);
    return 0;
}

/**
* 开启和关闭注入
* @return bool
* @note 使用前先开启开关，一旦开启，设备的输入将会失效，因此使用完成后需要关闭
*/
bool open_hook(bool flag){
    LOGI("open_hook: %d", flag);
    if(g_pTrackingclient == nullptr){
        int ret = init_trackingservice_client();
        if(ret != 0){
            return false;
        }
    }
    g_client_interface.setFakePoseMode(g_pTrackingclient, flag ? 1 : 0);
    return true;
}

void switch_open_hook(){
    open_hook(!g_openHook);
    g_openHook =!g_openHook;
}


/**
* rotate hmd
* @param nwdx normal window delta x
* @param nwdy normal window delta y
* @return
* @note window origin is left up corner,normal range:[-1,1] map to [-90,90] degree
*/
void rotate_hmd(float nwdx, float nwdy){
    if(!g_openHook){
        LOGI("auto open hook,when drag mouse in pressed right state!!");
        switch_open_hook();
    }
    float nx = -nwdx;
    float ny = -nwdy;
    LOGI("rotate_hmd nx:%f ny:%f", nx, ny);

    g_rotate_ratio.x += nx;
    g_rotate_ratio.y += ny;
    Quaternion quater =  eulerToQuaternion(g_rotate_ratio.y*90,g_rotate_ratio.x*90,0);
    g_fakepose.pose.rw = quater.w;
    g_fakepose.pose.rx = quater.x;
    g_fakepose.pose.ry = quater.y;
    g_fakepose.pose.rz = quater.z;
    g_client_interface.injectHMDPose(g_pTrackingclient, &g_fakepose);
}

class AutoCleanUp{
public:
    AutoCleanUp(){
        LOGI("AutoCleanUp constructor");
    }
    ~AutoCleanUp(){
        LOGI("AutoCleanUp destructor");
        if(g_openHook){
            LOGI("AutoCleanUp will close pico inject");

            // 清理旋转数据
            g_rotate_ratio.reset();
            rotate_hmd(0,0);

            // 关闭
            g_openHook = false;
            open_hook(false);

        }
    }
};
static AutoCleanUp s_automactic_clean_up;
