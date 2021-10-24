/*
 * B.h
 *
 *  Created on: Sep 3, 2020
 *      Author: OS1
 */

#ifndef B_H_
#define B_H_
#include "Thread.h"
class B: public Thread{
private:
	int i;
public:
	B(): i(1){};
	~B();
protected:
	virtual void run();
};


#endif /* B_H_ */
