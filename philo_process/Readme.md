# 주의 사항
- 모든 포크들은 테이블 중앙에 있습니다.
- 상태를 메모리에 가지고 있지는 않지만, 사용 가능한 포크의 수는 세마포어로 나타냅니다.
- 각각의 철학자는 프로세스이며, main 프로세스는 철학자가 아니다.


NAME
     sem_open -- initialize and open a named semaphore

SYNOPSIS
     #include <semaphore.h>

     sem_t *
     sem_open(const char *name, int oflag, ...);

     The parameters "mode_t mode" and "unsigned int value" are optional.

DESCRIPTION
     The named semaphore named name is initialized and opened as specified by
     the argument oflag and a semaphore descriptor is returned to the calling
     process.

     The value of oflag is formed by or'ing the following values:

           O_CREAT         create the semaphore if it does not exist
           O_EXCL          error if create and semaphore exists

     If O_CREAT is specified, sem_open() requires an additional two arguments.
     mode specifies the permissions for the semaphore as described in chmod(2)
     and modified by the process' umask value (see umask(2)).  The semaphore
     is created with an initial value, which must be less than or equal to
     SEM_VALUE_MAX.

     If O_EXCL is specified and the semaphore exists, sem_open() fails.  The
     check for the existence of the semaphore and the creation of the sema-
     phore are atomic with respect to all processes calling sem_open() with
     O_CREAT and O_EXCL set.

     When a new semaphore is created, it is given the user ID and group ID
     which correspond to the effective user and group IDs of the calling
     process. There is no visible entry in the file system for the created
     object in this implementation.

     The returned semaphore descriptor is available to the calling process
     until it is closed with sem_close(), or until the caller exits or execs.

     If a process makes repeated calls to sem_open(), with the same name argu-
     ment, the same descriptor is returned for each successful call, unless
     sem_unlink() has been called on the semaphore in the interim.

     If sem_open() fails for any reason, it will return a value of SEM_FAILED
     and sets errno.  On success, it returns a semaphore descriptor.