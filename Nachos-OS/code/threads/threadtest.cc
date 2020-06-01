#include "kernel.h"
#include "main.h"
#include "thread.h"

void
SimpleThread(int which)
{
    int num;
    
    for (num = 0; num < 5; num++) {
        printf("*** thread %d looped %d times\n", which, num);
        kernel->currentThread->Yield();
    }
}

void
ThreadTest()
{


    Thread *t = new Thread("forked thread");
    // Thread *t2 = new Thread("forked thread");
    // Thread *t3 = new Thread("forked thread");

    t->Fork((VoidFunctionPtr) SimpleThread, (void *) 1);
    // t2->Fork((VoidFunctionPtr) SimpleThread, (void *) 2);
    // t3->Fork((VoidFunctionPtr) SimpleThread, (void *) 3);

 	
    SimpleThread(0);	
}
