// exception.cc 
//	Entry point into the Nachos kernel from user programs.
//	There are two kinds of things that can cause control to
//	transfer back to here from user code:
//
//	syscall -- The user code explicitly requests to call a procedure
//	in the Nachos kernel.  Right now, the only function we support is
//	"Halt".
//
//	exceptions -- The user code does something that the CPU can't handle.
//	For instance, accessing memory that doesn't exist, arithmetic errors,
//	etc.  
//
//	Interrupts (which can also cause control to transfer from user
//	code into the Nachos kernel) are handled elsewhere.
//
// For now, this only handles the Halt() system call.
// Everything else core dumps.
//
// Copyright (c) 1992-1996 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation 
// of liability and disclaimer of warranty provisions.

#include "copyright.h"
#include "main.h"
#include "syscall.h"
#include "ksyscall.h"

//----------------------------------------------------------------------
// ExceptionHandler
// 	Entry point into the Nachos kernel.  Called when a user program
//	is executing, and either does a syscall, or generates an addressing
//	or arithmetic exception.
//
// 	For system calls, the following is the calling convention:
//
// 	system call code -- r2
//		arg1 -- r4
//		arg2 -- r5
//		arg3 -- r6
//		arg4 -- r7
//
//	The result of the system call, if any, must be put back into r2. 
//
// If you are handling a system call, don't forget to increment the pc
// before returning. (Or else you'll loop making the same system call forever!)
//
//	"which" is the kind of exception.  The list of possible exceptions 
//	is in machine.h.
//----------------------------------------------------------------------

void
ExceptionHandler(ExceptionType which)
{
	int type = kernel->machine->ReadRegister(2);

	DEBUG(dbgSys, "Received Exception " << which << " type: " << type << "\n");

	switch (which) {
		case SyscallException:

		switch(type) {
			case SC_Halt:
				DEBUG(dbgSys, "Shutdown, initiated by user program.\n");

				SysHalt();

				ASSERTNOTREACHED();
				break;

			case SC_Add:
				DEBUG(dbgSys, "Add " << kernel->machine->ReadRegister(4) << " + " << kernel->machine->ReadRegister(5) << "\n");

				/* Process SysAdd Systemcall*/
				int result;
				result = SysAdd(/* int op1 */(int)kernel->machine->ReadRegister(4),
				/* int op2 */(int)kernel->machine->ReadRegister(5));

				DEBUG(dbgSys, "Add returning with " << result << "\n");
				/* Prepare Result */
				kernel->machine->WriteRegister(2, (int)result);

				/* Modify return point */
				{
				/* set previous programm counter (debugging only)*/
				kernel->machine->WriteRegister(PrevPCReg, kernel->machine->ReadRegister(PCReg));

				/* set programm counter to next instruction (all Instructions are 4 byte wide)*/
				kernel->machine->WriteRegister(PCReg, kernel->machine->ReadRegister(PCReg) + 4);

				/* set next programm counter for brach execution */
				kernel->machine->WriteRegister(NextPCReg, kernel->machine->ReadRegister(PCReg)+4);
				}

				return;

				ASSERTNOTREACHED();

				break;

			case SC_Read:
			{
				DEBUG(dbgSys, "read from buffer" << kernel->machine->ReadRegister(4) 
					<< kernel->machine->ReadRegister(5)<< kernel->machine->ReadRegister(6) << "\n");

				int buffer = (int)kernel->machine->ReadRegister(4);
				int size = (int)kernel->machine->ReadRegister(5);//register 5 save the address of next process
				OpenFileId enterIn = (OpenFileId)kernel->machine->ReadRegister(6);//The id of the file that will be write.
				
				// Result: bytes actually read
				int result = SysRead(buffer, size, enterIn);

	            DEBUG(dbgSys, "SysRead returning with " << result << "\n");
	            // Store the result into register 2
				kernel->machine->WriteRegister(2, result);

				/* Modify return point */
				{
					kernel->machine->WriteRegister(PrevPCReg, kernel->machine->ReadRegister(PCReg));
					kernel->machine->WriteRegister(PCReg, kernel->machine->ReadRegister(PCReg) + 4);
					kernel->machine->WriteRegister(NextPCReg, kernel->machine->ReadRegister(PCReg)+4);
				}

				return;
				ASSERTNOTREACHED();
			}
			break;	

			case SC_Write:
            {
				DEBUG(dbgSys, "write to buffer" << kernel->machine->ReadRegister(4) << kernel->machine->ReadRegister(5)<< kernel->machine->ReadRegister(6) << "\n");
  		
                int buffer = (int) kernel->machine->ReadRegister(4);
                int size = (int) kernel->machine->ReadRegister(5);
				OpenFileId enterOut = (OpenFileId)kernel->machine->ReadRegister(6);	//The id of the file that will be write.

				// Result: bytes successfully written
                int result = SysWrite(buffer, size, enterOut);
	    
	            DEBUG(dbgSys, "Add returning with " << result << "\n");
                /* Prepare Result */
                kernel->machine->WriteRegister(2, result);

                /* Modify return point */
                {
                    kernel->machine->WriteRegister(PrevPCReg, kernel->machine->ReadRegister(PCReg));
                    kernel->machine->WriteRegister(PCReg, kernel->machine->ReadRegister(PCReg) + 4);
                    kernel->machine->WriteRegister(NextPCReg, kernel->machine->ReadRegister(PCReg)+4);
                }
                return;
                ASSERTNOTREACHED();
            }
            break;

            case SC_Exit:
            {
				DEBUG(dbgSys, "Exit " << kernel->machine->ReadRegister(4) << "\n");
				int status = (int)kernel->machine->ReadRegister(4);

				SysExit(status);

                return;
                ASSERTNOTREACHED();
            }
            break;

            case SC_SysFork:
            {
            	// Call SysFork function, return the pid of the parent thread 
            	ThreadId rc = SysFork();
            	// Store the returned value into register 2
        	    kernel->machine->WriteRegister(2, (int)rc);    // Child Thread
        	    /* Modify return point */
            	{
                    kernel->machine->WriteRegister(PrevPCReg, kernel->machine->ReadRegister(PCReg) );
                    kernel->machine->WriteRegister(PCReg, kernel->machine->ReadRegister(PCReg) + 4);
                    kernel->machine->WriteRegister(NextPCReg, kernel->machine->ReadRegister(PCReg) + 4);
                }
                return;
                ASSERTNOTREACHED();
            }
            break;

            case SC_Exec:
            {
            	DEBUG(dbgSys, "Exec" << kernel->machine->ReadRegister(4) << "\n");

            	int size = 40;

            	int addr = (int)kernel->machine->ReadRegister(4);
            	char buffer[size];

            	//Read size bytes from file into buffer 
            	for(int i = 0; i < size; i++) {
            		kernel->machine->ReadMem(addr++, 1, (int*)&buffer[i]);
            	}

            	SpaceId id = SysExec((char*) buffer);

            	kernel->machine->WriteRegister(2, (int)id);

            	{
                    kernel->machine->WriteRegister(PrevPCReg, kernel->machine->ReadRegister(PCReg));
                    kernel->machine->WriteRegister(PCReg, kernel->machine->ReadRegister(PCReg) + 4);
                    kernel->machine->WriteRegister(NextPCReg, kernel->machine->ReadRegister(PCReg)+4);
            	}
            	return;
            	ASSERTNOTREACHED();
            }
            break;

			default:
				cerr << "Unexpected system call " << type << "\n";
			break;
		}
		break;


		// Task 3
		case PageFaultException:{
			//Increse number of page faults 
			kernel->stats->numPageFaults++;
			//Address of page fault 
			int pageFaultAdd = (int)kernel->machine->ReadRegister(BadVAddrReg);
			// Compute the physical page number 
			int pageFaultPPN = (int)pageFaultAdd / PageSize;
			// Try to get a free page in physical memory and set that it as used if found 
			int PPN = kernel->freeMap->FindAndSet();
			int pid = kernel->currentThread->pid;
			//Get the page entry 
			TranslationEntry* pageEntry  = kernel->currentThread->space->getPageEntry(pageFaultPPN);
			// The previous entry accessed 
			TranslationEntry* preEntry;

			// If the physical memory isn't full, we could load a new page into it
			if (PPN != -1){   
				//Set the corresponding ppn in page table as the number of that page we're gonna use 
				pageEntry->physicalPage = PPN;
				//Set the valid bit as TRUE 
				pageEntry->valid = TRUE;
				//Read the data&instruction from the corresponding swap file
				kernel->swapSpace->ReadAt(&kernel->machine->mainMemory[PPN*PageSize],
					PageSize,pageEntry->virtualPage * PageSize);
				//Append the page to the end of LRU list 
				kernel->LRU->Append(pageEntry);
				//Print the output
				cout << "L[pid " << pid << "]: [virtualPage: " << pageEntry->virtualPage << "] -> [physicalPage: " 
				<< pageEntry->physicalPage << "]" << endl;

			}
			// If the physical memory is full, we need to swap out the least used page first
			// and load the new one 
			else {
			    //According to our algorithm, the first page on the list is the least used one 	
				preEntry = kernel->LRU->RemoveFront();
				int physicalPN = preEntry->physicalPage;
				//Store the updated data back to swap file 
				kernel->swapSpace->WriteAt(&kernel->machine->mainMemory[physicalPN * PageSize],
					PageSize,preEntry->virtualPage * PageSize);
				//Mark the corresponding physical page as free
				preEntry->physicalPage = -1;
				preEntry->valid = FALSE;

				//Load the new page into memory 
				pageEntry->physicalPage = physicalPN;
				pageEntry->valid = TRUE;
				kernel->swapSpace->ReadAt(&kernel->machine->mainMemory[physicalPN * PageSize],
					PageSize,pageEntry->virtualPage * PageSize);
				//Append the new loaded page into the end of LRU list 
				kernel->LRU->Append(pageEntry);
			
				cout << "S[pid " << pid << "]: [physicalPage: " << pageEntry->physicalPage 
				<< "] -> [virtualPage: " << pageEntry->virtualPage << "]" << endl;
			}
			return;
		}
		break;


		// case AddressErrorException:{
		// 	cout<<"Address Over Error"<<endl;

		// 	cout<<"PFAddress: "<<kernel->machine->ReadRegister(BadVAddrReg)<<endl;
		// 	cout<<"pid: "<<kernel->currentThread->pid<<endl;
		// 	SysHalt();
			
		// 	return;
			
		// }
		// break;  


		default:
			cerr << "Unexpected user mode exception" << (int)which << "\n";
		break;
	}
	ASSERTNOTREACHED();
}
