#include "syscall.h"

int 
main()
{
	SpaceId newProc;
	OpenFileId input = CONSOLEINPUT;
	OpenFileId output = CONSOLEOUTPUT;
	char feedback[18] = "PASS!!	Reading is ";
	char newline[1] = "\n";
	char prompt[2], buffer[60];
	int i;
	prompt[0] = '>';
	prompt[1] = '>';
	Write(prompt, 2, output);
	do {

		Read(&buffer[i], 1, input);

	} while (buffer[i++] != '\n');
	Write(feedback, 18, output);
	Write(buffer, 60, output);
	Write(newline, 1, output);
}
