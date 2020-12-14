#include "mathematics/set.h"
#include "OpenCL/platform.h"

int main(const int argc, const char *const *const argv) {
  Set platforms;
  allocOpenCLPlatforms(&platforms);
  printOpenCLInfo(&platforms);
  freeOpenCLPlatforms(&platforms);
  return 0;
}
