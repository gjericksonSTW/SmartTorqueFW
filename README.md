# SHELL TECHWORKS
# SMART TORQUE WRENCH FIRMWARE

*********************************************************************
*********************************************************************
Source code for a Bluetooth enabled, ultra-low powered Torque Wrenched designed to be used within
the oil and gas industry. The code is currently developed for the FRDMKL43Z Development board
built on an ARM M0+ Cortex. The Bluetooth is connected to the device through the addition of the BT121
chip made by BlueGiga providing the v4.0 stack. The system is wrapped by FreeRTOS providing a Real Time
Framework.

In the future the firmware will be merged over to the KL33Z chip to run the entire system on a custom PCB.

### How to Branch Code to new Machine

1. Download [MCUxpresso IDE](http://www.nxp.com/products/software-and-tools/run-time-software/mcuxpresso-software-and-tools/mcuxpresso-integrated-development-environment-ide:MCUXpresso-IDE) from NXP
2. Install SDK for KL43Z [Here](https://mcuxpresso.nxp.com/en/welcome)
3. Copy the SDK to the **Installed SDK** window of MCUxpresso

