/*
 * _Bluetooth.c
 *
 *  Created on: Jun 12, 2017
 *      Author: gerickson
 */

#include <_Bluetooth.h>
#include "Public.h"

BGLIB_DEFINE();

/*******************************************************************************
 * Globals
 ******************************************************************************/

// Initialize globals for transmitting and receiving data over Bluetooth

// UART buffers for handling API calls from BLuegiga
uint8_t msg_Head[4];
uint8_t btBuffer[MAX_BT_LEN];
uint8_t respBuffer[MAX_BT_LEN];
struct dumo_cmd_packet* pck;

// Local name for the Bluetooth module **this is to be changed for each device**
char *localName = "CEM50N3X12G_BTD";

// Received Bluetooth messages
uint8_t Bluetooth_rx[64];
volatile uint8_t Bluetooth_len;
volatile bool message_recieved;

// Bluetooth Addresses
uint8_t my_address[6];
uint8_t connected_address[6];

// UART Handles & Configuration
uart_rtos_handle_t uart_handle;
struct _uart_handle t_uart_handle;
uart_rtos_config_t uart_config = {
		.baudrate = 115200,
		.parity = kUART_ParityDisabled,
		.stopbits = kUART_OneStopBit,
		.buffer = btBuffer,
		.buffer_size = sizeof(btBuffer)
};

// Variables to track the connection state and what the endpoint of host device is
uint8_t endpoint;
volatile bool BTConnected;

/***
 *  The counters used by the various examples.  The usage is described in the
 * comments at the top of this file.
 ***/
volatile uint8_t rxIndex;
volatile uint8_t serviceLocation;

/*******************************************************************************
 * Code
 ******************************************************************************/

/*	Function passes to the BG LIB for handling API calls by mapping messages and data to UART	*/
void on_message_send(uint8_t msg_len, uint8_t *msg_data, uint16_t data_len, uint8_t *data){

	/***
	 * Develop UART function to take API command and send it byte by byte to the BT121
	 * Handles message and data parameters separately, call another functions for UART transmit
	 * uart_send(msg_data, msg_len) . . . error control  . . .  uart_send(data, data_len) . . . error control
	***/
	for( uint8_t i = 0 ; i < msg_len; i++){
		UART_WriteByte(UART_BASE, msg_data[i]);
		while(!(UART_GetStatusFlags(UART_BASE) & kUART_TxDataRegEmptyFlag));
	}

	for( uint8_t i = 0 ; i < data_len; i++){
			UART_WriteByte(UART_BASE, data[i]);
			while(!(UART_GetStatusFlags(UART_BASE) & kUART_TxDataRegEmptyFlag));
		}
}

// Initializing Bluetooth Interface
void Bluetooth_INIT(void){

	 	uart_config_t uart_config2;
	 	BTConnected = false;

	 	// Initialize the BG output function to deliver data to BG121 over UART2
	 	BGLIB_INITIALIZE(on_message_send);

	    // Set high priority for the UART IRQ to quickly stuff UART data into btBuffer to be read
	    NVIC_SetPriority(UART_IRQn, 8);

	    UART_GetDefaultConfig(&uart_config2);
	    uart_config2.baudRate_Bps = BOARD_DEBUG_UART_BAUDRATE;
	    uart_config2.enableTx = true;
	    uart_config2.enableRx = true;

	    UART_Init(UART_BASE, &uart_config2, UART_CLOCK);

	    EnableIRQ(UART_IRQn);
	    UART_EnableInterrupts(UART_BASE, kUART_RxDataRegFullInterruptEnable|kUART_RxOverrunInterruptEnable);
}

// Interrupt to be called when the RxBuffer is full
void UART_IRQ(void){

	// Data is collected in byte format from the Rx Buffer
	uint8_t data;

	/***
	 *  Check if the Rx Register is full and the flag is set, also double check the Rx Overrun
	 *  The two Rx Buffer flags are ANDed with the StatusFlag Register to determine if they are active
	***/
	if( ( kUART_RxOverrunFlag | kUART_RxDataRegFullFlag ) & UART_GetStatusFlags(UART_BASE)){
		data = UART_ReadByte(UART_BASE);
		btBuffer[rxIndex] = data;
		rxIndex++;
		if(rxIndex == 64){
			rxIndex = 0;
		}
		rxIndex %= MAX_BT_LEN;
	}

		/***
		 *  Grab data from the UART2 Rx Buffer and copy to data variable
		 *  Write the data into the Bluetooth Buffer (UART2 is dedicated to BT communication)
		 *  The next open index of the buffer is tracked and incremented after each byte
		 *  A ring buffer is used to ensure space for data. The Bluetooth will be cleaning data
		 *  behind the receiver so it should never reach the end of the loop
		***/
}

// Bluetooth task to handle all data coming in via UART or BT
void vBluetoothTask(void *pvParameters){
	uint8_t data[64];
	uint8_t data_len = 0;
	serviceLocation = 0;

	// Set each of the buffers to be all zeroes initially
	memset(&btBuffer, 0, sizeof(btBuffer));
	memset(&respBuffer, 0 , sizeof(respBuffer));
	memset(&msg_Head, 0 , sizeof(msg_Head));

	// Apply parameters to the configuration file to initialize UART2
	uart_config.srcclk = UART_CLOCK;
	uart_config.base = UART_BASE;

	// Initialize UART2 as communication interface with BlueGiga Module and within the RTOS
	if( 0 > UART_RTOS_Init(&uart_handle, &t_uart_handle, &uart_config))
		{	vTaskSuspend(NULL); }

	// Will have to update this to a randomly generated ID for each wrench
	dumo_cmd_system_set_local_name(strlen(localName), localName);

	while(1) {
		// If the receiving buffer has not been serviced yet and has not reached end of the Bluetooth buffer
		if(serviceLocation != rxIndex){

		// Copy the header of the incoming response message to obtain packet information
			memcpy(&msg_Head, &btBuffer[serviceLocation], 4);

			/***
			 * Use 2nd field of header file to read out of the buffer up the length specified
			 * copy the contents into the response buffer and update the index for the
			 * service location, wrap around if hitting end of buffer
			 ***/
			for (uint8_t i = 0; i < (msg_Head[1] + 4); i++){
				if(serviceLocation == rxIndex){
					break;
				}
				respBuffer[i] = btBuffer[serviceLocation++];
				serviceLocation %= MAX_BT_LEN;
			}
		}

		/***
		 * The first byte of the response buffer is set to 0 after each service routine to ensure a response is
		 * not interpreted more than once. The response buffer is ignored while there is a zero in first field
	     * When a new message comes into the response buffer the ID is checked against various predefined IDs
	     * within the switch statement. When the system starts the address of the BlueGiga connected to the host
	     * is noted within a the my_address variable. The connected_address will change depending on connected
	     * device.
		 ***/

			pck = BGLIB_MSG(respBuffer);

			switch( BGLIB_MSG_ID(respBuffer) )
			{

			// Print to console a hello message when system hello command sent
				case dumo_rsp_system_hello_id:
					PRINTF("Hello from BG\r\n");
					dumo_cmd_system_reset(0);
					break;

			// Console output that system has begun reboot process
				case dumo_evt_system_boot_id:
					PRINTF("Rebooting\r\n");
					break;

			// During system initialization print out address for BlueGiga
				case dumo_evt_system_initialized_id:
					PRINTF("Initializing System address: ");
					print_address(pck->evt_system_initialized.address.addr);

					// start RFCOMM server
					dumo_cmd_bt_rfcomm_start_server(2,0);
					break;

			// Respond to get address request by printing address to console in big endian format
				case dumo_rsp_system_get_bt_address_id:
					memcpy(&my_address, &pck->rsp_system_get_bt_address.address.addr, 6);
					print_address(my_address);
					break;

			// When beginning RFCOMM server print to console if success or failure also set GAP mode to be discoverable and bondable
				case dumo_rsp_bt_rfcomm_start_server_id:
					if(pck->rsp_bt_rfcomm_start_server.result == 0)
					{
						PRINTF("Started RFCOMM Server. Device is discoverable and bondable.\r\n");
						dumo_cmd_bt_gap_set_mode(1, 1, 0);
						dumo_cmd_sm_set_bondable_mode(1);
					}
					else{	PRINTF("SPP Server Start failed.\r\n");	}
					break;

			// Once GAP is set for Bluetooth Classic, also set GAP for BLE
				case dumo_rsp_bt_gap_set_mode_id:
					// Uncomment to advertise on the BLE channel
//					if( pck->rsp_bt_gap_set_mode.result == 0 ){
//						dumo_cmd_le_gap_set_mode(2, 2);
//					}
					break;

			// Print to console that the device is now bondable
				case dumo_rsp_sm_set_bondable_mode_id:
					if( pck->rsp_sm_set_bondable_mode.result == 0 )
					{
						PRINTF("Waiting for connection...\r\n");
					}
					break;

			// Called after the device has been bonded
				case dumo_evt_sm_bonded_id:
					if( pck->evt_sm_bonded.bonding != 0xff ) dumo_cmd_sm_read_bonding( pck->evt_sm_bonded.bonding );
					break;

			// Print address of device connected to device (Works for both BR and BLE)
				case dumo_evt_bt_connection_opened_id:
					BTConnected = true;
					PRINTF("Bonding with ID: %02x\r\n", pck->evt_bt_connection_opened.bonding);
//					dumo_cmd_bt_rfcomm_open(&pck->evt_bt_connection_opened.address, endpoint, 2, 0x1101);
					dumo_cmd_bt_gap_set_mode(0, 0, 0);

					break;

			// Shut off LED on disconnection for Bluetooth and reset the device to be bondable / discoverable
				case dumo_evt_bt_connection_closed_id:
					BTConnected = false;
					dumo_cmd_bt_gap_set_mode(1, 1, 0);
					break;

			// Print to console that SPP connect is made and with what address
				case dumo_evt_bt_rfcomm_opened_id:
					PRINTF("SPP Connection opened with: ");
					print_address(pck->evt_bt_rfcomm_opened.address.addr);
					memcpy(&connected_address, &pck->evt_bt_rfcomm_opened.address.addr, 6);
					dumo_cmd_endpoint_send(endpoint, strlen("E00\r\n\0"), "E00\r\n\0");
					endpoint = pck->evt_bt_rfcomm_opened.endpoint;
					PRINTF("endpoint is : %02x\r\n", endpoint);
					break;

			// Print to console the address of BLE connection
				case dumo_evt_le_connection_opened_id:
//					memcpy(&connected_address, &pck->evt_le_connection_opened.address.addr, 6);
//					PRINTF("BLE Connection opened with: ");
//					dumo_cmd_endpoint_send(endpoint, strlen("E00\r\n\0"), "E00\r\n\0");
//					print_address(connected_address);
					break;

			// Print the error code and connection number when a LE connection closes
				case dumo_evt_le_connection_closed_id:
//					PRINTF("Connection closed -> Error code: %04x -> Connection: %02x\r\n", pck->evt_le_connection_closed.reason,
//							pck->evt_le_connection_closed.connection);
//					dumo_cmd_le_gap_set_mode(2, 2);
					break;

			// After the Low Energy GAP is set, make the security manager bondable
				case dumo_rsp_le_gap_set_mode_id:
//					if ( pck->rsp_bt_gap_set_mode.result == 0 ){
//						PRINTF("Device now bondable\r\n");
//					}
					break;

			// Acknowledge that endpoint is closing and close the endpoint
				case dumo_evt_endpoint_closing_id:
					PRINTF("Closing endpoint: %02x\r\n", pck->evt_endpoint_closing.endpoint);
					dumo_cmd_endpoint_close(pck->evt_endpoint_closing.endpoint);
					BTConnected = false;
					endpoint = 0;
					break;

			// Check the endpoint send response for error code
				case dumo_rsp_endpoint_send_id:
					if( pck->rsp_endpoint_send.result == 0 ){
					}
					else if( pck->rsp_endpoint_send.result == dumo_err_buffers_full ) {
					}
					else if ( pck->rsp_endpoint_send.result != 0 ) PRINTF("err %04x\n", pck->rsp_endpoint_send.result);
					break;

			// When data reaches the end point take the length and data of the message to print to the console.
			// Also handle echo response to a ping
				case dumo_evt_endpoint_data_id:
					data_len = pck->evt_endpoint_data.data.len;
					memcpy(&data, &pck->evt_endpoint_data.data.data, data_len);
					Bluetooth_len = data_len;
					memcpy(&Bluetooth_rx, &data, data_len);
					message_recieved = true;
					break;
				default:
					break;
		}
		memset(&respBuffer, 0 , sizeof(respBuffer));
		vTaskDelay(50);
	}
}

// Public function for other tasks to request a Bluetooth transmission
void Bluetooth_Send(uint8_t* data, uint8_t data_len){
	if (BTConnected == false && !(endpoint > 0)){
		__NOP();
	}
	else{
		dumo_cmd_endpoint_send(endpoint, data_len, data);
	}
}

// Public function for reseting the Bluetooth module
void Bluetooth_Reset(void){
    dumo_cmd_system_reset(0);
}

// Function for printing out the Bluetooth address **initially used for debugging purposes
void print_address(uint8_t address[6]){
	PRINTF("%02x:%02x:%02x:%02x:%02x:%02x\r\n", address[5],address[4],address[3],address[2],address[1],address[0]);
}
