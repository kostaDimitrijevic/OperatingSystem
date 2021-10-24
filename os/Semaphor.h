/*
 * Semaphore.h
 *
 *  Created on: Sep 7, 2020
 *      Author: OS1
 */
#include"Thread.h"
#ifndef SEMAPHOR_H_
#define SEMAPHOR_H_
class KernelSem;
struct SemaphoreList{
	KernelSem* sem;
	SemaphoreList* next;
};
struct Blocked{
	PCB* thread;
	Blocked* next;
	Blocked(PCB* t, Blocked* n):thread(t),next(n){};
};
struct BlockedTime{
	PCB* thread;
	Time t;
	BlockedTime* next;
	BlockedTime* prev;
	BlockedTime(PCB* t, Time time, BlockedTime* p, BlockedTime* n):thread(t),t(time),prev(p),next(n){};
};

class Semaphore {
public:
 Semaphore (int init=1);
 virtual ~Semaphore ();
 virtual int wait (Time maxTimeToWait);
 virtual int signal(int n=0);
 int val () const; // Returns the current value of the semaphore
 KernelSem* getmyImpl();
private:
 KernelSem* myImpl;
};


#endif /* SEMAPHOR_H_ */
