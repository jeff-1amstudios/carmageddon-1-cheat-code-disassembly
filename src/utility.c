#include "utility.h"
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "errors.h"
#include "loading.h"
#include "pc/sys.h"

int gEncryption_method = 1;
char gLong_key[] = {0x6C, 0x1B, 0x99, 0x5F, 0xB9, 0xCD, 0x5F, 0x13, 0xCB, 0x4, 0x20, 0x0E, 0x5E, 0x1C, 0xA1, 0x0E};
char gOther_long_key[] = {0x67, 0xA8, 0xD6, 0x26, 0xB6, 0xDD, 0x45, 0x1B, 0x32, 0x7E, 0x22, 0x13, 0x15, 0xC2, 0x94, 0x37};

// void EncodeAllFilesInDirectory (char *pThe_path) {
//   char *pThe_path;
//   char s[256];
// }

void StripCR (char *s) {
  char *pos;
  pos = s;
  while (*pos != 0) {
    if (*pos == '\r' || *pos == '\n') {
      *pos = 0;
      break;
    }
    pos++;
  }
}


void EncodeFileWrapper (char *pThe_path) {
  int len = strlen(pThe_path);

  if (strcmp(&pThe_path[len - 4], ".TXT") == 0) {
    return;
  }
  if (strcmp(pThe_path, "DKEYMAP0.TXT") == 0) {
    return;
  }
  if (strcmp(pThe_path, "DKEYMAP1.TXT") == 0) {
    return;
  }
  if (strcmp(pThe_path, "DKEYMAP2.TXT") == 0) {
    return;
  }
  if (strcmp(pThe_path, "DKEYMAP3.TXT") == 0) {
    return;
  }
  if (strcmp(pThe_path, "KEYMAP_0.TXT") == 0) {
    return;
  }
  if (strcmp(pThe_path, "KEYMAP_1.TXT") == 0) {
    return;
  }
  if (strcmp(pThe_path, "KEYMAP_2.TXT") == 0) {
    return;
  }
  if (strcmp(pThe_path, "KEYMAP_3.TXT") == 0) {
    return;
  }
  if (strcmp(pThe_path, "OPTIONS.TXT") == 0) {
    return;
  }
  if (strcmp(pThe_path, "KEYNAMES.TXT") == 0) {
    return;
  }
  if (strcmp(pThe_path, "KEYMAP.TXT") == 0) {
    return;
  }
  if (strcmp(pThe_path, "PATHS.TXT") == 0) {
    return;
  }

  EncodeFile(pThe_path);
}


void EncodeFile(char *pThe_path)
{
  char line[257];
  char new_file[256];
  FILE *f;
  FILE *d;
  char *s;
  char *result;
  int ch;
  int decode;
  int len;
  int count;

  len = strlen(pThe_path);
  strcpy(new_file, pThe_path);
  strcat(new_file, "ENC");

  f = fopen(pThe_path, "rt");
  if (!f) {
    FatalError(0x6b, new_file);
  }

  ch = fgetc(f);
  ungetc(ch, f);

  if (gDecodeThing == '@' && gDecodeThing == (char)ch) {
    fclose(f);
    return;
  }

  d = fopen(new_file, "wb");
  if (!d) {
    FatalError(0x6b, new_file);
  }

  result = &line[1];

  while (!feof(f)) {
    fgets(result, 256, f);

    if (ch == '@') {
      decode = 1;
    } else {
      decode = 0;
      s = &result[1];
      while (line[0] == ' ' || line[0] == '\t') {
        memmove(result, s, strlen(result));
      }
    }

    if (decode == 0) {
      EncodeLine2(result + decode);
    } else {
      DecodeLine2(result + decode);
    }

    line[0] = '@';
    fputs(&line[decode*2], d);
    count = -1;
    ch = fgetc(f);
    while (ch == '\r' || ch == '\n') {
      count++;
    }
    if (count >= 2) {
      fputc(0x0d, d);
      fputc(0x0a, d);
    }
    fputc(0x0d, d);
    fputc(0x0a, d);

    if (ch != -1) {
      ungetc(ch, f);
    }
  }
  fclose(f);
  fclose(d);

  PDFileUnlock(pThe_path);
  unlink(pThe_path);
  rename(new_file, pThe_path);
}

void EncodeLine2(char *pS)
{
  int len;
  int seed;
  int i;
  int count;
  unsigned char c;
  char *key;

  len = strlen(pS);
  count = 0;
  key = gLong_key;
  while ( len > 0 && (pS[len - 1] == 13 || pS[len - 1] == 10))
  {
    --len;
    pS[len] = 0;
  }

  seed = len % 16;
  
  for ( i = 0; i < len; ++pS )
  {
    if ( count == 2 )
      key = gOther_long_key;
    if ( *pS == '/' )
    {
      ++count;
    }
    else {
      count = 0;
    }
    if ( *pS == '\t' ) {
      *pS = 0x80;
    }
    c = *pS - 0x20;
    if (!(c & 0x80)) {
      c = c ^ (key[seed] & 0x7F);
      c += 0x20;
    }
    seed += 7;
    seed = seed % 16;
    
    if ( c == 0x80 ) {
      c = '\t';
    }
    *pS = c;
    ++i;
  }
}

void DecodeLine2(char *pS)
{
  int len;
  int seed;
  int i;
  int count;
  unsigned char c;
  char *key;

  len = strlen(pS);
  count = 0;
  key = gLong_key;
  while ( len > 0 && (pS[len - 1] == 13 || pS[len - 1] == 10))
  {
    --len;
    pS[len] = 0;
  }
  seed = len % 16;
  for ( i = 0; i < len; i++)
  {
    c = pS[i];
    if (i >= 2) {
      if (pS[i - 1] == '/' && pS[i - 2] == '/') {
        key = gOther_long_key;
      }
    }
    if (gEncryption_method == 1) 
    { 
      if ( c == '\t' ) {
        c = 0x80;
      }
      c -= 0x20;
      if (!(c & 0x80)) {
        c = (c ^ key[seed]) & 0x7f;
        c += 0x20;
      }
      seed += 7;
      seed = seed % 16;
      
      if ( c == 0x80 ) {
        c = '\t';
      }
    }
    else {
      if (c == '\t') {
        c = 0x9f;
      }
      c -= 0x20;
      c = (c ^ key[seed]) & 0x7f;
      c += 0x20;

      seed += 7;
      seed = seed % 16;
      
      if ( c == 0x9f ) {
        c = '\t';
      }
    }
    pS[i] = c;
  }
}
