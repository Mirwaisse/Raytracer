#include "../Headers/Lights.hpp"

using namespace std;

Light::Light(Color c): _c(c){}

Color Light::getColor()const{return _c;}

AmbientLight::AmbientLight(int r, int g, int  b): Light({r, g, b}){}

DirectionnalLight::DirectionnalLight(Color c, Vec3 p): Light(c), _pos(p){}

Vec3 DirectionnalLight::getPos()const{return _pos;}
