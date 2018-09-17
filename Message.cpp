/*
 * Message.cpp
 *
 *  Created on: Sep 16, 2018
 *      Author: kl
 */

#include "Message.h"

Message::Message() {

	this->iSender=-1;
	this->type=-1;
	this-> val1=this->val2=0;

}

void Message::SendMsg(int val1, int val2, int type, int iSender){
	this->val1=val1;
	this->val2=val2;
	this->type=type;
	this->iSender=iSender;
}

int Message::RecvMsg(int iSender){
	return -1;
}

void Message::ClearMsg() {
	this->iSender = -1;
	this->type = -1;
	this->val1 = this->val2 = 0;
}

bool Message::isEmpty(){
	return(iSender==-1);
}

Message::~Message() {
	// TODO Auto-generated destructor stub
}

