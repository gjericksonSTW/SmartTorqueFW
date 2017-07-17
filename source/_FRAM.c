/*
 * _FRAM.c
 *
 *  Created on: Jun 13, 2017
 *      Author: gerickson
 */

#include "_FRAM.h"

/*******************************************************************************
 * Globals
 ******************************************************************************/

//Variables used for device discovery and register access
i2c_master_handle_t g_m_handle;
bool completionFlag;
bool nakFlag;
volatile i2c_FRAM_t _FRAM;

/*******************************************************************************
 * Code
 ******************************************************************************/

void i2c_master_callback(I2C_Type *base, i2c_master_handle_t *handle, status_t status, void *userData)
{
    /* Signal transfer success when received success status. */
    if (status == kStatus_Success)
    {
        completionFlag = true;
    }
    /* Signal transfer success when received success status. */
    if ((status == kStatus_I2C_Nak) || (status == kStatus_I2C_Addr_Nak))
    {
        nakFlag = true;
    }
}

void FRAM_INIT(void){

	i2c_master_config_t masterConfig;
	uint32_t sourceClock;

	// BOARD_I2C_ReleaseBus();
	I2C_MasterTransferCreateHandle(I2C_BASE, &g_m_handle, i2c_master_callback, NULL);

	// Configure I2C instance as a master with 100k baud and 48MHz clk
	I2C_MasterGetDefaultConfig(&masterConfig);
	masterConfig.baudRate_Bps = I2C_BAUD_RATE;
	masterConfig.enableMaster = true;
	sourceClock = CLK_SOURCE_FREQ;
	I2C_MasterInit(I2C_BASE, &masterConfig, sourceClock);

	_FRAM.write = write;
	_FRAM.read = read;
	_FRAM.master_handle = g_m_handle;
}

static void i2c_release_bus_delay(void)
{
    uint32_t i = 0;
    for (i = 0; i < 10; i++)
    {
        __NOP();
    }
}

void BOARD_I2C_ReleaseBus(void)
{
    uint8_t i = 0;
    gpio_pin_config_t pin_config;
    port_pin_config_t i2c_pin_config = {0};

    /* Config pin mux as gpio */
    i2c_pin_config.pullSelect = kPORT_PullUp;
    i2c_pin_config.mux = kPORT_MuxAsGpio;

    pin_config.pinDirection = kGPIO_DigitalOutput;
    pin_config.outputLogic = 1U;
    CLOCK_EnableClock(kCLOCK_PortE);
    PORT_SetPinConfig(SCL_PORT, SCL_PIN, &i2c_pin_config);
    PORT_SetPinConfig(SCL_PORT, SDA_PIN, &i2c_pin_config);

    GPIO_PinInit(SCL_GPIO, SCL_PIN, &pin_config);
    GPIO_PinInit(SDA_GPIO, SDA_PIN, &pin_config);

    /* Drive SDA low first to simulate a start */
    GPIO_WritePinOutput(SDA_GPIO, SDA_PIN, 0U);
    i2c_release_bus_delay();

    /* Send 9 pulses on SCL and keep SDA low */
    for (i = 0; i < 9; i++)
    {
        GPIO_WritePinOutput(SCL_GPIO, SCL_PIN, 0U);
        i2c_release_bus_delay();

        GPIO_WritePinOutput(SDA_GPIO, SDA_PIN, 1U);
        i2c_release_bus_delay();

        GPIO_WritePinOutput(SCL_GPIO, SCL_PIN, 1U);
        i2c_release_bus_delay();
        i2c_release_bus_delay();
    }

    /* Send stop */
    GPIO_WritePinOutput(SCL_GPIO, SCL_PIN, 0U);
    i2c_release_bus_delay();

    GPIO_WritePinOutput(SDA_GPIO, SDA_PIN, 0U);
    i2c_release_bus_delay();

    GPIO_WritePinOutput(SCL_GPIO, SCL_PIN, 1U);
    i2c_release_bus_delay();

    GPIO_WritePinOutput(SDA_GPIO, SDA_PIN, 1U);
    i2c_release_bus_delay();

    const port_pin_config_t i2c = {
           kPORT_PullUp,                                            /* Internal pull-up resistor is enabled */
           kPORT_FastSlewRate,                                      /* Fast slew rate is configured */
           kPORT_PassiveFilterDisable,                              /* Passive filter is disabled */
           kPORT_LowDriveStrength,                                  /* Low drive strength is configured */
           kPORT_MuxAlt6,                                           /* Pin is configured as I2C0_SCL */
         };

    PORT_SetPinConfig(PORTE, 0U, &i2c);
    PORT_SetPinConfig(PORTE, 1U, &i2c);
}

void write(uint16_t address, uint8_t* data, size_t dataSize, uint32_t flag){

	BOARD_I2C_ReleaseBus();

	i2c_master_transfer_t masterXfer;
	memset(&masterXfer, 0, sizeof(masterXfer));

	masterXfer.slaveAddress = FRAM_ADDR;
	masterXfer.direction = kI2C_Write;
	masterXfer.subaddress = address;

	masterXfer.subaddressSize = 2;
	masterXfer.data = data;
	masterXfer.dataSize = dataSize;
	masterXfer.flags = flag;

	I2C_MasterTransferNonBlocking(I2C_BASE, &g_m_handle, &masterXfer);

	while ((!nakFlag) && (!completionFlag))	{}

	nakFlag = false;

	if (completionFlag == true)
	{
		completionFlag = false;
	}
}

void read(uint16_t address, uint8_t* readBuff, size_t dataSize, uint32_t flag){

	 i2c_master_transfer_t masterXfer;
	 memset(&masterXfer, 0, sizeof(masterXfer));

	 masterXfer.slaveAddress = FRAM_ADDR;
	 masterXfer.direction = kI2C_Read;
	 masterXfer.subaddress = address;
	 masterXfer.subaddressSize = 2;
	 masterXfer.data = readBuff;
	 masterXfer.dataSize = dataSize;
	 masterXfer.flags = flag;

	 I2C_MasterTransferNonBlocking(I2C_BASE, &g_m_handle, &masterXfer);

	 while ((!nakFlag) && (!completionFlag))
		{
		}

	 nakFlag = false;

	 if (completionFlag == true)
	 {
		completionFlag = false;
	 }
}

