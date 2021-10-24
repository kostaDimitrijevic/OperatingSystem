/*
 * Producer.h
 *
 *  Created on: Apr 17, 2020
 *      Author: OS1
 */
#include"Thread.h"
#include<iostream.h>
#ifndef A_H_
#define A_H_
class A: public Thread{
private:
	int i;
public:
	A(): i(0){};
	~A();
protected:
	virtual void run();
};

#endif
