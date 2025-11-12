#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void* print_message(void* arg) {
    	char* id = (char *)arg;
	printf("Thread %s is running. id = %lu.\n", id, (unsigned long)pthread_self());
    	return NULL;
}

int main(){
	pthread_t thr1, thr2, thr3;
	
	if(pthread_create(&thr1, NULL, print_message, (void*)"1") != 0) {
		perror("Failed to create thread 1");
        	return 1;
	}

	if(pthread_create(&thr2, NULL, print_message, (void*)"2") != 0) {
                perror("Failed to create thread 2");
                return 1;
	}

	if(pthread_create(&thr3, NULL, print_message, (void*)"3") != 0) {
                perror("Failed to create thread 3");
                return 1;
        }
	
	if (pthread_join(thr1, NULL) != 0) {
        	perror("Failed to join thread 1");
        	return 1;
    	}

    	if (pthread_join(thr2, NULL) != 0) {
        	perror("Failed to join thread 2");
        	return 1;
    	}

        if (pthread_join(thr3, NULL) != 0) {
                perror("Failed to join thread 3");
                return 1;
        }

    	printf("All threads have finished execution\n");

    	return 0;
}
