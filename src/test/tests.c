#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "framework/unity_fixture.h"
#include "../log/zf_log.h"

void Tests_Run() {
  zf_log_set_output_level(ZF_LOG_DEBUG);
  RUN_TEST_GROUP(controls);
  RUN_TEST_GROUP(utility);
  RUN_TEST_GROUP(input);
  RUN_TEST_GROUP(errors);
}