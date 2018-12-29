#ifndef SHADER_HPP
#define SHADER_HPP
#define GL_SILENCE_DEPRECATION

#include <OpenGL/gl3.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
public:
    // Program ID
    unsigned int ID;

    Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
    void use();
    void setBool(const std::string &name, bool value)const;
    void setInt(const std::string &name, int value)const;
    void setFloat(const std::string &name, float value)const;
};
#endif