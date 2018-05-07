#ifndef CAMERA_H
#define CAMERA_H

#include <ostream>
#include <vector>
#include "utils.hpp"

class Camera{

    friend std::ostream& operator <<(std::ostream& stream, const Camera& c);

    public:
        //Constructeurs
        Camera() = default;
        Camera(const Vec3& o, const Vec3& hg, const Vec3& hd, const Vec3& bg, int width);
        Camera(Camera& c, int width);

        void init();
        Rayon getRay(double x, double y) const;
        
        //Getters and setters
        double getWidth() const;
        double getHeigth() const;
        Pixel getPixel(int x, int y) const;
        void setPixel(int x, int y, Color c);//Change la couleur du pixel de coordonnées (x,y) de l'écran
    

    private:
        std::vector<std::vector<Pixel>> _screen;
        Vec3 _o, _hg, _hd, _bg;
        int _width, _heigth;
        
};

std::ostream& operator<<(std::ostream& stream, const Camera& c);

#endif
