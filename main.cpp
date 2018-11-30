#include <iostream>
#include <chrono>
#include <functional>
#include <SFML/Window.hpp>
#include <array>
#include <cmath>
#include "shader.hpp"
#include "window_manager.hpp"

int main()
{
    if (init())
    {
        sf::Clock Clock;
        // run the main loop
        bool running = true;
        while (running)
        {
            // handle events
            sf::Event event;
            while (getWindow()->pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                {
                    // end the program
                    running = false;
                }else{
                    handleKeys(event);
                }
            }
            // clear the buffers
            clearScreen();
            // draw...
            draw();
            // end the current frame (internally swaps the front and back buffers)
            diaplayScreen();
        }
        // release resources...
        release();
    }
    return 0;
}
