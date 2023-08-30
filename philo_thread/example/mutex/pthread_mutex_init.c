#include <stdio.h>
#include <pthread.h>
#include <errno.h>
#include <stdlib.h>
#define MAX_VALUE 5000000000LL
int main()
{
    pthread_mutex_t m;
    
    int a;
    int ret;
    // 1. integer a를 destroy해보기.
    ret = pthread_mutex_init((pthread_mutex_t *)&a, NULL);
    // zsh: illegal hardware instruction
    printf("Test 1 init integer a | ret:%d\n", ret);
    
    // 2. 생성되지 않은 m을 destroy해보기
    ret = pthread_mutex_init(&m, NULL);
    printf("Test 2 init mutex m | ret:%d\n", ret);
    // Test 2 Destroy uncreate m | ret:22

    pthread_mutex_t *m_test = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * MAX_VALUE);
    for (long i = 0 ; i < MAX_VALUE ; ++i)
    {
        ret = pthread_mutex_init(&m_test[i], NULL);
        // printf("Test 3 init mutex m | ret:%d\n", ret);
        if (ret == ENOMEM)
        {
            printf("Test 3 init mutex m | ret:%d\n", ret);
            break;
        }

    }
}

/* pthread_mutex_destroy
SUCCESS: 0
EINVAL : 22
ENOMEM  : 12 // 뜨지 않음. 최대로 stack영역으로 테스트 했을 경우 8M가 넘어가서 세그폴트인듯.
*/
