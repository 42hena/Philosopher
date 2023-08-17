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

## DESCRIPTION
- 이름 있는 세마포어는 이름을 지정하고, oflag의 인자에 지정된대로 열리고, 세마포어 디스크립터가 호출 프로세스로 반환됩니다.

oflag 파라메터는 or한다. → O_CREAT | O_EXCL

- O_CREAT
    - 세마포어가 존재하지 않는다면 생성한다.
- O_EXCL
    - error if create and semaphore exists
    - 해석 상 세마포어가 존재하면 에러

- O_CREAT가 지정된 경우, sem_open() 함수는 두 개의 인수가 추가로 필요합니다.
- mode는 chmod(2)에 설명된 대로 세마포어에 대한 권한을 지정하고 프로세스의 umask 값으로 수정합니다
- 세마포어는 초기 값에 의해 생성되고, SEM_VALUE_MAX와 같거나 작아야 합니다.  
- O_EXCL이 지정되어 있고 세마포어가 존재하면, sem_open()은 실패합니다.
- O_CREATE 및 O_EXCL 집합에서 sem_open()을 호출하는 모든 프로세스에 대해 세마포어의 존재를 체크하는 것과 세마포어 생성은 atomic합니다. 
- 새 세마포어가 생성되면 호출 프로세스의 유효 사용자 및 그룹 ID에 해당하는 사용자 ID와 그룹 ID가 부여됩니다.
- There is no visible entry in the file system for the created object in this implementation.
-> 찾아봐야 함.
- 반환된 세마포어 디스크립터는 sem_close() 함수를 호출하기 이전 또는 호출자가 exit하거나 exec 하기 전까지 사용가능합니다.
- 프로세스가 동일한 이름 인수를 사용하여 sem_open()함수를 반복 호출할 경우, sem_unlink()함수가 중간에 호출될 때까지 같은 디스크립터가 반환된다.
- sem_open()함수가 어떤 이유로든 실패한다면, SEM_FAILID를 리턴하고 errno를 세팅합니다. 성공 시에 세마포어 디스크립터를 반환합니다.

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


# sem_close - 이름 있는 세마포어를 닫음

```cpp
     #include <semaphore.h>

     int
     sem_close
	(
		sem_t *sem
	);
```

## DESCRIPTION
- 참조된'sem'과 관련된 이름있는 세마포어 시스템 자원은 해제되고, 디스크립터는 유효하지 않게됩니다.
- 성공 시에 0을 실패시에 -1을 리턴하고 errno가 세팅됩니다.

# ERRORS
- [EINVAL]
	- sem 값이 유효한 세마포어 디스크립터가 아닙니다.