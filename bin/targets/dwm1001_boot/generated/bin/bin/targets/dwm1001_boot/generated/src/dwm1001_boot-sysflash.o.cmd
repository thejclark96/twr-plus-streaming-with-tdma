arm-none-eabi-gcc
-DAPP_NAME=mynewt
-DAPP_mynewt
-DARCH_NAME=cortex_m4
-DARCH_cortex_m4
-DBSP_NAME=dwm1001
-DBSP_dwm1001
-DMCUBOOT_MYNEWT
-DMYNEWT=1
-DNRF52
-Os
-Wall
-Werror
-fdata-sections
-ffunction-sections
-fno-exceptions
-ggdb
-mcpu=cortex-m4
-mthumb
-mthumb-interwork
-Ibin/targets/dwm1001_boot/generated/include
-Ibin/targets/dwm1001_boot/generated/include/dwm1001_boot-sysinit-app/arch/cortex_m4
-Ibin/targets/dwm1001_boot/generated/src
-Ibin/targets/dwm1001_boot/generated/src/arch/cortex_m4
-Irepos/apache-mynewt-core/crypto/mbedtls/include
-Irepos/apache-mynewt-core/crypto/mbedtls/include/mbedtls/arch/cortex_m4
-Irepos/apache-mynewt-core/hw/cmsis-core/include
-Irepos/apache-mynewt-core/hw/cmsis-core/include/cmsis-core/arch/cortex_m4
-Irepos/apache-mynewt-core/hw/cmsis-core/src/ext
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
-Irepos/apache-mynewt-core/sys/console/stub/include
-Irepos/apache-mynewt-core/sys/console/stub/include/stub/arch/cortex_m4
-Irepos/apache-mynewt-core/sys/defs/include
-Irepos/apache-mynewt-core/sys/defs/include/defs/arch/cortex_m4
-Irepos/apache-mynewt-core/sys/flash_map/include
-Irepos/apache-mynewt-core/sys/flash_map/include/flash_map/arch/cortex_m4
-Irepos/apache-mynewt-core/sys/log/common/include
-Irepos/apache-mynewt-core/sys/log/common/include/common/arch/cortex_m4
-Irepos/apache-mynewt-core/sys/log/modlog/include
-Irepos/apache-mynewt-core/sys/log/modlog/include/modlog/arch/cortex_m4
-Irepos/apache-mynewt-core/sys/log/stub/include
-Irepos/apache-mynewt-core/sys/log/stub/include/stub/arch/cortex_m4
-Irepos/apache-mynewt-core/sys/mfg/include
-Irepos/apache-mynewt-core/sys/mfg/include/mfg/arch/cortex_m4
-Irepos/apache-mynewt-core/sys/sys/include
-Irepos/apache-mynewt-core/sys/sys/include/sys/arch/cortex_m4
-Irepos/apache-mynewt-core/sys/sysdown/include
-Irepos/apache-mynewt-core/sys/sysdown/include/sysdown/arch/cortex_m4
-Irepos/apache-mynewt-core/sys/sysinit/include
-Irepos/apache-mynewt-core/sys/sysinit/include/sysinit/arch/cortex_m4
-Irepos/apache-mynewt-core/util/mem/include
-Irepos/apache-mynewt-core/util/mem/include/mem/arch/cortex_m4
-Irepos/apache-mynewt-core/util/rwlock/include
-Irepos/apache-mynewt-core/util/rwlock/include/rwlock/arch/cortex_m4
-Irepos/decawave-uwb-core/hw/bsp/dwm1001/include
-Irepos/decawave-uwb-core/hw/bsp/dwm1001/include/bsp
-Irepos/decawave-uwb-core/hw/bsp/dwm1001/include/dwm1001/arch/cortex_m4
-Irepos/decawave-uwb-core/hw/bsp/dwm1001/src
-Irepos/decawave-uwb-core/hw/bsp/dwm1001/src/arch/cortex_m4
-Irepos/mcuboot/boot/bootutil/include
-Irepos/mcuboot/boot/bootutil/include/bootutil/arch/cortex_m4
-Irepos/mcuboot/boot/mynewt/flash_map_backend/include
-Irepos/mcuboot/boot/mynewt/flash_map_backend/include/flash_map_backend/arch/cortex_m4
-Irepos/mcuboot/boot/mynewt/include
-Irepos/mcuboot/boot/mynewt/include/mynewt/arch/cortex_m4
-Irepos/mcuboot/boot/mynewt/mcuboot_config/include
-Irepos/mcuboot/boot/mynewt/mcuboot_config/include/mcuboot_config/arch/cortex_m4
-Irepos/mcuboot/boot/mynewt/src
-Irepos/mcuboot/boot/mynewt/src/arch/cortex_m4
-Itargets/dwm1001_boot/include
-Itargets/dwm1001_boot/include/dwm1001_boot/arch/cortex_m4
-Itargets/dwm1001_boot/src
-Itargets/dwm1001_boot/src/arch/cortex_m4
-c
-o
/home/joel/Capstone/uwb-apps/bin/targets/dwm1001_boot/generated/bin/bin/targets/dwm1001_boot/generated/src/dwm1001_boot-sysflash.o
bin/targets/dwm1001_boot/generated/src/dwm1001_boot-sysflash.c