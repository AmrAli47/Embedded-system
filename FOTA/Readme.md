https://github.com/user-attachments/assets/985a28c3-6f19-46d8-9fe0-02db997a35e4

### FOTA (Firmware Over The Air) Project Description

The FOTA project is designed to streamline the process of updating applications via a wireless
network. This system utilizes a frontend web page developed with HTML and JavaScript to facilitate
the transfer of firmware files using the HTTP protocol. The project employs a NodeMCU operating in
server mode to wirelessly send the firmware files.
Additionally, the NodeMCU communicates with a Blue Pill microcontroller through UART, ensuring efficient data transfer.
To maintain data integrity,a Cyclic Redundancy Check (CRC) is implemented, providing a reliable method for verifying the accuracy of the transmitted data.


