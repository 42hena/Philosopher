# philo

## Arguments 
1. number_of_philosophers
2. time_to_die
3. time_to_eat
4. time_to_sleep
5. [number_of_times_each_philosopher_must_eat]


## function
### memset


printf, malloc, free, write, usleep, gettimeofday, 


### Thread function
#### pthread_create
```cpp
#include <pthread.h>

int
pthread_create
(
	pthread_t *thread, 
	const pthread_attr_t *attr,
	void *(*start_routine)(void *), 
	void *arg
);
```
- 새로운 스레드를 만드는 데 사용.
- attr(속성)이 NULL인 경우 기본 속성 사용, 스레드를 만들고 속성을 수정해도 스레드의 속성은 영향을 받지 않음.
- 성공 시 생성된 스레드의 ID가 스레드에 의해 지정된 위치에 저장.
- arg를 유일한 인수로 사용하여 start_routine을 실행하여 생성.
- start_routine이 반환되면 start_routine의 반환 값을 종료 상태로 사용하여 pthread_exit()에 대한 암시적 호출이 있었던 것과 같은 효과가 있습니다.
=> return 0을 하면 종료 상태는 0임.
- 스레드 종료 시 pthread_join()에 대한 호출을 통해 스레드에 대한 저장소를 다른 스레드에서 회수해야 합니다. 
- 또는 시스템이 종료 시 스레드 저장소를 자동으로 회수할 수 있음을 나타내기 위해 스레드에서 pthread_detach()를 호출해야 함.
- 새로 생성된 스레드에서 pthread_detach()에 대한 호출과 동일한 효과를 얻기 위해 pthread_attr_setdetachstate() 함수를 pthread_create()에 전달된 속성 인수에서 사용할 수 있습니다.

#### pthread_detach
```cpp
#include <pthread.h>

int
pthread_detach
(
	pthread_t thread
);
```
- 스레드가 종료될 때 스레드의 저장소를 회수할 수 있음을 알림.
- 스레드가 종료되지 않은 경우 pthread_detach()로 인해 스레드가 종료되지 않습니다.
- 동일한 대상 스레드에서 여러 pthread_detach() 호출의 효과는 지정되지 않습니다.

#### pthread_join
```cpp
#include <pthread.h>
int
pthread_join
(
	pthread_t thread, 
	void **value_ptr
);
```

- 대상 스레드가 아직 종료되지 않은 경우 대상 스레드가 종료될 때까지 호출 스레드의 실행을 일시 중단.
- 성공적으로 완료된 pthread_join() 호출에서 value_ptr 인수가 NULL이 아닌 값으로 지정된 경우, 종료되는 스레드에서 pthread_exit()에 의해 전달된 값이 value_ptr이 참조하는 위치에 저장됩니다.
- pthread_join()이 성공적으로 반환되면 대상 스레드가 종료됩니다.

#### pthread_mutex_init
```cpp
#include <pthread.h>

int
pthread_mutex_init(
	pthread_mutex_t *mutex, 
	const pthread_mutexattr_t *attr
);
```
- attr로 지정된 속성으로 새로운 mutex를 생성.
- attr이 NULL값이면 기본 속성을 사용. 

#### pthread_mutex_destroy
```cpp
#include <pthread.h>

int
pthread_mutex_destroy
(
	pthread_mutex_t *mutex
);
```
- 뮤텍스에 할당된 리소스를 해제합니다.

#### pthread_mutex_lock
```cpp
#include <pthread.h>

int
pthread_mutex_lock
(
	pthread_mutex_t *mutex
);
```
- mutex를 lock함.
- 이미 lock이 걸려있을 시에 함수를 호출한 스레드는 mutex를 사용할 수 있을 때까지 block됨.

#### pthread_mutex_unlock
```cpp
#include <pthread.h>

int
pthread_mutex_unlock
(
	pthread_mutex_t *mutex
);
```
- mutex lock을 가지고 있을 시에 unlock함.
- lock을 가지고 있지 않은 호출 스레드가 호출 시 UB 발생.

# TODO
1. 해제 기법
2. nanosleep 