#!/bin/bash
#This is a bash file
clang++ main.cpp -std=c++11 -F./frameworks -framework SFML -framework sfml-audio -framework sfml-graphics -framework sfml-network -framework sfml-system -framework sfml-window -framework OpenGL -o build/openglP -O0 -g