
void initialize();

void release();

//append print_str to filename
void output_data(char *filename, char *print_str);

//set the fan speed
void shutdownBMC();

//set the speed
void set_speed(int speed);

//get the lib infomation
cndevLibVersionInfo_t getLibVersion();

//get the num of board
int getBoardNum();

//get the utilization of the board with id 
int getBoardUtilization(unsigned Id);

//get the number of cores
int getCoreNum(int boardId);
//get each core's utilization
void getCoreUtilization(unsigned boardId,int a[]);

//get theboard tmperature
int getBoardTemperature(int boardId);

//get cluster num
int getClusterNum(int boardId);
//get cluster temperature
void getClusterTemperature(int boardId,int a[]);

//get the board frequency
int getBoardFreq(int boardId);

//get the board power usage
int getBoardPowerUsage(int boardId);


//get process infomation
cndevProcessInfo_t *processInfo();
