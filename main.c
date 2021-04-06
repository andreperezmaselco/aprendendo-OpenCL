#include "arguments.h"
#include "mathematics/set.h"
#include "OpenCL/platform.h"

Arguments arguments;

int main(int argc, char *argv[]) {
  // Allocate the arguments.
  allocArguments(argc, argv);

  // Allocate, print and free the platforms.
  Set platforms = {0, NULL};
  allocOpenCLPlatforms(&platforms);
  printOpenCLInfo(&platforms);
  freeOpenCLPlatforms(&platforms);
  return 0;
}
