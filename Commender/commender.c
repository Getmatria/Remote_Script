#include <pthread.h>
#include "Commender.h"

int main()
{
	int is_create, thread_return, flag;
	char ip_addr[MAX_IPLEN];
	pthread_t thread_id;
	
	do{
		printf("[*] TARGET IP >> ");
		scanf("%s", ip_addr);
		
		is_create = pthread_create(&thread_id, NULL, TCP_Client, ip_addr);
		if(is_create < 0){
			perror("thread_create:");
			exit(1);
		}
		
		// 쓰레드 생성
		pthread_join(thread_id, (void*)&thread_return);
		
		// 쓰레드 종료 후 리소스 해제
		printf("[*] CONNECTION RESET!\n");
		printf("[*] PROGRAM END\n");
		flag = End_Process();

	}while(flag);
	
	return 0;
}
