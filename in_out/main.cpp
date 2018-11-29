#include <iostream>
#include <chrono>
#include <functional>
#include <SFML/Window.hpp>
#include <OpenGL/gl3.h>
#include <array>
#include <cmath>

constexpr int windowWhidth(800), windowHeight(600);

// Array to define the vertices from -1 to 1
float vertices[] = {
     0.5f,  0.5f, 0.0f,  // top right
     0.5f, -0.5f, 0.0f,  // bottom right
    -0.5f, -0.5f, 0.0f,  // bottom left
    -0.5f,  0.5f, 0.0f   // top left
};
// Indices to draw in order
unsigned int indices[] =
{
    0, 1, 3,
    1, 2, 3
};
// Source the vertex shadow
const char *vertexShaderSource = "#version 410 core\n"
                                 "layout (location = 0) in vec3 aPos;\n"
                                 "out vec4 vertexColor;\n"
                                 "void main()\n"
                                 "{\n"
                                 "    gl_Position = vec4(aPos, 1.0);\n"
                                 "    vertexColor = vec4(0.5, 0.0, 0.0, 1.0);\n"
                                 "}\n";

const char *fragmentShaderSource = "#version 410 core\n"
                                   "out vec4 FragColor;\n"
                                   "in vec4 vertexColor;\n"
                                   "void main()\n"
                                   "{\n"
                                   "    FragColor = vertexColor;\n"
                                   "}\n";

unsigned int VBO;
unsigned int VAO;
unsigned int EBO;
unsigned int vertexShader;

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

    // load resources, initialize the OpenGL states, ...
    vertexShader = glCreateShader(GL_VERTEX_SHADER);

    // To compile the shader in runtime
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    // Verify errors to complie shader
    int success;
    char infolog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infolog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
                  << infolog << std::endl;
    }

    // To create fragment shader
    unsigned int fragmenShader;

    fragmenShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmenShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmenShader);

    // Verify errors to complie shader
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infolog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
                  << infolog << std::endl;
    }

    // Creating the shader program
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();

    // Attach the shader program
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmenShader);
    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infolog);
        std::cout << "ERROR::SHADER::POGRAM::COMPILATION_FAILED\n"
                  << infolog << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmenShader);

    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    int nrAttributes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
    std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;

    // This line call to draw in wireframe polygons, to show lines
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

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
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        // end the current frame (internally swaps the front and back buffers)
        window.display();
    }

    // release resources...

    return 0;
}
