arm-none-eabi-gcc
-o
/home/joel/Capstone/uwb-apps/bin/targets/ultrawidebuffs_datatransfer/app/apps/ultrawidebuffs_datatransfer/ultrawidebuffs_datatransfer.elf
-DAPP_NAME=ultrawidebuffs_datatransfer
-DAPP_ultrawidebuffs_datatransfer
-DARCH_NAME=cortex_m4
-DARCH_cortex_m4
-DBSP_NAME=dwm1001
-DBSP_dwm1001
-DMYNEWT=1
-DNRF52
-Os
-Wall
-Werror
-Wno-strict-aliasing
-fdata-sections
-ffunction-sections
-fms-extensions
-fno-exceptions
-g
-ggdb
-mcpu=cortex-m4
-mfloat-abi=hard
-mfpu=fpv4-sp-d16
-mthumb
-mthumb-interwork
-std=gnu11
-w
-Wl,--start-group
/home/joel/Capstone/uwb-apps/bin/targets/ultrawidebuffs_datatransfer/app/apps/ultrawidebuffs_datatransfer/apps_ultrawidebuffs_datatransfer.a
/home/joel/Capstone/uwb-apps/bin/targets/ultrawidebuffs_datatransfer/app/boot/bootutil/boot_bootutil.a
/home/joel/Capstone/uwb-apps/bin/targets/ultrawidebuffs_datatransfer/app/boot/split/boot_split.a
/home/joel/Capstone/uwb-apps/bin/targets/ultrawidebuffs_datatransfer/app/crypto/mbedtls/crypto_mbedtls.a
/home/joel/Capstone/uwb-apps/bin/targets/ultrawidebuffs_datatransfer/app/encoding/base64/encoding_base64.a
/home/joel/Capstone/uwb-apps/bin/targets/ultrawidebuffs_datatransfer/app/encoding/cborattr/encoding_cborattr.a
/home/joel/Capstone/uwb-apps/bin/targets/ultrawidebuffs_datatransfer/app/encoding/tinycbor/encoding_tinycbor.a
/home/joel/Capstone/uwb-apps/bin/targets/ultrawidebuffs_datatransfer/app/fs/fcb/fs_fcb.a
/home/joel/Capstone/uwb-apps/bin/targets/ultrawidebuffs_datatransfer/app/hw/bsp/dwm1001/hw_bsp_dwm1001.a
/home/joel/Capstone/uwb-apps/bin/targets/ultrawidebuffs_datatransfer/app/hw/cmsis-core/hw_cmsis-core.a
/home/joel/Capstone/uwb-apps/bin/targets/ultrawidebuffs_datatransfer/app/hw/drivers/rtt/hw_drivers_rtt.a
/home/joel/Capstone/uwb-apps/bin/targets/ultrawidebuffs_datatransfer/app/hw/drivers/uwb/hw_drivers_uwb.a
/home/joel/Capstone/uwb-apps/bin/targets/ultrawidebuffs_datatransfer/app/hw/drivers/uwb/uwb_dw1000/hw_drivers_uwb_uwb_dw1000.a
/home/joel/Capstone/uwb-apps/bin/targets/ultrawidebuffs_datatransfer/app/hw/hal/hw_hal.a
/home/joel/Capstone/uwb-apps/bin/targets/ultrawidebuffs_datatransfer/app/hw/mcu/nordic/hw_mcu_nordic.a
/home/joel/Capstone/uwb-apps/bin/targets/ultrawidebuffs_datatransfer/app/hw/mcu/nordic/nrf52xxx/hw_mcu_nordic_nrf52xxx.a
/home/joel/Capstone/uwb-apps/bin/targets/ultrawidebuffs_datatransfer/app/kernel/os/kernel_os.a
/home/joel/Capstone/uwb-apps/bin/targets/ultrawidebuffs_datatransfer/app/lib/dsp/lib_dsp.a
/home/joel/Capstone/uwb-apps/bin/targets/ultrawidebuffs_datatransfer/app/lib/euclid/lib_euclid.a
/home/joel/Capstone/uwb-apps/bin/targets/ultrawidebuffs_datatransfer/app/lib/json/lib_json.a
/home/joel/Capstone/uwb-apps/bin/targets/ultrawidebuffs_datatransfer/app/lib/nrng/lib_nrng.a
/home/joel/Capstone/uwb-apps/bin/targets/ultrawidebuffs_datatransfer/app/lib/rng_math/lib_rng_math.a
/home/joel/Capstone/uwb-apps/bin/targets/ultrawidebuffs_datatransfer/app/lib/tdma/lib_tdma.a
/home/joel/Capstone/uwb-apps/bin/targets/ultrawidebuffs_datatransfer/app/lib/timescale/timescale_m4_hardfloat/libtimescale_core.a
/home/joel/Capstone/uwb-apps/bin/targets/ultrawidebuffs_datatransfer/app/lib/twr_ss_nrng/lib_twr_ss_nrng.a
/home/joel/Capstone/uwb-apps/bin/targets/ultrawidebuffs_datatransfer/app/lib/uwb_ccp/lib_uwb_ccp.a
/home/joel/Capstone/uwb-apps/bin/targets/ultrawidebuffs_datatransfer/app/lib/uwb_rng/lib_uwb_rng.a
/home/joel/Capstone/uwb-apps/bin/targets/ultrawidebuffs_datatransfer/app/lib/uwb_transport/lib_uwb_transport.a
/home/joel/Capstone/uwb-apps/bin/targets/ultrawidebuffs_datatransfer/app/lib/uwb_wcs/lib_uwb_wcs.a
/home/joel/Capstone/uwb-apps/bin/targets/ultrawidebuffs_datatransfer/app/libc/baselibc/libc_baselibc.a
/home/joel/Capstone/uwb-apps/bin/targets/ultrawidebuffs_datatransfer/app/mgmt/imgmgr/mgmt_imgmgr.a
/home/joel/Capstone/uwb-apps/bin/targets/ultrawidebuffs_datatransfer/app/mgmt/mgmt/mgmt_mgmt.a
/home/joel/Capstone/uwb-apps/bin/targets/ultrawidebuffs_datatransfer/app/mgmt/newtmgr/mgmt_newtmgr.a
/home/joel/Capstone/uwb-apps/bin/targets/ultrawidebuffs_datatransfer/app/mgmt/newtmgr/nmgr_os/mgmt_newtmgr_nmgr_os.a
/home/joel/Capstone/uwb-apps/bin/targets/ultrawidebuffs_datatransfer/app/mgmt/newtmgr/transport/nmgr_shell/mgmt_newtmgr_transport_nmgr_shell.a
/home/joel/Capstone/uwb-apps/bin/targets/ultrawidebuffs_datatransfer/app/porting/dpl_lib/porting_dpl_lib.a
/home/joel/Capstone/uwb-apps/bin/targets/ultrawidebuffs_datatransfer/app/sys/config/sys_config.a
/home/joel/Capstone/uwb-apps/bin/targets/ultrawidebuffs_datatransfer/app/sys/console/full/sys_console_full.a
/home/joel/Capstone/uwb-apps/bin/targets/ultrawidebuffs_datatransfer/app/sys/flash_map/sys_flash_map.a
/home/joel/Capstone/uwb-apps/bin/targets/ultrawidebuffs_datatransfer/app/sys/log/full/sys_log_full.a
/home/joel/Capstone/uwb-apps/bin/targets/ultrawidebuffs_datatransfer/app/sys/log/modlog/sys_log_modlog.a
/home/joel/Capstone/uwb-apps/bin/targets/ultrawidebuffs_datatransfer/app/sys/mfg/sys_mfg.a
/home/joel/Capstone/uwb-apps/bin/targets/ultrawidebuffs_datatransfer/app/sys/reboot/sys_reboot.a
/home/joel/Capstone/uwb-apps/bin/targets/ultrawidebuffs_datatransfer/app/sys/shell/sys_shell.a
/home/joel/Capstone/uwb-apps/bin/targets/ultrawidebuffs_datatransfer/app/sys/stats/full/sys_stats_full.a
/home/joel/Capstone/uwb-apps/bin/targets/ultrawidebuffs_datatransfer/app/sys/sysdown/sys_sysdown.a
/home/joel/Capstone/uwb-apps/bin/targets/ultrawidebuffs_datatransfer/app/sys/sysinit/sys_sysinit.a
/home/joel/Capstone/uwb-apps/bin/targets/ultrawidebuffs_datatransfer/app/sys/uwbcfg/sys_uwbcfg.a
/home/joel/Capstone/uwb-apps/bin/targets/ultrawidebuffs_datatransfer/app/time/datetime/time_datetime.a
/home/joel/Capstone/uwb-apps/bin/targets/ultrawidebuffs_datatransfer/app/util/cbmem/util_cbmem.a
/home/joel/Capstone/uwb-apps/bin/targets/ultrawidebuffs_datatransfer/app/util/crc/util_crc.a
/home/joel/Capstone/uwb-apps/bin/targets/ultrawidebuffs_datatransfer/app/util/mem/util_mem.a
/home/joel/Capstone/uwb-apps/bin/targets/ultrawidebuffs_datatransfer/app/util/rwlock/util_rwlock.a
/home/joel/Capstone/uwb-apps/bin/targets/ultrawidebuffs_datatransfer/app/util/streamer/util_streamer.a
/home/joel/Capstone/uwb-apps/bin/targets/ultrawidebuffs_datatransfer/generated/bin/ultrawidebuffs_datatransfer-sysinit-app.a
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
-Wl,-Map=/home/joel/Capstone/uwb-apps/bin/targets/ultrawidebuffs_datatransfer/app/apps/ultrawidebuffs_datatransfer/ultrawidebuffs_datatransfer.elf.map