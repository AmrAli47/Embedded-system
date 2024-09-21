https://github.com/user-attachments/assets/2a010212-d1bf-41c2-8b41-3fd7b9a12a75

The Smart Home System project features a master-slave architecture utilizing two MCUs connected via I2C bus. The master MCU reads the current date and time from a DS1307 RTC module and transmits this information via UART. Additionally, it retrieves temperature values from a TC47 temperature sensor and sends them to the slave MCU. The slave MCU then controls motors using an L298N driver based on the temperature data received. To enhance functionality, a 24C02C EEPROM is integrated for data storage.







