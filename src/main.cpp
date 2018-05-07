#include <iostream>
#include "../Headers/scene.hpp"
#include <SDL/SDL.h>



#define acces_pixel(e,w,i,j) (*((unsigned int *)e->pixels + w * i + j))

using namespace std;


SDL_Surface *ecran;

int main(int argc, char *argv[])
{

    if (argc < 1){
        cout << "ERROR: No files loaded\n";
           return 1;
    }
    std::string arg1(argv[1]);

    SDL_Init(SDL_INIT_VIDEO); //Initialisation de la SDL
    cout << arg1 << "\n"; 
    Scene scene(arg1);
    scene.makeScene();

    cout << "Save? (y/n) : ";

    //Dessin de l'image sur la surface
    ecran = SDL_SetVideoMode(scene.mCamera.getWidth(), scene.mCamera.getHeigth(), 32, SDL_HWSURFACE);
    SDL_LockSurface(ecran);

    //
    for (int i = 0; i < (int)scene.mCamera.getHeigth(); i++){
        for (int j = 0; j < (int)scene.mCamera.getWidth(); j++){
            Pixel p = scene.mCamera.getPixel(i,j);
            acces_pixel(ecran,(int)scene.mCamera.getWidth(),i,j) = SDL_MapRGB(ecran->format, p.c.r, p.c.g, p.c.b);
        }
    }
    //Déblocage de l'image (on rend la main à l'utilisateur)
    SDL_UnlockSurface(ecran);
    SDL_Flip(ecran);

    char c = getchar();
    if(c == 'y'){
        scene.save(arg1 + ".ppm");
        cout << "\nScene saved under " << arg1 << ".ppm";
    }
    SDL_Quit();
    cout << "\n";
    return 0;
}
