#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define MAX_STR 100
#define PORT 1234
#define MAX_IPLEN 15

typedef int i_sd; // 소켓 디스크럽터를 구분하기위한 자료형 재정의

void* TCP_Client();
int Connection(char* ip);
int Send_Commend(i_sd sock);
int End_Process();		// 프로그램 나가기
void Continue_Process(int* _flag); // 프로그램을 계속 실행할지 묻는 함수