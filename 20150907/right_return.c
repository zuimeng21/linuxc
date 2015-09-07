/*************************************************************************
	> File Name: right_return.c
	> Author: 
	> Mail: 
	> Created Time: Mon 07 Sep 2015 18:28:07 CST
 ************************************************************************/

#include<stdio.h>
#include<setjmp.h>
#include<signal.h>
#include<unistd.h>

int           flag = 0;
jmp_buf       env;

void handler_sigrtmin15(int signo)
{
    if(flag == 0)
    {
        return;
    }
    printf("recv SIGRTMIN+15\n");
    sleep(5);
    printf("in handler_sigrtmin15,after sleep\n");
    siglongjmp(env,1);

    
}

int main(int argc,char *argv[])
{
    sleep(20);
    switch(sigsetjmp(env,1))
    {
        case 0:
        {
            printf("return 0\n");
            flag = 1;
            break;
        }
        case 1:
        {
            printf("return from SIGRTMIN+15\n");
            break;
        }
        default:
        {
            printf("return else\n");
            break;
        }
    
    }
    signal(SIGRTMIN+15,handler_sigrtmin15);
    while(1);

    return 0;


}
