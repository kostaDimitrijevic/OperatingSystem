/*
 * main.cpp
 *
 *  Created on: Apr 17, 2020
 *      Author: OS1
 */

#include "A.h"
#include "B.h"
#include"PCB.h"
#include<SCHEDULE.H>
#include"Semaphor.h"
#include"KernSem.h"
#include"Idle.h"
#include"Event.h"
#include"IVTEntry.h"
#include"Thread.h"
int ifIdle;
typedef void interrupt (*pInterrupt)(...);
pInterrupt oldISR;
volatile int counter = defaultTimeSlice;
volatile int dispatchcalled = 0;
unsigned tsp, tss;
IdleThread* idle = new IdleThread();
void interrupt timer(...) {
	if (!dispatchcalled) {
		counter--;
		if(KernelSem::semHead)
			KernelSem::checkSemaphores();
	}
	if (counter <= 0 || dispatchcalled) {
#ifndef BCC_BLOCK_IGNORE
		asm {
			mov tsp, sp
			mov tss, ss
		}
#endif
		PCB::running->sp = tsp;
		PCB::running->ss = tss;
		if (PCB::running->stat != blocked && PCB::running->stat != finished) {
			PCB::running->stat = ready;
			Scheduler::put(PCB::running);
			PCB::ifidle = 0;
		}
		PCB::running = Scheduler::get();
		if (PCB::running == 0 ) {
			PCB::running = idle->getmyPCB();
			PCB::ifidle = 1;
		}
		counter = PCB::running->t;
		tsp = PCB::running->sp;
		tss = PCB::running->ss;
#ifndef BCC_BLOCK_IGNORE
		asm {
			mov sp, tsp
			mov ss, tss
		}
#endif
	}
#ifndef BCC_BLOCK_IGNORE
	if(!dispatchcalled) oldISR();
#endif
	dispatchcalled = 0;
}
;

void inic() {
#ifndef BCC_BLOCK_IGNORE
	lock
	idle->start();
	oldISR = getvect(0x8);
	setvect(0x8, timer);
	unlock
#endif
}

void restore() {
#ifndef BCC_BLOCK_IGNORE
	lock
	setvect(0x8, oldISR);
	delete idle;
	unlock
#endif
}
void dispatch() {
#ifndef BCC_BLOCK_IGNORE
	lock
	dispatchcalled=1;
	timer();
	unlock
#endif
}
int userMain(int argc, char* argv[]);

int main(int argc, char* argv[]) {
	inic();
	userMain(argc, argv);
	restore();
	return 0;
}

