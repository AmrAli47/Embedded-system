<div align="center">
<video width="560" height="315" src="https://github.com/user-attachments/assets/ce49503c-a856-4fdd-b692-5c172e4f9551"></video>  
</div>

### FOTA Project 
The FOTA (Firmware Over The Air) project aims to simplify and automate the firmware update process for embedded systems. 

### Key Features
- **Frontend Interface**: A user-friendly web page built with HTML and JavaScript allows users to easily initiate firmware updates.
- **HTTP Protocol**: Firmware files are transferred securely over the HTTP protocol.
- **NodeMCU Server Mode**: The NodeMCU operates in server mode to wirelessly send firmware updates to connected devices.
- **UART Communication**: The NodeMCU communicates with the Blue Pill using UART.
- **Bootloader Functionality**: The project includes a robust bootloader on the Blue Pill microcontroller that  manages firmware updates, verifying data integrity.
<br>
### Bootloader Overview
The bootloader in the Blue Pill microcontroller plays a vital role in the FOTA (Firmware Over The Air) project by managing the firmware update process. Its primary functions include:

1. Write and Jump Function: The bootloader features a function that handles both writing new firmware to memory and jumping to the application code after a successful update.

2. Address Verification: Upon receiving the starting address for the firmware update, the bootloader verifies it using a Cyclic Redundancy Check (CRC) to ensure the address is valid and has not been corrupted during transmission.

3. File Size Reception: The bootloader receives the size of the firmware file, which is essential for memory allocation and ensuring the file can be fully accommodated.

4. Content Reception and Verification: The bootloader then receives the firmware content and performs a CRC check to verify the integrity of the data, confirming that it matches the original firmware file.

5. Writing to Memory: If both the address and content verifications succeed, the bootloader writes the new firmware data to the specified memory location.

6. Jumping to Application: Finally, after successfully writing the firmware, the bootloader jumps to the application code, allowing the updated firmware to take control of the device.
