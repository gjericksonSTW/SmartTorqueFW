/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
!!GlobalInfo
product: Pins v3.0
processor: MKL43Z256xxx4
package_id: MKL43Z256VLH4
mcu_data: ksdk2_0
processor_version: 2.0.0
board: FRDM-KL43Z
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */

#include "fsl_common.h"
#include "fsl_port.h"
#include "pin_mux.h"

/*FUNCTION**********************************************************************
 *
 * Function Name : BOARD_InitBootPins
 * Description   : Calls initialization functions.
 *
 *END**************************************************************************/
void BOARD_InitBootPins(void) {
    BOARD_InitPins();
}

#define PIN0_IDX                         0u   /*!< Pin number for pin 0 in a port */
#define PIN1_IDX                         1u   /*!< Pin number for pin 1 in a port */
#define PIN2_IDX                         2u   /*!< Pin number for pin 2 in a port */
#define PIN3_IDX                         3u   /*!< Pin number for pin 3 in a port */
#define PIN5_IDX						 5u
#define PIN6_IDX                         6u   /*!< Pin number for pin 6 in a port */
#define PIN7_IDX                         7u   /*!< Pin number for pin 7 in a port */
#define PIN12_IDX                       12u   /*!< Pin number for pin 12 in a port */
#define PIN13_IDX                       13u   /*!< Pin number for pin 13 in a port */
#define PIN16_IDX                       16u   /*!< Pin number for pin 16 in a port */
#define PIN17_IDX                       17u   /*!< Pin number for pin 17 in a port */
#define PIN18_IDX						18U
#define PIN19_IDX						19U
#define PIN20_IDX                       20u   /*!< Pin number for pin 20 in a port */
#define PIN22_IDX                       22u   /*!< Pin number for pin 22 in a port */
#define PIN23_IDX                       23u   /*!< Pin number for pin 23 in a port */
#define PIN29_IDX                       29u   /*!< Pin number for pin 29 in a port */
#define PIN30_IDX                       30u   /*!< Pin number for pin 30 in a port */
#define PIN31_IDX						31u

/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_InitPins:
- options: {callFromInitBoot: 'true', prefix: BOARD_, coreID: core0, enableClock: 'true'}
- pin_list:
  - {pin_num: '11', peripheral: UART2, signal: TX, pin_signal: ADC0_DP3/ADC0_SE3/PTE22/TPM2_CH0/UART2_TX/FXIO0_D6}
  - {pin_num: '12', peripheral: UART2, signal: RX, pin_signal: ADC0_DM3/ADC0_SE7a/PTE23/TPM2_CH1/UART2_RX/FXIO0_D7}
  - {pin_num: '1', peripheral: I2C1, signal: SDA, pin_signal: LCD_P48/PTE0/CLKOUT32K/SPI1_MISO/LPUART1_TX/RTC_CLKOUT/CMP0_OUT/I2C1_SDA, identifier: ''}
  - {pin_num: '2', peripheral: I2C1, signal: SCL, pin_signal: LCD_P49/PTE1/SPI1_MOSI/LPUART1_RX/SPI1_MISO/I2C1_SCL}
  - {pin_num: '63', peripheral: ADC0, signal: 'SE, 7b', pin_signal: LCD_P46/ADC0_SE7b/PTD6/LLWU_P15/SPI1_MOSI/LPUART0_RX/SPI1_MISO/FXIO0_D6}
  - {pin_num: '40', peripheral: GPIOB, signal: 'GPIO, 17', pin_signal: LCD_P13/PTB17/SPI1_MISO/LPUART0_TX/TPM_CLKIN1/SPI1_MOSI}
  - {pin_num: '39', peripheral: GPIOB, signal: 'GPIO, 16', pin_signal: LCD_P12/PTB16/SPI1_MOSI/LPUART0_RX/TPM_CLKIN0/SPI1_MISO}
  - {pin_num: '38', peripheral: GPIOB, signal: 'GPIO, 3', pin_signal: LCD_P3/ADC0_SE13/PTB3/I2C0_SDA/TPM2_CH1}
  - {pin_num: '18', peripheral: GPIOE, signal: 'GPIO, 30', pin_signal: DAC0_OUT/ADC0_SE23/CMP0_IN4/PTE30/TPM0_CH3/TPM_CLKIN1/LPUART1_TX/LPTMR0_ALT1}
  - {pin_num: '17', peripheral: GPIOE, signal: 'GPIO, 29', pin_signal: CMP0_IN5/ADC0_SE4b/PTE29/TPM0_CH2/TPM_CLKIN0}
  - {pin_num: '45', peripheral: ADC0, signal: 'SE, 11', pin_signal: LCD_P22/ADC0_SE11/PTC2/I2C1_SDA/TPM0_CH1/I2S0_TX_FS}
  - {pin_num: '28', peripheral: GPIOA, signal: 'GPIO, 12', pin_signal: PTA12/TPM1_CH0/I2S0_TXD0}
  - {pin_num: '29', peripheral: GPIOA, signal: 'GPIO, 13', pin_signal: PTA13/TPM1_CH1/I2S0_TX_FS}
  - {pin_num: '34', peripheral: GPIOA, signal: 'GPIO, 20', pin_signal: PTA20/RESET_b}
  - {pin_num: '64', peripheral: GPIOD, signal: 'GPIO, 7', pin_signal: LCD_P47/PTD7/SPI1_MISO/LPUART0_TX/SPI1_MOSI/FXIO0_D7}
  - {pin_num: '46', peripheral: GPIOC, signal: 'GPIO, 3', pin_signal: LCD_P23/PTC3/LLWU_P7/SPI1_SCK/LPUART1_RX/TPM0_CH2/CLKOUT/I2S0_TX_BCLK, identifier: ''}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */

/*FUNCTION**********************************************************************
 *
 * Function Name : BOARD_InitPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 *END**************************************************************************/
void BOARD_InitPins(void) {
	CLOCK_EnableClock(kCLOCK_PortA);                           /* Port A Clock Gate Control: Clock enabled */
	CLOCK_EnableClock(kCLOCK_PortB);                           /* Port B Clock Gate Control: Clock enabled */
	CLOCK_EnableClock(kCLOCK_PortC);                           /* Port C Clock Gate Control: Clock enabled */
	CLOCK_EnableClock(kCLOCK_PortD);                           /* Port D Clock Gate Control: Clock enabled */
	CLOCK_EnableClock(kCLOCK_PortE);                           /* Port E Clock Gate Control: Clock enabled */

	PORT_SetPinMux(PORTA, PIN18_IDX, kPORT_MuxAlt4); /* PORTA18 (pin 32) is configured as EXTAL0 */
	PORT_SetPinMux(PORTA, PIN19_IDX, kPORT_PinDisabledOrAnalog);
	PORT_SetPinMux(PORTC, PIN1_IDX, kPORT_MuxAsGpio);
	PORT_SetPinMux(PORTB, PIN0_IDX, kPORT_MuxAsGpio);
	PORT_SetPinMux(PORTC, PIN2_IDX, kPORT_PinDisabledOrAnalog); /* PORTC2 (pin 45) is configured as ADC0_SE11 */
	PORT_SetPinMux(PORTD, PIN6_IDX, kPORT_PinDisabledOrAnalog); /* PORTD6 (pin 63) is configured as ADC0_SE7b */
	PORT_SetPinMux(PORTE, PIN22_IDX, kPORT_MuxAlt4);           /* PORTE22 (pin 11) is configured as UART2_TX */
	PORT_SetPinMux(PORTE, PIN23_IDX, kPORT_MuxAlt4);           /* PORTE23 (pin 12) is configured as UART2_RX */
	PORT_SetPinMux(PORTD, PIN5_IDX, kPORT_MuxAlt4);

	const port_pin_config_t button_config = {
	  kPORT_PullDown,                                            /* Internal pull-up resistor is enabled */
	  kPORT_FastSlewRate,                                      /* Fast slew rate is configured */
	  kPORT_PassiveFilterDisable,                              /* Passive filter is disabled */
	  kPORT_LowDriveStrength,                                  /* Low drive strength is configured */
	  kPORT_MuxAsGpio,                                         /* Pin is configured as PTA4 */
	};
	PORT_SetPinConfig(PORTA, PIN12_IDX, &button_config);  /* PORTA4 (pin 26) is configured as PTA4 */
	PORT_SetPinConfig(PORTA, PIN13_IDX, &button_config);
	PORT_SetPinConfig(PORTD, PIN7_IDX, &button_config);

	SIM->SOPT1 |= SIM_SOPT1_OSC32KSEL(2);
	SIM->SOPT2 |= SIM_SOPT2_RTCCLKOUTSEL(1);

}


#define PCR_DSE_LOW                   0x00u   /*!< Drive Strength Enable: Low drive strength is configured on the corresponding pin, if pin is configured as a digital output. */
#define PCR_PE_DISABLED               0x00u   /*!< Pull Enable: Internal pullup or pulldown resistor is not enabled on the corresponding pin. */
#define PCR_PS_UP                     0x01u   /*!< Pull Select: Internal pullup resistor is enabled on the corresponding pin, if the corresponding PE field is set. */
#define PCR_SRE_SLOW                  0x01u   /*!< Slew Rate Enable: Slow slew rate is configured on the corresponding pin, if the pin is configured as a digital output. */

#define PIN0_IDX                         0u   /*!< Pin number for pin 0 in a port */

#define PIN2_IDX                         2u   /*!< Pin number for pin 2 in a port */

#define PIN3_IDX                         3u   /*!< Pin number for pin 3 in a port */
#define PIN4_IDX                         4u   /*!< Pin number for pin 4 in a port */

#define PIN6_IDX                         6u   /*!< Pin number for pin 6 in a port */

#define PIN7_IDX                         7u   /*!< Pin number for pin 7 in a port */

#define PIN20_IDX                       20u   /*!< Pin number for pin 20 in a port */
#define PIN21_IDX                       21u   /*!< Pin number for pin 21 in a port */

/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_InitLCD:
- options: {prefix: BOARD_, coreID: core0, enableClock: 'true'}
- pin_list:
  - {pin_num: '41', peripheral: LCD, signal: 'P, 14', pin_signal: LCD_P14/PTB18/TPM2_CH0/I2S0_TX_BCLK, slew_rate: slow, pull_select: up, pull_enable: disable}
  - {pin_num: '42', peripheral: LCD, signal: 'P, 15', pin_signal: LCD_P15/PTB19/TPM2_CH1/I2S0_TX_FS, slew_rate: slow, pull_select: up, pull_enable: disable}
  - {pin_num: '43', peripheral: LCD, signal: 'P, 20', pin_signal: LCD_P20/ADC0_SE14/PTC0/EXTRG_IN/USB_SOF_OUT/CMP0_OUT/I2S0_TXD0, identifier: LCD_P20, slew_rate: slow,
    pull_select: up, pull_enable: disable}
  - {pin_num: '53', peripheral: LCD, signal: 'P, 24', pin_signal: LCD_P24/PTC4/LLWU_P8/SPI0_SS/LPUART1_TX/TPM0_CH3/I2S0_MCLK, identifier: LCD_P24, slew_rate: slow,
    drive_strength: low, pull_select: up, pull_enable: disable}
  - {pin_num: '55', peripheral: LCD, signal: 'P, 26', pin_signal: LCD_P26/CMP0_IN0/PTC6/LLWU_P10/SPI0_MOSI/EXTRG_IN/I2S0_RX_BCLK/SPI0_MISO/I2S0_MCLK, identifier: LCD_P26,
    slew_rate: slow, pull_select: up, pull_enable: disable}
  - {pin_num: '56', peripheral: LCD, signal: 'P, 27', pin_signal: LCD_P27/CMP0_IN1/PTC7/SPI0_MISO/USB_SOF_OUT/I2S0_RX_FS/SPI0_MOSI, identifier: LCD_P27, slew_rate: slow,
    pull_select: up, pull_enable: disable}
  - {pin_num: '57', peripheral: LCD, signal: 'P, 40', pin_signal: LCD_P40/PTD0/SPI0_SS/TPM0_CH0/FXIO0_D0, slew_rate: slow, pull_select: up, pull_enable: disable}
  - {pin_num: '59', peripheral: LCD, signal: 'P, 42', pin_signal: LCD_P42/PTD2/SPI0_MOSI/UART2_RX/TPM0_CH2/SPI0_MISO/FXIO0_D2, slew_rate: slow, pull_select: up, pull_enable: disable}
  - {pin_num: '60', peripheral: LCD, signal: 'P, 43', pin_signal: LCD_P43/PTD3/SPI0_MISO/UART2_TX/TPM0_CH3/SPI0_MOSI/FXIO0_D3, slew_rate: slow, pull_select: up, pull_enable: disable}
  - {pin_num: '61', peripheral: LCD, signal: 'P, 44', pin_signal: LCD_P44/PTD4/LLWU_P14/SPI1_SS/UART2_RX/TPM0_CH4/FXIO0_D4, slew_rate: slow, pull_select: up, pull_enable: disable}
  - {pin_num: '9', peripheral: LCD, signal: 'P, 59', pin_signal: LCD_P59/ADC0_DP0/ADC0_SE0/PTE20/TPM1_CH0/LPUART0_TX/FXIO0_D4, slew_rate: slow, pull_select: up, pull_enable: disable}
  - {pin_num: '10', peripheral: LCD, signal: 'P, 60', pin_signal: LCD_P60/ADC0_DM0/ADC0_SE4a/PTE21/TPM1_CH1/LPUART0_RX/FXIO0_D5, slew_rate: slow, pull_select: up,
    pull_enable: disable}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */

/*FUNCTION**********************************************************************
 *
 * Function Name : BOARD_InitLCD
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 *END**************************************************************************/
void BOARD_InitLCD(void) {
  CLOCK_EnableClock(kCLOCK_PortB);                           /* Port B Clock Gate Control: Clock enabled */
  CLOCK_EnableClock(kCLOCK_PortC);                           /* Port C Clock Gate Control: Clock enabled */
  CLOCK_EnableClock(kCLOCK_PortD);                           /* Port D Clock Gate Control: Clock enabled */
  CLOCK_EnableClock(kCLOCK_PortE);                           /* Port E Clock Gate Control: Clock enabled */

  PORT_SetPinMux(PORTB, PIN18_IDX, kPORT_PinDisabledOrAnalog); /* PORTB18 (pin 41) is configured as LCD_P14 */
  PORTB->PCR[18] = ((PORTB->PCR[18] &
    (~(PORT_PCR_PS_MASK | PORT_PCR_PE_MASK | PORT_PCR_SRE_MASK | PORT_PCR_ISF_MASK))) /* Mask bits to zero which are setting */
      | PORT_PCR_PS(PCR_PS_UP)                               /* Pull Select: Internal pullup resistor is enabled on the corresponding pin, if the corresponding PE field is set. */
      | PORT_PCR_PE(PCR_PE_DISABLED)                         /* Pull Enable: Internal pullup or pulldown resistor is not enabled on the corresponding pin. */
      | PORT_PCR_SRE(PCR_SRE_SLOW)                           /* Slew Rate Enable: Slow slew rate is configured on the corresponding pin, if the pin is configured as a digital output. */
    );
  PORT_SetPinMux(PORTB, PIN19_IDX, kPORT_PinDisabledOrAnalog); /* PORTB19 (pin 42) is configured as LCD_P15 */
  PORTB->PCR[19] = ((PORTB->PCR[19] &
    (~(PORT_PCR_PS_MASK | PORT_PCR_PE_MASK | PORT_PCR_SRE_MASK | PORT_PCR_ISF_MASK))) /* Mask bits to zero which are setting */
      | PORT_PCR_PS(PCR_PS_UP)                               /* Pull Select: Internal pullup resistor is enabled on the corresponding pin, if the corresponding PE field is set. */
      | PORT_PCR_PE(PCR_PE_DISABLED)                         /* Pull Enable: Internal pullup or pulldown resistor is not enabled on the corresponding pin. */
      | PORT_PCR_SRE(PCR_SRE_SLOW)                           /* Slew Rate Enable: Slow slew rate is configured on the corresponding pin, if the pin is configured as a digital output. */
    );
  PORT_SetPinMux(PORTC, PIN0_IDX, kPORT_PinDisabledOrAnalog); /* PORTC0 (pin 43) is configured as LCD_P20 */
  PORTC->PCR[0] = ((PORTC->PCR[0] &
    (~(PORT_PCR_PS_MASK | PORT_PCR_PE_MASK | PORT_PCR_SRE_MASK | PORT_PCR_ISF_MASK))) /* Mask bits to zero which are setting */
      | PORT_PCR_PS(PCR_PS_UP)                               /* Pull Select: Internal pullup resistor is enabled on the corresponding pin, if the corresponding PE field is set. */
      | PORT_PCR_PE(PCR_PE_DISABLED)                         /* Pull Enable: Internal pullup or pulldown resistor is not enabled on the corresponding pin. */
      | PORT_PCR_SRE(PCR_SRE_SLOW)                           /* Slew Rate Enable: Slow slew rate is configured on the corresponding pin, if the pin is configured as a digital output. */
    );
  PORT_SetPinMux(PORTC, PIN4_IDX, kPORT_PinDisabledOrAnalog); /* PORTC4 (pin 53) is configured as LCD_P24 */
  PORTC->PCR[4] = ((PORTC->PCR[4] &
    (~(PORT_PCR_PS_MASK | PORT_PCR_PE_MASK | PORT_PCR_SRE_MASK | PORT_PCR_DSE_MASK | PORT_PCR_ISF_MASK))) /* Mask bits to zero which are setting */
      | PORT_PCR_PS(PCR_PS_UP)                               /* Pull Select: Internal pullup resistor is enabled on the corresponding pin, if the corresponding PE field is set. */
      | PORT_PCR_PE(PCR_PE_DISABLED)                         /* Pull Enable: Internal pullup or pulldown resistor is not enabled on the corresponding pin. */
      | PORT_PCR_SRE(PCR_SRE_SLOW)                           /* Slew Rate Enable: Slow slew rate is configured on the corresponding pin, if the pin is configured as a digital output. */
      | PORT_PCR_DSE(PCR_DSE_LOW)                            /* Drive Strength Enable: Low drive strength is configured on the corresponding pin, if pin is configured as a digital output. */
    );
  PORT_SetPinMux(PORTC, PIN6_IDX, kPORT_PinDisabledOrAnalog); /* PORTC6 (pin 55) is configured as LCD_P26 */
  PORTC->PCR[6] = ((PORTC->PCR[6] &
    (~(PORT_PCR_PS_MASK | PORT_PCR_PE_MASK | PORT_PCR_SRE_MASK | PORT_PCR_ISF_MASK))) /* Mask bits to zero which are setting */
      | PORT_PCR_PS(PCR_PS_UP)                               /* Pull Select: Internal pullup resistor is enabled on the corresponding pin, if the corresponding PE field is set. */
      | PORT_PCR_PE(PCR_PE_DISABLED)                         /* Pull Enable: Internal pullup or pulldown resistor is not enabled on the corresponding pin. */
      | PORT_PCR_SRE(PCR_SRE_SLOW)                           /* Slew Rate Enable: Slow slew rate is configured on the corresponding pin, if the pin is configured as a digital output. */
    );
  PORT_SetPinMux(PORTC, PIN7_IDX, kPORT_PinDisabledOrAnalog); /* PORTC7 (pin 56) is configured as LCD_P27 */
  PORTC->PCR[7] = ((PORTC->PCR[7] &
    (~(PORT_PCR_PS_MASK | PORT_PCR_PE_MASK | PORT_PCR_SRE_MASK | PORT_PCR_ISF_MASK))) /* Mask bits to zero which are setting */
      | PORT_PCR_PS(PCR_PS_UP)                               /* Pull Select: Internal pullup resistor is enabled on the corresponding pin, if the corresponding PE field is set. */
      | PORT_PCR_PE(PCR_PE_DISABLED)                         /* Pull Enable: Internal pullup or pulldown resistor is not enabled on the corresponding pin. */
      | PORT_PCR_SRE(PCR_SRE_SLOW)                           /* Slew Rate Enable: Slow slew rate is configured on the corresponding pin, if the pin is configured as a digital output. */
    );
  PORT_SetPinMux(PORTD, PIN0_IDX, kPORT_PinDisabledOrAnalog); /* PORTD0 (pin 57) is configured as LCD_P40 */
  PORTD->PCR[0] = ((PORTD->PCR[0] &
    (~(PORT_PCR_PS_MASK | PORT_PCR_PE_MASK | PORT_PCR_SRE_MASK | PORT_PCR_ISF_MASK))) /* Mask bits to zero which are setting */
      | PORT_PCR_PS(PCR_PS_UP)                               /* Pull Select: Internal pullup resistor is enabled on the corresponding pin, if the corresponding PE field is set. */
      | PORT_PCR_PE(PCR_PE_DISABLED)                         /* Pull Enable: Internal pullup or pulldown resistor is not enabled on the corresponding pin. */
      | PORT_PCR_SRE(PCR_SRE_SLOW)                           /* Slew Rate Enable: Slow slew rate is configured on the corresponding pin, if the pin is configured as a digital output. */
    );
  PORT_SetPinMux(PORTD, PIN2_IDX, kPORT_PinDisabledOrAnalog); /* PORTD2 (pin 59) is configured as LCD_P42 */
  PORTD->PCR[2] = ((PORTD->PCR[2] &
    (~(PORT_PCR_PS_MASK | PORT_PCR_PE_MASK | PORT_PCR_SRE_MASK | PORT_PCR_ISF_MASK))) /* Mask bits to zero which are setting */
      | PORT_PCR_PS(PCR_PS_UP)                               /* Pull Select: Internal pullup resistor is enabled on the corresponding pin, if the corresponding PE field is set. */
      | PORT_PCR_PE(PCR_PE_DISABLED)                         /* Pull Enable: Internal pullup or pulldown resistor is not enabled on the corresponding pin. */
      | PORT_PCR_SRE(PCR_SRE_SLOW)                           /* Slew Rate Enable: Slow slew rate is configured on the corresponding pin, if the pin is configured as a digital output. */
    );
  PORT_SetPinMux(PORTD, PIN3_IDX, kPORT_PinDisabledOrAnalog); /* PORTD3 (pin 60) is configured as LCD_P43 */
  PORTD->PCR[3] = ((PORTD->PCR[3] &
    (~(PORT_PCR_PS_MASK | PORT_PCR_PE_MASK | PORT_PCR_SRE_MASK | PORT_PCR_ISF_MASK))) /* Mask bits to zero which are setting */
      | PORT_PCR_PS(PCR_PS_UP)                               /* Pull Select: Internal pullup resistor is enabled on the corresponding pin, if the corresponding PE field is set. */
      | PORT_PCR_PE(PCR_PE_DISABLED)                         /* Pull Enable: Internal pullup or pulldown resistor is not enabled on the corresponding pin. */
      | PORT_PCR_SRE(PCR_SRE_SLOW)                           /* Slew Rate Enable: Slow slew rate is configured on the corresponding pin, if the pin is configured as a digital output. */
    );
  PORT_SetPinMux(PORTD, PIN4_IDX, kPORT_PinDisabledOrAnalog); /* PORTD4 (pin 61) is configured as LCD_P44 */
  PORTD->PCR[4] = ((PORTD->PCR[4] &
    (~(PORT_PCR_PS_MASK | PORT_PCR_PE_MASK | PORT_PCR_SRE_MASK | PORT_PCR_ISF_MASK))) /* Mask bits to zero which are setting */
      | PORT_PCR_PS(PCR_PS_UP)                               /* Pull Select: Internal pullup resistor is enabled on the corresponding pin, if the corresponding PE field is set. */
      | PORT_PCR_PE(PCR_PE_DISABLED)                         /* Pull Enable: Internal pullup or pulldown resistor is not enabled on the corresponding pin. */
      | PORT_PCR_SRE(PCR_SRE_SLOW)                           /* Slew Rate Enable: Slow slew rate is configured on the corresponding pin, if the pin is configured as a digital output. */
    );
  PORT_SetPinMux(PORTE, PIN20_IDX, kPORT_PinDisabledOrAnalog); /* PORTE20 (pin 9) is configured as LCD_P59 */
  PORTE->PCR[20] = ((PORTE->PCR[20] &
    (~(PORT_PCR_PS_MASK | PORT_PCR_PE_MASK | PORT_PCR_SRE_MASK | PORT_PCR_ISF_MASK))) /* Mask bits to zero which are setting */
      | PORT_PCR_PS(PCR_PS_UP)                               /* Pull Select: Internal pullup resistor is enabled on the corresponding pin, if the corresponding PE field is set. */
      | PORT_PCR_PE(PCR_PE_DISABLED)                         /* Pull Enable: Internal pullup or pulldown resistor is not enabled on the corresponding pin. */
      | PORT_PCR_SRE(PCR_SRE_SLOW)                           /* Slew Rate Enable: Slow slew rate is configured on the corresponding pin, if the pin is configured as a digital output. */
    );
  PORT_SetPinMux(PORTE, PIN21_IDX, kPORT_PinDisabledOrAnalog); /* PORTE21 (pin 10) is configured as LCD_P60 */
  PORTE->PCR[21] = ((PORTE->PCR[21] &
    (~(PORT_PCR_PS_MASK | PORT_PCR_PE_MASK | PORT_PCR_SRE_MASK | PORT_PCR_ISF_MASK))) /* Mask bits to zero which are setting */
      | PORT_PCR_PS(PCR_PS_UP)                               /* Pull Select: Internal pullup resistor is enabled on the corresponding pin, if the corresponding PE field is set. */
      | PORT_PCR_PE(PCR_PE_DISABLED)                         /* Pull Enable: Internal pullup or pulldown resistor is not enabled on the corresponding pin. */
      | PORT_PCR_SRE(PCR_SRE_SLOW)                           /* Slew Rate Enable: Slow slew rate is configured on the corresponding pin, if the pin is configured as a digital output. */
    );
}



#define PIN3_IDX                         3u   /*!< Pin number for pin 3 in a port */

#define PIN4_IDX                         4u   /*!< Pin number for pin 4 in a port */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_InitBUTTONS:
- options: {prefix: BOARD_, coreID: core0, enableClock: 'true'}
- pin_list:
  - {pin_num: '26', peripheral: GPIOA, signal: 'GPIO, 4', pin_signal: PTA4/I2C1_SDA/TPM0_CH1/NMI_b, direction: INPUT, slew_rate: fast, pull_select: up, pull_enable: enable,
    passive_filter: disable}
  - {pin_num: '46', peripheral: GPIOC, signal: 'GPIO, 3', pin_signal: LCD_P23/PTC3/LLWU_P7/SPI1_SCK/LPUART1_RX/TPM0_CH2/CLKOUT/I2S0_TX_BCLK, direction: INPUT, slew_rate: fast,
    drive_strength: low, pull_select: up, pull_enable: enable}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */

/*FUNCTION**********************************************************************
 *
 * Function Name : BOARD_InitBUTTONS
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 *END**************************************************************************/
void BOARD_InitBUTTONS(void) {
  CLOCK_EnableClock(kCLOCK_PortA);                           /* Port A Clock Gate Control: Clock enabled */
  CLOCK_EnableClock(kCLOCK_PortC);                           /* Port C Clock Gate Control: Clock enabled */

  const port_pin_config_t porta4_pin26_config = {
    kPORT_PullUp,                                            /* Internal pull-up resistor is enabled */
    kPORT_FastSlewRate,                                      /* Fast slew rate is configured */
    kPORT_PassiveFilterDisable,                              /* Passive filter is disabled */
    kPORT_LowDriveStrength,                                  /* Low drive strength is configured */
    kPORT_MuxAsGpio,                                         /* Pin is configured as PTA4 */
  };
  PORT_SetPinConfig(PORTA, PIN4_IDX, &porta4_pin26_config);  /* PORTA4 (pin 26) is configured as PTA4 */
  const port_pin_config_t portc3_pin46_config = {
    kPORT_PullUp,                                            /* Internal pull-up resistor is enabled */
    kPORT_FastSlewRate,                                      /* Fast slew rate is configured */
    kPORT_PassiveFilterDisable,                              /* Passive filter is disabled */
    kPORT_LowDriveStrength,                                  /* Low drive strength is configured */
    kPORT_MuxAsGpio,                                         /* Pin is configured as PTC3 */
  };
  PORT_SetPinConfig(PORTC, PIN3_IDX, &portc3_pin46_config);  /* PORTC3 (pin 46) is configured as PTC3 */
}


#define PIN5_IDX                         5u   /*!< Pin number for pin 5 in a port */
#define PIN31_IDX                       31u   /*!< Pin number for pin 31 in a port */

/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_InitLEDs:
- options: {prefix: BOARD_, coreID: core0, enableClock: 'true'}
- pin_list:
  - {pin_num: '19', peripheral: GPIOE, signal: 'GPIO, 31', pin_signal: PTE31/TPM0_CH4, direction: OUTPUT, slew_rate: slow, pull_select: down, pull_enable: disable}
  - {pin_num: '62', peripheral: GPIOD, signal: 'GPIO, 5', pin_signal: LCD_P45/ADC0_SE6b/PTD5/SPI1_SCK/UART2_TX/TPM0_CH5/FXIO0_D5, direction: OUTPUT, slew_rate: slow,
    pull_select: down, pull_enable: disable}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */

/*FUNCTION**********************************************************************
 *
 * Function Name : BOARD_InitLEDs
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 *END**************************************************************************/
void BOARD_InitLEDs(void) {
  CLOCK_EnableClock(kCLOCK_PortD);                           /* Port D Clock Gate Control: Clock enabled */
  CLOCK_EnableClock(kCLOCK_PortE);                           /* Port E Clock Gate Control: Clock enabled */

//  const port_pin_config_t portd5_pin62_config = {
//    kPORT_PullDisable,                                       /* Internal pull-up/down resistor is disabled */
//    kPORT_SlowSlewRate,                                      /* Slow slew rate is configured */
//    kPORT_PassiveFilterDisable,                              /* Passive filter is disabled */
//    kPORT_LowDriveStrength,                                  /* Low drive strength is configured */
//    kPORT_MuxAsGpio,                                         /* Pin is configured as PTD5 */
//  };
//  PORT_SetPinConfig(PORTD, PIN5_IDX, &portd5_pin62_config);  /* PORTD5 (pin 62) is configured as PTD5 */
  const port_pin_config_t porte31_pin19_config = {
    kPORT_PullDisable,                                       /* Internal pull-up/down resistor is disabled */
    kPORT_SlowSlewRate,                                      /* Slow slew rate is configured */
    kPORT_PassiveFilterDisable,                              /* Passive filter is disabled */
    kPORT_LowDriveStrength,                                  /* Low drive strength is configured */
    kPORT_MuxAsGpio,                                         /* Pin is configured as PTE31 */
  };
  PORT_SetPinConfig(PORTE, PIN31_IDX, &porte31_pin19_config); /* PORTE31 (pin 19) is configured as PTE31 */
}



#define PIN1_IDX                         1u   /*!< Pin number for pin 1 in a port */

#define PIN2_IDX                         2u   /*!< Pin number for pin 2 in a port */
#define SOPT5_LPUART0RXSRC_LPUART_RX  0x00u   /*!< LPUART0 Receive Data Source Select: LPUART_RX pin */
#define SOPT5_LPUART0TXSRC_LPUART_TX  0x00u   /*!< LPUART0 Transmit Data Source Select: LPUART0_TX pin */

/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_InitDEBUG_UART:
- options: {prefix: BOARD_, coreID: core0, enableClock: 'true'}
- pin_list:
  - {pin_num: '23', peripheral: LPUART0, signal: RX, pin_signal: PTA1/LPUART0_RX/TPM2_CH0, slew_rate: fast, pull_select: down, pull_enable: disable}
  - {pin_num: '24', peripheral: LPUART0, signal: TX, pin_signal: PTA2/LPUART0_TX/TPM2_CH1, direction: OUTPUT, slew_rate: fast, pull_select: down, pull_enable: disable}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */

/*FUNCTION**********************************************************************
 *
 * Function Name : BOARD_InitDEBUG_UART
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 *END**************************************************************************/
void BOARD_InitDEBUG_UART(void) {
  CLOCK_EnableClock(kCLOCK_PortA);                           /* Port A Clock Gate Control: Clock enabled */

  const port_pin_config_t porta1_pin23_config = {
    kPORT_PullDisable,                                       /* Internal pull-up/down resistor is disabled */
    kPORT_FastSlewRate,                                      /* Fast slew rate is configured */
    kPORT_PassiveFilterDisable,                              /* Passive filter is disabled */
    kPORT_LowDriveStrength,                                  /* Low drive strength is configured */
    kPORT_MuxAlt2,                                           /* Pin is configured as LPUART0_RX */
  };
  PORT_SetPinConfig(PORTA, PIN1_IDX, &porta1_pin23_config);  /* PORTA1 (pin 23) is configured as LPUART0_RX */
  const port_pin_config_t porta2_pin24_config = {
    kPORT_PullDisable,                                       /* Internal pull-up/down resistor is disabled */
    kPORT_FastSlewRate,                                      /* Fast slew rate is configured */
    kPORT_PassiveFilterDisable,                              /* Passive filter is disabled */
    kPORT_LowDriveStrength,                                  /* Low drive strength is configured */
    kPORT_MuxAlt2,                                           /* Pin is configured as LPUART0_TX */
  };
  PORT_SetPinConfig(PORTA, PIN2_IDX, &porta2_pin24_config);  /* PORTA2 (pin 24) is configured as LPUART0_TX */
  SIM->SOPT5 = ((SIM->SOPT5 &
    (~(SIM_SOPT5_LPUART0TXSRC_MASK | SIM_SOPT5_LPUART0RXSRC_MASK))) /* Mask bits to zero which are setting */
      | SIM_SOPT5_LPUART0TXSRC(SOPT5_LPUART0TXSRC_LPUART_TX) /* LPUART0 Transmit Data Source Select: LPUART0_TX pin */
      | SIM_SOPT5_LPUART0RXSRC(SOPT5_LPUART0RXSRC_LPUART_RX) /* LPUART0 Receive Data Source Select: LPUART_RX pin */
    );
}



#define PCR_PE_DISABLED               0x00u   /*!< Pull Enable: Internal pullup or pulldown resistor is not enabled on the corresponding pin. */

#define PCR_PS_UP                     0x01u   /*!< Pull Select: Internal pullup resistor is enabled on the corresponding pin, if the corresponding PE field is set. */
#define PCR_SRE_FAST                  0x00u   /*!< Slew Rate Enable: Fast slew rate is configured on the corresponding pin, if the pin is configured as a digital output. */

#define PIN0_IDX                         0u   /*!< Pin number for pin 0 in a port */

#define PIN5_IDX                         5u   /*!< Pin number for pin 5 in a port */

/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_InitUSB:
- options: {prefix: BOARD_, coreID: core0, enableClock: 'true'}
- pin_list:
  - {pin_num: '5', peripheral: USB0, signal: DP, pin_signal: USB0_DP}
  - {pin_num: '6', peripheral: USB0, signal: DM, pin_signal: USB0_DM}
  - {pin_num: '8', peripheral: USB0, signal: VREGIN, pin_signal: VREGIN}
  - {pin_num: '43', peripheral: USB0, signal: SOF_OUT, pin_signal: LCD_P20/ADC0_SE14/PTC0/EXTRG_IN/USB_SOF_OUT/CMP0_OUT/I2S0_TXD0, identifier: USB_SOF_OUT, slew_rate: fast,
    pull_select: up, pull_enable: disable}
  - {pin_num: '27', peripheral: USB0, signal: CLKIN, pin_signal: PTA5/USB_CLKIN/TPM0_CH2/I2S0_TX_BCLK, slew_rate: fast, pull_select: up, pull_enable: disable}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */

/*FUNCTION**********************************************************************
 *
 * Function Name : BOARD_InitUSB
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 *END**************************************************************************/
void BOARD_InitUSB(void) {
  CLOCK_EnableClock(kCLOCK_PortA);                           /* Port A Clock Gate Control: Clock enabled */
  CLOCK_EnableClock(kCLOCK_PortC);                           /* Port C Clock Gate Control: Clock enabled */

  PORT_SetPinMux(PORTA, PIN5_IDX, kPORT_MuxAlt2);            /* PORTA5 (pin 27) is configured as USB_CLKIN */
  PORTA->PCR[5] = ((PORTA->PCR[5] &
    (~(PORT_PCR_PS_MASK | PORT_PCR_PE_MASK | PORT_PCR_SRE_MASK | PORT_PCR_ISF_MASK))) /* Mask bits to zero which are setting */
      | PORT_PCR_PS(PCR_PS_UP)                               /* Pull Select: Internal pullup resistor is enabled on the corresponding pin, if the corresponding PE field is set. */
      | PORT_PCR_PE(PCR_PE_DISABLED)                         /* Pull Enable: Internal pullup or pulldown resistor is not enabled on the corresponding pin. */
      | PORT_PCR_SRE(PCR_SRE_FAST)                           /* Slew Rate Enable: Fast slew rate is configured on the corresponding pin, if the pin is configured as a digital output. */
    );
  PORT_SetPinMux(PORTC, PIN0_IDX, kPORT_MuxAlt4);            /* PORTC0 (pin 43) is configured as USB_SOF_OUT */
  PORTC->PCR[0] = ((PORTC->PCR[0] &
    (~(PORT_PCR_PS_MASK | PORT_PCR_PE_MASK | PORT_PCR_SRE_MASK | PORT_PCR_ISF_MASK))) /* Mask bits to zero which are setting */
      | PORT_PCR_PS(PCR_PS_UP)                               /* Pull Select: Internal pullup resistor is enabled on the corresponding pin, if the corresponding PE field is set. */
      | PORT_PCR_PE(PCR_PE_DISABLED)                         /* Pull Enable: Internal pullup or pulldown resistor is not enabled on the corresponding pin. */
      | PORT_PCR_SRE(PCR_SRE_FAST)                           /* Slew Rate Enable: Fast slew rate is configured on the corresponding pin, if the pin is configured as a digital output. */
    );
}



#define PCR_PE_DISABLED               0x00u   /*!< Pull Enable: Internal pullup or pulldown resistor is not enabled on the corresponding pin. */

#define PCR_PS_UP                     0x01u   /*!< Pull Select: Internal pullup resistor is enabled on the corresponding pin, if the corresponding PE field is set. */

#define PCR_SRE_FAST                  0x00u   /*!< Slew Rate Enable: Fast slew rate is configured on the corresponding pin, if the pin is configured as a digital output. */

#define PIN1_IDX                         1u   /*!< Pin number for pin 1 in a port */

#define PIN5_IDX                         5u   /*!< Pin number for pin 5 in a port */
#define PIN24_IDX                       24u   /*!< Pin number for pin 24 in a port */
#define PIN25_IDX                       25u   /*!< Pin number for pin 25 in a port */

/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_InitACCEL_I2C:
- options: {prefix: BOARD_, coreID: core0, enableClock: 'true'}
- pin_list:
  - {pin_num: '20', peripheral: I2C0, signal: SCL, pin_signal: PTE24/TPM0_CH0/I2C0_SCL, slew_rate: fast, pull_select: up, pull_enable: enable}
  - {pin_num: '21', peripheral: I2C0, signal: SDA, pin_signal: PTE25/TPM0_CH1/I2C0_SDA, slew_rate: fast, pull_select: up, pull_enable: enable}
  - {pin_num: '58', peripheral: GPIOD, signal: 'GPIO, 1', pin_signal: LCD_P41/ADC0_SE5b/PTD1/SPI0_SCK/TPM0_CH1/FXIO0_D1, identifier: INT2_ACCEL, direction: INPUT,
    slew_rate: fast, pull_select: up, pull_enable: disable}
  - {pin_num: '54', peripheral: GPIOC, signal: 'GPIO, 5', pin_signal: LCD_P25/PTC5/LLWU_P9/SPI0_SCK/LPTMR0_ALT2/I2S0_RXD0/CMP0_OUT, identifier: INT1_ACCEL, direction: INPUT,
    slew_rate: fast, pull_select: up, pull_enable: disable}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */

/*FUNCTION**********************************************************************
 *
 * Function Name : BOARD_InitACCEL_I2C
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 *END**************************************************************************/
void BOARD_InitACCEL_I2C(void) {
  CLOCK_EnableClock(kCLOCK_PortC);                           /* Port C Clock Gate Control: Clock enabled */
  CLOCK_EnableClock(kCLOCK_PortD);                           /* Port D Clock Gate Control: Clock enabled */
  CLOCK_EnableClock(kCLOCK_PortE);                           /* Port E Clock Gate Control: Clock enabled */

  PORT_SetPinMux(PORTC, PIN5_IDX, kPORT_MuxAsGpio);          /* PORTC5 (pin 54) is configured as PTC5 */
  PORTC->PCR[5] = ((PORTC->PCR[5] &
    (~(PORT_PCR_PS_MASK | PORT_PCR_PE_MASK | PORT_PCR_SRE_MASK | PORT_PCR_ISF_MASK))) /* Mask bits to zero which are setting */
      | PORT_PCR_PS(PCR_PS_UP)                               /* Pull Select: Internal pullup resistor is enabled on the corresponding pin, if the corresponding PE field is set. */
      | PORT_PCR_PE(PCR_PE_DISABLED)                         /* Pull Enable: Internal pullup or pulldown resistor is not enabled on the corresponding pin. */
      | PORT_PCR_SRE(PCR_SRE_FAST)                           /* Slew Rate Enable: Fast slew rate is configured on the corresponding pin, if the pin is configured as a digital output. */
    );
  PORT_SetPinMux(PORTD, PIN1_IDX, kPORT_MuxAsGpio);          /* PORTD1 (pin 58) is configured as PTD1 */
  PORTD->PCR[1] = ((PORTD->PCR[1] &
    (~(PORT_PCR_PS_MASK | PORT_PCR_PE_MASK | PORT_PCR_SRE_MASK | PORT_PCR_ISF_MASK))) /* Mask bits to zero which are setting */
      | PORT_PCR_PS(PCR_PS_UP)                               /* Pull Select: Internal pullup resistor is enabled on the corresponding pin, if the corresponding PE field is set. */
      | PORT_PCR_PE(PCR_PE_DISABLED)                         /* Pull Enable: Internal pullup or pulldown resistor is not enabled on the corresponding pin. */
      | PORT_PCR_SRE(PCR_SRE_FAST)                           /* Slew Rate Enable: Fast slew rate is configured on the corresponding pin, if the pin is configured as a digital output. */
    );
  const port_pin_config_t porte24_pin20_config = {
    kPORT_PullUp,                                            /* Internal pull-up resistor is enabled */
    kPORT_FastSlewRate,                                      /* Fast slew rate is configured */
    kPORT_PassiveFilterDisable,                              /* Passive filter is disabled */
    kPORT_LowDriveStrength,                                  /* Low drive strength is configured */
    kPORT_MuxAlt5,                                           /* Pin is configured as I2C0_SCL */
  };
  PORT_SetPinConfig(PORTE, PIN24_IDX, &porte24_pin20_config); /* PORTE24 (pin 20) is configured as I2C0_SCL */
  const port_pin_config_t porte25_pin21_config = {
    kPORT_PullUp,                                            /* Internal pull-up resistor is enabled */
    kPORT_FastSlewRate,                                      /* Fast slew rate is configured */
    kPORT_PassiveFilterDisable,                              /* Passive filter is disabled */
    kPORT_LowDriveStrength,                                  /* Low drive strength is configured */
    kPORT_MuxAlt5,                                           /* Pin is configured as I2C0_SDA */
  };
  PORT_SetPinConfig(PORTE, PIN25_IDX, &porte25_pin21_config); /* PORTE25 (pin 21) is configured as I2C0_SDA */
}


/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_InitOSC:
- options: {prefix: BOARD_, coreID: core0, enableClock: 'true'}
- pin_list:
  - {pin_num: '32', peripheral: OSC0, signal: EXTAL0, pin_signal: EXTAL0/PTA18/LPUART1_RX/TPM_CLKIN0, slew_rate: no_init, pull_select: no_init, pull_enable: no_init}
  - {pin_num: '33', peripheral: OSC0, signal: XTAL0, pin_signal: XTAL0/PTA19/LPUART1_TX/TPM_CLKIN1/LPTMR0_ALT1, slew_rate: no_init, pull_select: no_init, pull_enable: no_init}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */

/*FUNCTION**********************************************************************
 *
 * Function Name : BOARD_InitOSC
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 *END**************************************************************************/
void BOARD_InitOSC(void) {
  CLOCK_EnableClock(kCLOCK_PortA);                           /* Port A Clock Gate Control: Clock enabled */

  PORT_SetPinMux(PORTA, PIN18_IDX, kPORT_PinDisabledOrAnalog); /* PORTA18 (pin 32) is configured as EXTAL0 */
  PORT_SetPinMux(PORTA, PIN19_IDX, kPORT_PinDisabledOrAnalog); /* PORTA19 (pin 33) is configured as XTAL0 */
}

/*******************************************************************************
 * EOF
 ******************************************************************************/
