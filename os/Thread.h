/*
 * Thread
 *
 *  Created on: Apr 10, 2020
 *      Author: OS1
 */

#ifndef THREAD_H_
#define THREAD_H_
#include<stdio.h>
#include<iostream.h>
#include<dos.h>
#include<SCHEDULE.h>
typedef unsigned long StackSize;
const StackSize defaultStackSize = 4096;
typedef unsigned int Time; // time, x 55ms
const Time defaultTimeSlice = 2; // default = 2*55ms;
typedef int ID; // Kernel's implementation of a user's thread
enum Status{ready, blocked, running, finished, notready};
struct ListOfThreads{
	ID tid;
	PCB* t;
	ListOfThreads* next;
};
#define lock asm cli
#define unlock asm sti

class Thread {
public:
	void start();
	void waitToComplete();
	virtual ~Thread();
	ID getId();
	static ID getRunningId();
	static Thread * getThreadById(ID id);
	PCB* getmyPCB();
protected:
	friend class PCB;
	Thread ( StackSize stackSize = defaultStackSize, Time timeSlice = defaultTimeSlice);
	virtual void run() {};
private:
	PCB* myPCB;
};
void dispatch();
//void dispatch();
#endif /* THREAD_H_ */
