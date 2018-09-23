/*
 * main.cpp
 *
 *  Created on: Sep 16, 2018
 *      Author: kl
 */

#include<stdlib.h>
#include<stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#include "Mailbox.h"

Mailbox mailbox[11];
sem_t sumSem;

//this writes the sum of the 2 numbers in the val1 spot
void *FindSum(void *threadid) {

	//get the thread id to an int
	long tidInit;
	tidInit = (long) threadid;
	int tid = (int) tidInit;

	//read then send the message
	contents recieved;
	recieved = mailbox[tid].RecvMsg(0);
	contents toSend;
	for (int i = recieved.val1; i <= recieved.val2; i++) {
		toSend.val1 += i;
	}
//	printf("sending from %d\n", tid);
	mailbox[0].SendMsg(toSend, ALLDONE, tid);
//	printf("message sent\n");
	pthread_exit(NULL);
}

int main(int argc, char* argv[]) {
	//first time setup
	if (argc == 3) {
		const int THREAD_NUM = atoi(argv[1]);
		const int final = atoi(argv[2]);

		if(THREAD_NUM<1 || THREAD_NUM>10){
			printf("please enter thread no. between 1 and 10\n");
			return -1;
		}
		if(final%THREAD_NUM!=0){
			printf("WARNING the final value is not divisible by "
					"thread count and may lead to incorrect output!\n");
		}
		int messagesNeeded = THREAD_NUM;
		pthread_t threads[THREAD_NUM];
		//set this to be one so one adder can run at first
		sem_init(&sumSem, 0, 1);

		//initializes the threads
		int threadError;
		//create the threads
		for (int i = 0; i < THREAD_NUM; i++) {
			//printf("main() creating thread %d\n", i + 1);
			threadError = pthread_create(&threads[i], NULL, FindSum,
					(void *) i + 1); //this sets the thread id's to be 1-> range
			if (threadError) {
				printf("couldn't make thread ayy lmao\n");
				exit(-1);
			}
		}

		//sends the values to add to the threads
		printf("thread num %d, final val %d\n", THREAD_NUM, final);
		int prevVal = 0;
		int step = final / THREAD_NUM;
		for (int i = 1; i <= THREAD_NUM; i++) {
			contents toSend;
			toSend.val1 = prevVal + 1;
			toSend.val2 = prevVal += step;
			//printf("val1: %d, val2: %d\n", toSend.val1, toSend.val2);
			mailbox[i].SendMsg(toSend, RANGE, 0);
		}

		//set up sum
		int sum = 0;
		//check for messages
		while (messagesNeeded > 0) {
			contents msgContents;
			msgContents = mailbox[0].RecvMsg(1);
			//printf("read message\n");
			sum += msgContents.val1;
			messagesNeeded--;
		}

		//print sum
		printf("sum is %d\n", sum);
		pthread_exit(NULL);
		return 0;

	} else {
		printf("error: requires 3 args\n");
		return -1;
	}
}

