#!/bin/bash
#This is a bash file
clang++ main.cpp shader.h shader.cpp -std=c++11 -I/usr/local/include -L/usr/local/lib -F./frameworks -framework SFML -framework sfml-audio -framework sfml-graphics -framework sfml-network -framework sfml-system -framework sfml-window -framework OpenGL -o build/ogl -O0 -g