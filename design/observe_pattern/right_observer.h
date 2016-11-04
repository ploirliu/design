#pragma once
#include "subject.h"

#ifndef OBSERVER
#define OBSERVER
#include <iostream>
using namespace std;
class observer{
protected:
	subject* s;
public:
	observer() :s(NULL){};
	void setSubject(subject* _s){
		s = _s;
		s->addObserver(this);
	}
	void removeSubject(){
		if (s){
			s->removeObserver(this);
			s = NULL;
		}
	}
	virtual void update(int _i,double _d)=0;
	virtual void update(subject *)=0;
};


class show_observer :public observer{
	
public:
	void update(int _i, double _d){
		cout << "push" << endl;
		cout << _i << ' ' << _d << endl;
	}
	void update(subject *_n){
		cout << "pull" << endl;
		int_subject *now = dynamic_cast<int_subject *>(_n);
		cout << now->get_ival() << ' ' << now->get_dval() << endl;
	}
};

class square_observer :public observer{
public:
	void update(int _i, double _d){
		cout << "push" << endl;
		cout << _i*_i << ' ' << _d*_d << endl;
	}
	void update(subject *_n){
		cout << "pull" << endl;
		int_subject *now = dynamic_cast<int_subject *>(_n);
		cout << now->get_ival()*now->get_ival() << ' ' << now->get_dval()*now->get_dval() << endl;
	}
};
#endif