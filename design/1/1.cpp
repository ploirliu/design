// 1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "duck.h"

int _tmain(int argc, _TCHAR* argv[])
{
	duck* miao = new m_duck();
	miao->display();
	miao->make_quark();
	miao->set_quark(new wang_quark());
	miao->make_quark();
	delete miao;
	return 0;
}

