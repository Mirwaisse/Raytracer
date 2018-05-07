#ifndef LIGHTS_HPP
#define LIGHTS_HPP

#include "utils.hpp"

class Light{

    private:
        Color _c;

    public:
        Light() = default;
        Light(Color c);
        Color getColor() const;
};


class AmbientLight: public Light{

    public:
        AmbientLight() = default;
        AmbientLight(int r, int g, int  b);
};

class DirectionnalLight: public Light{

    private:
        Vec3 _pos;
        
    public:
        DirectionnalLight() = default;
        DirectionnalLight(Color c, Vec3 p);
        Vec3 getPos() const;
};

#endif
