/*
 * B.cpp

 *
 *  Created on: Sep 3, 2020
 *      Author: OS1
 */
//#include "Thread.h"
#include"B.h"
void B::run(){
	//sem.wait(0);
	for(int i=0;i<30;++i){
		#ifndef BCC_BLOCK_IGNORE
		lock
		cout<<"u b() i = "<< i <<endl;
		unlock
		#endif
		for(int k=0; k<10000;k++)
			for(int j=0; j<30000;j++);
	}
	//sem.signal(1);
}
B::~B(){
	this->waitToComplete();
}

