

https://github.com/user-attachments/assets/2d7232f5-2482-46d7-8cc5-07141d4ab8a9

# Sockek Programming Project

This project implements a client-server communication system based on the TCP protocol, 
allowing both the client and server to send and receive data.

## Steps for server and client communication

### server steps:
1. **Initialize Winsock using `WSAStartup` function: Before using any Winsock functions the Application must call WSAStartup
  to initialize Winsock library.
2. **Create a socket using `socket` function: After the initialization, we create the socket that will be used for communication
  between client and server.
3. **Binding the socket using `bind` function: After creating a socket, the next step is to bind it to a specific address
 and port number.
4. **Listen for incoming connection using `listen` function: After Binding the socket, the next step is to instruct the socket
 to listen for incoming client connection requests.
5. **Accept connection request using `accept` function: After the server is listening for incoming connections, the next step
is to accept a client connection request.

Now, the server can receive and send data to the client.

### client steps:
1. **Initialize Winsock using `WSAStartup` function: Before using any Winsock functions the Application must call WSAStartup
  to initialize Winsock library.
2. **Create a socket using `socket` function: After the initialization, we create the socket that will be used for communication
  between client and server.
3. **Connect to the server using `connect` function: After creating the socket, the next step is to establish a connection to the server.

Now, the client can receive and send data to the server.
