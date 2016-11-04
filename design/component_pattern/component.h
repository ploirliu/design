#include <iostream>
#include <string>
using namespace std;

class component{
	string s;
public:
	component(string _s = "") :s(_s){};
	virtual string getDespriction(){
		return s;
	}
	virtual double cost() = 0;
};

class tea_component :public component{
	double price;
public:
	tea_component() :component("tea"), price(2.2){}
	double cost(){
		return price;
	}
};



class suger_c_component :public component{
	string s;
	double price;
	component *has;
public:
	suger_c_component(component *_com) :has(_com),s("suger"), price(0.2){};
	string getDespriction(){
		return has->getDespriction() + "," + s;
	}
	double cost(){
		return has->cost() + price;
	}
};

class demon_c_component :public component{
	string s;
	double price;
	component *has;
public:
	demon_c_component(component *_com) :has(_com), s("demon"), price(0.4){};
	string getDespriction(){
		return has->getDespriction() + "," + s;
	}
	double cost(){
		return has->cost() + price;
	}
};