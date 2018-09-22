/*
 * Message.h
 *
 *  Created on: Sep 16, 2018
 *      Author: kl
 */

#ifndef MAILBOX_H_
#define MAILBOX_H_

#define RANGE 1
#define ALLDONE 2
#define EMPTY -1
#include<semaphore.h>

class Mailbox {
	int iSender;
	int type;
	sem_t boxSem;
public:
	int val1, val2;
	Mailbox();
	void SendMsg(int val1, int val2, int type, int iSender);
	int RecvMsg(int iSender);
	void ClearMsg();
	bool isEmpty();
	virtual ~Mailbox();
};

#endif /* MAILBOX_H_ */
