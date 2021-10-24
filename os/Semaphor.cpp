/*
 * Semaphor.cpp
 *
 *  Created on: Sep 7, 2020
 *      Author: OS1
 */

#include"Semaphor.h"
#include"KernSem.h"
int Semaphore::wait(Time maxTimeToWait){
	return myImpl->wait(maxTimeToWait);
};

int Semaphore::signal(int n){
	return myImpl->signal(n);
};

Semaphore::Semaphore(int init){
	KernelSem* sem=new KernelSem(init);
	myImpl=sem;
}
KernelSem* Semaphore::getmyImpl(){
	return myImpl;
}
int Semaphore::val() const{
	return myImpl->value();
}
Semaphore::~Semaphore(){
	delete myImpl;
}
