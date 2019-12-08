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
#define TARGET 30
#define KP 2.0
#define KI 3.5
#define KD 5
#define INTERVAL 10
#define INITSPEED 20
#define LOWSPEED 10
typedef struct tmpQ{
	int len;
	int tail;
	float target;
	float a[100];	
	float sum;
	float diff;
	float err;
	float integral;
}tmpQ;

void initTmp(tmpQ* q,int interval){
	q->len = interval;
	q->tail = 0;
	q->target = TARGET;
	q->sum = TARGET;	
	q->diff = 0;
	q->err = 0;
	q->integral = 0;
	for(int i=0;i<INTERVAL;i++) q->a[i] = TARGET;
}

float getHead(tmpQ* q){
	return q->a[(q->tail+1)%(q->len)];
}
void pushq(tmpQ* q,float t){
	float oldt = getHead(q);
	q->diff = (t-oldt)/q->len;
	q->sum = q->sum+(t-oldt)/q->len;
	q->tail = (q->tail+1)%q->len;
	q->a[q->tail] = t;
	q->err = t - q->target;
	q->integral = q->sum - TARGET;
	printf("err = %f,sum = %f, diff = %f, integral = %f\n",q->err,q->sum,q->diff,q->integral);
}

int getSpeed(tmpQ* q){
	if(q->err<0) return LOWSPEED;
	float target = TARGET;
//	if((q->err)<0) return 10;
	int outSpeed =  KP*q->err+KI*q->integral+KD*q->diff + INITSPEED;
	return outSpeed>100?100:outSpeed;
}
int main(){
	cndevCheckErrors(cndevInit(CNDEV_VERSION_4));
	int b[100];	
	int boardNum = getBoardNum();
	int clusernum = getClusterNum(0);
	//shutdownBMC();
	tmpQ q;
	initTmp(&q,INTERVAL);
	while(1){
		int t = getBoardTemperature(0);
		getClusterTemperature(0,b);
		printf("The tmp of board is %dC,core tmp = %dC\n",t,b[1]);
//		getClusterTemperature(0,b);
		pushq(&q,t);
		int speed = getSpeed(&q);
		printf("speed is %d\n",speed);
		set_speed(speed);
		sleep(1);
	}
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





