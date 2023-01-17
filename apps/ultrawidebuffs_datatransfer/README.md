<!--
#
# Licensed to the Apache Software Foundation (ASF) under one
# or more contributor license agreements.  See the NOTICE file
# distributed with this work for additional information
# regarding copyright ownership.  The ASF licenses this file
# to you under the Apache License, Version 2.0 (the
# "License"); you may not use this file except in compliance
# with the License.  You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing,
# software distributed under the License is distributed on an
# "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
#  KIND, either express or implied.  See the License for the
# specific language governing permissions and limitations
# under the License.
#
-->

# Ultrawide Buffs [-] Data Transfer


## Overview

The streaming example makes use of the UWB transport layer for stream data.

## Setup

1. Flash ultrawidebuffs_datatransfer apps

In this example the tx_stream streams transmits a buffer at 3.9Mbps to the rx_stream. The rx_stream is the designated clock master. The example also enables bleprph package so stats information can be view through AdaFruit Mynewt Manager App or in the CLI.


```no-highlight
// RX
newt target create ultrawidebuffs_datatransfer
newt target set ultrawidebuffs_datatransfer app=apps/ultrawidebuffs_datatransfer
newt target set ultrawidebuffs_datatransfer bsp=@decawave-uwb-core/hw/bsp/dwm1001
newt target set ultrawidebuffs_datatransfer build_profile=debug
newt target amend ultrawidebuffs_datatransfer syscfg=UWB_TRANSPORT_ROLE=0:OS_LATENCY=1000:CONSOLE_UART_BAUD=115200:CONSOLE_UART=0:CONSOLE_RTT=1:DW1000_SYS_STATUS_BACKTRACE_LEN=128
newt run ultrawidebuffs_datatransfer 0

```

```no-highlight
// TX
newt target create ultrawidebuffs_datatransfer
newt target set ultrawidebuffs_datatransfer app=apps/ultrawidebuffs_datatransfer
newt target set ultrawidebuffs_datatransfer bsp=@decawave-uwb-core/hw/bsp/dwm1001
newt target set ultrawidebuffs_datatransfer build_profile=optimized
newt target amend ultrawidebuffs_datatransfer syscfg=UWB_TRANSPORT_ROLE=1:OS_LATENCY=1000:CONSOLE_UART_BAUD=115200:CONSOLE_UART=0:CONSOLE_RTT=1:DW1000_SYS_STATUS_BACKTRACE_LEN=128
newt build ultrawidebuffs_datatransfer
newt create-image ultrawidebuffs_datatransfer 1.0.0
newt load ultrawidebuffs_datatransfer 0

```

