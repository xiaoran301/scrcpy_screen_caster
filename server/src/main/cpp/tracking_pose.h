enum PoseErrorType {
    BRIGHT_LIGHT_ERROR = (1 << 0),
    LOW_LIGHT_ERROR = (1 << 1),
    LOW_FEATURE_COUNT_ERROR = (1 << 2),
    CAMERA_CALIBRATION_ERROR = (1 << 3),
    RELOCATION_IN_PROGRESS = (1 << 4),
    INITILIZATION_IN_PROGRESS = (1 << 5),
    NO_CAMERA_ERROR = (1 << 6),
    NO_IMU_ERROR = (1 << 7),
    IMU_JITTER_ERROR = (1 << 8),
    UNKNOWN_ERROR = (1 << 9)
};

typedef struct six_dof {
    int64_t timestamp;  // nanoseconds
    double x;           // positon X
    double y;           // position Y
    double z;           // position Z
    double rw;          // rotation W
    double rx;          // rotation X
    double ry;          // rotation Y
    double rz;          // rotation Z
    uint8_t type;       // 1:6DOF 0:3DOF
    uint8_t confidence; // 1:good 0:bad
    PoseErrorType error;
    double plane_height;
    uint8_t plane_status;
    uint8_t relocation_status;
    uint8_t reserved[24];
} six_dof_t;

typedef struct {
    six_dof_t pose;
    six_dof_t relocation_pose;
    double vx, vy, vz;       //!< 线速度
    double ax, ay, az;       //!< 线加速度
    double wx, wy, wz;       //!< 角速度
    double w_ax, w_ay, w_az; //!< 角加速度
    uint8_t reserved[48];
} algo_result_t;
