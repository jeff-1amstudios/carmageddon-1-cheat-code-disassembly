#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utility.h"
#include "loading.h"

void Debug_EncodeFile(char *pThe_path) {
  gDecodeThing = '@';
  EncodeFile(pThe_path);
}

void Debug_DecodeFile(char *pThe_path) {
  gDecodeThing = 0;
  EncodeFile(pThe_path);
}

int main(int argc, char * argv[]) {

  if (argc > 1) {
    if (strcmp("-encode", argv[1]) == 0) {
      Debug_EncodeFile(argv[2]);
    }
    else if (strcmp("-decode", argv[1]) == 0) {
      Debug_DecodeFile(argv[2]);
    }
  }
  
  // char a2[256];
  // char exp[256];
  // // int i = 0;
  // FILE *f = fopen("/Users/jeff/temp/GENERAL.TXT.ENC", "rb");
  // fgets(exp, 256, f);

  // // printf("exp: %s\n", exp);
  // DecodeLine2(&exp[1]);
  // printf("exp2: %s\n", exp);
  // return 0;

  // // FILE *f = fopen("test.txt", "wb");
  // // fputs(a2, f);
  // // fclose(f);
  // printf("%d %d\n", strlen(exp), strlen(a2));
  // int res = strcmp(a2, exp);
  // for (i = 0; i < strlen(a2); i++) {
  //   printf(" %02x", a2[i]);
  //   printf(" %02x", exp[i+1]);
  //   if (a2[i] != exp[i+1]) {
  //     printf("difference found at %d\n", i);
  //     return -1;
  //   }
  // }
  // printf("\n** all same ** \n");
}