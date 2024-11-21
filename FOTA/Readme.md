<div align="center">
<video width="560" height="315" src="https://github.com/user-attachments/assets/ce49503c-a856-4fdd-b692-5c172e4f9551"></video>  
</div>

### Video Demonstration: FOTA (Firmware Over-the-Air) Update

In this video, we demonstrate the process of updating firmware wirelessly via a web user interface, utilizing a NodeMCU to send the firmware to a Blue Pill microcontroller.

Key Steps in the Video:
1. Overview of Components:
- The Web User Interface allows the user to select and send a binary (.bin) file.
- The NodeMCU receives the firmware wirelessly and forwards it to the Blue Pill microcontroller.
- The Blue Pill is responsible for verifying the integrity of the firmware through a CRC check.
2.Triggering the FOTA Process:

- The binary file is selected and sent through the web interface.
- The NodeMCU receives the file and passes it to the Blue Pill microcontroller.
3.Verifying the Firmware:

- The Blue Pill performs a CRC check to ensure the firmware was correctly received without errors.
Applying the Firmware:

- If the CRC check is successful, the Blue Pill jumps to the application address and starts executing the new firmware.
The new firmware application in this demonstration is a simple LED Blinking program.

### FOTA Project 
The FOTA (Firmware Over The Air) project aims to simplify and automate the firmware update process for embedded systems. 

### Key Features
- **Frontend Interface**: A user-friendly web page built with HTML and JavaScript allows users to easily initiate firmware updates.
- **HTTP Protocol**: Firmware files are transferred securely over the HTTP protocol.
- **NodeMCU Server Mode**: The NodeMCU operates in server mode to wirelessly send firmware updates to connected devices.
- **UART Communication**: The NodeMCU communicates with the Blue Pill using UART.
- **Bootloader Functionality**: a robust bootloader on the Blue Pill Board that manages firmware updates, verifying data integrity.

### Bootloader Overview
The bootloader in the Blue Pill plays a vital role in the FOTA project by managing the firmware update process, Its primary functions include:

1. **Write and Jump Function**: The bootloader features a function that handles both writing new firmware to memory and jumping to the application code after a successful update.

2. **Address Verification**: Upon receiving the starting address for the firmware update, the bootloader verifies it using a Cyclic Redundancy Check (CRC) to ensure the address is valid and has not been corrupted during transmission.

3. **File Size Reception**: The bootloader receives the size of the firmware file, which is essential for memory allocation and ensuring the file can be fully accommodated.

4. **Content Reception and Verification**: The bootloader then receives the firmware content and performs a CRC check to verify the integrity of the data, confirming that it matches the original firmware file.

5. **Writing to Memory**: If both the address and content verifications succeed, the bootloader writes the new firmware data to the specified memory location.

6. **Jumping to Application**: Finally, after successfully writing the firmware, the bootloader jumps to the application code, allowing the updated firmware to take control of the device.
