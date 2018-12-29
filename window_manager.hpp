#ifndef LUtil_hpp
#define LUtil_hpp
#define GL_SILENCE_DEPRECATION

/*#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"*/
#include <SFML/Graphics/Image.hpp>
#include <iostream>
#include <chrono>
#include <functional>
#include <SFML/Window.hpp>
#include <OpenGL/gl3.h>
#include <array>
#include <cmath>
#include "shader.hpp"
#include "config.hpp"

constexpr int windowWhidth(800), windowHeight(600);

//Init window
bool init();
//Update logic
void update();
//Update screen
void diaplayScreen();
//Clear screen
void clearScreen();
//Load media
bool loadMedia();
//Render textures and shapes
void draw();
//Release resources
void release();
//Handle events keys
void handleKeys(sf::Event event);
// Return the window
sf::Window *getWindow();

#endif /* LUtil_hpp */


