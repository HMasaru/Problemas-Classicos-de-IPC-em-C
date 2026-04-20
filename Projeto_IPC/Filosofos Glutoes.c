#include <pthread.h> 
#include <semaphore.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#define NUM_CADEIRAS 3 
 
sem_t clientes; 
sem_t barbeiro; 
pthread_mutex_t mutex_cadeiras; 
int cadeiras_livres = NUM_CADEIRAS; 
 
int num_clientes; 
 
void* barbeiro_func(void* arg) { 
    int atendidos = 0; 
    while (atendidos < num_clientes) { 
        sem_wait(&clientes); 
 
        pthread_mutex_lock(&mutex_cadeiras); 
        cadeiras_livres++; 
        sem_post(&barbeiro); 
        pthread_mutex_unlock(&mutex_cadeiras); 
 
        printf("Barbeiro cortando cabelo...\n"); 
        sleep(3); 
        atendidos++; 
    } 
    printf("Barbeiro finalizou o expediente.\n"); 
    pthread_exit(NULL); 
} 
 
void* cliente_func(void* arg) { 
    long id = (long)arg; 
 
    pthread_mutex_lock(&mutex_cadeiras); 
    if (cadeiras_livres > 0) { 
        cadeiras_livres--; 
        printf("Cliente %ld esperando na cadeira. Cadeiras livres: %d\n", id, 
cadeiras_livres); 
        sem_post(&clientes); 
        pthread_mutex_unlock(&mutex_cadeiras); 
 
        sem_wait(&barbeiro); 
        printf("Cliente %ld sendo atendido\n", id); 
    } else { 
        pthread_mutex_unlock(&mutex_cadeiras); 
        printf("Cliente %ld foi embora, sem cadeira.\n", id); 
    } 
 
    pthread_exit(NULL); 
} 
 
int main() { 
    pthread_t barbeiro_tid, *clientes_tid; 
 
    printf("Digite o número de clientes: "); 
    scanf("%d", &num_clientes); 
 
    clientes_tid = malloc(num_clientes * sizeof(pthread_t)); 
    if (!clientes_tid) { 
        perror("malloc"); 
        return 1; 
} 
sem_init(&clientes, 0, 0); 
sem_init(&barbeiro, 0, 0); 
pthread_mutex_init(&mutex_cadeiras, NULL); 
pthread_create(&barbeiro_tid, NULL, barbeiro_func, NULL); 
for (long i = 0; i < num_clientes; i++) { 
pthread_create(&clientes_tid[i], NULL, cliente_func, (void*)i); 
sleep(1); 
} 
for (int i = 0; i < num_clientes; i++) 
pthread_join(clientes_tid[i], NULL); 
pthread_join(barbeiro_tid, NULL); 
sem_destroy(&clientes); 
sem_destroy(&barbeiro); 
pthread_mutex_destroy(&mutex_cadeiras); 
free(clientes_tid); 
printf("Finalizado após atender %d clientes.\n", num_clientes); 
return 0; 
} 