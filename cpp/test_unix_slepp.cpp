#include<unistd.h>
#include<time.h>
#include<iostream>
#include<stdio.h>
void *func(void *)
{
	for (int i = 0 ; i < 100000 ; i++)
    		usleep(10);
};

int main()
{
    clock_t begin_t,end_t;
    void *status;
    pthread_t thrd_1;
    begin_t = clock();
    pthread_create(&thrd_1, NULL, func, NULL);
    sleep(3);
    end_t = clock();
    printf("begin : %ld\n",begin_t);
    printf("end : %ld\n",end_t);
    std::cout << "per_sec: " << CLOCKS_PER_SEC << std::endl;
    std::cout << "diff between begin and end : " << (double)((end_t - begin_t)/(double)CLOCKS_PER_SEC) << std::endl;
    pthread_join(thrd_1, &status);
    end_t = clock();
    printf("end2 : %ld\n",end_t);
    return 0;
}
