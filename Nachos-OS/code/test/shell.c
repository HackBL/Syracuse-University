#include "syscall.h"

int
main()
{
	SpaceId newProc;
	OpenFileId input = CONSOLEINPUT;
	OpenFileId output = CONSOLEOUTPUT;
	char feedback[16] = "PASS!! Input is ";
	char newline[1] = "\n";
	char prompt[2], buffer[60];
	int i;

	prompt[0] = '>';
	prompt[1] = '>';

	while (1)
	{
		Write(prompt, 2, output);

		i = 0;

		do {

			Read(&buffer[i], 1, input);

		} while (buffer[i++] != '\n');

		Write(feedback, 16, output);
		Write(buffer, 60, output);
		Write(newline, 1, output);
		
	}
}
