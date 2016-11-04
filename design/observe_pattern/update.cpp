#include "stdafx.h"
#include "update.h"


update::update()
{
}


update::~update()
{
}

void update::com(int _v){
	cout << _v << " " << _v << endl;
}

void double_update::com(int _v){
	cout << _v << " " << _v * 2 << endl;
}

void square_update::com(int _v){
	cout << _v << " " << _v *_v << endl;
}