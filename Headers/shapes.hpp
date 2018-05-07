#ifndef SHAPE_H
#define SHAPE_H

#include <vector>
#include "utils.hpp"

class Shape{

    public:
        Shape() = default;
        Shape(const Color& color, double ref);
        ~Shape();

        Color getColor() const;
        double getRef() const;
        virtual Vec3 getOrigine() const = 0;
        virtual std::vector<Vec3> interpolate(const Rayon& r) const = 0;
    
    private:
        Color _color;
        double _ref;
};

class Sphere : public Shape{
    public:
        Sphere() = default;
        Sphere(const Vec3& o, double rayon, const Color& color, double ref);
        ~Sphere();

        Vec3 getOrigine() const;
        double getRayon() const;
        virtual std::vector<Vec3> interpolate(const Rayon& r) const;

    private:
        Vec3 _o;
        double _rayon;
};


#endif
