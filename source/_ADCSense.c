/*
 * ADCSense.c
 *
 *  Created on: Jun 12, 2017
 *      Author: gerickson
 */

#include <_ADCSense.h>

/*******************************************************************************
 * Globals
 ******************************************************************************/

//Global variables to be used for holding configuration settings and values
adc16_channel_config_t adc16ChanConfig;
adc16_config_t adc16Config;

//Global handles for the DMA
dma_handle_t DMA_handle;
dma_transfer_config_t DMA_transfer;

//Global variables for storing the ADC values and sending voltage values over the System Control
uint32_t volatile gTorqueSense;
uint32_t gMaxTorque;
uint32_t gBatterySense[8];
uint32_t volatile temp = 0;
uint32_t ADC16_Array[32];
volatile int TorqueVoltage, BatteryVoltage;

/*******************************************************************************
 * Code
 ******************************************************************************/

//Initialize ADC
void ADC_INIT(ADC_Type *base){

	ADC16_GetDefaultConfig(&adc16Config);
	TorqueVoltage = 0;
	BatteryVoltage = 40;
	temp = 0;

	//Use built in ADC clock
	adc16Config.clockSource = kADC16_ClockSourceAsynchronousClock;
	adc16Config.clockDivider = kADC16_ClockDivider1;

	//Enable low Power, do not need to sample fast enough for high power
	adc16Config.enableLowPower = 1;

	//Use exterior voltage reference of 3V
	adc16Config.referenceVoltageSource = kADC16_ReferenceVoltageSourceVref;

	//continuous conversion allows for the IRQ to work continuously
	adc16Config.enableContinuousConversion = false;

	//Use the 16 bit high resolution setting for maximum information
	adc16Config.resolution = kADC16_ResolutionSE16Bit;

	//enable the high speed conversion for ADC
	adc16Config.enableHighSpeed = true;

	//Use longest sample mode since a low rate of sampling is allowed
	adc16Config.longSampleMode = kADC16_LongSampleDisabled;

	//Initialize the ADC with settings
	ADC16_Init(base, &adc16Config);

	//Make sure that software trigger is set for ADC IRQ
	ADC16_EnableHardwareTrigger(base, true);

	//Channel B of pin 7 is used, set the Mux to push to channel B instead of A
	ADC16_SetChannelMuxMode(base, kADC16_ChannelMuxB);

	adc16ChanConfig.channelNumber = ADC16_BATTERY_CHANNEL;
	ADC16_SetChannelConfig(ADC16_BASE, ADC16_CHANNEL_GROUP, &adc16ChanConfig);

	//Use hardware averaging during sampling through ADC0
	//ADC16_SetHardwareAverage(ADC16_BASE, 3U);

	//Use Built-In Calibration
	ADC16_DoAutoCalibration(base);

	//Enable ADC to be connected to the DMA
	ADC16_EnableDMA(ADC16_BASE, true);

	// Initialize the DMA to handle ADC
	DMA_CONFIG();
	// Set the timing constraints for the Low Power Timer 1kHz clk src
	LPTMR_TRIG();
	// Set the Low Power Timer as hardware trigger for the ADC
	BOARD_ConfigTrigger();
	// Begin the Low Power Timer
	LPTMR_StartTimer(LPTMR_BASE);

	getMeasurements();
}

void BOARD_ConfigTrigger(void){
	/* Configure SIM for ADC hw trigger source selection */
	SIM->SOPT7 |= SIM_SOPT7_ADC0TRGSEL(14) | SIM_SOPT7_ADC0ALTTRGEN(1);
}

//Initialize the DMA for routing ADC information into a storage array
void DMA_CONFIG(void){

	//Initialize the DMAMUX to be set to service the ADC Peripheral
	DMAMUX_Init(DMAMUX_BASE);
	DMAMUX_SetSource(DMAMUX_BASE, DMA_CHANNEL, DMA_ADC_SRC);
	DMAMUX_EnableChannel(DMAMUX_BASE, DMA_CHANNEL);

	//Setup the DMA and create handle/ transfer structure
	DMA_Init(DMA_BASEADDR);
	DMA_CreateHandle(&DMA_handle, DMA_BASEADDR, DMA_CHANNEL);
	DMA_PrepareTransfer(&DMA_transfer, (void *)ADC16_RESULT_REG_ADDR, sizeof(uint32_t),
			(void*) ADC16_Array, sizeof(uint32_t),  sizeof(ADC16_Array),
			kDMA_PeripheralToMemory);

	DMA_SetTransferConfig(DMA_BASEADDR, DMA_CHANNEL, &DMA_transfer);
	/* Enable interrupt when transfer is done. */
	DMA_EnableInterrupts(DMA_BASEADDR, DMA_CHANNEL);
	/* Enable async DMA request. */
	DMA_EnableAsyncRequest(DMA_BASEADDR, DMA_CHANNEL, true);
	/* Forces a single read/write transfer per request. */
	DMA_EnableCycleSteal(DMA_BASEADDR, DMA_CHANNEL, true);
	/* Enable transfer. */
	DMA_StartTransfer(&DMA_handle);
	/* Enable IRQ. */
	NVIC_EnableIRQ(DMA_IRQ);
}

//Handle the ADC conversions with the DMA switching channels once every 5 minutes for the battery level
void DMA_IRQHandler(void){
	static uint16_t channelswap = 0;
	/* Stop trigger */
	LPTMR_StopTimer(LPTMR_BASE);
	/* Clear transaction done interrupt flag */
	DMA_ClearChannelStatusFlags(DMA_BASEADDR, DMA_CHANNEL, kDMA_TransactionsDoneFlag);
	/* Setup transfer to poll the battery every 5 minutes */
	if(channelswap < 100){
		adc16ChanConfig.channelNumber = ADC16_TORQUE_CHANNEL;
		ADC16_SetChannelConfig(ADC16_BASE, ADC16_CHANNEL_GROUP, &adc16ChanConfig);
		DMA_PrepareTransfer(&DMA_transfer, (void *)ADC16_RESULT_REG_ADDR, sizeof(uint32_t),
							(void *)ADC16_Array, sizeof(uint32_t), sizeof(ADC16_Array),
							kDMA_PeripheralToMemory);
		DMA_SetTransferConfig(DMA_BASEADDR, DMA_CHANNEL, &DMA_transfer);
		channelswap += 1;
	} else{
		adc16ChanConfig.channelNumber = ADC16_BATTERY_CHANNEL;
		ADC16_SetChannelConfig(ADC16_BASE, ADC16_CHANNEL_GROUP, &adc16ChanConfig);
		DMA_PrepareTransfer(&DMA_transfer, (void *)ADC16_RESULT_REG_ADDR, sizeof(uint32_t),
									(void *)gBatterySense, sizeof(uint32_t), sizeof(gBatterySense),
									kDMA_PeripheralToMemory);
		DMA_SetTransferConfig(DMA_BASEADDR, DMA_CHANNEL, &DMA_transfer);
		channelswap = 0;
	}
	LPTMR_StartTimer(LPTMR_BASE);
}

//Convert values from their binary value over to a voltage
void getMeasurements(void){

	uint32_t TorqueAve = 0;
	uint32_t BatteryAve = 0;

	for(uint8_t i = 0; i < 32; i ++){
		TorqueAve += ADC16_Array[i];
	}
	TorqueAve /= 32;
	TorqueVoltage = (int) ( 1000 * ( 3.12 * (double) TorqueAve / ADC_VDD ));

	for(uint8_t i = 0; i < 8; i++){
		BatteryAve += gBatterySense[i];
	}

	BatteryAve /= 8;
	BatteryVoltage = (int) ( 1000 * ( 3.12 * (double) BatteryAve / ADC_VDD ));
}

//enable the hardware trigger source for the ADC to DMA transfer / conversion
void LPTMR_TRIG(void){

	lptmr_config_t lptmrUserConfig;
	LPTMR_GetDefaultConfig(&lptmrUserConfig);

	/* Init LPTimer driver */
	LPTMR_Init(LPTMR_BASE, &lptmrUserConfig);

	/* Set the LPTimer period */
	LPTMR_SetTimerPeriod(LPTMR_BASE, CONV_RATE);
}

//ADC RTOS Task for handling both channels of interest
void vADC16Task(void *pvParameters){


	while(1){
		//Loop grabbing measurements from the registers and converting to the proper voltage level
		getMeasurements();
		vTaskDelay(66);
	}
}
