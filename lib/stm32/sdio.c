/** @defgroup sdio_file SDIO

@ingroup STM32F_files

@brief <b>libopencm3 STM32Fxxx SDIO</b>

@version 0.1.0

@author @htmlonly &copy; @endhtmlonly 2013 Stefan Agner <stefan@agner.ch>

@date 16 Mai 2013

The SDIO card host interface supports amongst others SD memory cards, SDIO and
CE-ATA devices. A transfer rate up to 48 MHz in 8 bit mode can be used.
The peripherial supports DMA transfer mode in both direction.

LGPL License Terms @ref lgpl_license
*/
/*
 * This file is part of the libopencm3 project.
 *
 * Copyright (C) 2013 Stefan Agner <stefan@agner.ch>
 *
 * This library is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <libopencm3/stm32/sdio.h>

#if defined(STM32F1)
#	include <libopencm3/stm32/f1/rcc.h>
#elif defined(STM32F2)
#	include <libopencm3/stm32/f2/rcc.h>
#elif defined(STM32F4)
#	include <libopencm3/stm32/f4/rcc.h>
#elif defined(STM32L1)
#	include <libopencm3/stm32/l1/rcc.h>
#else
#	error "stm32 family not defined."
#endif

/* STM32F1 doesnt allow reset by RCC peripherial... */
#if defined(STM32F2) || defined(STM32F4)
/*-----------------------------------------------------------------------------*/
/** @brief SDIO Reset

The SDIO peripheral and all its associated configuration registers are placed in the
reset condition. The reset is effective via the RCC peripheral reset system.
 */
void sdio_reset()
{
	rcc_peripheral_reset(&RCC_APB2RSTR, RCC_APB2RSTR_SDIORST);
	rcc_peripheral_clear_reset(&RCC_APB2RSTR, RCC_APB2RSTR_SDIORST);
}
#endif

/*-----------------------------------------------------------------------------*/
/** @brief SDIO power on

Enable card clock power.
 */
void sdio_power_on()
{
        SDIO_POWER = SDIO_POWER_PWRCTRL_PWRON;
}

/*-----------------------------------------------------------------------------*/
/** @brief SDIO power off

Disable card clock power.
 */
void sdio_power_off()
{
        SDIO_POWER = SDIO_POWER_PWRCTRL_PWROFF;
}

/*-----------------------------------------------------------------------------*/
/** @brief SDIO set clock divisor

Controls the output clock. The SDIO pheripherial is clocked with 48MHz, this is
divided by (clkdiv + 2). For using MMC frequency must be less than 400kHz.
 */
void sdio_set_clockdiv(u8 clkdiv)
{
        SDIO_CLKCR |= (SDIO_CLKCR_CLKDIV_MSK & clkdiv);
}

/*-----------------------------------------------------------------------------*/
/** @brief SDIO enable clock

Enables the output clock on the SD_CLK line. This clock is used for the command and
data channel.
 */
void sdio_enable_clock()
{
        SDIO_CLKCR |= SDIO_CLKCR_CLKEN;
}

/*-----------------------------------------------------------------------------*/
/** @brief SDIO set bus width

Set bus width to be used to tranfer data. 1, 4 or 8 bit bus are supported.
 */
void sdio_set_buswidth(u16 buswidth)
{
        SDIO_CLKCR |= buswidth;
}

