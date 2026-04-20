#include <pthread.h> 
#include <semaphore.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
int leitor_contador = 0; 
pthread_mutex_t mutex_leitor; 
sem_t resource; 
 
int num_iteracoes; 
 
void* leitor(void* arg) { 
    for (int i = 0; i < num_iteracoes; i++) { 
        pthread_mutex_lock(&mutex_leitor); 
        leitor_contador++; 
        if (leitor_contador == 1) 
            sem_wait(&resource); 
        pthread_mutex_unlock(&mutex_leitor); 
 
        printf("Leitor %ld está lendo\n", (long)arg); 
        sleep(1); 
 
        pthread_mutex_lock(&mutex_leitor); 
        leitor_contador--; 
        if (leitor_contador == 0) 
            sem_post(&resource); 
        pthread_mutex_unlock(&mutex_leitor); 
 
        sleep(1); 
    } 
    pthread_exit(NULL); 
} 
 
void* escritor(void* arg) { 
    for (int i = 0; i < num_iteracoes; i++) { 
        sem_wait(&resource); 
        printf("Escritor %ld está escrevendo\n", (long)arg); 
        sleep(2); 
        sem_post(&resource); 
 
        sleep(2); 
    } 
    pthread_exit(NULL); 
} 
 
int main() { 
    pthread_t leitores[5], escritores[2]; 
 
    printf("Digite o número de iterações: "); 
    scanf("%d", &num_iteracoes); 
 
    pthread_mutex_init(&mutex_leitor, NULL); 
    sem_init(&resource, 0, 1); 
 
    for (long i = 0; i < 5; i++) 
        pthread_create(&leitores[i], NULL, leitor, (void*)i); 
 
    for (long i = 0; i < 2; i++) 
        pthread_create(&escritores[i], NULL, escritor, (void*)i); 
 
    for (int i = 0; i < 5; i++) 
        pthread_join(leitores[i], NULL); 
 
    for (int i = 0; i < 2; i++) 
        pthread_join(escritores[i], NULL); 
pthread_mutex_destroy(&mutex_leitor); 
sem_destroy(&resource); 
printf("Finalizado após %d iterações.\n", num_iteracoes); 
return 0; 
} 