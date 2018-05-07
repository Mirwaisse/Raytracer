#include <iostream>
#include "../Headers/utils.hpp"

using namespace std;


Color& Color::operator*= (double d){
    if(d < 0) d = 0;
    r *= d;
    g *= d;
    b *= d;
    return *this;
}

Color& Color::operator/= (double d){
    if(d < 1) d = 1;
    r /= d;
    g /= d;
    b /= d;
    return *this;
}


Color& Color::operator*= (const Color& c){r *= c.r;g *= c.g;b *= c.b;return *this;}

Color& Color::operator+= (const Color& c){r += c.r;g += c.g;b += c.b;return *this;}

Color operator* (const Color& c, double d){Color res(c);return res *= d;}

Color operator* (const Color& c1, const Color& c2){Color res(c1);return res *= c2;}

Color operator+ (const Color& c1, const Color& c2){Color res(c1);return res += c2;}






/**
*
* VEC 3
*
**/



Vec3 operator+(const Vec3& v1, const Vec3& v2){Vec3 v(v1);v.x = v1.x + v2.x;v.y = v1.y + v2.y;
v.z = v1.z + v2.z; return v;}

Vec3 operator-(const Vec3& v1, const Vec3& v2){Vec3 v(v1);v.x = v1.x - v2.x;v.y = v1.y - v2.y;v.z = v1.z - v2.z; return v;}

Vec3 operator*(const Vec3& v1, double d){Vec3 v(v1);v.x = v1.x *d;v.y = v1.y *d;v.z = v1.z *d;return v;}

Vec3 operator/(const Vec3& v1, double d){Vec3 v(v1);v.x = v1.x /d;v.y = v1.y /d;v.z = v1.z /d;return v;}


Vec3 Vec3::operator*(const Vec3& v){x *= v.x;y *= v.y;z *= v.z;return *this;}

double scalaire(Vec3 v1, Vec3 v2){return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);}
double sommer(Vec3 v){return (v.x + v.y + v.z);}
double Vec3::norme(){return sqrt(x * x + y * y + z * z);}
Vec3 normalisation(Vec3 v){return Vec3{v.x/v.norme(), v.y/v.norme(), v.z/v.norme()};}


/**
*
*  RAYON
*
**/

Rayon::Rayon(const Vec3& ori, const Vec3& direc):o(ori),dir(normalisation(direc)){}

Rayon Rayon::reflexion(const Vec3& ori, const Vec3& direc) const{
    return Rayon(ori, dir - direc * 2 * (scalaire(direc, dir)));
}
