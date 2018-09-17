/*
 * Message.h
 *
 *  Created on: Sep 16, 2018
 *      Author: kl
 */

#ifndef MESSAGE_H_
#define MESSAGE_H_

#define RANGE 1
#define ALLDONE 2
#define EMPTY -1

class Message {
	int iSender;
	int type;
public:
	int val1, val2;
	Message();
	void SendMsg(int val1, int val2, int type, int iSender);
	int RecvMsg(int iSender);
	void ClearMsg();
	bool isEmpty();
	virtual ~Message();
};

#endif /* MESSAGE_H_ */
