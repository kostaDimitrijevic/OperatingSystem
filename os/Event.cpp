/*
 * Event.cpp
 *
 *  Created on: Sep 14, 2020
 *      Author: OS1
 */
#include"Event.h"
#include"KernelEv.h"
Event::Event(IVTNo ivtNo){
	myImpl=new KernelEv(ivtNo);
}
void Event::wait(){
	myImpl->wait();
}
void Event::signal(){
	myImpl->signal();
};
Event::~Event(){
	delete myImpl;
}
