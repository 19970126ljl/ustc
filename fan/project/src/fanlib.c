#include<stdio.h>
#include<errno.h>
#include "../include/cndev.h"

void initialize(){
        cndevCheckErrors(cndevInit(CNDEV_VERSION_4));
}
void release(){
        cndevRelease();
}
void output_data(char *filename, char *print_str)
{
    FILE* out;
    if((out = fopen(filename,"a+"))==NULL){
        fprintf(stderr,"opened file wrong： %s",strerror(errno));
    }
    if(fprintf(out,print_str)<0){
        fprintf(stderr,"output file wrong： %s",strerror(errno));
    }
    fclose(out);
}

void shutdownBMC(){
    system("ipmitool raw 0x30 0x70 0x02 0x01");
    //printf("shutdown BMC\n");
}
void set_speed(int speed)
{
	static int oldSpeed = 5;
	char command_str[64] = {0};
	if (speed != oldSpeed)
	{
		oldSpeed = speed;
		if (speed > 100)
			speed = 100;
		if (speed < 5)
			speed = 5;
		sprintf(command_str, "ipmitool raw 0x30 0x70 0x66 0x01 0x01 %#x\n", speed);
		system(command_str);
	}
}



cndevLibVersionInfo_t getLibVersion(){ 
    cndevLibVersionInfo_t libVersion;
    libVersion.version = CNDEV_VERSION_4;
    cndevCheckErrors(cndevGetLibVersion(&libVersion));
    printf("cndev lib version:%d.%d.%d\n",
        libVersion.LibMajorVersion,
        libVersion.LibMinorVersion,
        libVersion.LibBuildVersion);
    return libVersion;
}

int getBoardNum(){
    cndevRet_t ret;
    cndevCardInfo_t cardInfo;
    cardInfo.version = CNDEV_VERSION_3;
    cndevCheckErrors(cndevGetDeviceCount(&cardInfo));
    return cardInfo.Number;
}


int getBoardUtilization(unsigned Id){
    cndevUtilizationInfo_t utilInfo;
    utilInfo.version = CNDEV_VERSION_3;
    cndevCheckErrors(cndevGetDeviceUtilizationInfo(&utilInfo,Id));
    //printf("Util:%d\n", utilInfo.BoardUtilization);
    return utilInfo.BoardUtilization;
}

int getCoreNum(int boardId){
    cndevCardCoreCount_t cardCoreCount;
    cardCoreCount.version = CNDEV_VERSION_3;
    cndevCheckErrors(cndevGetCoreCount(&cardCoreCount,boardId));
    return cardCoreCount.count;
}
void getCoreUtilization(unsigned boardId,int a[]){
    cndevUtilizationInfo_t utilInfo;
    utilInfo.version = CNDEV_VERSION_3;
    cndevCheckErrors(cndevGetDeviceUtilizationInfo(&utilInfo,boardId));
    cndevCardCoreCount_t cardCoreCount;
    cardCoreCount.version = CNDEV_VERSION_3;
    cndevCheckErrors(cndevGetCoreCount(&cardCoreCount,boardId));
    //for (int i = 0; i < cardCoreCount.count; i++) 
    //    printf("Util CORE%d:%d\n",i,utilInfo.CoreUtilization[i]);
    for(int i = 0;i<cardCoreCount.count;i++) a[i] = utilInfo.CoreUtilization[i];
}

int getBoardTemperature(int boardId){
    cndevTemperatureInfo_t tempInfo;
    tempInfo.version = CNDEV_VERSION_3;
    cndevCheckErrors(cndevGetTemperatureInfo(&tempInfo,boardId));
    //printf("temperatures:board:%dC\n",tempInfo.Board);
    return tempInfo.Board;
}

int getClusterNum(int boardId){
    cndevTemperatureInfo_t tempInfo;
    tempInfo.version = CNDEV_VERSION_3;
    cndevCheckErrors(cndevGetTemperatureInfo(&tempInfo,boardId));
    cndevCardClusterCount_t cardClusterCount;
    cardClusterCount.version = CNDEV_VERSION_3;
    cndevCheckErrors(cndevGetClusterCount(&cardClusterCount,boardId));
    return cardClusterCount.count;
}

void getClusterTemperature(int boardId,int a[]){
    cndevTemperatureInfo_t tempInfo;
    tempInfo.version = CNDEV_VERSION_3;
    cndevCheckErrors(cndevGetTemperatureInfo(&tempInfo,boardId));
    cndevCardClusterCount_t cardClusterCount;
    cardClusterCount.version = CNDEV_VERSION_3;
    cndevCheckErrors(cndevGetClusterCount(&cardClusterCount,boardId));
    //printf("Clusters:");
    //for (int i = 0; i < cardClusterCount.count; i++) 
    //    printf("%dC ", tempInfo.Cluster[i]);
    for(int i = 0;i<cardClusterCount.count;i++) a[i] = tempInfo.Cluster[i];
    //printf("\n");
}

cndevProcessInfo_t *processInfo(){
    unsigned tCount = 10;
    cndevRet_t ret;
    cndevProcessInfo_t *procInfo = NULL;
    procInfo = (cndevProcessInfo_t *) malloc(tCount * sizeof(cndevProcessInfo_t));
    procInfo->version = CNDEV_VERSION_3;
    ret = cndevGetProcessInfo(&tCount, procInfo, 0);
    while (ret == CNDEV_ERROR_INSUFFICIENT_SPACE) {
        procInfo = (cndevProcessInfo_t *)realloc(procInfo,tCount * sizeof(cndevProcessInfo_t));
        realloc(procInfo,tCount * sizeof(cndevProcessInfo_t));
        ret = cndevGetProcessInfo(&tCount, procInfo, 0);
    }
    cndevCheckErrors(ret);
    return procInfo;
}
