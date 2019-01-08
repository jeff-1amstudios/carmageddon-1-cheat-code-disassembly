#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "framework/unity_fixture.h"
#include "../log/zf_log.h"

#include "../utility.h"
#include "../loading.h"
#include "../errors.h"
#include "../input.h"
#include "../controls.h"

TEST_GROUP(controls);

TEST_SETUP(controls) 
{ 
} 
 
TEST_TEAR_DOWN(controls) 
{ 
}

TEST(controls, CheckKevKeys)
{
  int i;
  char *input = "spamfritters";
  tU32 *result;
  for (i = 0; i < strlen(input); i++) {
    gLast_key_down = input[i] - 75; // 0x1e;
    result = KevKeyService();
    gLast_key_down = 0;
    result = KevKeyService();
  }
  sleep(1);
  gLast_key_down = 0;

  CheckKevKeys();
}


TEST_GROUP_RUNNER(controls) {
  RUN_TEST_CASE(controls, CheckKevKeys);
}