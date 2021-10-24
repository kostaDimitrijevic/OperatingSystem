/*
 * Thread.cpp
 *
 *  Created on: Apr 11, 2020
 *      Author: OS1
 */
#include"PCB.h"
#include<iostream.h>

Thread::Thread(StackSize stackSize, Time timeSlice){
	unsigned* st= new unsigned[stackSize/sizeof(unsigned)];
	PCB *newPCB = new PCB(timeSlice, stackSize);
	this->myPCB = newPCB;
	this->myPCB->myThread=this;
#ifndef BCC_BLOCK_IGNORE
		st[stackSize - 1] = 0x200;
		st[stackSize - 2] = FP_SEG(PCB::wrapper);
		st[stackSize - 3] = FP_OFF(PCB::wrapper);
		this->myPCB->sp = FP_OFF(st + stackSize - 12);
		this->myPCB->ss = FP_SEG(st + stackSize - 12);
#endif
	this->myPCB->stack=st;
}
void Thread::start(){
	if(PCB::ifidle){
		myPCB->stat=finished;
		myPCB->pid = ++PCB::id;
		PCB::ifidle=0;
		return;
	}
	if(this->myPCB->pid == 0){
		this->myPCB->pid = ++PCB::id;
		this->myPCB->stat = ready;
		ListOfThreads* newThread=new ListOfThreads;
		newThread->tid=this->myPCB->pid;
		newThread->t=this->myPCB;
		newThread->next=NULL;
		if(!PCB::head){
			PCB::head=PCB::tail=newThread;
		}
		else{
			PCB::tail=PCB::tail->next=newThread;
		}
		Scheduler::put(this->myPCB);
	}
}
ID Thread::getId(){ return this->myPCB->pid; }
ID Thread::getRunningId(){ return PCB::running->pid; }
Thread* Thread::getThreadById(ID id){
	ListOfThreads* temp=PCB::head;
	if(PCB::id>=id){
		while(temp){
			if(temp->tid==id) return temp->t->myThread;
			temp=temp->next;
		}
	}
	return 0;
}
void Thread::waitToComplete(){
	if(myPCB->pid!=1 && myPCB->stat!=finished){
		myPCB->sem->wait(0);
	}

}
PCB* Thread::getmyPCB(){
	return myPCB;
}
Thread::~Thread(){
	#ifndef BCC_BLOCK_IGNORE
		lock
		delete myPCB;
		unlock
	#endif;
}
