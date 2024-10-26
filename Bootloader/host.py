 
# File:   host.py
# Author: Amr Ali
 

import serial
import serial.tools.list_ports
import time
import struct

def calc_crc_32(temp_val,Poly=0x4C11DB7,initial_value = 0xFFFFFFFF) :
    Buffer = []
    Buffer.append(temp_val)
    crc_result = initial_value
    for i in Buffer :
        crc_result ^= i
        for j in range(32) :
            if(crc_result & 0x80000000) :
                crc_result = (crc_result << 1) ^ Poly
            else :
                crc_result <<= 1
    return crc_result & 0xFFFFFFFF


def calc_crc_8(temp_val,initial_value=0xFF,Poly=0x4C) :
    Buffer = []
    Buffer.extend(temp_val)
    crc_result = initial_value
    for i in Buffer :
        crc_result ^= i
        for j in range(8) :
            if (crc_result & 0x80) :
                crc_result  = (crc_result << 1) ^ Poly
            else :
                crc_result <<= 1 
    return crc_result & 0xFF


def get_version_and_commands(ser):
    ser.write(bytes([0x00,0xFF]))
    response = ser.read(1)
    if response == b'\x79' :
        print("Acknowledge Received")
        no_of_commands = ser.read(1)
        command_count = no_of_commands[0]
        protocol_version = ser.read(1)
        protocol_version = protocol_version[0]
        protocol_version = protocol_version / 10.0
        print(f"Your Protocol Version is : {protocol_version}")
        supported_commands = ser.read(command_count)
        print(f"Your MCU Supports {len(supported_commands)-1} commands, which are")
        for command in (supported_commands):
            print(f"{hex(command)}",end="    ")
        response = ser.read(1)
        if response == b'\x79' :
            print("\nAcknowledge Received")
        elif response == b'\x1F':
            print("Not acknowledge received")
        else :
            print("Unexpected response received:", response)
    elif response == b'\x1F':
        print("Not acknowledge received")
    else :
        print("Unexpected response received:", response)


def get_protocol_version(ser):
    ser.write(bytes([0x01,0xFE]))
    response = ser.read(1)
    print(response)
    if response == b'\x79' :
        print("Acknowledge received")
        protocol_version = ser.read(1)
        protocol_version = protocol_version[0]
        protocol_version = protocol_version / 10.0
        print(f"Your Protocol Version is {protocol_version}")
        response = ser.read(1)
        if response == b'\x79' :
            print("\nAcknowledge Received")
        elif response == b'\x1F':
            print("Not acknowledge received")    
    elif response == b'\x1F':
        print("Not acknowledge received")
    else :
        print("Unexpected response received:", response)




def get_chip_id(ser):
    ser.write(bytes([0x02,0xFD]))
    response = ser.read(1)
    if response == b'\x79' :
        print("Acknowledge received\n")
        No_of_Bytes = ser.read(1)
        No_of_Bytes = No_of_Bytes[0]
        ID = ser.read(No_of_Bytes)
        ID = ((ID[0]) << 8) | ID[1]
        print(f"Your chip id is : 0x{ID:x}")
        response = ser.read(1)
        if response == b'\x79' :
            print("\nAcknowledge Received")
        elif response == b'\x1F':
            print("Not acknowledge Received")  
        else :
            print("Unexpected response Received:", response)  
    elif response == b'\x1F':
        print("Not acknowledge Received")
    else :
        print("Unexpected response Received:", response)



def read_memory(ser):
    ser.write(bytes([0x11,0xEE]))
    response = ser.read(1)
    if response == b'\x79':
        print("Acknowledge Received")
        address = input("Enter a Valid address in hexadecimal : ")
        address = int(address,16)
        address_crc = calc_crc_32(address)
        address_bytes = [
            (address >> 24) & 0xFF,
            (address >> 16) & 0xFF,
            (address >> 8) & 0xFF,
            address & 0xFF,
            ]
        crc_bytes = [
            (address_crc >> 24) & 0xFF,
            (address_crc >> 16) & 0xFF,
            (address_crc >> 8) & 0xFF,
            address_crc & 0xFF,
            ]
        data = address_bytes + crc_bytes  
        ser.write(data)
        response = ser.read(1)
        if response == b'\x79' :
            print("Acknowledge Received")
            no_of_bytes = int(input("Enter the number of bytes to read: "))
            ser.write(bytes([no_of_bytes]))
            received_data = []
            received_data = ser.read(no_of_bytes+1)
            received_values = list(received_data)
            crc_val_8 = received_values[-1]
            received_values = received_values[:-1]
            data = []
            for i in range(0,len(received_values),2):
                if i+1 < len(received_values):
                    data.append(received_values[i+1])
                data.append(received_values[i])
            crc_calc_8 = calc_crc_8(received_values)
            if crc_val_8 == crc_calc_8:
                print("Your data : ")
                for i in data:
                    print(hex(i),end="     ")
            else :
                print("Unable to receive the data")
        elif response == b'\x1F' :
            print("Not acknowledge Received")  
        else :
            print("Unexpected response Received:", response)      
    elif response == b'\x1F' :
        print("Not acknowledge Received")  
    else :
        print("Unexpected response Received:", response)





def jump_to_user_app(ser):
    ser.write(bytes([0x21,0xDE]))
    response = ser.read(1)
    if response == b'\x79' :
        print("Acknowledge Received")
        address = input("Enter a Valid address in hexadecimal : ")
        address = int(address,16)
        address_bytes = [
            (address >> 24 ) & 0xFF,
            (address >> 16 ) & 0xFF,
            (address >> 8 ) & 0xFF,
            address  & 0xFF,
        ]
        ser.write(bytes(address_bytes))
        response = ser.read(1)
        if response == b'\x79' :
            print("Acknowledge Received")
        elif response == b'\x1F' :
            print("Not acknowledge Received")  
        else :
            print("Unexpected response Received:", response)
    elif response == b'\x1F' :
        print("Not acknowledge Received")  
    else :
        print("Unexpected response Received:", response)


def write_memory(ser):
    ser.write(bytes([0x31,0xCE]))   
    response = ser.read(1)
    if response == b'\x79' :
        print("Acknowledge received\n")
        address = input("Enter a Valid address in hexadecimal : ")
        address = int(address,16)
        address_bytes = [
        (address >> 24 ) & 0xFF,
        (address >> 16 ) & 0xFF,
        (address >> 8 ) & 0xFF,
        address  & 0xFF,
        ]
        address_crc = calc_crc_32(address)
        crc_bytes = [
        (address_crc >> 24 ) & 0xFF,
        (address_crc >> 16 ) & 0xFF,
        (address_crc >> 8 ) & 0xFF,
            address_crc  & 0xFF,
        ]
        data = address_bytes + crc_bytes  
        ser.write(bytes(data))
        response = ser.read(1)
        if response == b'\x79' : 
            print("Acknowledge received\n")      
            file_path = input("Enter the path to your binary file: ")
            data = []
            with open(file_path,'rb') as my_file :
                while True :
                    byte = my_file.read(1) 
                    if not byte :
                        break
                    data.append(byte[0])
            if len(data) %2 != 0 :
                data.append(0xFF)
        crc_result = calc_crc_8(data)
        data.append(crc_result)
        length = len(data)
        ser.write(bytes([length]))
        response = ser.read(1)
        if response == b'\x79' :
            print("Acknowledge received\n")  
            ser.write(bytes(data))
            if response == b'\x79' : 
                print("Acknowledge received\n")                  
            elif response == b'\x1F':
                print("Not acknowledge received")  
            else :
                print("Unexpected response received:", response)  
        elif response == b'\x1F':
            print("Not acknowledge received")  
        else :
            print("Unexpected response received:", response) 
    elif response == b'\x1F':
        print("Not acknowledge received")
    else :
        print("Unexpected response received:", response)

def erase_flash(ser):
    response = ser.write(bytes([0x43,0xBC]))   
    response = ser.read(1)
    if response == b'\x79' :
        print("Acknowledge received\n")
        address = input("Enter the page's start address in hexadecimal : ")
        address = int(address,16)
        address_bytes = [
        (address >> 24 ) & 0xFF,
        (address >> 16 ) & 0xFF,
        (address >> 8 ) & 0xFF,
        address  & 0xFF,
        ]
        address_crc = calc_crc_32(address)
        crc_bytes = [
        (address_crc >> 24 ) & 0xFF,
        (address_crc >> 16 ) & 0xFF,
        (address_crc >> 8 ) & 0xFF,
            address_crc  & 0xFF,
        ]
        data = address_bytes + crc_bytes  
        ser.write(bytes(data))
        response = ser.read(1)
        if response == b'\x79' : 
            print("Acknowledge received\n") 
            no_of_pages = int(input("Enter Number of pages to erase : "))
            ser.write(bytes([no_of_pages]))
        elif response == b'\x1F':
            print("Not acknowledge received")
        else :
            print("Unexpected response received:", response)   
    elif response == b'\x1F':
        print("Not acknowledge received")
    else :
        print("Unexpected response received:", response)




def enable_write_protection(ser):
    ser.write(bytes([0x63,0x8C]))
    response = ser.read(1)
    if response == b'\x79':
        print("Acknowledge received")
        sector_number = int(input("Enter sector number to enable protection for: "))
        ser.write(bytes([sector_number]))
        response = ser.read(1)
        if response == b'\x79':
            print("Acknowledge received")
        elif response == b'\x1F':
            print("Not acknowledge received")
        else :
            print("Unexpected response received:", response)     
    elif response == b'\x1F':
        print("Not acknowledge received")
    else :
        print("Unexpected response received:", response)



def disable_write_protection(ser):
    ser.write(bytes([0x73,0x9C]))
    response = ser.read(1)
    if response == b'\x79':
        print("Acknowledge received")
        sector_number = int(input("Enter sector number to disable protection for: "))
        ser.write(bytes([sector_number]))
        response = ser.read(1)
        if response == b'\x79':
            print("Acknowledge received")
        elif response == b'\x1F':
            print("Not acknowledge received")
        else :
            print("Unexpected response received:", response)     
    elif response == b'\x1F':
        print("Not acknowledge received")
    else :
        print("Unexpected response received:", response)



def enable_read_protection(ser):
    ser.write(bytes([0x82,0x7D]))
    response = ser.read(1)
    if response == b'\x79':
        print("Level 1 Read Protection has been applied")
    elif response == b'\x1F':
        print("Not acknowledge received")
    else :
        print("Unexpected response received:", response)




def disable_read_protection(ser):
    ser.write(bytes([0x92,0x9C]))
    response = ser.read(1)
    if response == b'\x79':
        print("Level 0 Read Protection has been applied")
    elif response == b'\x1F':
        print("Not acknowledge received")
    else :
        print("Unexpected response received:", response)



def list_serial_Ports() :
    Ports = serial.tools.list_ports.comports()
    available_ports = []
    for Port in Ports :
        available_ports.append(Port.device)
    return available_ports



def initialize_communication() :
    Ports = list_serial_Ports()
    if not Ports :
        print("No Ports found")
    else :
        print("\nselect one port from the available options.")
        for index,port in enumerate(Ports,start=1) :
            print(f"{index} : {port}")
        while True:
            try: 
                port_choice = int(input("\nEnter Your Choice : "))
                if port_choice in range(1,(len(Ports)+1)) :
                    try :
                        return serial.Serial(Ports[port_choice-1],bytesize=serial.EIGHTBITS,parity=serial.PARITY_NONE,stopbits=serial.STOPBITS_ONE,baudrate=9600,timeout=20) 
                    except serial.SerialException as e:
                        print(f"Failed to open serial port: {e}")
                    except OSError as e:
                        print(f"OS error: {e}")
                else :
                    print(f"\nPlase Enter a valid Number from 1 to {len(Ports)}\n")
            except ValueError as e:
                        print(f"\n{e} - Please Enter a valid Integer Number\n")

        
commands = {
    1:get_version_and_commands,
    2:get_protocol_version,
    3:get_chip_id,
    4:read_memory,
    5:jump_to_user_app,
    6:write_memory,
    7:erase_flash,
    8:enable_write_protection,
    9:disable_write_protection,
    10:enable_read_protection,
    11:disable_read_protection
}

def display_menu() :
    print("select an option of the following -> \n")
    print("1)  Get the version and allowed Commands")
    print("2)  Get Protocol version")
    print("3)  Get Chip ID")
    print("4)  Read memory")
    print("5)  Jump to user Application")
    print("6)  Write Memory")
    print("7)  Erase Flash")
    print("8)  Enable Write Protection")
    print("9)  Disable Write Protection")
    print("10) Enable Read Protection")
    print("11) Disable Read Protection")

def get_user_choice() :
    while True:
        try: 
            display_menu()
            choice = int(input("\nEnter Your Choice : "))
            if choice in range(1,14) :
                return choice
            else :
                print("\nPlase Enter a valid Number from 1 to 13\n")
        except ValueError as e:
            print(f"\n{e} - Please Enter a valid Integer Number\n")



choice = get_user_choice()

ser = initialize_communication()

commands[choice](ser)
