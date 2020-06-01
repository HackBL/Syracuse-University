#include "syscall.h"

int
main()
{
	SpaceId newProc;
	OpenFileId output = CONSOLEOUTPUT;
	char feedback[6] = "PASS!!";
	Write(feedback, 6, output);
}
