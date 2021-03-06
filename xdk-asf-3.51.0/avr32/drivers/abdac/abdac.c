/*****************************************************************************
 *
 * \file
 *
 * \brief AVR32 ABDAC example application.
 *
 * \par Application note:
 *  AVR32120 - Using the AVR32 audio bitstream DAC ABDAC
 *
 * \par Documentation
 *  For comprehensive code documentation, supported compilers, compiler
 *  settings and supported devices see readme.html.
 *
 *  Microchip Technology Inc: http://www.microchip.com \n
 *
 * $Revision: 506 $
 * $Date: 2007-05-21 20:00:05 +0200 (Mon, 21 May 2007) $ \n
 * Copyright (c) 2014-2018 Microchip Technology Inc. and its subsidiaries.
 *
 * \asf_license_start
 *
 * \page License
 *
 * Subject to your compliance with these terms, you may use Microchip
 * software and any derivatives exclusively with Microchip products.
 * It is your responsibility to comply with third party license terms applicable
 * to your use of third party software (including open source software) that
 * may accompany Microchip software.
 *
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES,
 * WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE,
 * INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY,
 * AND FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT WILL MICROCHIP BE
 * LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, INCIDENTAL OR CONSEQUENTIAL
 * LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND WHATSOEVER RELATED TO THE
 * SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS BEEN ADVISED OF THE
 * POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE FULLEST EXTENT
 * ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN ANY WAY
 * RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
 * THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * \asf_license_stop
 *
 *****************************************************************************/
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#include "compiler.h"
#include "abdac.h"

void abdac_enable(volatile avr32_abdac_t *abdac)
{
  volatile avr32_pm_t *pm = &AVR32_PM;
  pm->gcctrl[ABDAC_GCLK] |= GCLK_BIT(CEN);
  abdac->cr |= (unsigned int) ABDAC_BIT(CR_EN);
}

void abdac_disable(volatile avr32_abdac_t *abdac)
{
  volatile avr32_pm_t *pm = &AVR32_PM;
  abdac->cr &= ~ABDAC_BIT(CR_EN);
  pm->gcctrl[ABDAC_GCLK] &= ~GCLK_BIT(CEN);
}

void abdac_swap_channels(volatile avr32_abdac_t *abdac)
{
  if(abdac->cr & ABDAC_BIT(CR_SWAP))
    abdac->cr &= ~ABDAC_BIT(CR_SWAP);
  else
    abdac->cr |= ABDAC_BIT(CR_SWAP);
}

unsigned long abdac_set_dac_hz(volatile avr32_abdac_t *abdac,
    const unsigned long bus_hz, const unsigned long dac_hz)
{
  volatile avr32_pm_t *pm = &AVR32_PM;
  unsigned short div;

  // Use OSC0
  pm->GCCTRL[ABDAC_GCLK].pllsel=0;// Oscillator source
  pm->GCCTRL[ABDAC_GCLK].oscsel=0;// OSC0

  if (bus_hz < (256 * dac_hz)) {
    // Disable diven to get the highest sample rate
    pm->GCCTRL[ABDAC_GCLK].diven=0;
    return EINVAL;
  }

  div = bus_hz / (256 * dac_hz);

  if (div > 1) {
    // Enable DIV
    pm->GCCTRL[ABDAC_GCLK].div= (div / 2) - 1;
    pm->GCCTRL[ABDAC_GCLK].diven=1;
  } else {
    // Disable DIV
    pm->GCCTRL[ABDAC_GCLK].diven=0;
  }

  return (bus_hz / (256 * div));
}

unsigned long abdac_get_dac_hz(volatile avr32_abdac_t *abdac,
    const unsigned long bus_hz)
{
  volatile avr32_pm_t *pm = &AVR32_PM;
  unsigned short div = 1;

  if (pm->gcctrl[ABDAC_GCLK] & GCLK_BIT(DIVEN)) {
    div = 2 * (GCLK_BFEXT(DIV, pm->gcctrl[ABDAC_GCLK]) + 1);
  }

  return (bus_hz / div);
}

int abdac_sink(volatile avr32_abdac_t *abdac,
    const unsigned short ch0, const unsigned short ch1)
{
  volatile unsigned long timeout = ABDAC_TIMEOUT;

  do {
    timeout--;
	if (0 == timeout) {
      return -ETIMEOUT;
    }
  } while (!(abdac->isr & ABDAC_BIT(ISR_TX_READY)));

  abdac->sdr = ABDAC_BF(SDR_CHANNEL0, ch0) | ABDAC_BF(SDR_CHANNEL1, ch1);

  return 0;
}


bool abdac_set_dac_sample_rate(const unsigned long dac_hz)
{
  // This function set the ABDAC Generic clock using sample
  // rate of the current song.
  // Here is the value of the oscillators and the PLLs
  // OSC0       12000000
  // OSC1       11289600
  // PLL0       62092800 (OSC1*5.5)
  // PLL1       48000000 (OSC0*4)
  //
  // The following table show the relative error given when
  // selecting one of the 4 frequency
  // (*) is the chosen OSC or PLL for the Generic clock
  //      settings for this application
  //                 ----------------------------------
  //                |        | Relative Error (%)      |
  //|--------------------------------------------------|
  //|Sample Rate(Hz)|OSC1    | OSC0   | PLL0  | PLL1   |
  //|--------------------------------------------------|
  //| 8000          |  -8.13 |  -2.34 |(*)1.06|   -2.34|
  //|11025          |(*)0.00 |   6.29 |   0.00|   -5.52|
  //|12000          |  -8.13 |  -2.34 |(*)1.06|   -2.34|
  //|16000          |  37.81 |  46.48 |  -5.25|(*)-2.34|
  //|22050          |(*)0.00 |   6.29 |  -8.33|    6.29|
  //|24000          |  -8.13 |  -2.34 |(*)1.06|   -2.34|
  //|32000          | -31.09 | -26.76 |  -5.25|(*)-2.34|
  //|44100          |(*)0.00 |   6.29 |  -8.33|    6.29|
  //|48000          |  -8.13 |  -2.34 | -15.78|(*)-2.34|
  // --------------------------------------------------
  //
  // Reminder : The frequency of this ABDAC clock must be 256
  // times the frequency of the desired samplerate

  volatile avr32_pm_t *pm = &AVR32_PM;
  switch(dac_hz) {
    case 8000:// PLL0/30/256
         pm->GCCTRL[ABDAC_GCLK].div= 14; // div by 2*(14+1)=30
         pm->GCCTRL[ABDAC_GCLK].diven=1; // Div Enable
         pm->GCCTRL[ABDAC_GCLK].pllsel=1;// PLL source
         pm->GCCTRL[ABDAC_GCLK].oscsel=0;// PLL 0
      break;
    case 11025:// OSC1/4/256
         pm->GCCTRL[ABDAC_GCLK].div= 1;  // div by 2*(1+1)=4
         pm->GCCTRL[ABDAC_GCLK].diven=1; // Div Enable
         pm->GCCTRL[ABDAC_GCLK].pllsel=0;// Oscillator source
         pm->GCCTRL[ABDAC_GCLK].oscsel=1;// OSC1
        break;
    case 12000:// PLL0/20/256
         pm->GCCTRL[ABDAC_GCLK].div= 9;  // div by 2*(9+1)=20
         pm->GCCTRL[ABDAC_GCLK].diven=1; // Div Enable
         pm->GCCTRL[ABDAC_GCLK].pllsel=1;// PLL source
         pm->GCCTRL[ABDAC_GCLK].oscsel=0;// PLL 0
        break;
    case 16000:// PLL1/12/256
         pm->GCCTRL[ABDAC_GCLK].div= 5;  // div by 2*(5+1)=12
         pm->GCCTRL[ABDAC_GCLK].diven=1; // Div Enable
         pm->GCCTRL[ABDAC_GCLK].pllsel=1;// PLL source
         pm->GCCTRL[ABDAC_GCLK].oscsel=1;// PLL 1
        break;
    case 22050:// OSC1/2/256
         pm->GCCTRL[ABDAC_GCLK].div= 0;  // div by 2*(0+1)=2
         pm->GCCTRL[ABDAC_GCLK].diven=1; // div Enable
         pm->GCCTRL[ABDAC_GCLK].pllsel=0;// Oscillator source
         pm->GCCTRL[ABDAC_GCLK].oscsel=1;// OSC1
        break;
    case 24000:// PLL0/10/256
         pm->GCCTRL[ABDAC_GCLK].div= 4;  // div by 2*(4+1)=10
         pm->GCCTRL[ABDAC_GCLK].diven=1; // Div Enable
         pm->GCCTRL[ABDAC_GCLK].pllsel=1;// PLL source
         pm->GCCTRL[ABDAC_GCLK].oscsel=0;// PLL 0
        break;
    case 32000:// PLL1/6/256
         pm->GCCTRL[ABDAC_GCLK].div= 2;  // div by 2*(2+1)=6
         pm->GCCTRL[ABDAC_GCLK].diven=1; // Div Enable
         pm->GCCTRL[ABDAC_GCLK].pllsel=1;// PLL source
         pm->GCCTRL[ABDAC_GCLK].oscsel=1;// PLL 1
        break;
    case 44100:// OSC1/256
         pm->GCCTRL[ABDAC_GCLK].div= 0;  // No Div factor
         pm->GCCTRL[ABDAC_GCLK].diven=0; // div disable
         pm->GCCTRL[ABDAC_GCLK].pllsel=0;// Oscillator source
         pm->GCCTRL[ABDAC_GCLK].oscsel=1;// OSC1
        break;
    case 48000:// PLL1/4/256
         pm->GCCTRL[ABDAC_GCLK].div= 1;  // div by 2*(1+1)=4
         pm->GCCTRL[ABDAC_GCLK].diven=1; // Div Enable
         pm->GCCTRL[ABDAC_GCLK].pllsel=1;// PLL source
         pm->GCCTRL[ABDAC_GCLK].oscsel=1;// PLL 1
        break;
    default:
       return false;
  }
  // Debug purpose function, copy ABDAC CLK on GCLK 1
  // this can be reached on J16-pin8
  //pm->gcctrl[2] = pm->gcctrl[ABDAC_GCLK];
  //pm->GCCTRL[2].cen = 1;
  //gpio_enable_module_pin(AVR32_PM_GCLK_2_1_PIN, AVR32_PM_GCLK_2_1_FUNCTION);
  return true;
}
