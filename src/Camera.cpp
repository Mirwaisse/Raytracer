#include "../Headers/Camera.hpp"

using namespace std;


//Constructeurs
Camera::Camera(const Vec3& o, const Vec3& hg, const Vec3& hd, const Vec3& bg, int width):_o(o), _hg(hg), _hd(hd), _bg(bg), _width(width){
    _heigth = int(width * ((bg - hg).norme() / (hd - hg).norme())); //Récupération de la  hauteur de l'image par relation de proportionnalité
    init();
}

Camera::Camera(Camera& c, int width):_o(c._o), _hg(c._hg), _hd(c._hd), _bg(c._bg), _width(width){ //Pseudo-constructeur de copie
    _heigth = int(width * ((_bg - _hg).norme() / (_hd - _hg).norme()));  //Récupération de la  hauteur de l'image par relation de proportionnalité
    init();
}



//Initialiseur
void Camera::init(){
    //Allocation de la mémoire pour stocker tous les pixels
    _screen.resize(_heigth);
    for(int i = 0; i < _heigth; i++){
        _screen[i].resize(_width);
    }

    //Initialisation de tous les pixels de l'écran
    for(unsigned int y= 0  ; y < _screen.size() ; ++y){
        for(unsigned int x = 0 ; x < _screen[y].size() ; ++x){
            _screen[y][x] = Pixel{Vec3(_hg + ((_hd - _hg) / _width) * x + ((_bg - _hg) / (_bg - _hg).norme() * ((_hd - _hg) / _width).norme()) * y), Color()};
        }
    }
}





//Obtient le rayon origine - pixel
Rayon Camera::getRay(double x, double y) const{
    Vec3 v{_screen[y][x].v.x, _screen[y][x].v.y, _screen[y][x].v.z};
    return {v, v - _o};
}


/**
================================================================
GETTERS AND SETTERS
================================================================
**/


//Change la couleur du pixel (x,y) de l'écran
void Camera::setPixel(int x, int y, Color c)
{
    if(c.r < 0) c.r = 0;
    if(c.g < 0) c.g = 0;
    if(c.b < 0) c.b = 0;

    if(c.r >255) c.r = 255;
    if(c.g >255) c.g = 255;
    if(c.b >255) c.b = 255;

    _screen[y][x].c = c;
}

double Camera::getWidth() const{return _width;}
double Camera::getHeigth() const{return _heigth;}
Pixel Camera::getPixel(int x, int y) const{return _screen[x][y];}

ostream& operator <<(ostream& stream, const Camera& camera){
    for(std::vector<Pixel> pixelArray: camera._screen){
        for(Pixel p: pixelArray){
            stream << p.c.r << " " << p.c.g << " " << p.c.b << "  ";
        }
        stream << '\n';
    }

    return stream;
}

