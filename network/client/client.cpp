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
type* tp; //구조체 전체로 정의
type tp1;
void reada(SOCKET& s) {
	for (int i = 0; i < 3; i++) {
		char buf[PACKET_SIZE];
		recv(s, buf, PACKET_SIZE, 0);
		tp = (type*)buf; //형변환
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
	connect(skt, (SOCKADDR*)&addr, sizeof(addr));		//server에 커넥트

	char buf[PACKET_SIZE];
	cout << "사용자의 이름을 입력하세요 : ";
	cin >> buf;
	strcpy(tp1.name, buf);
	cout << "1. 일반적인 에코 메시지 기능 (숫자키 1 입력)\n2. 모든 메시지를 대문자로 에코 기능(숫자키 2 입력)\n3. 모든 메시지를 소문자로 에코 기능(숫자키 3 입력)\n 기능을 선택하세요 : ";
	cin >> buf;
	strcpy(tp1.select, buf);
	cout << "보낼 메세지를 입력하세요(최대 20글자 h영어) : ";
	cin >> buf;
	strcpy(tp1.message, buf);


	send(skt, (char*)&tp1, PACKET_SIZE, 0);				//구조체로 send
	closesocket(skt);
	SOCKET skt1 = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

	connect(skt1, (SOCKADDR*)&addr, sizeof(addr));		//다시 커넥트

	recv(skt1, buf, PACKET_SIZE, 0);				//recv 
	tp = (type*)buf; //구조체 포인터형변환					

	cout << "before [" << tp1.name << "]:[" << tp1.message << "]" << endl;


	strcpy(tp1.message, tp->message);			//문자열 복사
	strcpy(tp1.name, tp->name);						//문자열 복사
	strcpy(tp1.select, tp->select);				//문자열 복사


	cout << "after [" << tp1.name << "]:[" << tp1.message << "]" << endl;		//출력

	closesocket(skt1);
	WSACleanup();
	return 0;
}


