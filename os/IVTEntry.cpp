/*
 * IVTEntry.cpp
 *
 *  Created on: Sep 14, 2020
 *      Author: OS1
 */
#include"IVTEntry.h"
IVTEntry** IVTEntry::arrOfEntries= new IVTEntry* [256];
IVTEntry::IVTEntry(IVTNo no, pInterrupt newIntr){
	oldIntr=0;
#ifndef BCC_BLOCK_IGNORE
	oldIntr=getvect(no);
	setvect(no, newIntr);
#endif
	entry=no;
	event=0;
	IVTEntry::arrOfEntries[entry]=this;
}


void IVTEntry::signal(){
	event->signal();
	dispatch();
}
IVTEntry::~IVTEntry(){
	//cout<<"IVTEntry"<<endl;
#ifndef BCC_BLOCK_IGNORE
	setvect(entry, oldIntr);
#endif
	//cout<<"prosao"<<endl;
	//IVTEntry::arrOfEntries[entry]=0;
	//delete IVTEntry::arrOfEntries[entry];
}
