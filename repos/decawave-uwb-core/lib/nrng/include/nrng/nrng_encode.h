/**
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

#pragma once

#ifndef _NRNG_ENCODE_H_
#define _NRNG_ENCODE_H_

#include <stdlib.h>
#include <stdint.h>
#include <fcntl.h>
#include <unistd.h>
#include <nrng/nrng.h>

#ifdef __cplusplus
extern "C" {
#endif

// Value created to store the range data into so it can be accessed in apps/UltraWideBuffs_DataTransfer/src/main.c
extern char* TX_Data;


void nrng_encode(struct nrng_instance * nrng, uint8_t seq_num, uint16_t base);

#ifdef __cplusplus
}
#endif

#endif
