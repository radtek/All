#include<unistd.h>
#include<time.h>
#include<iostream>
void func(void *)
{
    sleep(10);
};

int main()
{
    clock_t begin_t,end_t;
    pthread_t thrd_1;
    begin_t = clock();
    pthread_create(&thrd_1, NULL, (void *)&func, NULL);
    sleep(3);
    end_t = clock();
    std::cout << "diff between begin and end : " << (end_t - begin_t) << std::endl;
}