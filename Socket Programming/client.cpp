/*
 * Author: Amr Ali
 * Date: September 27, 2024
 */

#include <iostream>
#include "WinSock2.h"
#include "ws2tcpip.h"

using namespace std;

int main() {
	SOCKET clientsocket;
	WSADATA details;
	int port{ 5555 };
	int status;
	WORD socket_version = MAKEWORD(2, 2);

	/*download dll file and allocate resources using WSAStartup API*/

	status = WSAStartup(socket_version,&details);
	if (status == 0) {
		cout << "dll file found" << endl;
	}
	else {
		cout << "dll file not found" << endl;
		cout << "The stats " << details.szSystemStatus << endl;
	}
	/*create socket*/
	clientsocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (INVALID_SOCKET == clientsocket) {
		cout << "Socket creation failed" << WSAGetLastError() << endl;
	}
	else {
		cout << "Socket created successfully" << endl;
	}
	/* connect to the server */
	sockaddr_in client_service;
	client_service.sin_family = AF_INET;
	client_service.sin_port = htons(port);
	inet_pton(AF_INET,"192.168.1.5", &(client_service.sin_addr));

	if (SOCKET_ERROR == connect(clientsocket, (sockaddr*)&client_service, sizeof(client_service))) {
		cout << "Connection failed" << WSAGetLastError() << endl;
	}
	else {
		cout << "Connection established successfully" << endl;
	}
	/* send data to the server */
	char Buffer1[20] {};
	cout << "Enter The Message : ";
	cin.getline(Buffer1,20);
	int count_bytes;
	
	count_bytes = send(clientsocket, Buffer1,20,0);
	if (count_bytes < 0) {
		cout << "Message failed to send" << endl;
	}
	else {
		cout << "Message sent" << endl;
	}
	char Buffer2[20] {};
	/* receive data from the server */
	count_bytes = recv(clientsocket, Buffer2, 20, 0);
	if (count_bytes < 0) {
		cout << "Message failed to send" << endl;
	}
	else {
		cout << "Message received : " << Buffer2 << endl;
	}

	system("pause");
	/* close the socket */
	closesocket(clientsocket);
	/* delete dll file and deallocate the resources */
	WSACleanup();

}