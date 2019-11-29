#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include "../include/cndev.h"
#include "../include/readconfig.h"
#include "../include/debug.h"
#include "../include/fanOp.h"
/*

cndevCheckErrors(cndevInit(CNDEV_VERSION_4));
cndevRelease();

*/
int main(){
	cndevCheckErrors(cndevInit(CNDEV_VERSION_4));

	//char file[] = "outputTest.txt";
	//char str[] = " I am writing!";
	//output_data(file, str);
	//shutdownBMC();
	//void set_speed(int speed);
	//cndevLibVersionInfo_t getLibVersion();
	//int boardNum = getBoardNum();
	//printf("There are %d boards\n",boardNum);
	//int boardUtilization = getBoardUtilization(0);
	//printf("The utilization is  %d %%\n",boardUtilization);
//	int corenum = getCoreNum(0);
//	int i;
//	int *a=getCoreUtilization(0);
//	printf("There are %d core in one board\n",corenum);
//	for(i=0;i<corenum;i++)
//		printf("utilization%d: %d%%\n",i,a[i]);
	//int* getCoreUtilization(unsigned boardId);
	//int tmp = getBoardTemperature(0);
	//printf("The tmp of board is %dC\n",tmp);
	//int clusernum = getClusterNum(0);
	//int *a=getClusterTemperature(0);
	//for(int i=0;i<clusernum;i++) printf(" cluster %d: %dC\n",i,a[i]);
	//cndevProcessInfo_t * procInfo = processInfo();
	//printf("pid:%d\n",procInfo->pid);	
	
	
	

	

	cndevRelease();
	return 0;
}

