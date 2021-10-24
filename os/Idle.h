/*
 * Idle.h
 *
 *  Created on: Sep 8, 2020
 *      Author: OS1
 */

#ifndef IDLE_H_
#define IDLE_H_
#include"Thread.h"
class IdleThread: public Thread{
public:
	IdleThread(StackSize s=defaultStackSize ,Time t=1);
	virtual void run();
	~IdleThread();
};



#endif /* IDLE_H_ */
