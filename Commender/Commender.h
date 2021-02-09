#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define MAX_STR 100
#define PORT 1234
#define MAX_IPLEN 15

int Set_Socket();
void* TCP_Client();
int Exploit_Commend(int sock);
void End_Process();		// 프로그램 나가기
int Continue_Process(); // 프로그램을 계속 실행할지 묻는 함수