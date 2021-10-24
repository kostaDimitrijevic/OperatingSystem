/*
 * IVTEntry.h
 *
 *  Created on: Sep 14, 2020
 *      Author: OS1
 */
#include"KernelEv.h"
#ifndef IVTENTRY_H_
#define IVTENTRY_H_

class IVTEntry;
typedef unsigned char IVTNo;
typedef void interrupt (*pInterrupt)(...);
#define PREPAREENTRY(no,flag) 						\
		void interrupt intr##no(...); 				\
		IVTEntry ivte##no(no, intr##no); 			\
		void interrupt intr##no(...) 				\
		{											\
			ivte##no.signal();						\
			if(flag==1)								\
				ivte##no.oldIntr();					\
		}

class IVTEntry{
public:
	IVTEntry(IVTNo no, pInterrupt newIntr);
	void signal();
	KernelEv* event;
	pInterrupt oldIntr;
	static IVTEntry** arrOfEntries;
	IVTNo entry;
	~IVTEntry();
};



#endif /* IVTENTRY_H_ */
