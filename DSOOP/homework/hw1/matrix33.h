#ifndef _MATRIX33_H_
#define _MATRIX33_H_
#include "vector3.h"

class matrix33 
{  

	private:
			vector3 col1, col2, col3;
	public:
		matrix33();
		matrix33(const vector3&, const vector3&, const vector3&);
		matrix33(const matrix33&);	
		

		/*return references bc these values modify the object calling*/
		const vector3 &operator[]( unsigned int index)const;			
		vector3	 &operator[](unsigned int index);
		matrix33 &operator=(const matrix33&);	
		matrix33 &operator*=(float);
		matrix33 &operator/=(float);
		matrix33 &operator+=(const matrix33&);
		matrix33 &operator-=(const matrix33&);
		
		friend bool     operator!=(const matrix33&, const matrix33&);
		friend bool 	 operator==(const matrix33&,const matrix33&);

		/*return a copy of an object to not modify calling object*/
		friend	 matrix33 operator*(float f, const matrix33&);
		friend	 matrix33 operator*(const matrix33&,float f);
		friend	 matrix33 operator+(const matrix33&,const matrix33&); 
		friend	 matrix33 operator-(const matrix33&);
		friend	 matrix33 operator-(const matrix33&,const matrix33&);
		friend	 matrix33 operator*(const matrix33&, const matrix33&);
		float determinant();
		matrix33 invert();
		void identity();
		void printMatrix();
		
};

#endif
