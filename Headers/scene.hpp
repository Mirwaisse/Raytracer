#ifndef SCENE_H
#define SCENE_H
#include <string>
#include <vector>
#include <memory>
#include "Camera.hpp"
#include "utils.hpp"
#include "shapes.hpp"
#include "Lights.hpp"

class Scene{
    
    AmbientLight ambient; //Lumière ambiante de la scène
    DirectionnalLight directionnal; //Lumière directionnelle de la scène
    Color bgr; //Couleur de fond
    std::vector<Sphere> shapeList; //Liste des objets de la scène

public:
    Camera mCamera; //Caméra de la scène
    Scene() = default;;
    Scene(const std::string& file); 
    void makeScene(); //Rendu
    Color getColor(Rayon r, int n); //Calcul de la couleur d'un pixel
    void save(const std::string& dst) const; //Sauvegarde de l'image
};



#endif

