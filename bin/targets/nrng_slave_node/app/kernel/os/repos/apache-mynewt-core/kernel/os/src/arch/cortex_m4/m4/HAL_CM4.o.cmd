arm-none-eabi-gcc
-DAPP_NAME=twr_nranges_tdma
-DAPP_twr_nranges_tdma
-DARCH_NAME=cortex_m4
-DARCH_cortex_m4
-DBSP_NAME=dwm1001
-DBSP_dwm1001
-DMYNEWT=1
-DNRF52
-Og
-Wall
-Werror
-fdata-sections
-ffunction-sections
-fms-extensions
-fno-exceptions
-ggdb
-mcpu=cortex-m4
-mfloat-abi=hard
-mfpu=fpv4-sp-d16
-mthumb
-mthumb-interwork
-std=gnu11
-x
assembler-with-cpp
-Iapps/twr_nranges_tdma/include
-Iapps/twr_nranges_tdma/include/twr_nranges_tdma/arch/cortex_m4
-Iapps/twr_nranges_tdma/src
-Iapps/twr_nranges_tdma/src/arch/cortex_m4
-Ibin/targets/nrng_slave_node/generated/include
-Irepos/apache-mynewt-core/boot/split/include
-Irepos/apache-mynewt-core/boot/split/include/split/arch/cortex_m4
-Irepos/apache-mynewt-core/crypto/mbedtls/include
-Irepos/apache-mynewt-core/crypto/mbedtls/include/mbedtls/arch/cortex_m4
-Irepos/apache-mynewt-core/encoding/base64/include
-Irepos/apache-mynewt-core/encoding/base64/include/base64/arch/cortex_m4
-Irepos/apache-mynewt-core/encoding/cborattr/include
-Irepos/apache-mynewt-core/encoding/cborattr/include/cborattr/arch/cortex_m4
-Irepos/apache-mynewt-core/encoding/tinycbor/include
-Irepos/apache-mynewt-core/encoding/tinycbor/include/tinycbor/arch/cortex_m4
-Irepos/apache-mynewt-core/fs/fcb/include
-Irepos/apache-mynewt-core/fs/fcb/include/fcb/arch/cortex_m4
-Irepos/apache-mynewt-core/hw/cmsis-core/include
-Irepos/apache-mynewt-core/hw/cmsis-core/include/cmsis-core/arch/cortex_m4
-Irepos/apache-mynewt-core/hw/cmsis-core/src/ext
-Irepos/apache-mynewt-core/hw/drivers/rtt/include
-Irepos/apache-mynewt-core/hw/drivers/rtt/include/rtt/arch/cortex_m4
-Irepos/apache-mynewt-core/hw/hal/include
-Irepos/apache-mynewt-core/hw/hal/include/hal/arch/cortex_m4
-Irepos/apache-mynewt-core/hw/mcu/nordic/include
-Irepos/apache-mynewt-core/hw/mcu/nordic/include/nordic/arch/cortex_m4
-Irepos/apache-mynewt-core/hw/mcu/nordic/nrf52xxx/include
-Irepos/apache-mynewt-core/hw/mcu/nordic/nrf52xxx/include/nrf52xxx/arch/cortex_m4
-Irepos/apache-mynewt-core/hw/mcu/nordic/src/ext
-Irepos/apache-mynewt-core/hw/mcu/nordic/src/ext/nrfx
-Irepos/apache-mynewt-core/hw/mcu/nordic/src/ext/nrfx/drivers
-Irepos/apache-mynewt-core/hw/mcu/nordic/src/ext/nrfx/drivers/include
-Irepos/apache-mynewt-core/hw/mcu/nordic/src/ext/nrfx/drivers/src
-Irepos/apache-mynewt-core/hw/mcu/nordic/src/ext/nrfx/drivers/src/prs
-Irepos/apache-mynewt-core/hw/mcu/nordic/src/ext/nrfx/hal
-Irepos/apache-mynewt-core/hw/mcu/nordic/src/ext/nrfx/mdk
-Irepos/apache-mynewt-core/hw/mcu/nordic/src/ext/nrfx/soc
-Irepos/apache-mynewt-core/hw/mcu/nordic/src/ext/nrfx/templates
-Irepos/apache-mynewt-core/hw/mcu/nordic/src/ext/nrfx/templates/nRF51
-Irepos/apache-mynewt-core/hw/mcu/nordic/src/ext/nrfx/templates/nRF52810
-Irepos/apache-mynewt-core/hw/mcu/nordic/src/ext/nrfx/templates/nRF52811
-Irepos/apache-mynewt-core/hw/mcu/nordic/src/ext/nrfx/templates/nRF52832
-Irepos/apache-mynewt-core/hw/mcu/nordic/src/ext/nrfx/templates/nRF52840
-Irepos/apache-mynewt-core/hw/mcu/nordic/src/ext/nrfx/templates/nRF9160
-Irepos/apache-mynewt-core/kernel/os/include
-Irepos/apache-mynewt-core/kernel/os/include/os/arch/cortex_m4
-Irepos/apache-mynewt-core/kernel/os/src
-Irepos/apache-mynewt-core/kernel/os/src/arch/cortex_m4
-Irepos/apache-mynewt-core/libc/baselibc/include
-Irepos/apache-mynewt-core/libc/baselibc/include/baselibc/arch/cortex_m4
-Irepos/apache-mynewt-core/mgmt/imgmgr/include
-Irepos/apache-mynewt-core/mgmt/imgmgr/include/imgmgr/arch/cortex_m4
-Irepos/apache-mynewt-core/mgmt/mgmt/include
-Irepos/apache-mynewt-core/mgmt/mgmt/include/mgmt/arch/cortex_m4
-Irepos/apache-mynewt-core/mgmt/newtmgr/include
-Irepos/apache-mynewt-core/mgmt/newtmgr/include/newtmgr/arch/cortex_m4
-Irepos/apache-mynewt-core/mgmt/newtmgr/nmgr_os/include
-Irepos/apache-mynewt-core/mgmt/newtmgr/nmgr_os/include/nmgr_os/arch/cortex_m4
-Irepos/apache-mynewt-core/net/ip/mn_socket/include
-Irepos/apache-mynewt-core/net/ip/mn_socket/include/mn_socket/arch/cortex_m4
-Irepos/apache-mynewt-core/sys/config/include
-Irepos/apache-mynewt-core/sys/config/include/config/arch/cortex_m4
-Irepos/apache-mynewt-core/sys/console/full/include
-Irepos/apache-mynewt-core/sys/console/full/include/full/arch/cortex_m4
-Irepos/apache-mynewt-core/sys/defs/include
-Irepos/apache-mynewt-core/sys/defs/include/defs/arch/cortex_m4
-Irepos/apache-mynewt-core/sys/flash_map/include
-Irepos/apache-mynewt-core/sys/flash_map/include/flash_map/arch/cortex_m4
-Irepos/apache-mynewt-core/sys/log/common/include
-Irepos/apache-mynewt-core/sys/log/common/include/common/arch/cortex_m4
-Irepos/apache-mynewt-core/sys/log/full/include
-Irepos/apache-mynewt-core/sys/log/full/include/full/arch/cortex_m4
-Irepos/apache-mynewt-core/sys/log/modlog/include
-Irepos/apache-mynewt-core/sys/log/modlog/include/modlog/arch/cortex_m4
-Irepos/apache-mynewt-core/sys/mfg/include
-Irepos/apache-mynewt-core/sys/mfg/include/mfg/arch/cortex_m4
-Irepos/apache-mynewt-core/sys/reboot/include
-Irepos/apache-mynewt-core/sys/reboot/include/reboot/arch/cortex_m4
-Irepos/apache-mynewt-core/sys/shell/include
-Irepos/apache-mynewt-core/sys/shell/include/shell/arch/cortex_m4
-Irepos/apache-mynewt-core/sys/stats/full/include
-Irepos/apache-mynewt-core/sys/stats/full/include/full/arch/cortex_m4
-Irepos/apache-mynewt-core/sys/sys/include
-Irepos/apache-mynewt-core/sys/sys/include/sys/arch/cortex_m4
-Irepos/apache-mynewt-core/sys/sysdown/include
-Irepos/apache-mynewt-core/sys/sysdown/include/sysdown/arch/cortex_m4
-Irepos/apache-mynewt-core/sys/sysinit/include
-Irepos/apache-mynewt-core/sys/sysinit/include/sysinit/arch/cortex_m4
-Irepos/apache-mynewt-core/time/datetime/include
-Irepos/apache-mynewt-core/time/datetime/include/datetime/arch/cortex_m4
-Irepos/apache-mynewt-core/util/cbmem/include
-Irepos/apache-mynewt-core/util/cbmem/include/cbmem/arch/cortex_m4
-Irepos/apache-mynewt-core/util/crc/include
-Irepos/apache-mynewt-core/util/crc/include/crc/arch/cortex_m4
-Irepos/apache-mynewt-core/util/mem/include
-Irepos/apache-mynewt-core/util/mem/include/mem/arch/cortex_m4
-Irepos/apache-mynewt-core/util/parse/include
-Irepos/apache-mynewt-core/util/parse/include/parse/arch/cortex_m4
-Irepos/apache-mynewt-core/util/rwlock/include
-Irepos/apache-mynewt-core/util/rwlock/include/rwlock/arch/cortex_m4
-Irepos/apache-mynewt-core/util/streamer/include
-Irepos/apache-mynewt-core/util/streamer/include/streamer/arch/cortex_m4
-Irepos/decawave-uwb-core/hw/bsp/dwm1001/include
-Irepos/decawave-uwb-core/hw/bsp/dwm1001/include/bsp
-Irepos/decawave-uwb-core/hw/bsp/dwm1001/include/dwm1001/arch/cortex_m4
-Irepos/decawave-uwb-core/hw/bsp/dwm1001/src
-Irepos/decawave-uwb-core/hw/bsp/dwm1001/src/arch/cortex_m4
-Irepos/decawave-uwb-core/hw/drivers/uwb/include
-Irepos/decawave-uwb-core/hw/drivers/uwb/include/uwb/arch/cortex_m4
-Irepos/decawave-uwb-core/lib/dsp/include
-Irepos/decawave-uwb-core/lib/dsp/include/dsp/arch/cortex_m4
-Irepos/decawave-uwb-core/lib/euclid/include
-Irepos/decawave-uwb-core/lib/euclid/include/euclid/arch/cortex_m4
-Irepos/decawave-uwb-core/lib/json/include
-Irepos/decawave-uwb-core/lib/json/include/json/arch/cortex_m4
-Irepos/decawave-uwb-core/lib/nmgr_uwb/include
-Irepos/decawave-uwb-core/lib/nmgr_uwb/include/nmgr_uwb/arch/cortex_m4
-Irepos/decawave-uwb-core/lib/nrng/include
-Irepos/decawave-uwb-core/lib/nrng/include/nrng/arch/cortex_m4
-Irepos/decawave-uwb-core/lib/pan_utils/include
-Irepos/decawave-uwb-core/lib/pan_utils/include/pan_utils/arch/cortex_m4
-Irepos/decawave-uwb-core/lib/panmaster/include
-Irepos/decawave-uwb-core/lib/panmaster/include/panmaster/arch/cortex_m4
-Irepos/decawave-uwb-core/lib/rng_math/include
-Irepos/decawave-uwb-core/lib/rng_math/include/rng_math/arch/cortex_m4
-Irepos/decawave-uwb-core/lib/survey/include
-Irepos/decawave-uwb-core/lib/survey/include/survey/arch/cortex_m4
-Irepos/decawave-uwb-core/lib/tdma/include
-Irepos/decawave-uwb-core/lib/tdma/include/tdma/arch/cortex_m4
-Irepos/decawave-uwb-core/lib/twr_ss_nrng/include
-Irepos/decawave-uwb-core/lib/twr_ss_nrng/include/twr_ss_nrng/arch/cortex_m4
-Irepos/decawave-uwb-core/lib/uwb_ccp/include
-Irepos/decawave-uwb-core/lib/uwb_ccp/include/uwb_ccp/arch/cortex_m4
-Irepos/decawave-uwb-core/lib/uwb_pan/include
-Irepos/decawave-uwb-core/lib/uwb_pan/include/uwb_pan/arch/cortex_m4
-Irepos/decawave-uwb-core/lib/uwb_rng/include
-Irepos/decawave-uwb-core/lib/uwb_rng/include/uwb_rng/arch/cortex_m4
-Irepos/decawave-uwb-core/lib/uwb_wcs/include
-Irepos/decawave-uwb-core/lib/uwb_wcs/include/uwb_wcs/arch/cortex_m4
-Irepos/decawave-uwb-core/mgmt/bcast_ota/include
-Irepos/decawave-uwb-core/mgmt/bcast_ota/include/bcast_ota/arch/cortex_m4
-Irepos/decawave-uwb-core/porting/dpl/mynewt/include
-Irepos/decawave-uwb-core/porting/dpl/mynewt/include/mynewt/arch/cortex_m4
-Irepos/decawave-uwb-core/porting/dpl_lib/include
-Irepos/decawave-uwb-core/porting/dpl_lib/include/dpl_lib/arch/cortex_m4
-Irepos/decawave-uwb-core/sys/uwbcfg/include
-Irepos/decawave-uwb-core/sys/uwbcfg/include/uwbcfg/arch/cortex_m4
-Irepos/decawave-uwb-dw1000/hw/drivers/uwb/uwb_dw1000/include
-Irepos/decawave-uwb-dw1000/hw/drivers/uwb/uwb_dw1000/include/uwb_dw1000/arch/cortex_m4
-Irepos/mcuboot/boot/bootutil/include
-Irepos/mcuboot/boot/bootutil/include/bootutil/arch/cortex_m4
-Irepos/mcuboot/boot/mynewt/flash_map_backend/include
-Irepos/mcuboot/boot/mynewt/flash_map_backend/include/flash_map_backend/arch/cortex_m4
-Irepos/mcuboot/boot/mynewt/mcuboot_config/include
-Irepos/mcuboot/boot/mynewt/mcuboot_config/include/mcuboot_config/arch/cortex_m4
-Irepos/mynewt-timescale-lib/lib/timescale/include
-Irepos/mynewt-timescale-lib/lib/timescale/include/timescale/arch/cortex_m4
-Irepos/mynewt-timescale-lib/lib/timescale/timescale_m4_hardfloat/include
-Irepos/mynewt-timescale-lib/lib/timescale/timescale_m4_hardfloat/include/timescale_m4_hardfloat/arch/cortex_m4
-Itargets/nrng_slave_node/include
-Itargets/nrng_slave_node/include/nrng_slave_node/arch/cortex_m4
-Itargets/nrng_slave_node/src
-Itargets/nrng_slave_node/src/arch/cortex_m4
-c
-o
/home/joel/Capstone/uwb-apps/bin/targets/nrng_slave_node/app/kernel/os/repos/apache-mynewt-core/kernel/os/src/arch/cortex_m4/m4/HAL_CM4.o
repos/apache-mynewt-core/kernel/os/src/arch/cortex_m4/m4/HAL_CM4.s