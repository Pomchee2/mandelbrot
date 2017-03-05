#include "generator.hpp"
#include <math.h>
#include <stdlib.h>
#include <iostream>

Generator::Generator(float screenWidth, float screenHeight) {
  width = screenWidth;
  height = screenHeight;

  initRealStart = -2.0f;
  initRealEnd = 2.0f;
  initImagStart = -2.0f;
  initImagEnd = 2.0f;

  realStart = -2.0f;
  realEnd = 2.0f;
  imagStart = -2.0f;
  imagEnd = 2.0f;

  itcap = 256;

  memset(xPos, 0, sizeof(xPos));
  memset(yPos, 0, sizeof(yPos));

  needNewSet = true;

}

float* Generator::getComplexNumber(int x, int y, float realStart, float realEnd, float imagStart, float imagEnd, int width, int height) {

  float c[2] = {(realStart + (((float)x/width) * (realEnd - realStart))), (imagStart + (((float)y/height) * (imagEnd -imagStart)))};

  return c;
} 

void Generator::generate(float*(*pointFunction)(float, float, int)) {
  for (int pixel=0; pixel<(sizeof(pixels)/sizeof(pixels[0])); pixel++) {
    float* c = getComplexNumber((pixel % width), (int)(pixel / height), realStart, realEnd, imagStart, imagEnd, width, height);


    float* it = pointFunction(c[0], c[1], itcap);

    if ((int)it[0] == itcap) {
      pixels[pixel] = 0.0f;
    }
    else {
      // pixels[pixel] = (it[0] + 1 - log(log(sqrt(it[1] * it[1] + it[2] * it[2]))/log(2))) / itcap;
      pixels[pixel] = (it[0]/itcap);
    }

    needNewSet = false;
  }
}
