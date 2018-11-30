#include <iostream>
#include <chrono>
#include <functional>
#include <SFML/Window.hpp>
#include <OpenGL/gl3.h>
#include <array>
#include <cmath>
#include "shader.hpp"

constexpr int windowWhidth(800), windowHeight(600);

// Array to define the vertices from -1 to 1
float vertices[] = {
    0.5f,  -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
    -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
    0.0f,  0.5f, 0.0f , 0.0f, 0.0f, 1.0f
};

Shader* ourShader = NULL;

unsigned int VBO;
unsigned int VAO;

int main()
{
    sf::ContextSettings settings;
    settings.majorVersion = 4;
    settings.minorVersion = 0;
    // create the window
    sf::Window window(sf::VideoMode(windowWhidth, windowHeight), "OpenGL", sf::Style::Default, settings);

    window.setVerticalSyncEnabled(true);

    // activate the window
    window.setActive(true);
    sf::ContextSettings s = window.getSettings();

    std::cout << "version:" << s.majorVersion << "." << s.minorVersion << std::endl;

    ourShader = new Shader("../shaders/shader.vs", "../shaders/shader.fs");

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);


    int nrAttributes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
    std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;

    // This line call to draw in wireframe polygons, to show lines
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    sf::Clock Clock;
    // run the main loop
    bool running = true;
    while (running)
    {
        // handle events
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                // end the program
                running = false;
            }
            else if (event.type == sf::Event::Resized)
            {
                // adjust the viewport when the window is resized
                glViewport(0, 0, event.size.width, event.size.height);
            }
        }

        // clear the buffers
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // draw...
        ourShader->use();
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        // end the current frame (internally swaps the front and back buffers)
        window.display();
    }

    // release resources...
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    return 0;
}
