arm-none-eabi-gcc
-o
/home/joel/Capstone/uwb-apps/bin/targets/dwm1001_boot/app/boot/mynewt/mynewt.elf
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
-Wl,--start-group
/home/joel/Capstone/uwb-apps/bin/targets/dwm1001_boot/app/boot/bootutil/boot_bootutil.a
/home/joel/Capstone/uwb-apps/bin/targets/dwm1001_boot/app/boot/mynewt/boot_mynewt.a
/home/joel/Capstone/uwb-apps/bin/targets/dwm1001_boot/app/crypto/mbedtls/crypto_mbedtls.a
/home/joel/Capstone/uwb-apps/bin/targets/dwm1001_boot/app/hw/bsp/dwm1001/hw_bsp_dwm1001.a
/home/joel/Capstone/uwb-apps/bin/targets/dwm1001_boot/app/hw/cmsis-core/hw_cmsis-core.a
/home/joel/Capstone/uwb-apps/bin/targets/dwm1001_boot/app/hw/hal/hw_hal.a
/home/joel/Capstone/uwb-apps/bin/targets/dwm1001_boot/app/hw/mcu/nordic/hw_mcu_nordic.a
/home/joel/Capstone/uwb-apps/bin/targets/dwm1001_boot/app/hw/mcu/nordic/nrf52xxx/hw_mcu_nordic_nrf52xxx.a
/home/joel/Capstone/uwb-apps/bin/targets/dwm1001_boot/app/kernel/os/kernel_os.a
/home/joel/Capstone/uwb-apps/bin/targets/dwm1001_boot/app/libc/baselibc/libc_baselibc.a
/home/joel/Capstone/uwb-apps/bin/targets/dwm1001_boot/app/sys/flash_map/sys_flash_map.a
/home/joel/Capstone/uwb-apps/bin/targets/dwm1001_boot/app/sys/log/modlog/sys_log_modlog.a
/home/joel/Capstone/uwb-apps/bin/targets/dwm1001_boot/app/sys/log/stub/sys_log_stub.a
/home/joel/Capstone/uwb-apps/bin/targets/dwm1001_boot/app/sys/mfg/sys_mfg.a
/home/joel/Capstone/uwb-apps/bin/targets/dwm1001_boot/app/sys/sysdown/sys_sysdown.a
/home/joel/Capstone/uwb-apps/bin/targets/dwm1001_boot/app/sys/sysinit/sys_sysinit.a
/home/joel/Capstone/uwb-apps/bin/targets/dwm1001_boot/app/util/mem/util_mem.a
/home/joel/Capstone/uwb-apps/bin/targets/dwm1001_boot/app/util/rwlock/util_rwlock.a
/home/joel/Capstone/uwb-apps/bin/targets/dwm1001_boot/generated/bin/dwm1001_boot-sysinit-app.a
-Wl,--end-group
-Wl,--gc-sections
-lgcc
-nostartfiles
-specs=nosys.specs
-static
-T
/home/joel/Capstone/uwb-apps/repos/decawave-uwb-core/hw/bsp/dwm1001/boot-nrf52xxaa.ld
-T
/home/joel/Capstone/uwb-apps/repos/apache-mynewt-core/hw/mcu/nordic/nrf52xxx/nrf52.ld
-Wl,-Map=/home/joel/Capstone/uwb-apps/bin/targets/dwm1001_boot/app/boot/mynewt/mynewt.elf.map