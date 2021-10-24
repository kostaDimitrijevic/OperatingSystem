/*
 * PCB.cpp
 *
 *  Created on: Apr 19, 2020
 *      Author: OS1
 */
#include"PCB.h"
#include<iostream.h>
ID PCB::id=0;
volatile int PCB::ifidle=0;
ListOfThreads* PCB::head=0;
ListOfThreads* PCB::tail=0;
PCB* PCB::running= new PCB();
PCB::PCB(Time ti, StackSize s, ID pid, Status stat, unsigned sptr,unsigned sseg){
	sem=new Semaphore(0);
	unblocked=0;
	stack=0;
	t = ti;
	sp=sptr;
	ss=sseg;
	this->pid=pid;
	this->stat=stat;
	size=s;
	myThread=0;
};
void dispatch();
void PCB::wrapper(){
	running->myThread->run();
	//cout<<"kraj"<<endl;
	running->stat=finished;
	//cout<<running->sem->val()<<endl;
	running->sem->signal((-1)*running->sem->val());
	dispatch();
}
PCB::~PCB(){
	delete [] stack;
	delete sem;
}

