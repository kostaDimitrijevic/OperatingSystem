/*
 * KernelEv.h
 *
 *  Created on: Sep 14, 2020
 *      Author: OS1
 */
#include"Event.h"
#include"PCB.h"
#ifndef KERNELEV_H_
#define KERNELEV_H_

class KernelEv{
public:
	KernelEv(IVTNo num);
	void wait();
	void signal();
	IVTNo entrynum;
	int issignal;
	~KernelEv();
private:
	PCB* owner;
	PCB* waiting;
};



#endif /* KERNELEV_H_ */
