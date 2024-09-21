https://github.com/AmrAli47/Repo/assets/167882152/07e4552b-57f6-4a64-a012-f69d849d264b
### Components: 2 * PIC18F4620 MCU, TC74 Digital Temperature Sensor, DS1307 Real Time Clock Module,
### L289N Motor Driver, 24C02C EEPROM.
### Project Description:
### All devices are connected to I2C Bus, Master Controller reads date and Time 
### from RTC Module via I2C Bus Then Send date and Time value Through EUSART.
### Master Controller reads Temperature value from TC47 Temperature sensor and 
### send this value to Slave Controller via I2C Bus and Slave Controller
### will control the operation of motor based on the temperature value.
### Master Controller uses EEPROM memory to Save data.





