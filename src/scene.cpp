#include <fstream>
#include <sstream>
#include <iostream>

#include "../Headers/scene.hpp"
#include "../Headers/shapes.hpp"

#define ANTIALIASING 4
#define DEPTH 3



using namespace std;


//Chargement de la scène
Scene::Scene(const string& file){

    string _line;
    ifstream _file;
    _file.open(file);
    double x, y, z, ra, re;
    int r, g, b, cpt = 0;
    string figure;

    Vec3 o, hg, hd, bg;

    cout << "Loading source file..." << _line << "\n";

    while(getline( _file ,_line)){
        istringstream is(_line); 
        
        if(_line[0] != '#' && _line != ""){
            if(cpt == 0){
                is >> x >> y >> z;
                o = Vec3{x, y, z};
                cout << "Camera building..." << x << "," << y << "," << z << "\n";
                cpt++;
            }else if(cpt == 1){
                is >> x >> y >> z;
                hg = Vec3{x, y, z};
                cout << "Screen building: HG..." << x << "," << y << "," << z << "\n";
                cpt++;
            }else if(cpt == 2){
                is >> x >> y >> z;
                hd = Vec3{x, y, z};
                cout << "Screen building: HD..." << x << "," << y << "," << z << "\n";
                cpt++;
            }else if(cpt == 3){
                is >> x >> y >> z;
                bg = Vec3{x, y, z};
                cout << "Screen building: BG..." << x << "," << y << "," << z << "\n";
                cpt++;
            }else if(cpt == 4){
                is >> r;
                mCamera = Camera(o, hg, hd, bg, r);
                cout << "SUCCESS: Camera built !\n";
                cpt++;
            }else if(cpt == 5){
                is >> r >> g >> b;
                bgr = Color{r, g, b};
                cout << "Background built with colors..." << _line << "\n";
                cpt++;
            }else if(cpt == 6){
                is >> x >> y >> z >> r >> g >> b;
                directionnal = DirectionnalLight(Color{r,g,b}, Vec3{x, y, z});      
                cout << "Light built...\n";
                cpt++;
            }else{
                is >> figure;
                if(figure == "sphere:"){
                    is >> x >> y >> z >> ra >> r >> g >> b >> re;
                    shapeList.push_back(Sphere(Vec3{x, y, z}, ra, Color{r,g,b}, re));         
                    cout << "Sphere loaded... " << shapeList.size() <<"\n";
                }else if(figure == "ambient:"){
                    is >> r >> g >> b;
                    ambient = AmbientLight(r, g, b);
                    cout << "Ambient light loaded... " <<"\n";
                }else{
                    cout << "ERROR: Unimplemented figure ! " << figure << "\n";
                }
            }
        }
    }
    cout << "SUCCESS: Scene built successfully " <<"\n\n";
    _file.close(); 
}


//Calcul de  la couleur d'un pixel
Color Scene::getColor(Rayon r, int n = 0){
    
    bool inter = false;
    bool shade = false;
    
    Vec3 p_i{0, 0, 0}; //Point d'intersection
    Vec3 sp_i{0,0,0};  //Point d'intersection ombres
    Sphere s_i;        //Forme d'intersection
    Color _specular, _diffusal, _ambient;
    
    
    //_______________________________________________________
    //INTERPOLATIONS

    for(Sphere& _sphere: shapeList){
        for(Vec3& i: _sphere.interpolate(r)){
            if(!inter || (i - r.o).norme() < (p_i - r.o).norme()){
                inter = true;
                p_i = i;
                s_i = _sphere;
            }
        }
    }

    Rayon reflected{p_i, directionnal.getPos() - p_i};
    for(Sphere& _shape: shapeList){
        for(Vec3& i: _shape.interpolate(reflected)){
            if(!shade || (i - reflected.o).norme() < (sp_i - reflected.o).norme()){
                shade = true;
                sp_i = i;
            }
        }
    }

    if(!inter){
        if(n == 0) return bgr; //Si aucun objet n'a été touché par le rayon
        else if(n <= DEPTH) return Color(); //Si il s'agit d'un rayon réfléchi
    }

    //_______________________________________________________
    //LIGHT CALCULATION

    _ambient = ambient.getColor();

    if(s_i.getRef() > 0 && n < DEPTH){
        _specular = getColor(r.reflexion(p_i, normalisation((p_i - s_i.getOrigine()))), n + 1) * s_i.getRef();
    }
    else{
        _specular = Color();
    }

    if((sp_i - p_i).norme() > (directionnal.getPos() - p_i).norme() || !shade){
        _diffusal = s_i.getColor() * directionnal.getColor() * scalaire(normalisation((directionnal.getPos() - p_i)), normalisation((p_i - s_i.getOrigine()))) * (1. - s_i.getRef()) * (1 / 255.);
    }
    else{
        _diffusal = Color();
    }

    
    return _specular + _diffusal + _ambient;
}

 

//Rendu de la scène
void Scene::makeScene(){

    Camera c2 = Camera(mCamera, mCamera.getWidth()*ANTIALIASING);

    cout << "Rendering... ";

    //Parcours de l'ensemble des pixels de l'écran en parrallèle
    #pragma omp parallel for
    for(int x = 0 ; x < (int)c2.getWidth(); x+=ANTIALIASING){     
        
        #pragma omp parallel for
        for(int y = 0 ; y < (int)c2.getHeigth(); y+=ANTIALIASING){
            
            Color colorSet = Color{0,0,0};

            for(int i = 0; i < ANTIALIASING; i++){
                for(int j = 0; j < ANTIALIASING; j++){
                    Rayon r = c2.getRay(x + i, y + j);
                    colorSet += getColor(r);
                }
            }
            colorSet /= ANTIALIASING*ANTIALIASING; //Moyenneur de couleur
            if(x%ANTIALIASING == 0 && y%ANTIALIASING == 0){
                mCamera.setPixel((int)x/ANTIALIASING, (int)y/ANTIALIASING, colorSet);
            }
   
        }
    }

    cout << "DONE ! " << "\n\n";

    cout << "Press any key to exit the simulation..." << "\n";
}

//Ecriture dans le fichier de destination
void Scene::save(const std::string& dst) const{
    ofstream file(dst);
    file << "P3" << '\n'
             << mCamera.getWidth() << " " << mCamera.getHeigth() << '\n'
             << 255 << '\n';

    file << mCamera;
}

