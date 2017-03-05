#include "renderer.hpp"
#include "generator.hpp"
#include <cmath>
#include <iostream>
#include <Windows.h>
#include <GLFW/glfw3.h>

GLFWwindow* window = NULL;

void init_glfw(int screen_width, int screen_height) {
  glfwInit();

  window = glfwCreateWindow(screen_width, screen_height, "Fractal", NULL, NULL);

  glfwMakeContextCurrent(window);
}


static void scroll_callback(GLFWwindow* w, double xoffset, double yoffset) {
  Generator* generator = static_cast<Generator*>(glfwGetWindowUserPointer(window));

  glfwGetCursorPos(w, generator->xPos, generator->yPos);

  generator->realStart = generator->realStart + (yoffset * (generator->xPos[0]/generator->width) * ((generator->realEnd - generator->realStart)/10.0f));
  generator->realEnd = generator->realEnd - (yoffset * ((generator->width - generator->xPos[0])/generator->width) * ((generator->realEnd - generator->realStart)/10.0f));
  
  generator->imagStart = generator->imagStart + (yoffset * (generator->yPos[0]/generator->height) * ((generator->imagEnd - generator->imagStart)/10.0f));
  generator->imagEnd = generator->imagEnd - (yoffset * ((generator->height - generator->yPos[0])/generator->height) * ((generator->imagEnd - generator->imagStart)/10.0f));



  generator->needNewSet = true;
}

double* inMSet(double cReal, double cImag, int n) {
  double z[2] = {0.0, 0.0};

  for (int it = 0; it < n; it++) {
    double zRealTemp = ((z[0] * z[0]) - (z[1] * z[1]) + cReal);     // Mandelbrot
    double zImagTemp = (2 * z[0] * z[1] + cImag);

    // double zRealTemp = ((abs(z[0]) * abs(z[0])) - (abs(z[1]) * abs(z[1])) + cReal);      // Burning Ship
    // double zImagTemp = (2 * abs(z[0]) * abs(z[1]) + cImag);

    z[0] = zRealTemp; 
    z[1] = zImagTemp;



    if (std::pow(z[0], 2) + std::pow(z[1], 2) > 4) {
      double f[3] = {(double)it + 1.0, z[0], z[1]};
      return f;

    }
  }
  double f[3] = {(double)n, 0.0, 0.0};
  return f;
}

int main() {
  float screen_width = 1000.0f;
  float screen_height = 1000.0f;

  init_glfw((int)screen_width, (int)screen_height);

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
