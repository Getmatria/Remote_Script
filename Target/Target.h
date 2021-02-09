#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define MAX_STR 100
#define PORT 1234

int Set_Socket(); // socket() 함수
int Wait_Client(int sock);	// listen 함수
void Str_processing(char* commend, char** argv);
void* TCP_Server();
int Recv_Commend(int client_sock);
char* Execute_Commend(char** argv);
void Clear_Terminal();
void Remove_Newline(char* str);
void End_Process();