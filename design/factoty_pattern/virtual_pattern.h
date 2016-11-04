#include <iostream>
#include <string>
using namespace std;

class tea{
	string name;
public:
	tea(string _name) :name(_name){
		show();
	};
	void show(){
		cout << "prepare " << name << endl;
	}
};

class green_tea :public tea{
public:
	green_tea() :tea("green_tea"){}
};

class red_tea :public tea{
public:
	red_tea() :tea("red_tea"){}
};

class cup{
	string name;
public:
	cup(string _name) :name(_name){
		show();
	};
	void show(){
		cout << "prepare " << name << endl;
	}
};

class normal_cup :public cup{
public:
	normal_cup() :cup("normal cup"){};
};

class ceramics_cup :public cup{
public:
	ceramics_cup() : cup("ceramics cup"){};
};

class water{
	string name;
public:
	water(string _name) :name(_name){
		show();
	};
	void show(){
		cout << "prepare " << name << endl;
	}
};

class normal_water :public water{
public:
	normal_water() :water("normal water"){};
};

class spring_water :public water{
public:
	spring_water() :water("spring water"){};
};

class v_factory{
public:
	virtual tea* createTea() = 0;
	virtual water* create_high_water(){
		return new spring_water();
	}
	virtual water* create_normal_water(){
		return new normal_water();
	}
	virtual cup* create_high_Cup(){
		return new ceramics_cup();

	}
	virtual cup* create_normal_Cup(){
		return new normal_cup();
	}
};

class red_tea_factory :public v_factory{
public:
	tea* createTea(){
		return new red_tea();
	}
};

class green_tea_factory :public v_factory{
public:
	tea* createTea(){
		return new green_tea();
	}
};

class boil_function{
public:
	virtual void boil() = 0;
};

class hot_boil :public boil_function{
public:
	void boil(){
		cout << "boil to 100 degree" << endl;
	}
};

class not_hot_boil :public boil_function{
public:
	void boil(){
		cout << "boil to 100 degree and freeze to 85 degree" << endl;
	}
};

class drink_tea{
protected:
	tea* t;
	cup *c;
	water* w;
	boil_function* boil_f;
	v_factory *v;
	drink_tea(v_factory *_v) :v(_v){};
public:
	~drink_tea(){
		destory();
	}
	virtual void prepare() = 0;
	void boil(){
		boil_f->boil();
	}
	virtual void add_tea_water(){
		cout << "add tea and water" << endl;
	}
	virtual void wash_cup(){
		cout << "wash cup" << endl;
	}
	virtual void pull_cup(){
		cout << "all is done" << endl;
	}
	virtual void destory(){
		delete t;
		delete c;
		delete w;
		delete boil_f;
		delete v;
	}
};

class drink_high_green_tea:public drink_tea{
public:
	drink_high_green_tea(v_factory* _v) :drink_tea(_v){}
	void prepare(){
		t = v->createTea();
		w = v->create_high_water();
		c = v->create_high_Cup();
		boil_f = new  not_hot_boil();
	}
};

class drink_normal_green_tea :public drink_tea{
public:
	drink_normal_green_tea(v_factory* _v) :drink_tea(_v){}
	void prepare(){
		t = v->createTea();
		w = v->create_normal_water();
		c = v->create_normal_Cup();
		boil_f = new  not_hot_boil();
	}
};

class drink_high_red_tea :public drink_tea{
public:
	drink_high_red_tea(v_factory* _v) :drink_tea(_v){}
	void prepare(){
		t = v->createTea();
		w = v->create_high_water();
		c = v->create_high_Cup();
		boil_f = new  hot_boil();
	}
};

class drink_normal_red_tea :public drink_tea{
public:
	drink_normal_red_tea(v_factory* _v) :drink_tea(_v){}
	void prepare(){
		t = v->createTea();
		w = v->create_normal_water();
		c = v->create_normal_Cup();
		boil_f = new  hot_boil();
	}
};

class tea_store{
protected:
	virtual drink_tea* createTea(string _type)=0;
public:
	drink_tea* orderTea(string _type){
		drink_tea* out = createTea(_type);
		out->prepare();
		out->boil();
		out->add_tea_water();
		out->wash_cup();
		out->pull_cup();
		return out;
	}
};

class green_tea_store :public tea_store{
protected:
	drink_tea *createTea(string _type){
		v_factory *v = new green_tea_factory();
		if (_type == "high"){
			return new drink_high_green_tea(v);
		}
		else
			return new drink_normal_green_tea(v);
	}
};

class red_tea_store :public tea_store{
protected:
	drink_tea *createTea(string _type){
		v_factory *v = new red_tea_factory();
		if (_type == "high"){
			return new drink_high_red_tea(v);
		}
		else
			return new drink_normal_red_tea(v);
	}
};