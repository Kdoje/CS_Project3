/*
 * main.cpp
 *
 *  Created on: Sep 16, 2018
 *      Author: kl
 */

#include<stdlib.h>
#include<stdio.h>
#include <pthread.h>
#include <semaphore.h>

#include "Mailbox.h"


Mailbox mailbox[10];
sem_t sumSem;

//this writes the sum of the 2 numbers in the val1 spot
void *FindSum(void *threadid) {

	//get the thread id to an int
	long tidInit;
	tidInit = (long) threadid;
	int tid=(int)tidInit;
	//printf("Hello from thread %d\n", tid);

	//wait to make sure only one thing adds at once
	sem_wait(&sumSem);
	//add the nums
	mailbox[0].SendMsg(mailbox[tid].val1+mailbox[tid].val2, 0, ALLDONE, tid);


	pthread_exit(NULL);
}
//TODO implement this the right way lol
int main(int argc, char* argv[]) {
	//first time setup
	const int THREAD_NUM=5;
	int messagesNeeded=THREAD_NUM;
	pthread_t threads[THREAD_NUM];
	//set this to be one so one adder can run at first
	sem_init(&sumSem, 0, 1);
	int sum=0;

	//initializes the threads
	int threadError;
	int i;
	mailbox[0].ClearMsg();
	//create the threads
	for (i = 0; i < THREAD_NUM; i++) {
		printf("main() creating thread %d\n", i);
		threadError = pthread_create(&threads[i], NULL, FindSum, (void *) i+1); //this sets the thread id's to be 1-> range
		if (threadError) {
			printf("couldn't make thread ayy lmao\n");
			exit(-1);
		}
		//give them the values to add
		else{
			mailbox[i+1].SendMsg(0,5,RANGE, 0);
		}
	}

	//check for messages
	while(messagesNeeded>0){
		//check for a good message
		if(!mailbox[0].isEmpty()){
			sum+=mailbox[0].val1;
			mailbox[0].ClearMsg();
			messagesNeeded-=1;
			//then say the message was recieved so the next producer can run
			sem_post(&sumSem);
		}
	}
	printf("sum is %d\n", sum);
	pthread_exit(NULL);
	return 0;
}


