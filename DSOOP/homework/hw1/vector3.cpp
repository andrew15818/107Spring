#include "vector3.h"
#include<iostream>
#include<cmath>
/*empty constructor,constructor with another vector object*/
vector3::vector3(){
}
vector3::vector3(float inX, float inY, float inZ):x(inX),y(inY), z(inZ){};

vector3::vector3(const vector3 &v){
	x = v.x;
	y = v.y;
	z = v.z;
}
/*First we implement the public methods*/
void vector3::set(float xIn, float yIn, float zIn){
	x=xIn;
	y=yIn;
	z=zIn; 
}
float vector3::length() const{
	return sqrt(pow(x,2)+pow(y,2)+pow(z,2));
}
void vector3::printVector3() const{
	std::cout<<"("<<x<<", "<<y<<", "<<z<<")"<<std::endl;
}
/*Now we implement the operator overloading*/
//what do the two different [] operators return?
//returning random number?
float& vector3::operator[](unsigned int index){
	if(index ==1){return y;}	
	else if(index ==2){return z;}
	return x;
}
const float& vector3::operator[](unsigned int index) const{
	if(index==1){return y;}
	else if(index>=2){return z;}
	return x;
}
/*return a *this pointer to allow for cascaded function calls */
vector3& vector3::operator=(const vector3 &v){
	x=v.x;
	y=v.y;
	z=v.z;
	return *this;
}
vector3& vector3::operator+=(const vector3 &v){
	x+=v.x;
	y+=v.y;
	z+=v.z;
	return *this;
}
vector3& vector3::operator-=(const vector3 &v){
	x-=v.x;
	y-=v.y;
	z-=v.z;
	return *this;
}
vector3& vector3::operator*=(float f){
	x*=f;
	y*=f;
	z*=f;
	return *this;
}
vector3& vector3::operator/=(float f){
	x/=f;
	y/=f;
	z/=f;
	return *this;
}
bool operator==(const vector3 &a, const vector3 &b){
	if(a.x!=b.x || a.y!=b.y || a.z!=b.z){return false;}
	return true;
}
bool operator!=(const vector3 &a, const vector3 &b){
	if(a.x==b.x || a.y==b.y || a.z ==b.z){return false;}
	return true;
}
vector3 operator-(const vector3& v){
	vector3 temp(-v.x, -v.y, -v.z);
	return temp;
}
vector3 operator-(const vector3 &a, const vector3 &b){
	vector3 temp(a.x-b.x, a.y-b.y, a.z-b.z);
	return temp;
}
vector3 operator+(const vector3 &a, const vector3 &b){
	vector3 temp(a.x+b.x, a.y+b.y, a.z+b.z);
	return temp;
}
vector3 operator*(const vector3 &v, float f){
	vector3 temp(v.x*f, v.y*f, v.z*f);
	return temp;
}
vector3 operator*(float f, const vector3 &v){
	vector3 temp(v.x*f, v.y*f, v.z*f);	
	return temp;
}
vector3 operator/(const vector3 &v, float f){
	vector3 temp(v.x/f, v.y/f, v.z/f);
	return temp;
}
