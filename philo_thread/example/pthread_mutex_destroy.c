#include <stdio.h>
#include <pthread.h>

int main()
{
    pthread_mutex_t m;
    
    int a;
    int ret;
    // 1. integer a를 destroy해보기.
    ret = pthread_mutex_destroy((pthread_mutex_t *)&a);
    // zsh: illegal hardware instruction
    printf("Test 1 Destroy integer a | ret:%d\n", ret);
    
    // 2. 생성되지 않은 m을 destroy해보기
    ret = pthread_mutex_unlock(&m);
    printf("Test 2 Destroy uncreate m | ret:%d\n", ret);
    // Test 2 Destroy uncreate m | ret:22

    // 3. 생성 후 삭제
    ret = pthread_mutex_init(&m, NULL);
    printf("Test 3 init lock m | ret:%d\n", ret);
    ret = pthread_mutex_destroy(&m);
    printf("Test 3 Destroy lock m | ret:%d\n", ret);

    // 4. 생성 및 락 후 삭제
    ret = pthread_mutex_init(&m, NULL);
    printf("Test 4 init m | ret:%d\n", ret);
    ret = pthread_mutex_lock(&m);
    printf("Test 4 lock m | ret:%d\n", ret);
    ret = pthread_mutex_destroy(&m);
    printf("Test 4 Destroy lock m | ret:%d\n", ret);
}

/* pthread_mutex_destroy
SUCCESS: 0
EINVAL : 22
EBUSY  : 16
*/
