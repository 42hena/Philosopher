#include <stdio.h>
#include <pthread.h>

int main()
{
    pthread_mutex_t m;
    int ret;
    // 1. 생성되지 않은 뮤텍스를 unlock
    ret = pthread_mutex_unlock(&m);
    printf("Test 1 unlock | ret:%d\n", ret);
    // Test 1 unlock | ret:22
    
    // 2. 생성x lock 1번 unlock 2번.
    ret = pthread_mutex_lock(&m);
    printf("Test 2 lock | ret:%d\n", ret);
    // Test 2 lock | ret:22

    ret = pthread_mutex_lock(&m);
    printf("Test 2 unlock | ret:%d\n", ret);
    // Test 2 unlock | ret:22

    ret = pthread_mutex_lock(&m);
    printf("Test 2 unlock | ret:%d\n", ret);
    // Test 2 unlock | ret:22

    // 3. 생성되었지만, 락이 없는 뮤텍스를 unlock
    ret = pthread_mutex_init(&m, NULL);
    printf("Test 3 Init | ret:%d\n", ret);
    // Test 3 Init | ret:0

    ret = pthread_mutex_unlock(&m);
    printf("Test 3 unlock | ret:%d\n", ret);
    // Test 3 unlock | ret:0 // bug는 발생하지 않았지만, 알기 힘들것으로 보임. 
    // man에서는 UB라 칭함.

    // 4. 생성되었고, lock 1번, unlock 2번
    ret = pthread_mutex_lock(&m);
    printf("Test 4 lock | ret:%d\n", ret);
    // Test 4 lock | ret:0

    ret = pthread_mutex_unlock(&m);
    printf("Test 4 unlock | ret:%d\n", ret);
    // Test 4 unlock | ret:0

    ret = pthread_mutex_unlock(&m);
    printf("Test 4 unlock | ret:%d\n", ret);
    // Test 4 unlock | ret:0
    // UB
}

/* pthread_mutex_unlock
SUCCESS: 0
EINVAL : 22
EPERM  : 1
*/
