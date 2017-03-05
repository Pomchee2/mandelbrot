#pragma once

class Generator {
  public:

    int width;
    int height;

    double initRealStart;
    double initRealEnd;
    double initImagStart;
    double initImagEnd;

    double realStart;
    double realEnd;
    double imagStart;
    double imagEnd;

    int itcap;

    double xPos[1];
    double yPos[1];

    bool needNewSet;

    double pixels[1000000];

    void generate(double*(*pointFunction)(double, double, int));

    double* getComplexNumber(int x, int y, double realStart, double realEnd, double imagStart, double imagEnd, int width, int height);

    Generator(float width, float height);
};
