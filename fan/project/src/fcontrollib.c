#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include "../include/fanOp.h"
typedef struct temperatureQueue{
	int len;
	int tail; //the tail of the queue
	float target; // the target temperature
	float a[100]; // the array of temperatures	
	float average; // the average of temperatures
	float diff; 
	float err;
	float integral;
}temperatureQueue;

void initTmp(temperatureQueue* q,int interval,int target){
	q->len = interval;
	q->tail = 0;
	q->target = target;
	q->average = target;	
	q->diff = 0;
	q->err = 0;
	q->integral = 0;
	for(int i=0;i<interval;i++) q->a[i] = target;
}

//get the front element of the tempetature array
float getHead(temperatureQueue* q){
	return q->a[(q->tail+1)%(q->len)];
}

//push the new temperature into the rear of the array and upadate the variables
void pushq(temperatureQueue* q,float t){
	float oldt = getHead(q);
	q->diff = (t-oldt)/q->len;
	q->average = q->average+(t-oldt)/q->len;
	q->tail = (q->tail+1)%q->len;
	q->a[q->tail] = t;
	q->err = t - q->target;
	q->integral = q->average - TARGET;
	printf("err = %f,average = %f, diff = %f, integral = %f\n",q->err,q->average,q->diff,q->integral);
}



//calculate the speed according to the temperature queue
int getSpeed(temperatureQueue* q,int kp,int ki,int kd){
	if(q->err<0) return LOWSPEED;
	float target = TARGET;
	int outSpeed =  kp*q->err+ki*q->integral+kd*q->diff + INITSPEED;
	return outSpeed>100?100:outSpeed;
}

// record the infomation of temperature  
void record(int boardid,int boardtemperature,int clusternum,int *clustertemperature,int speed,int freq,int powerutility){

    time_t timep;
    time(&timep);
    char filename[32];
    char rec[256] = {0};
    struct tm *local = localtime(&timep);
    int MaxTemperature = 0;
    for (int i = 0; i < clusternum; i++){
        if(clustertemperature[i]>MaxTemperature) MaxTemperature = clustertemperature;
    }
    sprintf(filename, "../data/%d-%d-%d.csv", (local->tm_year + 1900), (local->tm_mon + 1), local->tm_mday);
	sprintf(rec, "%02d:%02d:%02d %d %d %d %d %d %d %d %d %d %d %d %d %d %d",
			local->tm_hour + 8, local->tm_min, local->tm_sec, boardid, boardtemperature, clustertemperature[0],
			clustertemperature[1], clustertemperature[2], clustertemperature[3], clustertemperature[4],
			clustertemperature[5], clustertemperature[6], clustertemperature[7],  MaxTemperature,
			speed, freq, powerutility);
    write_data(filename, rec);
}

// the control functoin
void startControl(int sleeptime,int kp,int ki,int kd,int target,int interval){
    initialize();
	int clustertemperature[100];	
	int boardNum = getBoardNum();
	int clusernum = getClusterNum(0);
	//shutdownBMC();
	temperatureQueue q;
	initTmp(&q,interval,target);
	while(1){
		int boardtemperature = getBoardTemperature(0);
		getClusterTemperature(0,clustertemperature);
        int boardfreq = getBoardFreq(0);
        int boardpowerusage = getBoardPowerUsage(0);
		printf("The tmp of board is %dC,core tmp = %dC\n",boardtemperature,clustertemperature[0]);
		pushq(&q,boardtemperature);
		int speed = getSpeed(&q,kp,ki,kd);
		printf("speed is %d\n",speed);
        record(0,boardtemperature,clusernum,clustertemperature,speed,boardfreq,boardpowerusage);
		set_speed(speed);
		sleep(sleeptime);
	}
    release();
}





