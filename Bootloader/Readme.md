https://github.com/user-attachments/assets/207b4b03-c02f-477b-9f5a-bc5cc0a5ad7e

### Video Demonstration: Jump Command
In this video, we demonstrate the functionality of the jump command within the bootloader. The bootloader resides in memory at address 0x08000000, 
while the main application (LED Blinking) is located at address 0x08010000.

Key Steps in the Video:

1. Overview of Applications:
- The first application is the Bootloader at 0x08000000.
- The second application is the Main Application (LED Blinking) at 0x08010000.
2. Triggering the Jump Command:

3. We invoke the jump command from the bootloader.
- The starting address of the main application (0x08010000) is provided as an argument.
- Transition to the Main Application:

The bootloader transfers control to the main application, allowing it to start execution.

This project implements a custom bootloader that manages various functionalities for embedded systems. It provides essential commands for interacting with the device's memory 
and allows for user application management.


### The bootloader supports the following functionalities:

1. Get the Version and Allowed Commands: Retrieve the bootloader version and the list of commands that can be executed.
2. Get Protocol Version: Obtain the current protocol version used for communication.
3. Get Chip ID: Retrieve the unique identifier for the microcontroller.
4. Read Memory: Access and read data from specific memory locations.
5. Jump to User Application: Transfer control to the user application for execution.
6. Write Memory: Write data to specified memory locations.
7. Erase Flash: Erase flash memory sections to prepare for new data.
8. Enable Write Protection: Protect specific memory sections from being written to.
9. Disable Write Protection: Remove write protection from previously protected memory sections.
10. Enable Read Protection: Secure the memory from being read by unauthorized access.
11. Disable Read Protection: Lift read protection to allow access to the memory.
