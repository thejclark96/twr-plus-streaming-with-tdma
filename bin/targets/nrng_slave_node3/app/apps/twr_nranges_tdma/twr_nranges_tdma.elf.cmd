arm-none-eabi-gcc
-o
/home/joel/Capstone/uwb-apps/bin/targets/nrng_slave_node3/app/apps/twr_nranges_tdma/twr_nranges_tdma.elf
-DAPP_NAME=twr_nranges_tdma
-DAPP_twr_nranges_tdma
-DARCH_NAME=cortex_m4
-DARCH_cortex_m4
-DBSP_NAME=dwm1001
-DBSP_dwm1001
-DMYNEWT=1
-DNRF52
-Os
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
-Wl,--start-group
/home/joel/Capstone/uwb-apps/bin/targets/nrng_slave_node3/app/apps/twr_nranges_tdma/apps_twr_nranges_tdma.a
/home/joel/Capstone/uwb-apps/bin/targets/nrng_slave_node3/app/boot/bootutil/boot_bootutil.a
/home/joel/Capstone/uwb-apps/bin/targets/nrng_slave_node3/app/boot/split/boot_split.a
/home/joel/Capstone/uwb-apps/bin/targets/nrng_slave_node3/app/crypto/mbedtls/crypto_mbedtls.a
/home/joel/Capstone/uwb-apps/bin/targets/nrng_slave_node3/app/encoding/base64/encoding_base64.a
/home/joel/Capstone/uwb-apps/bin/targets/nrng_slave_node3/app/encoding/cborattr/encoding_cborattr.a
/home/joel/Capstone/uwb-apps/bin/targets/nrng_slave_node3/app/encoding/tinycbor/encoding_tinycbor.a
/home/joel/Capstone/uwb-apps/bin/targets/nrng_slave_node3/app/fs/fcb/fs_fcb.a
/home/joel/Capstone/uwb-apps/bin/targets/nrng_slave_node3/app/hw/bsp/dwm1001/hw_bsp_dwm1001.a
/home/joel/Capstone/uwb-apps/bin/targets/nrng_slave_node3/app/hw/cmsis-core/hw_cmsis-core.a
/home/joel/Capstone/uwb-apps/bin/targets/nrng_slave_node3/app/hw/drivers/rtt/hw_drivers_rtt.a
/home/joel/Capstone/uwb-apps/bin/targets/nrng_slave_node3/app/hw/drivers/uwb/hw_drivers_uwb.a
/home/joel/Capstone/uwb-apps/bin/targets/nrng_slave_node3/app/hw/drivers/uwb/uwb_dw1000/hw_drivers_uwb_uwb_dw1000.a
/home/joel/Capstone/uwb-apps/bin/targets/nrng_slave_node3/app/hw/hal/hw_hal.a
/home/joel/Capstone/uwb-apps/bin/targets/nrng_slave_node3/app/hw/mcu/nordic/hw_mcu_nordic.a
/home/joel/Capstone/uwb-apps/bin/targets/nrng_slave_node3/app/hw/mcu/nordic/nrf52xxx/hw_mcu_nordic_nrf52xxx.a
/home/joel/Capstone/uwb-apps/bin/targets/nrng_slave_node3/app/kernel/os/kernel_os.a
/home/joel/Capstone/uwb-apps/bin/targets/nrng_slave_node3/app/lib/dsp/lib_dsp.a
/home/joel/Capstone/uwb-apps/bin/targets/nrng_slave_node3/app/lib/euclid/lib_euclid.a
/home/joel/Capstone/uwb-apps/bin/targets/nrng_slave_node3/app/lib/json/lib_json.a
/home/joel/Capstone/uwb-apps/bin/targets/nrng_slave_node3/app/lib/nmgr_uwb/lib_nmgr_uwb.a
/home/joel/Capstone/uwb-apps/bin/targets/nrng_slave_node3/app/lib/nrng/lib_nrng.a
/home/joel/Capstone/uwb-apps/bin/targets/nrng_slave_node3/app/lib/pan_utils/lib_pan_utils.a
/home/joel/Capstone/uwb-apps/bin/targets/nrng_slave_node3/app/lib/panmaster/lib_panmaster.a
/home/joel/Capstone/uwb-apps/bin/targets/nrng_slave_node3/app/lib/rng_math/lib_rng_math.a
/home/joel/Capstone/uwb-apps/bin/targets/nrng_slave_node3/app/lib/survey/lib_survey.a
/home/joel/Capstone/uwb-apps/bin/targets/nrng_slave_node3/app/lib/tdma/lib_tdma.a
/home/joel/Capstone/uwb-apps/bin/targets/nrng_slave_node3/app/lib/timescale/timescale_m4_hardfloat/libtimescale_core.a
/home/joel/Capstone/uwb-apps/bin/targets/nrng_slave_node3/app/lib/twr_ss_nrng/lib_twr_ss_nrng.a
/home/joel/Capstone/uwb-apps/bin/targets/nrng_slave_node3/app/lib/uwb_ccp/lib_uwb_ccp.a
/home/joel/Capstone/uwb-apps/bin/targets/nrng_slave_node3/app/lib/uwb_pan/lib_uwb_pan.a
/home/joel/Capstone/uwb-apps/bin/targets/nrng_slave_node3/app/lib/uwb_rng/lib_uwb_rng.a
/home/joel/Capstone/uwb-apps/bin/targets/nrng_slave_node3/app/lib/uwb_wcs/lib_uwb_wcs.a
/home/joel/Capstone/uwb-apps/bin/targets/nrng_slave_node3/app/libc/baselibc/libc_baselibc.a
/home/joel/Capstone/uwb-apps/bin/targets/nrng_slave_node3/app/mgmt/bcast_ota/mgmt_bcast_ota.a
/home/joel/Capstone/uwb-apps/bin/targets/nrng_slave_node3/app/mgmt/imgmgr/mgmt_imgmgr.a
/home/joel/Capstone/uwb-apps/bin/targets/nrng_slave_node3/app/mgmt/mgmt/mgmt_mgmt.a
/home/joel/Capstone/uwb-apps/bin/targets/nrng_slave_node3/app/mgmt/newtmgr/mgmt_newtmgr.a
/home/joel/Capstone/uwb-apps/bin/targets/nrng_slave_node3/app/mgmt/newtmgr/nmgr_os/mgmt_newtmgr_nmgr_os.a
/home/joel/Capstone/uwb-apps/bin/targets/nrng_slave_node3/app/net/ip/mn_socket/net_ip_mn_socket.a
/home/joel/Capstone/uwb-apps/bin/targets/nrng_slave_node3/app/porting/dpl_lib/porting_dpl_lib.a
/home/joel/Capstone/uwb-apps/bin/targets/nrng_slave_node3/app/sys/config/sys_config.a
/home/joel/Capstone/uwb-apps/bin/targets/nrng_slave_node3/app/sys/console/full/sys_console_full.a
/home/joel/Capstone/uwb-apps/bin/targets/nrng_slave_node3/app/sys/flash_map/sys_flash_map.a
/home/joel/Capstone/uwb-apps/bin/targets/nrng_slave_node3/app/sys/log/full/sys_log_full.a
/home/joel/Capstone/uwb-apps/bin/targets/nrng_slave_node3/app/sys/log/modlog/sys_log_modlog.a
/home/joel/Capstone/uwb-apps/bin/targets/nrng_slave_node3/app/sys/mfg/sys_mfg.a
/home/joel/Capstone/uwb-apps/bin/targets/nrng_slave_node3/app/sys/reboot/sys_reboot.a
/home/joel/Capstone/uwb-apps/bin/targets/nrng_slave_node3/app/sys/shell/sys_shell.a
/home/joel/Capstone/uwb-apps/bin/targets/nrng_slave_node3/app/sys/stats/full/sys_stats_full.a
/home/joel/Capstone/uwb-apps/bin/targets/nrng_slave_node3/app/sys/sysdown/sys_sysdown.a
/home/joel/Capstone/uwb-apps/bin/targets/nrng_slave_node3/app/sys/sysinit/sys_sysinit.a
/home/joel/Capstone/uwb-apps/bin/targets/nrng_slave_node3/app/sys/uwbcfg/sys_uwbcfg.a
/home/joel/Capstone/uwb-apps/bin/targets/nrng_slave_node3/app/time/datetime/time_datetime.a
/home/joel/Capstone/uwb-apps/bin/targets/nrng_slave_node3/app/util/cbmem/util_cbmem.a
/home/joel/Capstone/uwb-apps/bin/targets/nrng_slave_node3/app/util/crc/util_crc.a
/home/joel/Capstone/uwb-apps/bin/targets/nrng_slave_node3/app/util/mem/util_mem.a
/home/joel/Capstone/uwb-apps/bin/targets/nrng_slave_node3/app/util/parse/util_parse.a
/home/joel/Capstone/uwb-apps/bin/targets/nrng_slave_node3/app/util/rwlock/util_rwlock.a
/home/joel/Capstone/uwb-apps/bin/targets/nrng_slave_node3/app/util/streamer/util_streamer.a
/home/joel/Capstone/uwb-apps/bin/targets/nrng_slave_node3/generated/bin/nrng_slave_node3-sysinit-app.a
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
-Wl,-Map=/home/joel/Capstone/uwb-apps/bin/targets/nrng_slave_node3/app/apps/twr_nranges_tdma/twr_nranges_tdma.elf.map