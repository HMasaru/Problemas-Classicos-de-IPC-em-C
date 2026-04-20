#include <pthread.h> 
#include <semaphore.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
 
#define BUFFER_SIZE 5 
 
int buffer[BUFFER_SIZE]; 
int in = 0, out = 0; 
int num_iteracoes; 
 
sem_t empty, full; 
pthread_mutex_t mutex; 
 
void* produtor(void* arg) { 
    for (int i = 0; i < num_iteracoes; i++) { 
        int item = rand() % 100; 
 
        sem_wait(&empty); 
        pthread_mutex_lock(&mutex); 
 
        buffer[in] = item; 
        printf("Produtor produziu: %d\n", item); 
        in = (in + 1) % BUFFER_SIZE; 
 
        pthread_mutex_unlock(&mutex); 
        sem_post(&full); 
 
        sleep(1); 
    } 
 
    pthread_exit(NULL); 
} 
 
void* consumidor(void* arg) { 
    for (int i = 0; i < num_iteracoes; i++) { 
        sem_wait(&full); 
        pthread_mutex_lock(&mutex); 
 
        int item = buffer[out]; 
        printf("Consumidor consumiu: %d\n", item); 
        out = (out + 1) % BUFFER_SIZE; 
 
        pthread_mutex_unlock(&mutex); 
        sem_post(&empty); 
 
        sleep(2); 
    } 
 
    pthread_exit(NULL); 
} 
 
int main() { 
    pthread_t t1, t2; 
 
    printf("Digite o número de iterações (itens a produzir/consumir): "); 
    scanf("%d", &num_iteracoes); 
 
    sem_init(&empty, 0, BUFFER_SIZE); 
sem_init(&full, 0, 0); 
pthread_mutex_init(&mutex, NULL); 
pthread_create(&t1, NULL, produtor, NULL); 
pthread_create(&t2, NULL, consumidor, NULL); 
pthread_join(t1, NULL); 
pthread_join(t2, NULL); 
sem_destroy(&empty); 
sem_destroy(&full); 
pthread_mutex_destroy(&mutex); 
printf("Processo finalizado após %d iterações.\n", num_iteracoes); 
return 0; 
} 