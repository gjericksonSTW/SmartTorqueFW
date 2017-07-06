#ifndef _PIN_MUX_H_
#define _PIN_MUX_H_


/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @brief Direction type  */
typedef enum _pin_mux_direction
{
  kPIN_MUX_DirectionInput = 0U,         /* Input direction */
  kPIN_MUX_DirectionOutput = 1U,        /* Output direction */
  kPIN_MUX_DirectionInputOrOutput = 2U  /* Input or output direction */
} pin_mux_direction_t;

/*!
 * @addtogroup pin_mux
 * @{
 */

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @brief Calls initialization functions.
 *
 */
void BOARD_InitBootPins(void);

/* PORTE1 (number 2), J2[12]/D15/I2C1_SCL/LCD_P49 */
#define BOARD_I2C1_SCL_PERIPHERAL                                           I2C1   /*!< Device name: I2C1 */
#define BOARD_I2C1_SCL_SIGNAL                                                SCL   /*!< I2C1 signal: SCL */
#define BOARD_I2C1_SCL_PIN_NAME                                         I2C1_SCL   /*!< Pin name */
#define BOARD_I2C1_SCL_LABEL                       "J2[12]/D15/I2C1_SCL/LCD_P49"   /*!< Label */
#define BOARD_I2C1_SCL_NAME                                           "I2C1_SCL"   /*!< Identifier name */

/* PORTC2 (number 45), J4[10]/A4/LCD_P22/I2S_TXD0 */
#define BOARD_I2S0_TX_FS_PERIPHERAL                                         ADC0   /*!< Device name: ADC0 */
#define BOARD_I2S0_TX_FS_SIGNAL                                               SE   /*!< ADC0 signal: SE */
#define BOARD_I2S0_TX_FS_CHANNEL                                              11   /*!< ADC0 SE channel: 11 */
#define BOARD_I2S0_TX_FS_PIN_NAME                                      ADC0_SE11   /*!< Pin name */
#define BOARD_I2S0_TX_FS_LABEL                      "J4[10]/A4/LCD_P22/I2S_TXD0"   /*!< Label */
#define BOARD_I2S0_TX_FS_NAME                                       "I2S0_TX_FS"   /*!< Identifier name */


/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitPins(void);

/* PORTB18 (number 41), J1[1]/I2S_TX_BCLK/LCD_P14 */
#define BOARD_LCD_P14_PERIPHERAL                                             LCD   /*!< Device name: LCD */
#define BOARD_LCD_P14_SIGNAL                                                   P   /*!< LCD signal: P */
#define BOARD_LCD_P14_CHANNEL                                                 14   /*!< LCD P channel: 14 */
#define BOARD_LCD_P14_PIN_NAME                                           LCD_P14   /*!< Pin name */
#define BOARD_LCD_P14_LABEL                          "J1[1]/I2S_TX_BCLK/LCD_P14"   /*!< Label */
#define BOARD_LCD_P14_NAME                                             "LCD_P14"   /*!< Identifier name */

/* PORTB19 (number 42), J1[3]/I2S_TX_FS/LCD_P15 */
#define BOARD_LCD_P15_PERIPHERAL                                             LCD   /*!< Device name: LCD */
#define BOARD_LCD_P15_SIGNAL                                                   P   /*!< LCD signal: P */
#define BOARD_LCD_P15_CHANNEL                                                 15   /*!< LCD P channel: 15 */
#define BOARD_LCD_P15_PIN_NAME                                           LCD_P15   /*!< Pin name */
#define BOARD_LCD_P15_LABEL                            "J1[3]/I2S_TX_FS/LCD_P15"   /*!< Label */
#define BOARD_LCD_P15_NAME                                             "LCD_P15"   /*!< Identifier name */

/* PORTC0 (number 43), J1[5]/I2S_TXD/LCD_P20 */
#define BOARD_LCD_P20_PERIPHERAL                                             LCD   /*!< Device name: LCD */
#define BOARD_LCD_P20_SIGNAL                                                   P   /*!< LCD signal: P */
#define BOARD_LCD_P20_CHANNEL                                                 20   /*!< LCD P channel: 20 */
#define BOARD_LCD_P20_PIN_NAME                                           LCD_P20   /*!< Pin name */
#define BOARD_LCD_P20_LABEL                              "J1[5]/I2S_TXD/LCD_P20"   /*!< Label */
#define BOARD_LCD_P20_NAME                                             "LCD_P20"   /*!< Identifier name */

/* PORTC4 (number 53), J1[7]/I2S_MCLK/LCD_P24 */
#define BOARD_LCD_P24_PERIPHERAL                                             LCD   /*!< Device name: LCD */
#define BOARD_LCD_P24_SIGNAL                                                   P   /*!< LCD signal: P */
#define BOARD_LCD_P24_CHANNEL                                                 24   /*!< LCD P channel: 24 */
#define BOARD_LCD_P24_PIN_NAME                                           LCD_P24   /*!< Pin name */
#define BOARD_LCD_P24_LABEL                             "J1[7]/I2S_MCLK/LCD_P24"   /*!< Label */
#define BOARD_LCD_P24_NAME                                             "LCD_P24"   /*!< Identifier name */

/* PORTC6 (number 55), J1[9]/I2S_RX_BCLK/LCD_P26 */
#define BOARD_LCD_P26_PERIPHERAL                                             LCD   /*!< Device name: LCD */
#define BOARD_LCD_P26_SIGNAL                                                   P   /*!< LCD signal: P */
#define BOARD_LCD_P26_CHANNEL                                                 26   /*!< LCD P channel: 26 */
#define BOARD_LCD_P26_PIN_NAME                                           LCD_P26   /*!< Pin name */
#define BOARD_LCD_P26_LABEL                          "J1[9]/I2S_RX_BCLK/LCD_P26"   /*!< Label */
#define BOARD_LCD_P26_NAME                                             "LCD_P26"   /*!< Identifier name */

/* PORTC7 (number 56), J1[11]/I2S_RX_FS/USB_SOF_OUT/LCD_P27 */
#define BOARD_LCD_P27_PERIPHERAL                                             LCD   /*!< Device name: LCD */
#define BOARD_LCD_P27_SIGNAL                                                   P   /*!< LCD signal: P */
#define BOARD_LCD_P27_CHANNEL                                                 27   /*!< LCD P channel: 27 */
#define BOARD_LCD_P27_PIN_NAME                                           LCD_P27   /*!< Pin name */
#define BOARD_LCD_P27_LABEL               "J1[11]/I2S_RX_FS/USB_SOF_OUT/LCD_P27"   /*!< Label */
#define BOARD_LCD_P27_NAME                                             "LCD_P27"   /*!< Identifier name */

/* PORTD0 (number 57), LCD_P40 */
#define BOARD_LCD_P40_PERIPHERAL                                             LCD   /*!< Device name: LCD */
#define BOARD_LCD_P40_SIGNAL                                                   P   /*!< LCD signal: P */
#define BOARD_LCD_P40_CHANNEL                                                 40   /*!< LCD P channel: 40 */
#define BOARD_LCD_P40_PIN_NAME                                           LCD_P40   /*!< Pin name */
#define BOARD_LCD_P40_LABEL                                            "LCD_P40"   /*!< Label */
#define BOARD_LCD_P40_NAME                                             "LCD_P40"   /*!< Identifier name */

/* PORTD2 (number 59), J2[4]/D9/LCD_P42 */
#define BOARD_LCD_P42_PERIPHERAL                                             LCD   /*!< Device name: LCD */
#define BOARD_LCD_P42_SIGNAL                                                   P   /*!< LCD signal: P */
#define BOARD_LCD_P42_CHANNEL                                                 42   /*!< LCD P channel: 42 */
#define BOARD_LCD_P42_PIN_NAME                                           LCD_P42   /*!< Pin name */
#define BOARD_LCD_P42_LABEL                                   "J2[4]/D9/LCD_P42"   /*!< Label */
#define BOARD_LCD_P42_NAME                                             "LCD_P42"   /*!< Identifier name */

/* PORTD3 (number 60), J1[6]/D2/LCD_P43 */
#define BOARD_LCD_P43_PERIPHERAL                                             LCD   /*!< Device name: LCD */
#define BOARD_LCD_P43_SIGNAL                                                   P   /*!< LCD signal: P */
#define BOARD_LCD_P43_CHANNEL                                                 43   /*!< LCD P channel: 43 */
#define BOARD_LCD_P43_PIN_NAME                                           LCD_P43   /*!< Pin name */
#define BOARD_LCD_P43_LABEL                                   "J1[6]/D2/LCD_P43"   /*!< Label */
#define BOARD_LCD_P43_NAME                                             "LCD_P43"   /*!< Identifier name */

/* PORTD4 (number 61), J2[6]/D10/SPI1_PCS0/LCD_P44 */
#define BOARD_LCD_P44_PERIPHERAL                                             LCD   /*!< Device name: LCD */
#define BOARD_LCD_P44_SIGNAL                                                   P   /*!< LCD signal: P */
#define BOARD_LCD_P44_CHANNEL                                                 44   /*!< LCD P channel: 44 */
#define BOARD_LCD_P44_PIN_NAME                                           LCD_P44   /*!< Pin name */
#define BOARD_LCD_P44_LABEL                        "J2[6]/D10/SPI1_PCS0/LCD_P44"   /*!< Label */
#define BOARD_LCD_P44_NAME                                             "LCD_P44"   /*!< Identifier name */

/* PORTE20 (number 9), J4[1]/DIFF_ADC0_DP/LCD_P59 */
#define BOARD_LCD_P59_PERIPHERAL                                             LCD   /*!< Device name: LCD */
#define BOARD_LCD_P59_SIGNAL                                                   P   /*!< LCD signal: P */
#define BOARD_LCD_P59_CHANNEL                                                 59   /*!< LCD P channel: 59 */
#define BOARD_LCD_P59_PIN_NAME                                           LCD_P59   /*!< Pin name */
#define BOARD_LCD_P59_LABEL                         "J4[1]/DIFF_ADC0_DP/LCD_P59"   /*!< Label */
#define BOARD_LCD_P59_NAME                                             "LCD_P59"   /*!< Identifier name */

/* PORTE21 (number 10), J4[3]/DIFF_ADC0_DM/LCD_P60 */
#define BOARD_LCD_P60_PERIPHERAL                                             LCD   /*!< Device name: LCD */
#define BOARD_LCD_P60_SIGNAL                                                   P   /*!< LCD signal: P */
#define BOARD_LCD_P60_CHANNEL                                                 60   /*!< LCD P channel: 60 */
#define BOARD_LCD_P60_PIN_NAME                                           LCD_P60   /*!< Pin name */
#define BOARD_LCD_P60_LABEL                         "J4[3]/DIFF_ADC0_DM/LCD_P60"   /*!< Label */
#define BOARD_LCD_P60_NAME                                             "LCD_P60"   /*!< Identifier name */


/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitLCD(void);

/* PORTA4 (number 26), J1[10]/D4/SW1 */
#define BOARD_SW1_GPIO                                                     GPIOA   /*!< GPIO device name: GPIOA */
#define BOARD_SW1_PORT                                                     PORTA   /*!< PORT device name: PORTA */
#define BOARD_SW1_GPIO_PIN                                                    4U   /*!< PORTA pin index: 4 */
#define BOARD_SW1_PIN_NAME                                                  PTA4   /*!< Pin name */
#define BOARD_SW1_LABEL                                          "J1[10]/D4/SW1"   /*!< Label */
#define BOARD_SW1_NAME                                                     "SW1"   /*!< Identifier name */
#define BOARD_SW1_DIRECTION                              kPIN_MUX_DirectionInput   /*!< Direction */

/* PORTC3 (number 46), SW3/LLWU_P7/LCD_P23 */
#define BOARD_SW3_GPIO                                                     GPIOC   /*!< GPIO device name: GPIOC */
#define BOARD_SW3_PORT                                                     PORTC   /*!< PORT device name: PORTC */
#define BOARD_SW3_GPIO_PIN                                                    3U   /*!< PORTC pin index: 3 */
#define BOARD_SW3_PIN_NAME                                                  PTC3   /*!< Pin name */
#define BOARD_SW3_LABEL                                    "SW3/LLWU_P7/LCD_P23"   /*!< Label */
#define BOARD_SW3_NAME                                                     "SW3"   /*!< Identifier name */
#define BOARD_SW3_DIRECTION                              kPIN_MUX_DirectionInput   /*!< Direction */


/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitBUTTONS(void);

/* PORTE31 (number 19), LED2 */
#define BOARD_LED2_GPIO                                                    GPIOE   /*!< GPIO device name: GPIOE */
#define BOARD_LED2_PORT                                                    PORTE   /*!< PORT device name: PORTE */
#define BOARD_LED2_GPIO_PIN                                                  31U   /*!< PORTE pin index: 31 */
#define BOARD_LED2_PIN_NAME                                                PTE31   /*!< Pin name */
#define BOARD_LED2_LABEL                                                  "LED2"   /*!< Label */
#define BOARD_LED2_NAME                                                   "LED2"   /*!< Identifier name */
#define BOARD_LED2_DIRECTION                            kPIN_MUX_DirectionOutput   /*!< Direction */

/* PORTD5 (number 62), J2[12]/D13/SPI1_SCK/LED1/LCD_P45 */
#define BOARD_LED1_GPIO                                                    GPIOD   /*!< GPIO device name: GPIOD */
#define BOARD_LED1_PORT                                                    PORTD   /*!< PORT device name: PORTD */
#define BOARD_LED1_GPIO_PIN                                                   5U   /*!< PORTD pin index: 5 */
#define BOARD_LED1_PIN_NAME                                                 PTD5   /*!< Pin name */
#define BOARD_LED1_LABEL                      "J2[12]/D13/SPI1_SCK/LED1/LCD_P45"   /*!< Label */
#define BOARD_LED1_NAME                                                   "LED1"   /*!< Identifier name */
#define BOARD_LED1_DIRECTION                            kPIN_MUX_DirectionOutput   /*!< Direction */


/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitLEDs(void);

/* PORTA1 (number 23), J1[2]/D0/UART0_RX */
#define BOARD_DEBUG_UART0_RX_PERIPHERAL                                  LPUART0   /*!< Device name: LPUART0 */
#define BOARD_DEBUG_UART0_RX_SIGNAL                                           RX   /*!< LPUART0 signal: RX */
#define BOARD_DEBUG_UART0_RX_PIN_NAME                                 LPUART0_RX   /*!< Pin name */
#define BOARD_DEBUG_UART0_RX_LABEL                           "J1[2]/D0/UART0_RX"   /*!< Label */
#define BOARD_DEBUG_UART0_RX_NAME                               "DEBUG_UART0_RX"   /*!< Identifier name */

/* PORTA2 (number 24), J1[4]/D1/UART0_TX */
#define BOARD_DEBUG_UART0_TX_PERIPHERAL                                  LPUART0   /*!< Device name: LPUART0 */
#define BOARD_DEBUG_UART0_TX_SIGNAL                                           TX   /*!< LPUART0 signal: TX */
#define BOARD_DEBUG_UART0_TX_PIN_NAME                                 LPUART0_TX   /*!< Pin name */
#define BOARD_DEBUG_UART0_TX_LABEL                           "J1[4]/D1/UART0_TX"   /*!< Label */
#define BOARD_DEBUG_UART0_TX_NAME                               "DEBUG_UART0_TX"   /*!< Identifier name */
#define BOARD_DEBUG_UART0_TX_DIRECTION                  kPIN_MUX_DirectionOutput   /*!< Direction */


/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitDEBUG_UART(void);

/* USB0_DP (number 5), J10[3]/USB_DP */
#define BOARD_USB0_DP_PERIPHERAL                                            USB0   /*!< Device name: USB0 */
#define BOARD_USB0_DP_SIGNAL                                                  DP   /*!< USB0 signal: DP */
#define BOARD_USB0_DP_PIN_NAME                                           USB0_DP   /*!< Pin name */
#define BOARD_USB0_DP_LABEL                                      "J10[3]/USB_DP"   /*!< Label */
#define BOARD_USB0_DP_NAME                                             "USB0_DP"   /*!< Identifier name */

/* USB0_DM (number 6), J10[2]/USB_DM */
#define BOARD_USB0_DM_PERIPHERAL                                            USB0   /*!< Device name: USB0 */
#define BOARD_USB0_DM_SIGNAL                                                  DM   /*!< USB0 signal: DM */
#define BOARD_USB0_DM_PIN_NAME                                           USB0_DM   /*!< Pin name */
#define BOARD_USB0_DM_LABEL                                      "J10[2]/USB_DM"   /*!< Label */
#define BOARD_USB0_DM_NAME                                             "USB0_DM"   /*!< Identifier name */

/* VREGIN (number 8), KL43Z_REGIN */
#define BOARD_VREGIN_PERIPHERAL                                             USB0   /*!< Device name: USB0 */
#define BOARD_VREGIN_SIGNAL                                               VREGIN   /*!< USB0 signal: VREGIN */
#define BOARD_VREGIN_PIN_NAME                                             VREGIN   /*!< Pin name */
#define BOARD_VREGIN_LABEL                                         "KL43Z_REGIN"   /*!< Label */
#define BOARD_VREGIN_NAME                                               "VREGIN"   /*!< Identifier name */

/* PORTC0 (number 43), J1[5]/I2S_TXD/LCD_P20 */
#define BOARD_USB_SOF_OUT_PERIPHERAL                                        USB0   /*!< Device name: USB0 */
#define BOARD_USB_SOF_OUT_SIGNAL                                         SOF_OUT   /*!< USB0 signal: SOF_OUT */
#define BOARD_USB_SOF_OUT_PIN_NAME                                   USB_SOF_OUT   /*!< Pin name */
#define BOARD_USB_SOF_OUT_LABEL                          "J1[5]/I2S_TXD/LCD_P20"   /*!< Label */
#define BOARD_USB_SOF_OUT_NAME                                     "USB_SOF_OUT"   /*!< Identifier name */

/* PORTA5 (number 27), J1[12]/D5/I2S_TX_BCLK */
#define BOARD_I2S0_TX_BCLK_PERIPHERAL                                       USB0   /*!< Device name: USB0 */
#define BOARD_I2S0_TX_BCLK_SIGNAL                                          CLKIN   /*!< USB0 signal: CLKIN */
#define BOARD_I2S0_TX_BCLK_PIN_NAME                                    USB_CLKIN   /*!< Pin name */
#define BOARD_I2S0_TX_BCLK_LABEL                         "J1[12]/D5/I2S_TX_BCLK"   /*!< Label */
#define BOARD_I2S0_TX_BCLK_NAME                                   "I2S0_TX_BCLK"   /*!< Identifier name */


/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitUSB(void);

/* PORTE24 (number 20), U2[7]/U10[4]/I2C0_SCL */
#define BOARD_I2C0_SCL_PERIPHERAL                                           I2C0   /*!< Device name: I2C0 */
#define BOARD_I2C0_SCL_SIGNAL                                                SCL   /*!< I2C0 signal: SCL */
#define BOARD_I2C0_SCL_PIN_NAME                                         I2C0_SCL   /*!< Pin name */
#define BOARD_I2C0_SCL_LABEL                             "U2[7]/U10[4]/I2C0_SCL"   /*!< Label */
#define BOARD_I2C0_SCL_NAME                                           "I2C0_SCL"   /*!< Identifier name */

/* PORTE25 (number 21), U2[6]/U10[6]/I2C0_SDA */
#define BOARD_I2C1_SDA_PERIPHERAL                                           I2C0   /*!< Device name: I2C0 */
#define BOARD_I2C1_SDA_SIGNAL                                                SDA   /*!< I2C0 signal: SDA */
#define BOARD_I2C1_SDA_PIN_NAME                                         I2C0_SDA   /*!< Pin name */
#define BOARD_I2C1_SDA_LABEL                             "U2[6]/U10[6]/I2C0_SDA"   /*!< Label */
#define BOARD_I2C1_SDA_NAME                                           "I2C1_SDA"   /*!< Identifier name */

/* PORTD1 (number 58), U2[9]/U10[9]/INT2_ACCEL/INT1_MAG/LCD_P41 */
#define BOARD_INT2_ACCEL_GPIO                                              GPIOD   /*!< GPIO device name: GPIOD */
#define BOARD_INT2_ACCEL_PORT                                              PORTD   /*!< PORT device name: PORTD */
#define BOARD_INT2_ACCEL_GPIO_PIN                                             1U   /*!< PORTD pin index: 1 */
#define BOARD_INT2_ACCEL_PIN_NAME                                           PTD1   /*!< Pin name */
#define BOARD_INT2_ACCEL_LABEL        "U2[9]/U10[9]/INT2_ACCEL/INT1_MAG/LCD_P41"   /*!< Label */
#define BOARD_INT2_ACCEL_NAME                                       "INT2_ACCEL"   /*!< Identifier name */
#define BOARD_INT2_ACCEL_DIRECTION                       kPIN_MUX_DirectionInput   /*!< Direction */

/* PORTC5 (number 54), J1[15]/I2S_RXD/INT1_ACCEL/LCD_P25 */
#define BOARD_INT1_ACCEL_GPIO                                              GPIOC   /*!< GPIO device name: GPIOC */
#define BOARD_INT1_ACCEL_PORT                                              PORTC   /*!< PORT device name: PORTC */
#define BOARD_INT1_ACCEL_GPIO_PIN                                             5U   /*!< PORTC pin index: 5 */
#define BOARD_INT1_ACCEL_PIN_NAME                                           PTC5   /*!< Pin name */
#define BOARD_INT1_ACCEL_LABEL               "J1[15]/I2S_RXD/INT1_ACCEL/LCD_P25"   /*!< Label */
#define BOARD_INT1_ACCEL_NAME                                       "INT1_ACCEL"   /*!< Identifier name */
#define BOARD_INT1_ACCEL_DIRECTION                       kPIN_MUX_DirectionInput   /*!< Direction */


/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitACCEL_I2C(void);

/* PORTA18 (number 32), EXTAL_32KHZ */
#define BOARD_EXTAL_32KHZ_PERIPHERAL                                        OSC0   /*!< Device name: OSC0 */
#define BOARD_EXTAL_32KHZ_SIGNAL                                          EXTAL0   /*!< OSC0 signal: EXTAL0 */
#define BOARD_EXTAL_32KHZ_PIN_NAME                                        EXTAL0   /*!< Pin name */
#define BOARD_EXTAL_32KHZ_LABEL                                    "EXTAL_32KHZ"   /*!< Label */
#define BOARD_EXTAL_32KHZ_NAME                                     "EXTAL_32KHZ"   /*!< Identifier name */

/* PORTA19 (number 33), XTAL_32KHZ */
#define BOARD_XTAL_32KHZ_PERIPHERAL                                         OSC0   /*!< Device name: OSC0 */
#define BOARD_XTAL_32KHZ_SIGNAL                                            XTAL0   /*!< OSC0 signal: XTAL0 */
#define BOARD_XTAL_32KHZ_PIN_NAME                                          XTAL0   /*!< Pin name */
#define BOARD_XTAL_32KHZ_LABEL                                      "XTAL_32KHZ"   /*!< Label */
#define BOARD_XTAL_32KHZ_NAME                                       "XTAL_32KHZ"   /*!< Identifier name */


/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitOSC(void);

#if defined(__cplusplus)
}
#endif

/*!
 * @}
 */
#endif /* _PIN_MUX_H_ */

/*******************************************************************************
 * EOF
 ******************************************************************************/
