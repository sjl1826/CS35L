#include <math.h>
#include <stdio.h>

int main() {
  double num = 3.0, squareRoot, cosine;
  squareRoot = sqrt(num);
  cosine = cos(squareRoot);
  printf("%.17g", cosine);
  return 0;
}
