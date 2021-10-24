/*
 * KernelSem.h
 *
 *  Created on: Sep 7, 2020
 *      Author: OS1
 */
#include<dos.h>
#include"Semaphor.h"
#ifndef KERNSEM_H_
#define KERNSEM_H_

class KernelSem{
public:
	static int semid;
	int id;
	KernelSem(int value);
	static SemaphoreList* semHead;
	static SemaphoreList* semTail;
	static int blockedByTime;
	Blocked* head;
	Blocked* tail;
	BlockedTime* headT;
	BlockedTime* tailT;
	int val;
	int wait(Time maxTimeToWait);
	int signal(int n=0);
	int value() const;
	Semaphore *mySemaphore;
	static void checkSemaphores();
	void doneTime(BlockedTime* done);
	void block(Blocked* bt=0);
	void blockTime(BlockedTime* bt=0);
	void unblock();
	~KernelSem();
};


#endif /* KERNSEM_H_ */
