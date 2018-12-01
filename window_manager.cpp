#include "window_manager.hpp"

sf::Window *gWindow;
Shader *ourShader;

unsigned int VBO;
unsigned int VAO;
unsigned int EBO;

// Init OpenGL
bool initOpenGL()
{
    // Array to define the vertices from -1 to 1
   float vertices[] = {
         0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,
         0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f
    };

    unsigned int indices[] = {
        0, 1, 3,
        1, 2, 3
    };

    // Init shaders
    ourShader = new Shader("../shaders/shader.vs", "../shaders/shader.fs");

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    int nrAttributes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
    std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;

    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    sf::Image data;
    if (!data.loadFromFile("../assets/container.jpg"))
    {
        std::cout << "Failed to load texture" << std::endl;
        return false;
    }
    else
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, data.getSize().x, data.getSize().y, 0, GL_RGB, GL_UNSIGNED_BYTE, data.getPixelsPtr());
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    return true;
}

//Init window
bool init()
{
    bool success = true;

    sf::ContextSettings settings;
    settings.majorVersion = 4;
    settings.minorVersion = 0;

    // create the window
    gWindow = new sf::Window(sf::VideoMode(windowWhidth, windowHeight), "OpenGL", sf::Style::Default, settings);

    // Set orientation
    gWindow->setVerticalSyncEnabled(true);

    // activate the window
    gWindow->setActive(true);

    // Log OpenGl version
    std::cout << "version:" << gWindow->getSettings().majorVersion << "." << gWindow->getSettings().minorVersion << std::endl;

    if (!initOpenGL())
    {
        std::cout << "OpenGL failed" << std::endl;
        success = false;
    }
    return success;
}

//Update logic
void update()
{
}

//Update screen
void diaplayScreen()
{
    // end the current frame (internally swaps the front and back buffers)
    gWindow->display();
}

//Clear screen
void clearScreen()
{
    // Clear screen green color
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

//Load media
bool loadMedia()
{
}

//Render textures and shapes
void draw()
{
    ourShader->use();
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

// Release resources
void release()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

// Handle events keys
void handleKeys(sf::Event event)
{
    if (event.type == sf::Event::Resized)
    {
        // adjust the viewport when the window is resized
        glViewport(0, 0, event.size.width, event.size.height);
    }
}
// Return the window
sf::Window *getWindow()
{
    return gWindow;
}
