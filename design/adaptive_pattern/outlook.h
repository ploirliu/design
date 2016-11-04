//I perfer it in command_pattern , I find they are kind of similiar
#include <iostream>
using namespace std;
class light{
public:
	void on(){
		cout << "light on" << endl;
	}
	void off(){
		cout << "light off" << endl;
	}
};

class tv{
public:
	void on(){
		cout << "tv on" << endl;
	}
	void off(){
		cout << "tv off" << endl;
	}
};

class homeControl{
	light* l;
	tv* t;
public:
	homeControl(light* _l, tv* _t) :l(_l), t(_t){}
	void gohome(){
		cout << "going home" << endl;
		l->on();
		t->on();
	}
	void leavehome(){
		cout << "leaving home" << endl;
		l->off();
		t->off();
	}
};
/// well, now I found it's not so like command pattern

void test(){
	light* l = new light();
	tv *t = new tv();
	homeControl c(l, t);
	c.gohome();
	c.leavehome();
	delete l; delete t;
}