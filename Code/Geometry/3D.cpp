#include <bits/stdc++.h>
#define ld double
using namespace std;

struct PT {
	ld x, y, z;
	PT(ld x, ld y, ld z) : x(x), y(y), z(z) {}
	PT() : x(0), y(0), z(0) {}

	PT operator+(const PT&a)const{return PT(x+a.x, y+a.y, z+a.z);}
	PT operator-(const PT&a)const{return PT(x-a.x, y-a.y, z-a.z);}
	PT operator%(const PT&a)const{return PT(y*a.z - z*a.y, z*a.x - x*a.z, x*a.y - y*a.x);}
	PT operator*(ld c) const{ return PT(x*c, y*c, z*c); }
	PT operator/(ld c) const{ return PT(x/c, y/c, z/c); }
	ld operator*(const PT&a)const{return  (x*a.x + y*a.y + z*a.z);}
	bool operator< (const PT&a) const{ return tie(x, y, z) < tie(a.x, a.y, a.z); }
	ld len() const { return hypot(x,y,z); } // sqrt(p*p)

	PT rotate(double angle, PT axis) {
        double s = sin(angle), c = cos(angle); PT u = axis / axis.len();
        return u*(*this*u)*(1-c) + (*this)*c - *this%u*s;
    };
};

/*LATEX_DESC_BEGIN***************************
Pode reusar:
 - segmentDist

*****************************LATEX_DESC_END*/
