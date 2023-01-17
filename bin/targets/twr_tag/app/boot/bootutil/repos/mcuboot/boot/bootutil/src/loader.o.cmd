arm-none-eabi-gcc
-DAPP_NAME=twr_aloha
-DAPP_twr_aloha
-DARCH_NAME=cortex_m4
-DARCH_cortex_m4
-DBSP_NAME=dwm1001
-DBSP_dwm1001
-DMBEDTLS_USER_CONFIG_FILE="mbedtls/config_mynewt.h"
-DMCUBOOT_MYNEWT
-DMYNEWT=1
-DNRF52
-Og
-Wall
-Werror
-Wno-strict-aliasing
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
-Iapps/twr_aloha/include
-Iapps/twr_aloha/include/twr_aloha/arch/cortex_m4
-Iapps/twr_aloha/src
-Iapps/twr_aloha/src/arch/cortex_m4
-Ibin/targets/twr_tag/generated/include
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
-Irepos/apache-mynewt-core/hw/drivers/uart/include
-Irepos/apache-mynewt-core/hw/drivers/uart/include/uart/arch/cortex_m4
-Irepos/apache-mynewt-core/hw/drivers/uart/uart_hal/include
-Irepos/apache-mynewt-core/hw/drivers/uart/uart_hal/include/uart_hal/arch/cortex_m4
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
-Irepos/apache-mynewt-core/mgmt/newtmgr/transport/nmgr_shell/include
-Irepos/apache-mynewt-core/mgmt/newtmgr/transport/nmgr_shell/include/nmgr_shell/arch/cortex_m4
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
-Irepos/decawave-uwb-core/lib/cir/include
-Irepos/decawave-uwb-core/lib/cir/include/cir/arch/cortex_m4
-Irepos/decawave-uwb-core/lib/dsp/include
-Irepos/decawave-uwb-core/lib/dsp/include/dsp/arch/cortex_m4
-Irepos/decawave-uwb-core/lib/euclid/include
-Irepos/decawave-uwb-core/lib/euclid/include/euclid/arch/cortex_m4
-Irepos/decawave-uwb-core/lib/json/include
-Irepos/decawave-uwb-core/lib/json/include/json/arch/cortex_m4
-Irepos/decawave-uwb-core/lib/rng_math/include
-Irepos/decawave-uwb-core/lib/rng_math/include/rng_math/arch/cortex_m4
-Irepos/decawave-uwb-core/lib/twr_ds/include
-Irepos/decawave-uwb-core/lib/twr_ds/include/twr_ds/arch/cortex_m4
-Irepos/decawave-uwb-core/lib/twr_ds_ext/include
-Irepos/decawave-uwb-core/lib/twr_ds_ext/include/twr_ds_ext/arch/cortex_m4
-Irepos/decawave-uwb-core/lib/twr_ss/include
-Irepos/decawave-uwb-core/lib/twr_ss/include/twr_ss/arch/cortex_m4
-Irepos/decawave-uwb-core/lib/twr_ss_ack/include
-Irepos/decawave-uwb-core/lib/twr_ss_ack/include/twr_ss_ack/arch/cortex_m4
-Irepos/decawave-uwb-core/lib/twr_ss_ext/include
-Irepos/decawave-uwb-core/lib/twr_ss_ext/include/twr_ss_ext/arch/cortex_m4
-Irepos/decawave-uwb-core/lib/uwb_rng/include
-Irepos/decawave-uwb-core/lib/uwb_rng/include/uwb_rng/arch/cortex_m4
-Irepos/decawave-uwb-core/porting/dpl/mynewt/include
-Irepos/decawave-uwb-core/porting/dpl/mynewt/include/mynewt/arch/cortex_m4
-Irepos/decawave-uwb-core/porting/dpl_lib/include
-Irepos/decawave-uwb-core/porting/dpl_lib/include/dpl_lib/arch/cortex_m4
-Irepos/decawave-uwb-core/sys/uwbcfg/include
-Irepos/decawave-uwb-core/sys/uwbcfg/include/uwbcfg/arch/cortex_m4
-Irepos/decawave-uwb-dw1000/hw/drivers/uwb/uwb_dw1000/include
-Irepos/decawave-uwb-dw1000/hw/drivers/uwb/uwb_dw1000/include/uwb_dw1000/arch/cortex_m4
-Irepos/decawave-uwb-dw1000/lib/cir/cir_dw1000/include
-Irepos/decawave-uwb-dw1000/lib/cir/cir_dw1000/include/cir_dw1000/arch/cortex_m4
-Irepos/mcuboot/boot/bootutil/include
-Irepos/mcuboot/boot/bootutil/include/bootutil/arch/cortex_m4
-Irepos/mcuboot/boot/bootutil/src
-Irepos/mcuboot/boot/bootutil/src/arch/cortex_m4
-Irepos/mcuboot/boot/mynewt/flash_map_backend/include
-Irepos/mcuboot/boot/mynewt/flash_map_backend/include/flash_map_backend/arch/cortex_m4
-Irepos/mcuboot/boot/mynewt/mcuboot_config/include
-Irepos/mcuboot/boot/mynewt/mcuboot_config/include/mcuboot_config/arch/cortex_m4
-Itargets/twr_tag/include
-Itargets/twr_tag/include/twr_tag/arch/cortex_m4
-Itargets/twr_tag/src
-Itargets/twr_tag/src/arch/cortex_m4
-c
-o
/home/joel/Capstone/uwb-apps/bin/targets/twr_tag/app/boot/bootutil/repos/mcuboot/boot/bootutil/src/loader.o
repos/mcuboot/boot/bootutil/src/loader.c