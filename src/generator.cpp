#include "generator.hpp"
#include <math.h>
#include <stdlib.h>
#include <iostream>

Generator::Generator(float screenWidth, float screenHeight) {
  width = screenWidth;
  height = screenHeight;

  initRealStart = -2.0;
  initRealEnd = 2.0;
  initImagStart = -2.0;
  initImagEnd = 2.0;

  realStart = -2.0;
  realEnd = 2.0;
  imagStart = -2.0;
  imagEnd = 2.0;

  itcap = 256;

  memset(xPos, 0, sizeof(xPos));
  memset(yPos, 0, sizeof(yPos));

  needNewSet = true;

}

double* Generator::getComplexNumber(int x, int y, double realStart, double realEnd, double imagStart, double imagEnd, int width, int height) {

  double c[2] = {(realStart + (((double)x/width) * (realEnd - realStart))), (imagStart + (((double)y/height) * (imagEnd -imagStart)))};

  return c;
} 

void Generator::generate(double*(*pointFunction)(double, double, int)) {
  for (int pixel=0; pixel<(sizeof(pixels)/sizeof(pixels[0])); pixel++) {
    double* c = getComplexNumber((pixel % width), (int)(pixel / height), realStart, realEnd, imagStart, imagEnd, width, height);


    double* it = pointFunction(c[0], c[1], itcap);

    if ((int)it[0] == itcap) {
      pixels[pixel] = 0.0;
    }
    else {
      // pixels[pixel] = (it[0] + 1 - log(log(sqrt(it[1] * it[1] + it[2] * it[2]))/log(2))) / itcap;
      pixels[pixel] = (it[0]/itcap);
    }

    needNewSet = false;
  }
}
