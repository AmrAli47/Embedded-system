<div align="center">
<video width="560" height="315" src="https://github.com/user-attachments/assets/ce49503c-a856-4fdd-b692-5c172e4f9551"></video>  
</div>

### FOTA Project 
The FOTA (Firmware Over The Air) project aims to simplify and automate the firmware update process for embedded systems. 

### Key Features:
- Frontend Interface: The project includes a user-friendly web page built with HTML and JavaScript,
allowing users to easily initiate firmware updates through an intuitive interface.
- HTTP Protocol: Firmware files are transferred securely over the HTTP protocol.
- NodeMCU Server Mode: The NodeMCU is configured to operate in server mode,
enabling it to wirelessly send firmware updates to connected devices.
- UART Communication: The NodeMCU communicates with the Blue Pill  using UART.
- Data Integrity Verification: To ensure the reliability of the updates, a Cyclic Redundancy Check (CRC) is implemented.
  This mechanism verifies the integrity of the transferred data.
