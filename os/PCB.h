/*
 * PCB.h
 *
 *  Created on: Apr 19, 2020
 *      Author: OS1
 */

#ifndef PCB_H_
#define PCB_H_
#include<iostream.h>
#include"Thread.h"
#include"Semaphor.h"
class PCB{
public:
	Semaphore* sem;
	static volatile int ifidle;
	friend class Thread;
	int unblocked;//1-time,0-signal
	Status stat;
	static ID id;
	static ListOfThreads *head;
	static ListOfThreads *tail;
	static PCB* running;
	StackSize size;
	unsigned sp;
	unsigned ss;
	unsigned *stack;
	Thread* myThread;
	ID pid;
	Time t;
	PCB(Time ti=defaultTimeSlice, StackSize s=defaultStackSize, ID pid = 0, Status stat=notready, unsigned sp=0,unsigned ss=0);
	static void wrapper();
	~PCB();
};

#endif /* PCB_H_ */
