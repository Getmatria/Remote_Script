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

void* TCP_Server();
int Accept_Connect(int* _sock, int* _client_sock);
int Recv_Commend(int client_sock);
void End_Process();