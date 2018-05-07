#include <typeinfo>
#include "../Headers/shapes.hpp"

using namespace std;

Shape::Shape(const Color& color, double ref): _color(color), _ref(ref){}
Shape::~Shape(){}

Sphere::Sphere(const Vec3& o, double rayon, const Color& color, double ref):Shape(color, ref),_o(o),_rayon(rayon){}

Sphere::~Sphere(){}

//Renvoie 0, 1 ou 2 points obtenus par intersection d'un rayon avec une sphère
//Calcul de l'intersection d'un rayon avec une sphère. Renvoie le ou les points d'intersection
//La fonction résout un problème de type aX2 + bX + c = 0
vector<Vec3> Sphere::interpolate(const Rayon& r) const{
    const Vec3 &origine{r.o}, &direction{r.dir}, &ori{_o};
    vector<Vec3> v;

    double a = direction.x * direction.x + direction.y * direction.y + direction.z * direction.z;
    double b = 2 * ( sommer((origine - ori) * direction));
    double c = sommer((origine - ori) * (origine - ori)) - _rayon * _rayon;

    double discriminant = b * b - 4 * a * c;

    if (discriminant>= 0){
        double x1 = (-b - sqrt(discriminant)) / (2*a) - 1e-6;
        double x2 = (-b + sqrt(discriminant)) / (2*a) - 1e-6;

        if (x1 > 0) {
            v.push_back(origine + direction * x1);
        }
        if (x2 > 0) {
            v.push_back(origine + direction * x2);
        }        
        return v;
    } 
    else{
        return v;
    }
}


/**
================================================================
GETTERS AND SETTERS
================================================================
**/


Color Shape::getColor() const {return _color;}
double Shape::getRef() const {return _ref;}
Vec3 Sphere::getOrigine() const {return _o;}
double Sphere::getRayon() const {return _rayon;}
