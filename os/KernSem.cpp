/*
 * KernSem.cpp
 *
 *  Created on: Sep 7, 2020
 *      Author: OS1
 */
#include"PCB.h"
#include"KernSem.h"

SemaphoreList* KernelSem::semHead = 0;
SemaphoreList* KernelSem::semTail = 0;
int KernelSem::blockedByTime = 0;
int KernelSem::semid = 0;
KernelSem::KernelSem(int v) :
		val(v) {
	id = semid++;
	SemaphoreList* newSem = new SemaphoreList();
	newSem->sem = this;
	newSem->next = 0;
	if (!KernelSem::semHead) {
		KernelSem::semHead = KernelSem::semTail = newSem;
	} else {
		KernelSem::semTail->next = newSem;
		KernelSem::semTail = KernelSem::semTail->next;
	}

	head = tail = 0;
	headT = tailT = 0;
	mySemaphore = 0;
}
int KernelSem::value() const {
	return val;
}
int KernelSem::wait(Time maxTimeToWait) {
#ifndef BCC_BLOCK_IGNORE
	lock
	if(--val<0) {
		if(maxTimeToWait>0) {
			BlockedTime* newBlocked=new BlockedTime(PCB::running,maxTimeToWait,0,0);
			blockTime(newBlocked);
		}
		else {
			Blocked* newBlocked = new Blocked(PCB::running, 0);
			block(newBlocked);
		}
	}
	unlock
#endif
	if (PCB::running->unblocked) {
		PCB::running->unblocked = 0;
		return 0;
	} else
		return 1;
}
int KernelSem::signal(int n) {
#ifndef BCC_BLOCK_IGNORE
	lock
	if(n==0) {
		if(val++<0) {
			if(head) {
				KernelSem::blockedByTime=0;
				unblock();
			}
			else if(headT) {
				KernelSem::blockedByTime=1;
				unblock();
			}
		}
	}
	else if(n>0) {
		int i=n;
		while(head && i>0) {
			KernelSem::blockedByTime=0;
			unblock();
			i--;
		}
		while(headT && i>0) {
			KernelSem::blockedByTime=1;
			unblock();
			i--;
		}
		val=val+n;
		return n-i;
	}
	unlock
#endif
	return n;
}
void KernelSem::block(Blocked* bt) {
	if (!head)
		head = tail = bt;
	else {
		tail = tail->next = bt;
	}
	PCB::running->stat = blocked;
	dispatch();
}
void KernelSem::doneTime(BlockedTime* done) {
	++val;
	done->thread->stat = ready;
	done->thread->unblocked = 1;
	Scheduler::put(done->thread);
	if (done->prev)
		done->prev->next = done->next;
	else
		headT = done->next;
	if (done->next)
		done->next->prev = done->prev;
	else
		tailT = done->prev;
	delete done;
}
void KernelSem::unblock() {
	if (blockedByTime) {
		BlockedTime* temp = headT;
		temp->thread->stat = ready;
		temp->thread->unblocked = 0;
		Scheduler::put(temp->thread);
		headT = headT->next;
		if (headT)
			headT->prev = 0;
		else {
			tailT = 0;
		}
		delete temp;
	} else {
		Blocked* temp = head;
		temp->thread->stat = ready;
		temp->thread->unblocked = 0;
		Scheduler::put(temp->thread);
		head = head->next;
		if (!head)
			tail = 0;
		delete temp;
	}
}
void KernelSem::checkSemaphores() {
	SemaphoreList* semaphore = KernelSem::semHead;
	while (semaphore) {
		KernelSem* s;
		s = semaphore->sem;
		BlockedTime* thread = s->headT;
		while (thread) {
			if (thread->t > 0) {
				if (--thread->t == 0) {
					BlockedTime* temp = thread;
					thread = thread->next;
					s->doneTime(temp);
				} else
					thread = thread->next;
			} else
				thread = thread->next;
		}
		semaphore = semaphore->next;
	}
}
void KernelSem::blockTime(BlockedTime* bt) {
	if (!headT)
		headT = tailT = bt;
	else {
		bt->prev = tailT;
		tailT = tailT->next = bt;
	}
	PCB::running->stat = blocked;
	dispatch();
}
KernelSem::~KernelSem() {
#ifndef BCC_BLOCK_IGNORE
	lock;
	while(head) {
		Blocked* temp=head;
		head=head->next;
		temp->next=0;
		delete temp;
	}
	while(headT) {
		BlockedTime* temp=headT;
		headT=headT->next;
		if(headT) headT->prev=0;
		delete temp;
	}
	SemaphoreList* temp=KernelSem::semHead;
	SemaphoreList* prev=0;
	while(temp) {
		if(temp->sem->id==this->id) {
			SemaphoreList* todelete=temp;
			if(prev) prev->next=temp->next;
			else KernelSem::semHead=KernelSem::semHead->next;
			if(!temp->next) KernelSem::semTail=prev;
			delete todelete;
			break;
		}
		prev=temp;
		temp=temp->next;
	}
	unlock;
#endif
}
