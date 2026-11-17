#pragma once

/*
 * KB2040 in the Pro Micro socket from oso-keyboard/config.yaml.
 * Rows ROW0..ROW5 are D4..D9. Columns COL0..COL5 are D20, D19, D18, D15, D14, D16.
 * Both halves use the same pins; the right PCB is a mirror, so column 0 stays outer.
 * TRRS ring 2 is D21 (TX, GP29) and ring 1 is D0 (RX, GP1). The cable joins
 * TX to TX, so the master swaps its USART pins.
 */

#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 500U

#define EE_HANDS
#define SERIAL_USART_FULL_DUPLEX
#define SERIAL_USART_TX_PIN GP29
#define SERIAL_USART_RX_PIN GP1
#define SERIAL_USART_PIN_SWAP

#define TAPPING_TERM 200
#define QUICK_TAP_TERM 120

/*
 * Wired builds put a 4-pin SSD1306 on the nice!view header.
 * Header, left to right: MOSI, SCK, VCC, GND, CS, P10.
 * Module, left to right: SDA,  SCL, VCC, GND.
 * MOSI is Arduino D2 / GP2 and SCK is Arduino D3 / GP3, so this is I2C1
 * with SDA and SCL the right way around. CS and P10 are unused.
 */
#define I2C1_SDA_PIN GP2
#define I2C1_SCL_PIN GP3
#define OLED_DISPLAY_128X32
/* Blank the panel after 15 minutes with no keypress. A key turns it back on. */
#define OLED_TIMEOUT 900000

#define SPLIT_LAYER_STATE_ENABLE
#define SPLIT_LED_STATE_ENABLE
#define SPLIT_MODS_ENABLE
