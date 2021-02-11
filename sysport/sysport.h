#ifndef SYSPORT_SYSPORT_H
#define SYSPORT_SYSPORT_H

#ifdef __cplusplus
extern "C" {
#endif

extern sem_t *sem_new_with_id(int, int);
extern sem_t *sem_load_with_id(int);
extern int sem_unlink_with_id(int);

#ifdef __cplusplus
}
#endif

#endif
