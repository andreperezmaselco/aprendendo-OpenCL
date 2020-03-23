#include "mathematics/set.h"
#include "OpenCL/platform.h"

int main(int argc, char **argv) {
    Set platforms;
    allocOpenCLPlatforms(&platforms);
    printOpenCLInfo(&platforms);
    freeOpenCLPlatforms(&platforms);
    return 0;
}
