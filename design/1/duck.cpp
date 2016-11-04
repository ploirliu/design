#include "stdafx.h"
#include "duck.h"


duck::duck() :q(new quark())
{
}

duck::duck(quark *_q) : q(_q){

}

duck::~duck()
{
	delete q;
}

void duck::set_quark(quark* _q){
	delete q;
	q = NULL;
	q = _q;
}

void duck::display(){
	cout << "i am a duck" << endl;
}

void duck::make_quark(){
	q->myquark();
}

w_duck::w_duck():duck(new wang_quark()){

}

m_duck::m_duck() : duck(new miao_quark()){

}