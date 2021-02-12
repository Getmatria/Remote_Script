#include "Target.h"
#include <pthread.h>

int main()
{
	pthread_t thread_id;
	int is_create;
	
	while(1){
		printf("[+] Connect Wait....\n");
		printf("[!] You should press Ctrl+C to stop this program\n");
		is_create = pthread_create(&thread_id, NULL, TCP_Server, NULL);
		if(is_create < 0){
			perror("thread_create:");
		}
		pthread_join(thread_id, (void*)&is_create);
		End_Process();
		sleep(3);
	}
}
