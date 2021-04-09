// Aprendendo OpenCL
#include "arguments.h"
#include "mathematics/set.h"
#include "OpenCL/platform.h"

Arguments arguments;

int main(int argc, char *argv[]) {
  // Alocar os argumentos.
  allocArguments(argc, argv);

  // Alocar, imprimir e desalocar as plataformas.
  Set platforms = {0, NULL};
  allocOpenCLPlatforms(&platforms);
  printOpenCLPlatforms(&platforms);
  freeOpenCLPlatforms(&platforms);
  return 0;
}
