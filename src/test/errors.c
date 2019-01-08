#include "framework/unity_fixture.h"

#include <string.h>
#include "../errors.h"

extern int TEST_really_exit;

TEST_GROUP(errors);

TEST_SETUP(errors) 
{ 
} 
 
TEST_TEAR_DOWN(errors) 
{
}

TEST(errors, FatalError)
{
  TEST_really_exit = 0;
  FatalError(0x6b, "hello", "world");
}

TEST_GROUP_RUNNER(errors) {
  RUN_TEST_CASE(errors, FatalError);
}