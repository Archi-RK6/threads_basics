#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *print_numbers(void *arg) {
	int id = *(int*)arg;
	for (int i = 1; i <= 5; i++) {
        	printf("Thread %d. Thread id=%lu. Number = %d\n", id, (unsigned long)pthread_self(), i);
    	}
    	return NULL;
}

int main(){
	pthread_t threads[3];
	int threads_ids[3];

	for (int i = 0; i < 3; i++) {
            threads_ids[i] = i;
            if(pthread_create(&threads[i], NULL, print_numbers, (void*)&threads_ids[i]) != 0){
		    perror("Failed to create thread");
		    return 1;
	    }
        }

	for (int i = 0; i < 3; i++) {
                if (pthread_join(threads[i], NULL) != 0){
                        perror("Failed to join thread");
                	return 1;
		}
        }
	
	printf("All threads have finished execution\n");
	return 0;
}
