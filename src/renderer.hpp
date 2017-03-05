#pragma once

class Generator; //Forward declaration

class Renderer {
  public:
    static Renderer* get_renderer();

    void initialise_renderer(float width, float height);

    void render(Generator* generator);

  private:

    static Renderer* renderer;

    Renderer();
};

