arm-none-eabi-gcc
-o
/home/joel/Capstone/uwb-apps/bin/targets/rtdoa_slave/app/apps/rtdoa_node/rtdoa_node.elf
-DAPP_NAME=rtdoa_node
-DAPP_rtdoa_node
-DARCH_NAME=cortex_m4
-DARCH_cortex_m4
-DBSP_NAME=dwm1001
-DBSP_dwm1001
-DMYNEWT=1
-DNRF52
-O1
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
/home/joel/Capstone/uwb-apps/bin/targets/rtdoa_slave/app/apps/rtdoa_node/apps_rtdoa_node.a
/home/joel/Capstone/uwb-apps/bin/targets/rtdoa_slave/app/boot/bootutil/boot_bootutil.a
/home/joel/Capstone/uwb-apps/bin/targets/rtdoa_slave/app/boot/split/boot_split.a
/home/joel/Capstone/uwb-apps/bin/targets/rtdoa_slave/app/crypto/mbedtls/crypto_mbedtls.a
/home/joel/Capstone/uwb-apps/bin/targets/rtdoa_slave/app/crypto/tinycrypt/crypto_tinycrypt.a
/home/joel/Capstone/uwb-apps/bin/targets/rtdoa_slave/app/encoding/base64/encoding_base64.a
/home/joel/Capstone/uwb-apps/bin/targets/rtdoa_slave/app/encoding/cborattr/encoding_cborattr.a
/home/joel/Capstone/uwb-apps/bin/targets/rtdoa_slave/app/encoding/tinycbor/encoding_tinycbor.a
/home/joel/Capstone/uwb-apps/bin/targets/rtdoa_slave/app/fs/fcb/fs_fcb.a
/home/joel/Capstone/uwb-apps/bin/targets/rtdoa_slave/app/hw/bsp/dwm1001/hw_bsp_dwm1001.a
/home/joel/Capstone/uwb-apps/bin/targets/rtdoa_slave/app/hw/cmsis-core/hw_cmsis-core.a
/home/joel/Capstone/uwb-apps/bin/targets/rtdoa_slave/app/hw/drivers/adc/adc_nrf52/hw_drivers_adc_adc_nrf52.a
/home/joel/Capstone/uwb-apps/bin/targets/rtdoa_slave/app/hw/drivers/adc/hw_drivers_adc.a
/home/joel/Capstone/uwb-apps/bin/targets/rtdoa_slave/app/hw/drivers/uart/hw_drivers_uart.a
/home/joel/Capstone/uwb-apps/bin/targets/rtdoa_slave/app/hw/drivers/uart/uart_hal/hw_drivers_uart_uart_hal.a
/home/joel/Capstone/uwb-apps/bin/targets/rtdoa_slave/app/hw/drivers/uwb/hw_drivers_uwb.a
/home/joel/Capstone/uwb-apps/bin/targets/rtdoa_slave/app/hw/drivers/uwb/uwb_dw1000/hw_drivers_uwb_uwb_dw1000.a
/home/joel/Capstone/uwb-apps/bin/targets/rtdoa_slave/app/hw/hal/hw_hal.a
/home/joel/Capstone/uwb-apps/bin/targets/rtdoa_slave/app/hw/mcu/nordic/hw_mcu_nordic.a
/home/joel/Capstone/uwb-apps/bin/targets/rtdoa_slave/app/hw/mcu/nordic/nrf52xxx/hw_mcu_nordic_nrf52xxx.a
/home/joel/Capstone/uwb-apps/bin/targets/rtdoa_slave/app/kernel/os/kernel_os.a
/home/joel/Capstone/uwb-apps/bin/targets/rtdoa_slave/app/lib/bleprph/lib_bleprph.a
/home/joel/Capstone/uwb-apps/bin/targets/rtdoa_slave/app/lib/dsp/lib_dsp.a
/home/joel/Capstone/uwb-apps/bin/targets/rtdoa_slave/app/lib/euclid/lib_euclid.a
/home/joel/Capstone/uwb-apps/bin/targets/rtdoa_slave/app/lib/json/lib_json.a
/home/joel/Capstone/uwb-apps/bin/targets/rtdoa_slave/app/lib/nmgr_uwb/lib_nmgr_uwb.a
/home/joel/Capstone/uwb-apps/bin/targets/rtdoa_slave/app/lib/nrng/lib_nrng.a
/home/joel/Capstone/uwb-apps/bin/targets/rtdoa_slave/app/lib/pan_utils/lib_pan_utils.a
/home/joel/Capstone/uwb-apps/bin/targets/rtdoa_slave/app/lib/panmaster/lib_panmaster.a
/home/joel/Capstone/uwb-apps/bin/targets/rtdoa_slave/app/lib/rng_math/lib_rng_math.a
/home/joel/Capstone/uwb-apps/bin/targets/rtdoa_slave/app/lib/rtdoa/lib_rtdoa.a
/home/joel/Capstone/uwb-apps/bin/targets/rtdoa_slave/app/lib/rtdoa_node/lib_rtdoa_node.a
/home/joel/Capstone/uwb-apps/bin/targets/rtdoa_slave/app/lib/tdma/lib_tdma.a
/home/joel/Capstone/uwb-apps/bin/targets/rtdoa_slave/app/lib/timescale/timescale_m4_hardfloat/libtimescale_core.a
/home/joel/Capstone/uwb-apps/bin/targets/rtdoa_slave/app/lib/tofdb/lib_tofdb.a
/home/joel/Capstone/uwb-apps/bin/targets/rtdoa_slave/app/lib/twr_ss_nrng/lib_twr_ss_nrng.a
/home/joel/Capstone/uwb-apps/bin/targets/rtdoa_slave/app/lib/uwb_ccp/lib_uwb_ccp.a
/home/joel/Capstone/uwb-apps/bin/targets/rtdoa_slave/app/lib/uwb_pan/lib_uwb_pan.a
/home/joel/Capstone/uwb-apps/bin/targets/rtdoa_slave/app/lib/uwb_rng/lib_uwb_rng.a
/home/joel/Capstone/uwb-apps/bin/targets/rtdoa_slave/app/lib/uwb_wcs/lib_uwb_wcs.a
/home/joel/Capstone/uwb-apps/bin/targets/rtdoa_slave/app/libc/baselibc/libc_baselibc.a
/home/joel/Capstone/uwb-apps/bin/targets/rtdoa_slave/app/mgmt/bcast_ota/mgmt_bcast_ota.a
/home/joel/Capstone/uwb-apps/bin/targets/rtdoa_slave/app/mgmt/imgmgr/mgmt_imgmgr.a
/home/joel/Capstone/uwb-apps/bin/targets/rtdoa_slave/app/mgmt/mgmt/mgmt_mgmt.a
/home/joel/Capstone/uwb-apps/bin/targets/rtdoa_slave/app/mgmt/newtmgr/mgmt_newtmgr.a
/home/joel/Capstone/uwb-apps/bin/targets/rtdoa_slave/app/mgmt/newtmgr/nmgr_os/mgmt_newtmgr_nmgr_os.a
/home/joel/Capstone/uwb-apps/bin/targets/rtdoa_slave/app/mgmt/newtmgr/transport/ble/mgmt_newtmgr_transport_ble.a
/home/joel/Capstone/uwb-apps/bin/targets/rtdoa_slave/app/mgmt/newtmgr/transport/nmgr_shell/mgmt_newtmgr_transport_nmgr_shell.a
/home/joel/Capstone/uwb-apps/bin/targets/rtdoa_slave/app/net/ip/mn_socket/net_ip_mn_socket.a
/home/joel/Capstone/uwb-apps/bin/targets/rtdoa_slave/app/nimble/controller/nimble_controller.a
/home/joel/Capstone/uwb-apps/bin/targets/rtdoa_slave/app/nimble/drivers/nrf52/nimble_drivers_nrf52.a
/home/joel/Capstone/uwb-apps/bin/targets/rtdoa_slave/app/nimble/host/nimble_host.a
/home/joel/Capstone/uwb-apps/bin/targets/rtdoa_slave/app/nimble/host/services/ans/nimble_host_services_ans.a
/home/joel/Capstone/uwb-apps/bin/targets/rtdoa_slave/app/nimble/host/services/gap/nimble_host_services_gap.a
/home/joel/Capstone/uwb-apps/bin/targets/rtdoa_slave/app/nimble/host/services/gatt/nimble_host_services_gatt.a
/home/joel/Capstone/uwb-apps/bin/targets/rtdoa_slave/app/nimble/host/store/config/nimble_host_store_config.a
/home/joel/Capstone/uwb-apps/bin/targets/rtdoa_slave/app/nimble/host/util/nimble_host_util.a
/home/joel/Capstone/uwb-apps/bin/targets/rtdoa_slave/app/nimble/nimble.a
/home/joel/Capstone/uwb-apps/bin/targets/rtdoa_slave/app/nimble/transport/ram/nimble_transport_ram.a
/home/joel/Capstone/uwb-apps/bin/targets/rtdoa_slave/app/porting/dpl_lib/porting_dpl_lib.a
/home/joel/Capstone/uwb-apps/bin/targets/rtdoa_slave/app/sys/config/sys_config.a
/home/joel/Capstone/uwb-apps/bin/targets/rtdoa_slave/app/sys/console/full/sys_console_full.a
/home/joel/Capstone/uwb-apps/bin/targets/rtdoa_slave/app/sys/flash_map/sys_flash_map.a
/home/joel/Capstone/uwb-apps/bin/targets/rtdoa_slave/app/sys/id/sys_id.a
/home/joel/Capstone/uwb-apps/bin/targets/rtdoa_slave/app/sys/log/full/sys_log_full.a
/home/joel/Capstone/uwb-apps/bin/targets/rtdoa_slave/app/sys/log/modlog/sys_log_modlog.a
/home/joel/Capstone/uwb-apps/bin/targets/rtdoa_slave/app/sys/mfg/sys_mfg.a
/home/joel/Capstone/uwb-apps/bin/targets/rtdoa_slave/app/sys/reboot/sys_reboot.a
/home/joel/Capstone/uwb-apps/bin/targets/rtdoa_slave/app/sys/shell/sys_shell.a
/home/joel/Capstone/uwb-apps/bin/targets/rtdoa_slave/app/sys/stats/full/sys_stats_full.a
/home/joel/Capstone/uwb-apps/bin/targets/rtdoa_slave/app/sys/sysdown/sys_sysdown.a
/home/joel/Capstone/uwb-apps/bin/targets/rtdoa_slave/app/sys/sysinit/sys_sysinit.a
/home/joel/Capstone/uwb-apps/bin/targets/rtdoa_slave/app/sys/uwbcfg/sys_uwbcfg.a
/home/joel/Capstone/uwb-apps/bin/targets/rtdoa_slave/app/time/datetime/time_datetime.a
/home/joel/Capstone/uwb-apps/bin/targets/rtdoa_slave/app/util/cbmem/util_cbmem.a
/home/joel/Capstone/uwb-apps/bin/targets/rtdoa_slave/app/util/crc/util_crc.a
/home/joel/Capstone/uwb-apps/bin/targets/rtdoa_slave/app/util/mem/util_mem.a
/home/joel/Capstone/uwb-apps/bin/targets/rtdoa_slave/app/util/parse/util_parse.a
/home/joel/Capstone/uwb-apps/bin/targets/rtdoa_slave/app/util/rwlock/util_rwlock.a
/home/joel/Capstone/uwb-apps/bin/targets/rtdoa_slave/app/util/streamer/util_streamer.a
/home/joel/Capstone/uwb-apps/bin/targets/rtdoa_slave/generated/bin/rtdoa_slave-sysinit-app.a
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
-Wl,-Map=/home/joel/Capstone/uwb-apps/bin/targets/rtdoa_slave/app/apps/rtdoa_node/rtdoa_node.elf.map