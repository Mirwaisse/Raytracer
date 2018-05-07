C_FLAGS = -std=c++11 -Wall

all : rayTracer

nosdl : rayTracer_nosdl

utils.o : Sources/utils.cpp
	g++ $(C_FLAGS) -c -o Objects/utils.o Sources/utils.cpp

shapes.o : Sources/shapes.cpp
	g++ $(C_FLAGS) -c -o Objects/shapes.o Sources/shapes.cpp

Camera.o : Sources/Camera.cpp
	g++ $(C_FLAGS) -c -o Objects/Camera.o Sources/Camera.cpp

scene.o : Sources/scene.cpp
	g++ $(C_FLAGS) -c -o Objects/scene.o Sources/scene.cpp -fopenmp

Lights.o : Sources/Lights.cpp
	g++ $(C_FLAGS) -c -o Objects/Lights.o Sources/Lights.cpp

main.o : Sources/main.cpp
	g++ $(C_FLAGS) -c -o Objects/main.o Sources/main.cpp -lSDLmain -lSDL

main_nosdl.o : Sources/main_nosdl.cpp
	g++ $(C_FLAGS) -c -o Objects/main_nosdl.o Sources/main_nosdl.cpp

rayTracer : main.o scene.o shapes.o Lights.o Camera.o utils.o
	g++ $(C_FLAGS) -o rayTracer Objects/main.o Objects/scene.o Objects/shapes.o Objects/Lights.o Objects/Camera.o Objects/utils.o -lSDLmain -lSDL -fopenmp

rayTracer_nosdl : main_nosdl.o scene.o shapes.o Lights.o Camera.o utils.o
	g++ $(C_FLAGS) -o rayTracer Objects/main_nosdl.o Objects/scene.o Objects/shapes.o Objects/Lights.o Objects/Camera.o Objects/utils.o -fopenmp

clean	:
	rm -f Objects/*.o rayTracer

