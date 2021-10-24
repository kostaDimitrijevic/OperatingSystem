/*
 * KernelEv.cpp
 *
 *  Created on: Sep 14, 2020
 *      Author: OS1
 */
#include"KernelEv.h"
#include"SCHEDULE.h"
#include"IVTEntry.h"
#include"Thread.h"
KernelEv::KernelEv(IVTNo num){
	waiting=0;
	owner=PCB::running;
	IVTEntry::arrOfEntries[num]->event=this;
	entrynum=num;
	issignal=0;
}

void KernelEv::wait(){
	lock;
	if(issignal) {
		issignal=0;
		return;
	}
	if(PCB::running==owner){
		waiting=owner;
		PCB::running->stat=blocked;
		dispatch();
	}
	unlock;
}

void KernelEv::signal(){
	lock;
	if(waiting){
		//cout<<"signal"<<endl;
		waiting=0;
		issignal=0;
		owner->stat=ready;
		Scheduler::put(owner);
	}
	else{
		issignal=1;
	}
	unlock;
}

KernelEv::~KernelEv(){
	IVTEntry::arrOfEntries[entrynum]=0;
};
