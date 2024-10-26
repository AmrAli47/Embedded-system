This project implements a custom bootloader that manages various functionalities for embedded systems. It provides essential commands for interacting with the device's memory and allows for user application management.

## The bootloader supports the following functionalities:

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
