#define _CRT_SECURE_NO_WARNINGS
#include<iostream> 
#include<winsock2.h> 
#include<cstdlib>
#include <thread> 
using namespace std;
#pragma comment(lib,"ws2_32")
#pragma warning(disable:4996)
#define PACKET_SIZE 1024
#define PORT 12000
#define SERVER_IP "127.0.0.1"
typedef struct _type {
	char name[10];
	char select[2];
	char message[20];
}type;
type* tp; //����ü ��ü�� ����
type tp1;
void reada(SOCKET& s) {
	for (int i = 0; i < 3; i++) {
		char buf[PACKET_SIZE];
		recv(s, buf, PACKET_SIZE, 0);
		tp = (type*)buf; //����ȯ
	}
}

int main() {
	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 2), &wsa);
	SOCKET skt;
	skt = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

	SOCKADDR_IN addr = {};
	addr.sin_family = AF_INET;
	addr.sin_port = htons(PORT);
	addr.sin_addr.s_addr = inet_addr(SERVER_IP);
	struct sockaddr_in client;
	connect(skt, (SOCKADDR*)&addr, sizeof(addr));		//server�� Ŀ��Ʈ

	char buf[PACKET_SIZE];
	cout << "������� �̸��� �Է��ϼ��� : ";
	cin >> buf;
	strcpy(tp1.name, buf);
	cout << "1. �Ϲ����� ���� �޽��� ��� (����Ű 1 �Է�)\n2. ��� �޽����� �빮�ڷ� ���� ���(����Ű 2 �Է�)\n3. ��� �޽����� �ҹ��ڷ� ���� ���(����Ű 3 �Է�)\n ����� �����ϼ��� : ";
	cin >> buf;
	strcpy(tp1.select, buf);
	cout << "���� �޼����� �Է��ϼ���(�ִ� 20���� h����) : ";
	cin >> buf;
	strcpy(tp1.message, buf);


	send(skt, (char*)&tp1, PACKET_SIZE, 0);				//����ü�� send
	closesocket(skt);
	SOCKET skt1 = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

	connect(skt1, (SOCKADDR*)&addr, sizeof(addr));		//�ٽ� Ŀ��Ʈ

	recv(skt1, buf, PACKET_SIZE, 0);				//recv 
	tp = (type*)buf; //����ü ����������ȯ					

	cout << "before [" << tp1.name << "]:[" << tp1.message << "]" << endl;


	strcpy(tp1.message, tp->message);			//���ڿ� ����
	strcpy(tp1.name, tp->name);						//���ڿ� ����
	strcpy(tp1.select, tp->select);				//���ڿ� ����


	cout << "after [" << tp1.name << "]:[" << tp1.message << "]" << endl;		//���

	closesocket(skt1);
	WSACleanup();
	return 0;
}


