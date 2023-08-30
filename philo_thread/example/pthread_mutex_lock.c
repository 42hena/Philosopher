#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
pthread_mutex_t m3;
pthread_mutex_t m4;

void* DeadLock(void *param)
{
    int ret; 
    ret = pthread_mutex_lock(&m3);
    printf("Test 3 In thread lock 3 | ret:%d\n", ret);
    sleep(5);
    ret = pthread_mutex_lock(&m4);
    printf("Test 3 In thread lock 4| ret:%d\n", ret);
    sleep(5);
    return (NULL);
}

void* DeadLock1(void *param)
{
    int ret; 
    ret = pthread_mutex_lock(&m4);
    printf("Test 3 In thread lock 4| ret:%d\n", ret);
    sleep(5);
    ret = pthread_mutex_lock(&m3);
    printf("Test 3 In thread lock 3| ret:%d\n", ret);
    sleep(5);
    return (NULL);
}

void* DeadLock2(void *param)
{
    int ret; 
    ret = pthread_mutex_lock(&m3);
    printf("Test 3 In thread lock 3 | ret:%d\n", ret);
    return (NULL);
}

int main()
{
    pthread_mutex_t m1;
    pthread_mutex_t m2;
    
    int ret;

    // 1. 생성되지 않은 뮤텍스를 lock
    ret = pthread_mutex_lock(&m1);
    printf("Test 1 lock | ret:%d\n", ret);

    // 2. 생성되지 않은 뮤텍스 lock 2번.
    ret = pthread_mutex_lock(&m2);
    printf("Test 2 lock | ret:%d\n", ret);
   
    ret = pthread_mutex_lock(&m2);
    printf("Test 2 lock | ret:%d\n", ret);
    // Test 2 unlock | ret:22

    // 3. 생성되었지만, lock 여러 번
    ret = pthread_mutex_init(&m3, NULL);
    ret = pthread_mutex_init(&m4, NULL);
    printf("Test 3 Init | ret:%d\n", ret);
    // Test 3 Init | ret:0
    pthread_t thread_t;
    pthread_create(&thread_t, NULL, DeadLock, (void *)NULL);
    pthread_create(&thread_t, NULL, DeadLock1, (void *)NULL);
    
    // ret = pthread_mutex_lock(&m3);
    // ret = pthread_mutex_lock(&m3);

    while (1)
    ;
    // sleep(20);
    
    // printf("Test 3 lock | ret:%d\n", ret);
}

/* pthread_mutex_lock
SUCCESS: 0
EINVAL : 22
EDEADLK : 11
*/

// EDEADLK을 확인할 수 없었음. 환형 대기, owning 재귀, lock 걸고 스레드 종료 테스트.
