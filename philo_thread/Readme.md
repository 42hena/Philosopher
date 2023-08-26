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
#### pthread_detach
#### pthread_join
#### pthread_mutex_init
#### pthread_mutex_destroy
#### pthread_mutex_lock
#### pthread_mutex_unlock

# 데드락 조건
1. 점유 및 대기 (Hold on Wait)
    - 자원을 점유한 상태에서 다른 자원을 기다리는 상태
2. 상호배제 (Mutual exclusion)
    - 자원을 동시에 공유할 수 없는 상태
3. 비선점  (No Preemption)
    - 자원을 뺏지 못하는 상태
4. 원형 대기 (Circular wait)
    - 대기하는 프로세스들이 순환을 이루는 상태

데드락은 위의 4가지 조건이 모두 만족 시에 발생한다.
여기에서 락을 사용한다면 2번과 3번은 보장해주기 때문에 1번 또는 4번을 해결해야한다.

## 데드락 해결 방법
1. 순서를 맞춘다
    A -> B로 락을 걸었다면 모든 락을 A -> B로 맞춘다.
2. 자잘한 락을 합친다.
    A, B, C가 자잘하게 나뉘었는데 사실 A만 필요한 경우 A, B, C를 A로 통합한다.
3. 획득하지 못하면 해제한다.
    A를 획득한 상황에서 B를 얻으려고 시도했는데 B를 얻지 못했다면 A를 해제해버린다.





# TODO
1. 해제 기법
2. nanosleep 