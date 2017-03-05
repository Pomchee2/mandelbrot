#include "renderer.hpp"
#include "generator.hpp"
#include <GLFW/glfw3.h>
#include <cmath>
#include <iostream>
#include <Windows.h>

GLFWwindow* window = NULL;

void init_glfw(float screen_width, float screen_height) {
  glfwInit();

  window = glfwCreateWindow(screen_width, screen_height, "Fractal", NULL, NULL);

  glfwMakeContextCurrent(window);
}


static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
  Generator* generator = static_cast<Generator*>(glfwGetWindowUserPointer(window));

  glfwGetCursorPos(window, generator->xPos, generator->yPos);

  generator->realStart = generator->realStart + (yoffset * (generator->xPos[0]/generator->width) * ((generator->realEnd - generator->realStart)/10.0f));
  generator->realEnd = generator->realEnd - (yoffset * ((generator->width - generator->xPos[0])/generator->width) * ((generator->realEnd - generator->realStart)/10.0f));
  
  generator->imagStart = generator->imagStart + (yoffset * (generator->yPos[0]/generator->height) * ((generator->imagEnd - generator->imagStart)/10.0f));
  generator->imagEnd = generator->imagEnd - (yoffset * ((generator->height - generator->yPos[0])/generator->height) * ((generator->imagEnd - generator->imagStart)/10.0f));

  std::cout << generator->realStart << std::endl;
  std::cout << generator->realEnd << std::endl;
  std::cout << (generator->xPos[0]/generator->width) * ((generator->realEnd - generator->realStart)/10.0f) << std::endl;


  generator->needNewSet = true;
}

float* inMSet(float cReal, float cImag, int n) {
  float z[2] = {0.0f, 0.0f};

  for (int it = 0; it < n; it++) {
    float zRealTemp = ((z[0] * z[0]) - (z[1] * z[1]) + cReal);     // Mandelbrot
    float zImagTemp = (2 * z[0] * z[1] + cImag);

    // float zRealTemp = ((abs(z[0]) * abs(z[0])) - (abs(z[1]) * abs(z[1])) + cReal);      // Burning Ship
    // float zImagTemp = (2 * abs(z[0]) * abs(z[1]) + cImag);

    z[0] = zRealTemp; 
    z[1] = zImagTemp;



    if (std::pow(z[0], 2) + std::pow(z[1], 2) > 4) {
      float f[3] = {(float)it + 1.0f, z[0], z[1]};
      return f;

    }
  }
  float f[3] = {(float)n, 0.0f, 0.0f};
  return f;
}

int main(int argc, char** argv) {
  float screen_width = 500.0f;
  float screen_height = 500.0f;

  init_glfw(screen_width, screen_height);

  glfwSetScrollCallback(window, scroll_callback);


  Renderer* renderer = Renderer::get_renderer();
  renderer->initialise_renderer(screen_width, screen_height);
  Generator* generator = new Generator(screen_width, screen_height);

  glfwSetWindowUserPointer(window, generator);
  while(1){

    glfwPollEvents();


    //SYSTEMTIME start, end;

    //GetSystemTime(&start);
    if (generator->needNewSet) {
      generator->generate(*inMSet);
    }

    renderer->render(generator);

    glfwSwapBuffers(window);


    //GetSystemTime(&end);
    //std::cout << end.wMilliseconds-start.wMilliseconds << std::endl;
  }
}
