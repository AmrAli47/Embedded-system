#include <iostream>
#include "WinSock2.h"
#include "ws2tcpip.h"

using namespace std;

int main() {
	SOCKET serversocket,acceptsocket;
	WSADATA details;
	int port {5555};
	int status;
	WORD socket_version = MAKEWORD(2, 2);

	/*download dll file and allocate resources using WSAStartup API*/

	status = WSAStartup(socket_version, &details);
	if (status == 0) {
		cout << "dll file found" << endl;
	}
	else {
		cout << "dll file not found" << endl;
		cout << "The stats is " << details.szSystemStatus << endl;
	}
	/*create socket*/
	serversocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (INVALID_SOCKET == serversocket) {
		cout << "Socket creation failed" << WSAGetLastError() << endl;
	}
	else {
		cout << "Socket created successfully" << endl;
	}

	/* binding the socket */
	sockaddr_in server_service;
	server_service.sin_family = AF_INET;
	server_service.sin_port = htons(port);
	inet_pton(AF_INET, "192.168.1.5", &(server_service.sin_addr));

	if (SOCKET_ERROR == bind(serversocket, (sockaddr*)&server_service, sizeof(server_service))) {
		cout << "Biding failed" << WSAGetLastError() << endl;
	}
	else {
		cout << "Binding successful" << endl;
	}

	/* listen for connections */
	if (SOCKET_ERROR  == listen(serversocket, SOMAXCONN)) {
		cout << "listening failed" << WSAGetLastError() << endl;
	}
	else {
		cout << "listening on port successfully" << endl;
	}

	/* accept a connection from a client */
	acceptsocket = accept(serversocket, NULL, NULL);
	if (INVALID_SOCKET == acceptsocket) {
		cout << "Accepting connection failed" << WSAGetLastError() << endl;
	}
	else {
		cout << "Connection accepted" << endl;
	}
	/* receive data from the client */
	int count_bytes;
	char Buffer1[20] {};
	count_bytes = recv(acceptsocket, Buffer1, 20, 0);
	if (count_bytes < 0) {
		cout << "Message failed to receive" << endl;
	}
	else {
		cout << "Message received : " << Buffer1 << endl;
	}
	/* send data to the client */
	char Buffer2[20] {};
	cout << "Enter The Message : ";
	cin.getline(Buffer2, 20);
	count_bytes = send(acceptsocket, Buffer2, 20, 0);
	if (count_bytes < 0) {
		cout << "Message failed to send" << endl;
	}
	else {
		cout << "Message sent" << endl;
	}



	system("pause");
	/* close the socket */
	closesocket(serversocket);
	closesocket(acceptsocket);
	/* delete dll file and deallocate the resources */
	WSACleanup();

}