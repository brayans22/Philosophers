
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>

typedef struct s_pe{
    int i;
    pthread_mutex_t t1;
    pthread_mutex_t t2;
    int j;
}t_pe;

void *change_variable(void * st)
{
    t_pe *pe = (t_pe *)st;

    //pthread_mutex_lock(&pe->t1);
    for (int w = 0; w < 90000000; w++)
        pe->i++;
    for (int w = 0; w < 90000000; w++)
        pe->j++;
    printf("%i | %i\n", pe->i, pe->j);
    //pthread_mutex_unlock(&pe->t1);
    return 0;
}

int main()
{
    t_pe p;

    pthread_t philo_1;
    pthread_t philo_2;

    pthread_mutex_init(&p.t1, NULL);
    p.i = 0;
    p.j = 0;

    pthread_create(&philo_1, NULL, change_variable, &p);
    pthread_create(&philo_2, NULL, change_variable, &p);

    
    pthread_join(philo_1, NULL);
    pthread_join(philo_2, NULL);
    return 0;
}