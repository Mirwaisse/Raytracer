#include <iostream>
#include "../Headers/scene.hpp"

using namespace std;


int main(int argc, char *argv[])
{

    if (argc < 1){
        cout << "ERROR: No files loaded\n";
           return 1;
    }
    std::string arg1(argv[1]);

    cout << arg1 << "\n";
    Scene scene(arg1);
    scene.makeScene();

    cout << "Save? (y/n) : ";
    char c = getchar();
    if(c == 'y'){
        scene.save(arg1 + ".ppm");
        cout << "\nScene saved under " << arg1 << ".ppm";
    }

    return 0;
}
