#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int array[5] = {1,2,3,4,5};

void* print_square(void* arg) {
	int id = *((int*)arg);
	int x = array[id];
	printf("Square of %d is %d (calculated by thread %d)\n",x , x * x, id);
	return NULL;
}

int main() {
	pthread_t threads[5];
	int threads_ids[5];

        for (int i = 0; i < 5; i++) {
            threads_ids[i] = i;
            if(pthread_create(&threads[i], NULL, print_square, (void*)&threads_ids[i]) != 0){
                    perror("Failed to create thread");
                    return 1;
            }
        }

        for (int i = 0; i < 5; i++) {
                if (pthread_join(threads[i], NULL) != 0){
                        perror("Failed to join thread");
                        return 1;
                }
        }

        printf("All threads have finished execution\n");
        return 0;
}
