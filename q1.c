#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>

sem_t curr_sem;
int dis_stu = 0;
int w_time = 0;
time_t start_time;

typedef struct stud st;
struct stud
{
    int arrival_time;
    int washing_time;
    int patience_time;
    int index;
    int wait;
    int wash;
};

int compare(const void *a, const void *b)
{
    st *data_1 = (st *)a;
    st *data_2 = (st *)b;
    if (data_1->arrival_time - data_2->arrival_time == 0)
    {
        return (data_1->index - data_2->index);
    }
    else
    {
        return (data_1->arrival_time - data_2->arrival_time);
    }
}

void *patience(void *arg)
{
    st *s = (st *)(arg);
    while(1)
    {
        time_t curr_time = time(NULL) - start_time;
        if(s->wash == 1)
        {
            pthread_exit(&(s->index));
        }
        else
        {
            long int p_time = curr_time-s->arrival_time;
            if(s->patience_time <= p_time)
            {
                w_time = w_time + s->patience_time;
                dis_stu++;
                s->wait = 1;
                printf("\033[31mStudent %d leaves without washing\n\033[0m", s->index);
                pthread_exit(&(s->index));
            }
        }
        sleep(1);
    }
}

void *thread(void *arg)
{
    pthread_t t;
    st *s = (st *)(arg);
    printf("\033[37mStudent %d arrives\n\033[0m",s->index);
    pthread_create(&t, NULL, patience, (void*)(s));
    // wait
    sem_wait(&curr_sem);
    s->wash = 1;
    if(s->wait == 1)
    {
        sem_post(&curr_sem);
        pthread_exit(&(s->index));
    }
    // critical section
    time_t curr_time = time(NULL) - start_time;
    long int x = curr_time - s->arrival_time;
    w_time = w_time + x;
    printf("\033[32mStudent %d starts washing\n\033[0m",s->index);
    sleep(s->washing_time);
    printf("\033[33mStudent %d leaves after washing\n\033[0m",s->index);
    // signal
    sem_post(&curr_sem);
    return NULL;
}

int main()
{
    int no_of_students, no_of_washing_machines;
    scanf("%d %d", &no_of_students, &no_of_washing_machines);
    st student[no_of_students];
    for (int i = 0; i < no_of_students; i++)
    {
        scanf("%d %d %d", &student[i].arrival_time, &student[i].washing_time, &student[i].patience_time);
        student[i].index = i+1;
        student[i].wait = 0;
        student[i].wash = 0;
    }

    sem_init(&curr_sem, 0, no_of_washing_machines);
    pthread_t sthread[no_of_students];

    qsort(student, no_of_students, sizeof(st), compare);
    start_time = time(NULL);
    time_t curr_time = time(NULL);
    for (int i = 0; i < no_of_students; i++)
    {
        curr_time = time(NULL) - start_time;
        long int sleep_time = student[i].arrival_time - curr_time;
        sleep(sleep_time);
        pthread_create(&sthread[i], NULL, thread, (void*)(&student[i]));
    }
    for (int i = 0; i < no_of_students; i++)
    {
        pthread_join(sthread[i], NULL);
    }
    sem_destroy(&curr_sem);
    printf("%d\n%d\n", dis_stu, w_time);
    double percentage = (((double)(dis_stu * 100))/no_of_students);
    if(percentage >= 25)
    {
        printf("Yes\n");
    }
    else
    {
        printf("No\n");
    }
    return 0;
}