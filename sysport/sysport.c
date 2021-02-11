#include <fcntl.h>
#include <semaphore.h>
#include <stdio.h>

static const char *sem_name(int id) {
	static __thread char buffer[128];
	sprintf(buffer, "%d", id);
	return buffer;
}

sem_t *sem_new_with_id(int id, int value) {
	sem_open(sem_name(id), O_CREAT|O_EXCL, 0644, value);
}
