#include<iostream>
using namespace std;
class person{
	friend ostream& operator<<( ostream&, const person&);
	friend istream& operator>>( istream&, person&); 
	private:
		float height, weight;
	public:
		person(float height, float weight):height(height), weight(weight){};
		person operator+(const person&);
		
};
person person::operator+(const person& p){
	this->height+=p.height;
	this->weight+=p.weight;
	return *this;
}
ostream& operator<<(ostream& os, const person& p){
	os<<p.height<<" "<<p.weight<<endl;
	return os;
}
istream& operator>>(istream& is, person& p){
	is>>p.weight>>p.height;
	return is;
}
int main(){
	person andres(69, 69);
	cout<<andres<<endl;
}
