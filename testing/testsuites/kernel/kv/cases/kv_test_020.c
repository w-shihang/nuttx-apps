/****************************************************************************
 * apps/testing/testsuites/kernel/kv/cases/kv_test_020.c
 *
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 *The ASF licenses this file to you under the Apache License, Version 2.0
 *(the "License"); you may not use this file except in compliance with
 *the License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 *WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or
 *implied.  See the License for the specific language governing
 *permissions and limitations under the License.
 *
 ****************************************************************************/

/****************************************************************************
 * Included Files
 ****************************************************************************/
#include <nuttx/config.h>
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <syslog.h>
#include <stdint.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdio.h>
#include <cmocka.h>
#include <time.h>
#include <string.h>
#include "KvTest.h"
#include "kvdb.h"

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: test_nuttx_kv20
 ****************************************************************************/

void test_nuttx_kv20(FAR void **state)
{
  char data[TEST_VALUE_LENGTH] =
  {
    0
  };

  struct timespec t_start;
  struct timespec t_end;
  long timedif;
  int ret;
  char key[32] =
  {
    0
  };

  int test_round = 3000;

  sprintf(data, "test_data_%s", __func__);
  clock_gettime(CLOCK_MONOTONIC, &t_start);
  for (int i = 0; i < test_round; i++)
    {
      sprintf(key, "%s%s-%d", KV_TEST_PREFIX, __func__, i);
      ret = property_set(key, data);
      assert_int_equal(ret, 0);
    }

  clock_gettime(CLOCK_MONOTONIC, &t_end);
  timedif = 1000000 * (t_end.tv_sec - t_start.tv_sec) +
            (t_end.tv_nsec - t_start.tv_nsec) / 1000;
  syslog(LOG_INFO, "set data:%d takes:%ld microseconds\n", test_round,
         timedif);

  for (int k = 0; k < test_round; k++)
    {
      sprintf(key, "%s%s-%d", KV_TEST_PREFIX, __func__, k);
      ret = property_delete(key);
      assert_int_equal(ret, 0);
    }
}
