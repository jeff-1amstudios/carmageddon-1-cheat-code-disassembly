#include "framework/unity_fixture.h"

#include <string.h>
#include "../utility.h"

TEST_GROUP(utility);

TEST_SETUP(utility) 
{ 
} 
 
TEST_TEAR_DOWN(utility) 
{ 
}

TEST(utility, DecodeLine2)
{
    char buf[50];
    // first line of GENERAL.TXT, "@" prefix and line ending stripped
    char input[] = "\x29\x2a\x9c\x22\x61\x4d\x5e\x5f\x60\x34\x64\x57\x8d\x2b\x82\x7b\x33\x4c";
    strcpy(buf, input);
    DecodeLine2(buf);
    char expected[] = "0.01\t\t\t\t\t// Hither";
    TEST_ASSERT_EQUAL_STRING(expected, buf);
}

TEST(utility, EncodeLine2)
{
  char buf[50];
  strcpy(buf, "0.01\t\t\t\t\t// Hither");
  EncodeLine2(buf);
  char expected[] = "\x29\x2a\x9c\x22\x61\x4d\x5e\x5f\x60\x34\x64\x57\x8d\x2b\x82\x7b\x33\x4c";
  TEST_ASSERT_EQUAL_STRING(expected, buf);
}

TEST_GROUP_RUNNER(utility) {
  RUN_TEST_CASE(utility, DecodeLine2);
  RUN_TEST_CASE(utility, EncodeLine2);
}
