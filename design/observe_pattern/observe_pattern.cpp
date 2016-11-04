// observe_pattern.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "right_observer.h"

int _tmain(int argc, _TCHAR* argv[])
{
	//weather w;
	//observer *_w = new wang();
	//observer *_m = new miao();
	//_w->set_update(new double_update());
	//w.addClient(_w);
	//w.addClient(_m);
	//w.update(5);
	//w.notify();
	//w.update(6);
	//w.removeClient(_w);
	//w.notify();
	//_m->set_update(new square_update());
	//w.notify();
	//delete _w;
	//delete _m;
	int_subject _s;
	show_observer _show;
	//_s.setFunction(3);
	_show.setSubject(&_s);
	square_observer _square;
	_square.setSubject(&_s);
	_s.setData(5, 10);
	_show.removeSubject();
	_s.setData(6, 8.8);

	return 0;
}

