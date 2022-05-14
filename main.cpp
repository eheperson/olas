#include <iostream>
#include <adder.h>
#include <GLFW/glfw3.h>

#include <OLASConfig.h>

float add(float a, float b);

int main(int argc, char* argv[]){

    GLFWwindow* window;
    int width, height;

    std :: cout << argv[0] 
                << "Verion : "
                << OLAS_VERSION_MAJOR
                << "."
                << OLAS_VERSION_MINOR
                << std::endl;

    if( !glfwInit() )
    {
        fprintf( stderr, "Failed to initialize GLFW\n" );
        exit( EXIT_FAILURE );
    }

    window = glfwCreateWindow( 300, 300, "Gears", NULL, NULL );
    if (!window)
    {
        fprintf( stderr, "Failed to open GLFW window\n" );
        glfwTerminate();
        exit( EXIT_FAILURE );
    }

    // Main loop
    while( !glfwWindowShouldClose(window) )
    {
        // // Draw gears
        // draw();

        // // Update animation
        // animate();

        // Swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Terminate GLFW
    glfwTerminate();
    std::cout << "Hey, Zeus!\n";

    std::cout << add(34.5f, 34346.6f) << std :: endl;
    return 0;
}