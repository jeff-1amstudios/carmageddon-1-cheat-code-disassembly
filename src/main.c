#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utility.h"
#include "loading.h"


extern void Tests_Run();

// void Debug_EncodeFile(char *pThe_path) {
//   gDecodeThing = '@';
//   EncodeFile(pThe_path);
// }

// void Debug_DecodeFile(char *pThe_path) {
//   gDecodeThing = 0;
//   EncodeFile(pThe_path);
// }

int main(int argc, char * argv[]) {
  if (argc > 1) {
    if (strcmp("-test", argv[1]) == 0) {
      Tests_Run();
    }
  }
}

