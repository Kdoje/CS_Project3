/*
 * Message.cpp
 *
 *  Created on: Sep 16, 2018
 *      Author: kl
 */

#include "Mailbox.h"

Mailbox::Mailbox() {
	sem_init(&boxSem);
	this->iSender=-1;
	this->type=-1;
	this-> val1=this->val2=0;

}

void Mailbox::SendMsg(int val1, int val2, int type, int iSender){
	this->val1=val1;
	this->val2=val2;
	this->type=type;
	this->iSender=iSender;
}

int Mailbox::RecvMsg(int iSender){
	return -1;
}

void Mailbox::ClearMsg() {
	this->iSender = -1;
	this->type = -1;
	this->val1 = this->val2 = 0;
}

bool Mailbox::isEmpty(){
	return(iSender==-1);
}

Mailbox::~Mailbox() {
	// TODO Auto-generated destructor stub
}

