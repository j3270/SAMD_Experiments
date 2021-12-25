/**
 * \file
 *
 * \brief Autogenerated API include file for the Atmel Software Framework (ASF)
 *
 * Copyright (c) 2012 Atmel Corporation. All rights reserved.
 *
 * \asf_license_start
 *
 * \page License
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. The name of Atmel may not be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * 4. This software may only be redistributed and used in connection with an
 *    Atmel microcontroller product.
 *
 * THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * EXPRESSLY AND SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * \asf_license_stop
 *
 */

#ifndef ASF_H
#define ASF_H

/*
 * This file includes all API header files for the selected drivers from ASF.
 * Note: There might be duplicate includes required by more than one driver.
 *
 * The file is automatically generated and will be re-written when
 * running the ASF driver selector tool. Any changes will be discarded.
 */

// From module: Common SAM0 compiler driver
#include <compiler.h>
#include <status_codes.h>

// From module: Delay routines
#include <delay.h>

// From module: EXTINT - External Interrupt (Callback APIs)
#include <extint.h>
#include <extint_callback.h>

// From module: GFX Monochrome - Monochrome Graphic Library
#include <gfx_mono.h>

// From module: GFX Monochrome - Spinner/Spin control widget
#include <gfx_mono_spinctrl.h>

// From module: GFX Monochrome - System Font
#include <sysfont.h>

// From module: Generic board support
#include <board.h>

// From module: Interrupt management - SAM implementation
#include <interrupt.h>

// From module: NVM - Non volatile memory access
#include <common_nvm.h>

// From module: NVM - Non-Volatile Memory
#include <nvm.h>

// From module: PORT - GPIO Pin Control
#include <port.h>

// From module: Part identification macros
#include <parts.h>

// From module: RTC - Real Time Counter in Count Mode (Callback APIs)
#include <rtc_count.h>
#include <rtc_count_interrupt.h>
#include <rtc_tamper.h>

// From module: SERCOM Callback API
#include <sercom.h>
#include <sercom_interrupt.h>

// From module: SERCOM I2C - Master Mode I2C (Polled APIs)
#include <i2c_common.h>
#include <i2c_master.h>

// From module: SERCOM Polled API
#include <sercom.h>

// From module: SERCOM SPI - Serial Peripheral Interface (Polled APIs)
#include <spi.h>

// From module: SERCOM USART - Serial Communications (Callback APIs)
#include <usart.h>
#include <usart_interrupt.h>

// From module: SSD1306 OLED controller
#include <ssd1306.h>

// From module: SYSTEM - Clock Management for SAMR30
#include <clock.h>
#include <gclk.h>

// From module: SYSTEM - Core System Driver
#include <system.h>

// From module: SYSTEM - I/O Pin Multiplexer
#include <pinmux.h>

// From module: SYSTEM - Interrupt Driver For SAMR30
#include <system_interrupt.h>

// From module: SYSTEM - Power Management for SAM L21
#include <power.h>

// From module: SYSTEM - Reset Management for SAM L21
#include <reset.h>

// From module: Standard serial I/O (stdio)
#include <stdio_serial.h>

// From module: TC - Timer Counter (Callback APIs)
#include <tc.h>
#include <tc_interrupt.h>

// From module: USART - Serial interface- SAM implementation for devices with only USART
#include <serial.h>

#endif // ASF_H
