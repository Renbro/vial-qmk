#pragma once

/*
 * KB2040 in the Pro Micro socket from oso-keyboard/config.yaml.
 * Rows ROW0..ROW5 are D4..D9. Columns COL0..COL5 are D20, D19, D18, D15, D14, D16.
 * Both halves use the same pins; the right PCB is a mirror, so column 0 stays outer.
 * TRRS ring 2 is D21 (TX) and ring 1 is D0 (RX). The cable joins TX to TX, so the
 * master swaps its USART pins.
 */

#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 500U

#define EE_HANDS
#define SERIAL_USART_FULL_DUPLEX
#define SERIAL_USART_TX_PIN GP29
#define SERIAL_USART_RX_PIN GP3
#define SERIAL_USART_PIN_SWAP

#define TAPPING_TERM 200
#define QUICK_TAP_TERM 120
