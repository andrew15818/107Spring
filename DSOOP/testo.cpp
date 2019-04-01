#include<iostream>
using namespace std;
class Player{
	private:
		float health, attack;
	public:

	Player(float health, float attack){
		this->health = health;
		this->attack = attack;
	}
	void print(){
		cout<<"health: "<<health<<" attack "<<attack<<endl;
	}
};
class goblin:public Player{
	private:
		float health, attack,defense;
	public:
		goblin(float health, float attack, float defense):Player(health, attack), defense(defense){};
		virtual void print(){
			cout<<"Calling derived class function with values"<<health<< " attack "<<attack<<" defense "<<defense<<endl;	
		}

};
int main(){
	Player *p;
	goblin g(69, 420, 240);
	p = &g;
	p->print();
	return 	0;
}
