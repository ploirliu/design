#include <iostream>
#include <string>
using namespace std;

class drink_coffein{
public:
	void prepare_drink(){
		boilWater();
		brew();
		pourInCup();
		if (customerWantCondiments()){
			addCondiments();
		}
	}
	void boilWater(){
		cout << "boil water" << endl;
	}
	virtual void brew() = 0;
	void pourInCup(){
		cout << "pour drink into cup" << endl;
	}
	virtual void addCondiments() = 0;
	virtual bool customerWantCondiments(){
		return true;
	}
};

class drink_tea :public drink_coffein{
public:
	void brew(){
		cout << "add tea-bag" << endl;
	}
	void addCondiments(){
		cout << "add demon" << endl;
	}
	bool customerWantCondiments(){
		cout << "Do you want condiments(y/n):";
		string s;
		cin >> s;
		if (s == "y")
			return true;
		return false;
	}
};

class drink_coffee :public drink_coffein{
public:
	void brew(){
		cout << "drip coffee through filter" << endl;
	}
	void addCondiments(){
		cout << "add suger" << endl;
	}
};

void test(){
	drink_coffein* a = new drink_coffee();
	cout << "cook coffee" << endl;
	a->prepare_drink();
	delete a;
	cout << endl;
	drink_coffein *b = new drink_tea();
	cout << "cook tea" << endl;
	b->prepare_drink();
	delete b;
}