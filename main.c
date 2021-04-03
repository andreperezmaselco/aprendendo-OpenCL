#include "mathematics/set.h"
#include "OpenCL/platform.h"

int main(void) {
  Set platforms = {0, NULL};
  allocOpenCLPlatforms(&platforms);
  printOpenCLInfo(&platforms);
  freeOpenCLPlatforms(&platforms);
  return 0;
}
