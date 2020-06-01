#include "syscall.h"

int
main()
{
  // printf("Starting Exec Syscall\n");
  char name[13] = "../test/Write";
  Exec(name);
}
