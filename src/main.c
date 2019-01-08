#include <string.h>
#include "test/framework/unity_fixture.h"

extern void Tests_Run();

int main(int argc, const char *argv[]) {
  if (argc > 1) {
    if (strcmp("-test", argv[1]) == 0) {
      return UnityMain(argc, argv, Tests_Run); 
    }
  }
  return 0;
}

