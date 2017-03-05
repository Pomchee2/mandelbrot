#include <GLFW/glfw3.h>
#include <iostream>
#include "renderer.hpp"
#include "generator.hpp"

Renderer* Renderer::renderer = new Renderer();

Renderer::Renderer() {
}

Renderer* Renderer::get_renderer() {
  return Renderer::renderer;
}

void Renderer::initialise_renderer(float width, float height) {

  glClearColor(0, 0, 0, 1);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0, width, height, 0, -1, 1);
  glMatrixMode(GL_MODELVIEW);
}

void Renderer::render(Generator* generator) {
  glClear(GL_COLOR_BUFFER_BIT);
  glBegin(GL_POINTS);

  for (int i=0; i < (sizeof(generator->pixels)/sizeof(generator->pixels[0])); i++) {

    int x = (i % generator->width);
    int y = (i / generator->height); 
    glColor3f(generator->pixels[i], generator->pixels[i], generator->pixels[i]);

    glVertex2f(x, y);
  }

  glEnd();
}
