#include "matrix33.h"
#include<iostream>
/*constructors*/
matrix33::matrix33(){};
matrix33::matrix33(const vector3& column1, const vector3& column2, const vector3& column3){
	col1.x = column1.x, col1.y = column1.y, col1.z = column1.z;
	col2.x = column2.x, col2.y = column2.y, col2.z = column2.z;
	col3.x = column3.x, col3.y = column3.y, col3.z = column3.z;
}
matrix33::matrix33(const matrix33& matrix){
	col1.x = matrix.col1.x, col2.x = matrix.col2.x, col3.x = matrix.col3.x;
	col1.y = matrix.col1.y, col2.y = matrix.col2.y, col3.y = matrix.col3.y;
	col1.z = matrix.col1.z, col2.z = matrix.col2.z, col3.z = matrix.col3.z;
}
const vector3& matrix33::operator[](unsigned int index)const{
	if(index==1){return  col2;}
	else if(index==2){return col3;}
	return col1;
}

vector3& matrix33::operator[](unsigned int index){
	if(index == 1){return  col2;}
	else if (index == 2){return  col3;}
	return col1;
}
matrix33& matrix33::operator=(const matrix33& matrix){
	for(int i=0; i<3; i++){
		col1[i]=matrix.col1[i];	
		col2[i]=matrix.col2[i];
		col3[i]=matrix.col3[i];
	}
	return *this;
}
matrix33 &matrix33::operator*=(float f ){
	for(int i=0;i<3;i++){
		col1[i]*=f;
		col2[i]*=f;
		col3[i]*=f;
	}
	return *this;
}
matrix33 &matrix33::operator/=(float f){
		for(int i=0;i<3;i++){
			for(int j=0;j<3;j++){
				(*this)[i][j]/=f;	
			}	
		}
		return *this;
}
matrix33 &matrix33::operator+=(const matrix33& m){
	for(int i=0;i<3;i++){
		col1[i]+=m.col1[i];
		col2[i]+=m.col2[i];
		col3[i]+=m.col3[i];
	}
	return *this;
}
matrix33 &matrix33::operator-=(const matrix33& m){
	for(int i=0;i<3;i++){
		col1[i]-=m.col1[i];
		col2[i]-=m.col2[i];
		col3[i]-=m.col3[i];
	}
	return *this;
}
bool operator!=(const matrix33& m1, const matrix33& m2){
	matrix33 temp(m1);
	for(int i=0; i<3;i++){
		for(int j=0; j<3;j++){
			if(m1[i][j]!=m2[i][j]){
				return true;	
			}	
		}
	}	
	return false;
}
bool operator==(const matrix33& m1, const matrix33& m2){
	for(int i=0; i<3;i++){
		for(int j=0; j<3;j++){
			if(m1[i][j]!=m2[i][j]){
				return false;	
			}	
		}	
	}	
	return true;
}

matrix33 operator*(float f, const matrix33& m){
	matrix33 temp(m);
	for(int i=0; i<3;i++){
		for(int j=0;j<3;j++){
			temp[i][j]*=f;		
		}	
	}
	return temp;
}
matrix33 operator*(const matrix33& m, float f){
	matrix33 temp(m);
	for(int i=0;i<3;i++){
		temp.col1[i]*=f;
		temp.col2[i]*=f;
		temp.col3[i]*=f;
	}
	return temp;
}
matrix33 operator+(const matrix33& matrix1,const matrix33& matrix2){
	matrix33 temp(matrix1);
	for(int i=0;i<3;i++){
		temp.col1[i]+=matrix2.col1[i];	
		temp.col2[i]+=matrix2.col2[i];
		temp.col3[i]+=matrix2.col3[i];
	}	
	return temp;
}
matrix33 operator-(const matrix33& m){
	matrix33 temp(m);
	-temp.col1, -temp.col2, -temp.col3;
	return temp;
}
matrix33 operator-(const matrix33& m1, const matrix33& m2){
	matrix33 temp(m1);
	for(int i=0; i<3; i++){	
		temp.col1[i]-=m2.col1[i];
		temp.col2[i]-=m2.col2[i];
		temp.col3[i]-=m2.col3[i];
	}
	return temp;
}
//multiplication works fine :)
matrix33 operator*(const matrix33& m1,  const matrix33& m){
	vector3 temp1, temp2, temp3;	
	temp1.x = (m1.col1.x*m.col1.x + m1.col2.x*m.col1.y + m1.col3.x*m.col1.z), temp2.x = (m1.col1.x*m.col2.x+m1.col2.x*m.col2.y+m1.col3.x*m.col2.z), temp3.x=(m1.col1.x*m.col3.x + m1.col2.x*m.col3.y + m1.col3.x*m.col3.z);
	temp1.y =  (m1.col1.y*m.col1.x + m1.col2.y*m.col1.y + m1.col3.y*m.col1.z),temp2.y = (m1.col1.y*m.col2.x+m1.col2.y*m.col2.y+m1.col3.y*m.col2.z), temp3.y=(m1.col1.y*m.col3.x + m1.col2.y*m.col3.y + m1.col3.y*m.col3.z);
	temp1.z = (m1.col1.z*m.col1.x + m1.col2.z*m.col1.y+ m1.col3.z*m.col1.z), temp2.z =(m1.col1.z*m.col2.x+ m1.col2.z*m.col2.y+ m1.col3.z*m.col2.z), temp3.z=(m1.col1.z*m.col3.x + m1.col2.z*m.col3.y + m1.col3.z*m.col3.z);
	matrix33 temp(temp1, temp2,temp3);
	return temp;	
}
float matrix33::determinant(){
	float determinant = col1.x*(col2.y*col3.z - col2.z*col3.y) - col2.x*(col1.y*col3.z - col1.z*col3.y) +col3.x*(col1.y*col2.z - col1.z*col2.y);
	return determinant;
}
matrix33 matrix33::invert(){
	float determinant = this->determinant();
	matrix33 temp(*this);
	/*making a matrix with the cofactors*/
	temp.col1.x=(col2.y*col3.z - col2.z*col3.y)/determinant;
	temp.col2.x=-(col1.y*col3.z - col1.z*col3.y)/determinant;
	temp.col3.x=(col1.y*col2.z - col1.z*col2.y)/determinant;
	temp.col1.y=-(col2.x*col3.z - col2.z*col3.x)/determinant;
	temp.col2.y=(col1.x*col3.z - col1.z*col3.x)/determinant;
	temp.col3.y=-(col1.x*col2.z - col1.z*col2.x)/determinant;
	temp.col1.z=(col2.x*col3.y - col2.y*col3.x)/determinant;
	temp.col2.z=-(col1.x*col3.y - col1.y*col3.x)/determinant;
	temp.col3.z=(col1.x*col2.y - col1.y*col2.x)/determinant;
	matrix33 transpose(temp);	
	/*transposing*/
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			transpose[i][j]= temp[j][i];
		}	
	}
	return transpose;
}
/*set the elements equal to the identity matrix*/
void matrix33::identity(){
	matrix33& temp = *this;
	col1.x=col2.y=col3.z=1;
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			if(i!=j){
				temp[i][j]=0;
			}	
		}	
	}
}
void matrix33::printMatrix(){
	std::cout<<col1.x<<" "<<col2.x<<" "<<col3.x<<std::endl;
	std::cout<<col1.y<<" "<<col2.y<<" "<<col3.y<<std::endl;
	std::cout<<col1.z<<" "<<col2.z<<" "<<col3.z<<std::endl;
}

