#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <stack>
using namespace std;

class menuComponent;

template<class T>
class myiterator{
public:
	virtual bool hasNext() = 0;
	virtual T* next() = 0;
};

template<class T>
class nulliterator :public myiterator < T > {
public:
	virtual bool hasNext(){
		return false;
	}
	virtual T* next() {
		return NULL;
	}
};




class vector_iterator :public myiterator < menuComponent > {
	vector<menuComponent*>::iterator now;
	vector<menuComponent*>::iterator end;
public:
	vector_iterator(vector<menuComponent*> &_v) :now(_v.begin()), end(_v.end()){
	}
	bool hasNext(){
		if (now != end)
			return true;
		return false;
	}
	menuComponent* next() {
		return &**(now++);
	}
};


class set_iterator :public myiterator < menuComponent > {
	set<menuComponent*>::iterator now;
	set<menuComponent*>::iterator end;
public:
	set_iterator(set<menuComponent*> &_s) :now(_s.begin()), end(_s.end()){}
	bool hasNext(){
		if (now != end)
			return true;
		return false;
	}
	menuComponent* next() {
		return &**(now++);
	}
};



class menuComponent{
public:
	virtual void add(menuComponent*){
		throw new exception("not support");
	}
	virtual void remove(menuComponent*){
		throw new exception("not support");
	}
	virtual menuComponent* getChildren(int _id){
		throw new exception("not support");
	}


	virtual string getName(){
		throw new exception("not support");
	}
	virtual double getPrice(menuComponent*){
		throw new exception("not support");
	}
	virtual string getDescription(){
		throw new exception("not support");
	}
	virtual bool isVegetarian(){
		//throw new exception("not support");
		return false;
	}


	virtual void show(){
		throw new exception("not support");
	}


	virtual myiterator<menuComponent>* getIterator(){
		throw new exception("not support");
	}
};


class menuItem :public menuComponent{
	string name;
	string description;
	double price;
	bool vegetarian;
public:
	menuItem(string _n, string _d, double _p, bool _v) :
		name(_n), description(_d), price(_p), vegetarian(_v){}
	virtual string getName(){
		return name;
	}
	virtual double getPrice(menuComponent*){
		return price;
	}
	virtual string getDescription(){
		return description;
	}
	virtual bool isVegetarian(){
		return vegetarian;
	}


	virtual void show(){
		cout << name << ":" << price << endl;
	}


	myiterator<menuComponent>* getIterator(){
		return new nulliterator<menuComponent>();
	}
};


class vector_menu :public menuComponent{
	string name;
	vector<menuComponent*> all;
public:
	vector_menu(string _n) :
		name(_n){}
	
	virtual void add(menuComponent* _n){
		all.push_back(_n);
	}
	virtual void remove(menuComponent*){
		throw new exception("not support");
	}
	menuComponent* getChildren(int _id){
		if (_id >= all.size())
			return NULL;
		return all[_id];
	}
	virtual void show(){
		cout << name << endl;
		myiterator<menuComponent>* child = getIterator();
		while (child->hasNext()){
			menuComponent* tmp = child->next();
			tmp->show();
		}
	}


	myiterator<menuComponent>* getIterator(){
		return new vector_iterator(all);
	}
};



class set_menu :public menuComponent{
	string name;
	set<menuComponent*> all;
public:
	set_menu(string _n) :
		name(_n){}

	virtual void add(menuComponent* _n){
		all.insert(_n);
	}
	virtual void remove(menuComponent* _n){
		all.erase(_n);
	}

	virtual void show(){
		cout << name << endl;
		myiterator<menuComponent>* child = getIterator();
		while (child->hasNext()){
			menuComponent* tmp = child->next();
			tmp->show();
		}
	}


	myiterator<menuComponent>* getIterator(){
		return new set_iterator(all);
	}
};

class compositeIterator :public myiterator < menuComponent > {
	stack<myiterator < menuComponent >*> s;
public:
	compositeIterator(myiterator < menuComponent >* _in){
		s.push(_in);
	}
	bool hasNext(){
		if (s.empty())
			return false;
		else{
			myiterator < menuComponent >* now = s.top();
			if (!now->hasNext()){
				s.pop();
				return hasNext();
			}
			else
				return true;
		}
	}
	menuComponent* next(){
		if (hasNext()){
			myiterator < menuComponent >* now = s.top();
			menuComponent* out = now->next();
			s.push(out->getIterator());
			return out;
		}
		else
			return NULL;
	}
};

class waitress{
	menuComponent* all;
public:
	waitress(menuComponent* _all) :all(_all){};
	void show(){
		all->show();
	}
	void show_vegetarian(){
		cout << "show vegetarian" << endl;
		compositeIterator cache(all->getIterator());
		while (cache.hasNext()){
			menuComponent* tmp = cache.next();
			if (tmp->isVegetarian()){
				tmp->show();
			}
		}
	}
};


void test(){
	menuComponent* breakfast = new vector_menu("breakfast");
	breakfast->add(new menuItem("rou bao zi", "with meet", 1.0, false));
	breakfast->add(new menuItem("cai bao zi", "without meet", 1.0, true));
	breakfast->add(new menuItem("dou jiang", "been", 1.0, true));

	menuComponent* dessert = new set_menu("dessert");
	dessert->add(new menuItem("xi gua", "fruit", 1.0, true));
	dessert->add(new menuItem("ping guo", "fruti", 1.0, true));

	menuComponent* lunch = new vector_menu("lunch");
	lunch->add(new menuItem("mi", "zhu shi", 1.0, true));
	lunch->add(new menuItem("yu", "fish", 2.0, false));
	lunch->add(new menuItem("dou fu", "been", 2.0, true));
	lunch->add(dessert);

	menuComponent* dinner = new vector_menu("dinner");
	dinner->add(new menuItem("ji dan mian", "zhu shi", 1.0, true));
	dinner->add(new menuItem("niu rou mian", "beef", 2.0, false));

	menuComponent *all = new vector_menu("all");
	all->add(breakfast);
	all->add(lunch);
	all->add(dinner);
	

	waitress w(all);
	w.show();
	cout << endl;
	w.show_vegetarian();
}
