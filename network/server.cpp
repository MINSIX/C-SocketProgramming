#include <iostream>
#include <winsock2.h>
#include<cstdlib>
#include <thread> 
using namespace std;
#pragma comment(lib,"ws2_32")
#define PACKET_SIZE 1024 
#define PORT 12000
typedef struct _type {
	char name[10];
	char select[2];
	char message[20];
}type;
type* tp; //����ü ��ü�� ����
type tp1; //send�Ҷ� �������̾�� �Ǽ� �ϳ��� ����




int main() {
	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 2), &wsa);

	SOCKET skt;
	skt = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

	SOCKADDR_IN addr = {};
	addr.sin_family = AF_INET;
	addr.sin_port = htons(PORT);
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	bind(skt, (SOCKADDR*)&addr, sizeof(addr));
	listen(skt, SOMAXCONN);

	struct sockaddr_in client;
	int client_size = sizeof(client);
	SOCKET client_sock;
	client_sock = accept(skt, (SOCKADDR*)&client, &client_size);	//recv�ϱ����� accept



	char buf[PACKET_SIZE] = {};
	recv(client_sock, buf, PACKET_SIZE, 0);
	tp = (type*)buf; //����ȯ

	strcpy(tp1.message, tp->message);		//���ڿ� ����
	strcpy(tp1.name, tp->name);				//���ڿ� ����
	strcpy(tp1.select, tp->select);			//���ڿ� ����
	cout << "before [" << tp1.name << "]:[" << tp1.message << "]" << endl;
	if (tp1.select[0] == '2') {							//select�� ���� ��� ����
		for (int i = 0; i < strlen(tp1.message); i++)
			tp1.message[i] = toupper(tp1.message[i]);
	}
	else if (tp1.select[0] == '3') {
		for (int i = 0; i < strlen(tp1.message); i++)
			tp1.message[i] = tolower(tp1.message[i]);
	}
	else if (tp1.select[0] == '1') {}
	else
		printf("error");
	cout << "after [" << tp1.name << "]:[" << tp1.message << "]" << endl;
	SOCKET client_sock1 = accept(skt, (SOCKADDR*)&client, &client_size);
	send(client_sock1, (char*)&tp1, PACKET_SIZE, 0);				//send ����ü ����
	closesocket(skt);
	closesocket(client_sock1);
	closesocket(client_sock);
	WSACleanup();
	return 0;
}

