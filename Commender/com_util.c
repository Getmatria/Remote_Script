#include "Commender.h"
#define MAX_PTR 4096
#define TRUE 1

void* TCP_Client(void* ip_addr){	// send 구현
	i_sd sock;
	
	// Target pc와 연결
	sock = Connection((char*)ip_addr);
	
	// commend를 보내는 함수
	Send_Commend(sock);
	sleep(2);
	close(sock);
}

int Connection(char* ip){
	i_sd _sock;	
	struct sockaddr_in addr;
	
	if((_sock = socket(PF_INET, SOCK_STREAM, 0)) < 0){
		perror("socket");
		return 0;
	}
	
	memset(&addr, 0x00, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr(ip);
	addr.sin_port = htons(PORT);
	
	if(connect(_sock, (struct sockaddr*)&addr, sizeof(addr)) < 0){
		perror("connect");
		return 0;
	}
	
	return _sock;
}

int Send_Commend(i_sd sock){
	char cmd[MAX_STR];
	char _recv_data[MAX_PTR];
	char* tmp_str = "[+] commend is ";
	
	while(TRUE){
		printf("(press \'q\' to quit)$ ");
		scanf(" %[^\n]", cmd);	// 개행문자를 제외한 모든 문자 받기(white space 포함)
		
		// target pc에 commend 보내기
		if(send(sock, (char*)cmd, sizeof(cmd), 0) < 0){
			perror("send");
		}
		
		// q를 입력받으면 프로그램 종료(타겟 pc는 종료 안됨)
		if(!strcmp(cmd, "q")){
			break;
		}
		
		// commend에 대한 결과(ex. ls명령어를 치면 출력값을 받아서 뿌려준다)
		if(recv(sock, (char*)_recv_data, sizeof(_recv_data), 0) < 0){
			perror("recv");
		}
		printf("%s [%s]\n\n", tmp_str, cmd);
		printf("%s\n", (char*)_recv_data);

	}
	return 0;
}

// 타겟과의 연결을 끊고 화면을 clear 한다.
int End_Process(){
	int flag, status;
	pid_t pid = fork();
	
	if(pid < 0){
		printf("fork() error.....\n");
	}else if(pid == 0){
		sleep(1);
		execl("/usr/bin/clear", "clear", NULL);
	}else{
		wait(&status);
		Continue_Process(&flag);
	}
	return flag;
}

/* 
 *
 * 프로그램을 계속 실행할지 정하는 함수
 * y를 누르면 다시 원격지 ip를 치라는 화면이 뜨고
 * n을 누르면 프로그램이 종료.
 *
 */
void Continue_Process(int* _flag){
	char isContinue;
	while(TRUE){
		printf("[*] Continue? [y/n] : ");
		scanf(" %c", &isContinue);
		if(isContinue == 'y' || isContinue == 'Y'){
			*_flag = 1;
			break;
		}else if(isContinue == 'n' || isContinue == 'N'){
			*_flag = 0;
			break;
		}else{
			printf("[!] Please Enter [y/n]\n");
			continue;
		}
	}
}

