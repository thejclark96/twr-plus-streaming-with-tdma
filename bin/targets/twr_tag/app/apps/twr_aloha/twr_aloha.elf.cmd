arm-none-eabi-gcc
-o
/home/joel/Capstone/uwb-apps/bin/targets/twr_tag/app/apps/twr_aloha/twr_aloha.elf
-DAPP_NAME=twr_aloha
-DAPP_twr_aloha
-DARCH_NAME=cortex_m4
-DARCH_cortex_m4
-DBSP_NAME=dwm1001
-DBSP_dwm1001
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
-Wl,--start-group
/home/joel/Capstone/uwb-apps/bin/targets/twr_tag/app/apps/twr_aloha/apps_twr_aloha.a
/home/joel/Capstone/uwb-apps/bin/targets/twr_tag/app/boot/bootutil/boot_bootutil.a
/home/joel/Capstone/uwb-apps/bin/targets/twr_tag/app/boot/split/boot_split.a
/home/joel/Capstone/uwb-apps/bin/targets/twr_tag/app/crypto/mbedtls/crypto_mbedtls.a
/home/joel/Capstone/uwb-apps/bin/targets/twr_tag/app/encoding/base64/encoding_base64.a
/home/joel/Capstone/uwb-apps/bin/targets/twr_tag/app/encoding/cborattr/encoding_cborattr.a
/home/joel/Capstone/uwb-apps/bin/targets/twr_tag/app/encoding/tinycbor/encoding_tinycbor.a
/home/joel/Capstone/uwb-apps/bin/targets/twr_tag/app/fs/fcb/fs_fcb.a
/home/joel/Capstone/uwb-apps/bin/targets/twr_tag/app/hw/bsp/dwm1001/hw_bsp_dwm1001.a
/home/joel/Capstone/uwb-apps/bin/targets/twr_tag/app/hw/cmsis-core/hw_cmsis-core.a
/home/joel/Capstone/uwb-apps/bin/targets/twr_tag/app/hw/drivers/uart/hw_drivers_uart.a
/home/joel/Capstone/uwb-apps/bin/targets/twr_tag/app/hw/drivers/uart/uart_hal/hw_drivers_uart_uart_hal.a
/home/joel/Capstone/uwb-apps/bin/targets/twr_tag/app/hw/drivers/uwb/hw_drivers_uwb.a
/home/joel/Capstone/uwb-apps/bin/targets/twr_tag/app/hw/drivers/uwb/uwb_dw1000/hw_drivers_uwb_uwb_dw1000.a
/home/joel/Capstone/uwb-apps/bin/targets/twr_tag/app/hw/hal/hw_hal.a
/home/joel/Capstone/uwb-apps/bin/targets/twr_tag/app/hw/mcu/nordic/hw_mcu_nordic.a
/home/joel/Capstone/uwb-apps/bin/targets/twr_tag/app/hw/mcu/nordic/nrf52xxx/hw_mcu_nordic_nrf52xxx.a
/home/joel/Capstone/uwb-apps/bin/targets/twr_tag/app/kernel/os/kernel_os.a
/home/joel/Capstone/uwb-apps/bin/targets/twr_tag/app/lib/cir/cir_dw1000/lib_cir_cir_dw1000.a
/home/joel/Capstone/uwb-apps/bin/targets/twr_tag/app/lib/cir/lib_cir.a
/home/joel/Capstone/uwb-apps/bin/targets/twr_tag/app/lib/dsp/lib_dsp.a
/home/joel/Capstone/uwb-apps/bin/targets/twr_tag/app/lib/euclid/lib_euclid.a
/home/joel/Capstone/uwb-apps/bin/targets/twr_tag/app/lib/json/lib_json.a
/home/joel/Capstone/uwb-apps/bin/targets/twr_tag/app/lib/rng_math/lib_rng_math.a
/home/joel/Capstone/uwb-apps/bin/targets/twr_tag/app/lib/twr_ds/lib_twr_ds.a
/home/joel/Capstone/uwb-apps/bin/targets/twr_tag/app/lib/twr_ds_ext/lib_twr_ds_ext.a
/home/joel/Capstone/uwb-apps/bin/targets/twr_tag/app/lib/twr_ss/lib_twr_ss.a
/home/joel/Capstone/uwb-apps/bin/targets/twr_tag/app/lib/twr_ss_ack/lib_twr_ss_ack.a
/home/joel/Capstone/uwb-apps/bin/targets/twr_tag/app/lib/twr_ss_ext/lib_twr_ss_ext.a
/home/joel/Capstone/uwb-apps/bin/targets/twr_tag/app/lib/uwb_rng/lib_uwb_rng.a
/home/joel/Capstone/uwb-apps/bin/targets/twr_tag/app/libc/baselibc/libc_baselibc.a
/home/joel/Capstone/uwb-apps/bin/targets/twr_tag/app/mgmt/imgmgr/mgmt_imgmgr.a
/home/joel/Capstone/uwb-apps/bin/targets/twr_tag/app/mgmt/mgmt/mgmt_mgmt.a
/home/joel/Capstone/uwb-apps/bin/targets/twr_tag/app/mgmt/newtmgr/mgmt_newtmgr.a
/home/joel/Capstone/uwb-apps/bin/targets/twr_tag/app/mgmt/newtmgr/nmgr_os/mgmt_newtmgr_nmgr_os.a
/home/joel/Capstone/uwb-apps/bin/targets/twr_tag/app/mgmt/newtmgr/transport/nmgr_shell/mgmt_newtmgr_transport_nmgr_shell.a
/home/joel/Capstone/uwb-apps/bin/targets/twr_tag/app/porting/dpl_lib/porting_dpl_lib.a
/home/joel/Capstone/uwb-apps/bin/targets/twr_tag/app/sys/config/sys_config.a
/home/joel/Capstone/uwb-apps/bin/targets/twr_tag/app/sys/console/full/sys_console_full.a
/home/joel/Capstone/uwb-apps/bin/targets/twr_tag/app/sys/flash_map/sys_flash_map.a
/home/joel/Capstone/uwb-apps/bin/targets/twr_tag/app/sys/log/full/sys_log_full.a
/home/joel/Capstone/uwb-apps/bin/targets/twr_tag/app/sys/log/modlog/sys_log_modlog.a
/home/joel/Capstone/uwb-apps/bin/targets/twr_tag/app/sys/mfg/sys_mfg.a
/home/joel/Capstone/uwb-apps/bin/targets/twr_tag/app/sys/reboot/sys_reboot.a
/home/joel/Capstone/uwb-apps/bin/targets/twr_tag/app/sys/shell/sys_shell.a
/home/joel/Capstone/uwb-apps/bin/targets/twr_tag/app/sys/stats/full/sys_stats_full.a
/home/joel/Capstone/uwb-apps/bin/targets/twr_tag/app/sys/sysdown/sys_sysdown.a
/home/joel/Capstone/uwb-apps/bin/targets/twr_tag/app/sys/sysinit/sys_sysinit.a
/home/joel/Capstone/uwb-apps/bin/targets/twr_tag/app/sys/uwbcfg/sys_uwbcfg.a
/home/joel/Capstone/uwb-apps/bin/targets/twr_tag/app/time/datetime/time_datetime.a
/home/joel/Capstone/uwb-apps/bin/targets/twr_tag/app/util/cbmem/util_cbmem.a
/home/joel/Capstone/uwb-apps/bin/targets/twr_tag/app/util/crc/util_crc.a
/home/joel/Capstone/uwb-apps/bin/targets/twr_tag/app/util/mem/util_mem.a
/home/joel/Capstone/uwb-apps/bin/targets/twr_tag/app/util/rwlock/util_rwlock.a
/home/joel/Capstone/uwb-apps/bin/targets/twr_tag/app/util/streamer/util_streamer.a
/home/joel/Capstone/uwb-apps/bin/targets/twr_tag/generated/bin/twr_tag-sysinit-app.a
-Wl,--end-group
-Wl,--gc-sections
-lgcc
-lm
-nostartfiles
-specs=nosys.specs
-static
-T
/home/joel/Capstone/uwb-apps/repos/decawave-uwb-core/hw/bsp/dwm1001/nrf52xxaa.ld
-T
/home/joel/Capstone/uwb-apps/repos/apache-mynewt-core/hw/mcu/nordic/nrf52xxx/nrf52.ld
-Wl,-Map=/home/joel/Capstone/uwb-apps/bin/targets/twr_tag/app/apps/twr_aloha/twr_aloha.elf.map