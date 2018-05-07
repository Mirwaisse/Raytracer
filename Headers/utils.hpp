#ifndef UTILS_HPP
#define UTILS_HPP
#include <ostream>
#include <cmath>

typedef struct Color{
    int r;
    int g;
    int b;
    //int a; //Transparence

    Color() = default;
    Color(const Color&) = default; //Constructeur de copie
    Color& operator*= (double d);
    Color& operator/= (double d);
    Color& operator*= (const Color& c);
    Color& operator+= (const Color&);
}Color;

Color operator* (const Color& c, double d);
Color operator* (const Color& c1, const Color& c2);
Color operator+ (const Color& c1, const Color& c2);


typedef struct Vec3{
    double x;
    double y;
    double z;

    Vec3() = default;
    Vec3(const Vec3&) = default;
    Vec3 normalisation();
    Vec3 operator*(const Vec3& v);
    double norme();
}Vec3;

double scalaire(Vec3 v1, Vec3 v2);
double sommer(Vec3 v);
Vec3 normalisation(Vec3 v1);
Vec3 operator+(const Vec3& v1, const Vec3& v2);
Vec3 operator-(const Vec3& v1, const Vec3& v2);
Vec3 operator*(const Vec3& v1, double d);
Vec3 operator/(const Vec3& v1, double d);


//Un pixel = une position et une couleur
typedef struct Pixel{
    Vec3 v;
    Color c;
    Pixel() = default;
}Pixel;

//Un rayon= une origine et une direction
typedef struct Rayon{
    Vec3 o;
    Vec3 dir;
    Rayon(const Vec3& ori, const Vec3& direc);
    Rayon reflexion(const Vec3& ori, const Vec3& direc) const;
}Rayon;

#endif
