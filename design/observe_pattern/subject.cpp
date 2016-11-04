#include "stdafx.h"
#include "subject.h"
#include "right_observer.h"
subject::subject()
{
}

subject::~subject()
{
}

void subject::addObserver(observer *o){
	all.insert(o);
}

void subject::removeObserver(observer *o){
	all.erase(o);
}

void subject::notify(){}


void subject::notify(subject *_s){
	if (_s){
		for (auto i : all){
			i->update(this);
		}
	}
	else{
		notify();
	}
}

void int_subject::notify(){
	for (auto i : all){
		i->update(ival, dval);
	}
}



