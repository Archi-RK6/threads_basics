#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int array[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
long  partial_sums[2];

void* sum_func(void* arg){
	int thread_id = *((int*)arg);

	long  sum = 0;
	for(int i = thread_id * (5); i<(thread_id + 1) * (5); i++) {
		sum += array[i];
	}
	partial_sums[thread_id] = sum;
	printf("Thread %d sum = %ld\n", thread_id, sum);
	return NULL;
}

int main(){
	pthread_t threads[2];
	int thread_ids[2];
	int num_threads = 2;

        for (int i = 0; i < num_threads; i++) {
        	thread_ids[i] = i;
            	if (pthread_create(&threads[i], NULL, sum_func, (void*)&thread_ids[i]) != 0){
			perror("Failed to create thread");
			return 1;
		}
	}

        long total_sum = 0;
        for (int i = 0; i < num_threads; i++) {
            	if (pthread_join(threads[i], NULL) != 0){
			perror("Failed to join thread");
			return 1;
		}
            	total_sum += partial_sums[i];
        }
        printf("Total sum: %ld\n", total_sum);

    	return 0;
}
