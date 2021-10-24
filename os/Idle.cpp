/*
 * Idle.cpp
 *
 *  Created on: Sep 9, 2020
 *      Author: OS1
 */


#include"Idle.h"
#include"PCB.h"
IdleThread::IdleThread(StackSize s, Time t): Thread(s,t){
	PCB::ifidle=1;
}
void IdleThread::run(){
	while(1);
}
IdleThread::~IdleThread(){
};
