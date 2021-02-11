#include <fcntl.h>
#include <semaphore.h>
#include <stdio.h>

sem_t * sem_new_with_id(int id, int value) {
    sem_open("100", 0, 0, 0);
}
