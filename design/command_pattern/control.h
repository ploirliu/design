#include <iostream>
#include <stack>
#include <vector>
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

class fan{
	int speed;
	//	stack<int> last;

	//	void pushlast(){
	//		last.push(speed);
	//	}
public:
	enum{ OFF = 0, LOW, MEDIUM, HIGH };
	fan() :speed(OFF){
	}
	void high(){
		//		pushlast();
		speed = HIGH;
	}
	void mid(){
		//		pushlast();
		speed = MEDIUM;
	}
	void low(){
		//		pushlast();
		speed = LOW;
	}
	int getspeed(){
		return speed;
	}
	void off(){
		speed = OFF;
	}
	//void undo(){
	//	if (last.size() > 0){
	//		int out = last.top();
	//		last.pop();
	//		return out;
	//	}
	//	return 0;
	//}
	void show(){
		cout << "now fan's speed is " << speed << endl;
	}
};

class commad{
public:
	virtual ~commad(){
		cout << "base destroy" << endl;
	}
	virtual void execute() = 0;
	virtual void undo() = 0;
};

class nullcommnd :public commad{
public:
	virtual ~nullcommnd(){
		cout << "null command destory" << endl;
	}
	void execute(){
		cout << "no commad" << endl;
	}
	void undo(){
		cout << "no commad" << endl;
	}
};

class light_on_commnd :public commad{
	light* l;
public:
	light_on_commnd(light* _l) :l(_l){}
	void execute(){
		l->on();
	}
	void undo(){
		l->off();
	}
	~light_on_commnd(){
		cout << "light_on_commad_destory" << endl;
	};
};

class light_off_commnd :public commad{
	light* l;
public:
	light_off_commnd(light* _l) :l(_l){}
	void execute(){
		l->off();
	}
	void undo(){
		l->on();
	}
	~light_off_commnd(){
		cout << "light_off_commad_destory" << endl;
	};
};

class tv_on_commnd :public commad{
	tv* l;
public:
	tv_on_commnd(tv* _l) :l(_l){}
	void execute(){
		l->on();
	}
	void undo(){
		l->off();
	}
	~tv_on_commnd(){
		cout << "tv_on_commad_destory" << endl;
	};
};

class tv_off_commnd :public commad{
	tv* l;
public:
	tv_off_commnd(tv* _l) :l(_l){}
	void execute(){
		l->off();
	}
	void undo(){
		l->on();
	}
	~tv_off_commnd(){
		cout << "tv_off_commad_destory" << endl;
	};
};

class fan_commad :public commad{
protected:
	fan* f;
	stack<int> pre_speed;
public:
	fan_commad(fan* _f) :f(_f){}
	//virtual void now_commad(){
	//	cout << "no commad" << endl;
	//}
	//virtual void execute(){
	//	pre_speed = f->getspeed();
	//	now_commad();
	//	f->show();
	//}
	virtual void execute(){
		cout << "no commad" << endl;
	}
	~fan_commad(){
		cout << "fan_commad_destory" << endl;
	};
	void undo(){
		if (pre_speed.size()>=0){
			int pre = pre_speed.top();
			pre_speed.pop();
			switch (pre){
			case fan::OFF:{
				f->off();
				break;
			}
			case fan::LOW:{
				f->low();
				break;
			}
			case fan::MEDIUM:{
				f->mid();
				break;
			}
			case fan::HIGH:{
				f->high();
				break;
			}
			default:{
				f->off();
			}
			}
		}
		f->show();
	}
};

class fan_low_commad :public fan_commad{
public:
	fan_low_commad(fan* _f) :fan_commad(_f){}
	~fan_low_commad(){
		cout << "fan low commmand destory" << endl;
	}
	void execute(){
		pre_speed.push( f->getspeed());
		f->low();
		f->show();
	}
};

class fan_high_commad :public fan_commad{
public:
	fan_high_commad(fan* _f) :fan_commad(_f){}
	~fan_high_commad(){
		cout << "fan high command destory" << endl;
	}
	void execute(){
		pre_speed.push(f->getspeed());
		f->high();
		f->show();
	}
};

class fan_mid_commad :public fan_commad{
public:
	fan_mid_commad(fan* _f) :fan_commad(_f){}
	~fan_mid_commad(){
		cout << "fan_mid_commad destroy" << endl;
	}
	void execute(){
		pre_speed.push(f->getspeed());
		f->mid();
		f->show();
	}
};

class fan_off_commad :public fan_commad{
public:
	fan_off_commad(fan* _f) :fan_commad(_f){}
	~fan_off_commad(){
		cout << "fan off command destory" << endl;
	}
	void execute(){
		pre_speed.push(f->getspeed());
		f->off();
		f->show();
	}
};

class controlWithUndo{
	commad* all[7];
	stack<commad*> s;
	commad* null_c;
public:
	controlWithUndo() :null_c(new nullcommnd()){
		for (int i = 0; i < 7; ++i){
			all[i] = null_c;
		}
	}
	~controlWithUndo(){
		delete null_c;
	}
	void setButton(int id, commad* _c){
		all[id] = _c;
	}
	void pushButton(int id){
		all[id]->execute();
		s.push(all[id]);
	}
	void pushUndo(){
		commad* now = NULL;
		if (s.size() > 0){
			now = s.top();
			s.pop();
		}
		else
			now = null_c;
		now->undo();
	}
};

void test_control(){
	controlWithUndo myc;
	light* l = new light();
	tv* t = new tv();
	fan* f = new fan();
	commad* c[6];
	c[0] = new light_on_commnd(l);
	c[1] = new light_off_commnd(l);
	c[2] = new fan_low_commad(f);
	c[3] = new fan_mid_commad(f);
	c[4] = new fan_high_commad(f);
	c[5] = new fan_off_commad(f);
	for (int i = 0; i < 6; ++i)
		myc.setButton(i, c[i]);
	for (int i = 0; i < 10; ++i){
		int tmp = rand() % 6;
		cout << "press " << tmp << endl;
		myc.pushButton(tmp);
	}
	cout << endl << endl;
	for (int i = 0; i < 10; ++i){
		myc.pushUndo();
	}
	for (int i = 0; i < 6; ++i){
		cout << "delete " << i << endl;
		delete c[i];
	}
	delete f; delete t; delete l;
}

class macro_commad :public commad{
	vector<commad*> all;
public:
	macro_commad(vector<commad*> _all) :all(_all){};
	void execute(){
		for (int i = 0; i < all.size(); ++i){
			all[i]->execute();
		}
	}
	void undo(){
		for (int i = all.size() - 1; i >= 0; --i){
			all[i]->undo();
		}
	}
};

void test_macro(){
	controlWithUndo myc;
	light* l = new light();
	tv* t = new tv();
	fan* f = new fan();
	commad* c[6];
	c[0] = new light_on_commnd(l);
	c[1] = new light_off_commnd(l);
	c[2] = new fan_low_commad(f);
	c[3] = new fan_mid_commad(f);
	c[4] = new fan_high_commad(f);
	c[5] = new fan_off_commad(f);
	
	macro_commad *myon = new macro_commad(vector<commad*>({ c[1], c[2] }));
	macro_commad *myoff = new macro_commad(vector<commad*>({ c[0] }));
	
	myc.setButton(0, myon);
	myc.setButton(1, myoff);

	myc.pushButton(0); myc.pushUndo();
	myc.pushButton(0); 
	myc.pushButton(1); 

	delete myon; delete myoff;
	for (int i = 0; i < 6; ++i){
		cout << "delete " << i << endl;
		delete c[i];
	}
	delete f; delete t; delete l;
}