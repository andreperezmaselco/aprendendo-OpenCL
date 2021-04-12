// Aprendendo OpenCL
#include "arguments.h"
#include "OpenCL/platform.h"

int main(int argc, char *argv[]) {
  // Analisar os argumentos.
  parseArguments(argc, argv);

  // Alocar, imprimir e desalocar as plataformas.
  allocOpenCLPlatforms();
  printOpenCLPlatforms();
  freeOpenCLPlatforms();

  return 0;
}
