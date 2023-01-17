/*
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */

#ifndef _SOFT_TEST_H
#define _SOFT_TEST_H

#include <stdio.h>
#include <string.h>
#include "softfloat/softfloat.h"

#include "os/mynewt.h"
#include "testutil/testutil.h"

#ifdef __cplusplus
extern "C" {
#endif

float64_t soft_fabs(float64_t val);
bool f64_same(float64_t a, float64_t b);
#ifdef __cplusplus
}
#endif
#endif /* _SOFT_TEST_H_ */
