# 주의 사항
- 모든 포크들은 테이블 중앙에 있습니다.
- 상태를 메모리에 가지고 있지는 않지만, 사용 가능한 포크의 수는 세마포어로 나타냅니다.
- 각각의 철학자는 프로세스이며, main 프로세스는 철학자가 아니다.


# sem_open -- 생성 또는 이름 있는 세마포어를 열음
```cpp
     #include <semaphore.h>

	sem_t *sem_open
	(
		const char *name, 
		int oflag[, 
		mode_t mode, 
		unsigned int value]
	); 
	// The parameters "mode_t mode" and "unsigned int value" are optional.
```

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


# ERRORS: 세마포어는 아래의 에러들을 제외하고는 성공합니다.
- [EEXIST]
    - O_CREAT와 O_EXCL이 지정되어있으며, 세마포어가 존재합니다.
- [EINTR]
    - signal에 의해 sem_open() 동작이 중단되었습니다.
- [EINVAL]
    - shm_open() 명령어가 지원되지 않습니다.
    - O_CREATE로 설정되었으며, SEM_VALUE_MAX를 초과합니다.
- [EMFILE]
    - 프로세스가 이미 한계에 도달했다. 사용중인 세마포어 또는 파일 디스크립터
- [ENAMETOOLONG]
    - PSEMNAMLEN에 지정된 글자를 초과합니다.
- [ENFILE]
    - 너무 많은 세마포어 또는 파일 디스크립터가 시스템에 열려있습니다.
- [ENOENT]
    - O_CREAT가 설정되지 않고, 지정된 세마포어가 없음.
- [ENOSPC]
    - O_CREAT 파라메터가 지정되어 있으며, 파일은 존재하지 않지만 세마포어를 생성하기에는 불분한 공간일 경우