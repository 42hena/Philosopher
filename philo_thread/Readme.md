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

PTHREAD_CREATE(3)        BSD Library Functions Manual        PTHREAD_CREATE(3)

NAME
     pthread_create -- create a new thread

SYNOPSIS
     #include <pthread.h>

     int
     pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine)(void *), void *arg);

DESCRIPTION
     The pthread_create() function is used to create a new thread, with attributes specified by attr, within a
     process.  If attr is NULL, the default attributes are used.  If the attributes specified by attr are modi-
     fied later, the thread's attributes are not affected.  Upon successful completion pthread_create() will
     store the ID of the created thread in the location specified by thread.

     The thread is created executing start_routine with arg as its sole argument.  If the start_routine
     returns, the effect is as if there was an implicit call to pthread_exit() using the return value of
     start_routine as the exit status.  Note that the thread in which main() was originally invoked differs
     from this.  When it returns from main(), the effect is as if there was an implicit call to exit() using
     the return value of main() as the exit status.

     Upon thread exit the storage for the thread must be reclaimed by another thread via a call to
     pthread_join().  Alternatively, pthread_detach() may be called on the thread to indicate that the system
     may automatically reclaim the thread storage upon exit.  The pthread_attr_setdetachstate() function may be
     used on the attr argument passed to pthread_create() in order to achieve the same effect as a call to
     pthread_detach() on the newly created thread.

     The signal state of the new thread is initialized as:

           o   The signal mask is inherited from the creating thread.

           o   The set of signals pending for the new thread is empty.

RETURN VALUES
     If successful, the pthread_create() function will return zero.  Otherwise an error number will be returned
     to indicate the error.

ERRORS
     The pthread_create() function will fail if:
h
     [EAGAIN]           The system lacked te necessary resources to create another thread, or the system
                             imposed limit on the total number of threads in a process [PTHREAD_THREADS_MAX] would
                        be exceeded.

     [EPERM]            The caller does not have appropriate permission to set the required scheduling parameters or scheduling policy.

     [EINVAL]           The value specified by attr is invalid.

SEE ALSO
     fork(2), pthread_attr(3), pthread_cancel(3), pthread_cleanup_pop(3), pthread_cleanup_push(3),
     pthread_exit(3), pthread_join(3)

STANDARDS
     The pthread_create() function conforms to ISO/IEC 9945-1:1996 (``POSIX.1'').

#### pthread_detach
#### pthread_join
#### pthread_mutex_init
#### pthread_mutex_destroy
#### pthread_mutex_lock
#### pthread_mutex_unlock
