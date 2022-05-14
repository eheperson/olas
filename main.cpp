#include <iostream>
#include <OLASConfig.h>

#include<GL/glew.h>
#include<GL/glut.h>

#include <GLFW/glfw3.h>

#define GLEW_STATIC

#ifdef USE_ADDER
    #include <adder.h>
#endif


int main(int argc, char* argv[]){

    std::cout << "Hey, Zeus!\n";

    #ifdef USE_ADDER
        std::cout << add(22.2f, 22222.2f) << std :: endl;
    #else
        std::cout << 33.3f + 33333.3f << std :: endl;
    #endif

    GLFWwindow* window;
    int width, height;

    std :: cout << argv[0];
    std :: cout << "Version : ";
    std :: cout << OLAS_VERSION_MAJOR;
    std :: cout << ".";
    std :: cout << OLAS_VERSION_MINOR;
    std :: cout << std::endl;

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
    return 0;
}