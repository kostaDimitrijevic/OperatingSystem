/*
 * Producer.cpp
 *
 *  Created on: Sep 3, 2020
 *      Author: OS1
 */
#include "A.h"
#include"Semaphor.h"
//extern Semaphore* test;
void A::run(){
	//cout<<"nit id:"<<this->getId()<<" se blokirala"<<endl;
	//cout<<"wait"<<test->wait(15);
	//cout<<"nit id:"<<this->getId()<<" se odblokirala"<<endl;
	for(int i=0;i<30;++i){
		#ifndef BCC_BLOCK_IGNORE
		lock
		cout<<"u a() i = "<< i <<endl;
		unlock
		#endif
		for(int k=0; k<10000;k++)
			for(int j=0; j<30000;j++);
	}
	//sem.signal(1);
}
A::~A(){
	this->waitToComplete();
}

