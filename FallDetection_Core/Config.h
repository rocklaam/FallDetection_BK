// top limit of human rect- to prevent detecting fall in rotate camera
#define AREA_MAX			28800

// duration of stage- (unit: seconds)
#define DURATION_D0			1
#define DURATION_DY			2

#define FRAME_HEIGHT		180
#define FRAME_WIDTH			320

// duration of MHI- (unit: seconds)
#define MHI_DURATION		0.5

// stage of algorithm- for switch- case
#define STAGE_CMOTION		1
#define STAGE_D0			2
#define STAGE_DY			3

// threshold of algorithm
#define THRESHOLD_CMOTION	0.9 //1.5
#define THRESHOLD_D0		25
#define THRESHOLD_DA_B		0.9
