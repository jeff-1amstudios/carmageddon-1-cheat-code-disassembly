#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "emu_test.h"
#include "../utility.h"
#include "../loading.h"
#include "../errors.h"

extern int TEST_really_exit;

EMU_TEST(DecodeLine2)
{
    char buf[50];
    // first line of GENERAL.TXT, "@" prefix and line ending stripped
    char input[] = "\x29\x2a\x9c\x22\x61\x4d\x5e\x5f\x60\x34\x64\x57\x8d\x2b\x82\x7b\x33\x4c";
    strcpy(buf, input);
    DecodeLine2(buf);
    char expected[] = "0.01\t\t\t\t\t// Hither";
    EMU_EXPECT_STREQ(expected, buf);
    EMU_END_TEST();
}

EMU_TEST(EncodeLine2) 
{
  char buf[50];
  strcpy(buf, "0.01\t\t\t\t\t// Hither");
  EncodeLine2(buf);
  char expected[] = "\x29\x2a\x9c\x22\x61\x4d\x5e\x5f\x60\x34\x64\x57\x8d\x2b\x82\x7b\x33\x4c";
  EMU_EXPECT_STREQ(expected, buf);
  EMU_END_TEST();
}

EMU_TEST(FatalError)
{
  TEST_really_exit = 0;
  FatalError(0x6b, "hello", "world");
  EMU_END_TEST();
}

void Tests_Run() {
  EMU_RUN(DecodeLine2);
  EMU_RUN(EncodeLine2);
  EMU_RUN(FatalError);
}