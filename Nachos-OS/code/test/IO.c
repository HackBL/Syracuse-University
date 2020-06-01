#include "syscall.h"

int 
main()
{
  //printf("Starting Read Syscall and Write Syscall\n");
char a[20];
char b[50];

SysRead(a, 20);
SysRead(b, 48);

SysWrite(a, 10);
SysWrite(b, 48);

Exit(0);
}
