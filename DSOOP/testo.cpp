#include<iostream>
using namespace std;
class Being{
	private:
		int height, weight;
	public:
		Being(int height, int weight):height(height), weight(weight){}
		Being& set(int height, int weight){
			this->height=height;
			this->weight=weight;	
			return *this;
		}
		void print(){
			cout<<"height: "<< height<<"weight: "<<weight<<endl;	
		}
};
int main(){
	Being me(69, 420);	
	me.set(1,3).set(4,5);
	me.print();
	return 0;
}
