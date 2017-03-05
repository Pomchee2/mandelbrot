#pragma once

class Generator {
  public:

    int width;
    int height;

    float initRealStart;
    float initRealEnd;
    float initImagStart;
    float initImagEnd;

    float realStart;
    float realEnd;
    float imagStart;
    float imagEnd;

    int itcap;

    double xPos[1];
    double yPos[1];

    bool needNewSet;

    float pixels[250000];

    void generate(float*(*pointFunction)(float, float, int));

    float* getComplexNumber(int x, int y, float realStart, float realEnd, float imagStart, float imagEnd, int width, int height);

    Generator(float width, float height);
};
