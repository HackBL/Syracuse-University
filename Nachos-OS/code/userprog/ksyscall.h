/**************************************************************
 *
 * userprog/ksyscall.h
 *
 * Kernel interface for systemcalls 
 *
 * by Marcus Voelp  (c) Universitaet Karlsruhe
 *
 **************************************************************/

#ifndef __USERPROG_KSYSCALL_H__ 
#define __USERPROG_KSYSCALL_H__ 

#include "kernel.h"
#include "synchconsole.h"
#include "synchdisk.h"
#include "syscall.h"


void SysHalt()
{
	kernel->interrupt->Halt();
}


int SysAdd(int op1, int op2)
{
	return op1 + op2;
}


int SysRead(int buffer, int size, OpenFileId id) 
{
    // Check if id is CONSOLEINPUT (OpenFileId id 0 is “stdin) 
    if (id != 0) return -1;

    char ch;
    // Counter to count bytes actually read 
    int num = 0;

    // Read size bytes from the open file into buffer,
    do {
        ch = kernel->synchConsoleIn->GetChar();
        kernel->machine->WriteMem(buffer+num, 1, (int)ch);  
        num += 1;
    } while (num < size && ch != EOF);

    // Return bytes acutally read 
	return num;
}

int SysWrite(int buffer, int size, OpenFileId id ) {
    // Check if id is CONSOLEOUTPUT (OpenFileId id 1 is “stdout) 
    if (id != 1) return -1;
    // Counter to count bytes successfully written 
    int num = 0;

    while (num < size) {
        int current;
        // Write size bytes from buffer to the open file 
        kernel->machine->ReadMem(buffer+num, 1, &current);
        // Perform console I/O 
        kernel->synchConsoleOut->PutChar( (char) current );
        num += 1;
    }
    // Return bytes successfully written
    return num;
}



// Restore the state of thread
// void restoreFunction(int restore) { 

void restoreFunction() {
    // Restore the state of thread and run it 
    kernel->currentThread->RestoreUserState();
    kernel->currentThread->space->RestoreState();  // swap into machine
    kernel->machine->Run();
}


ThreadId SysFork() {
    Thread *thread = new Thread("ThreadFork");
    thread->space = new AddrSpace(*(kernel->currentThread->space)); // Invoke Copy Constructor

    kernel->machine->WriteRegister(2, (int)0);    //Save child-thread pid to Reg 2
    thread->SaveUserState();     // Kernal -> User 
    int* n = thread->getUserRegisters();        // GetUserReg

    // Add 4
    n[PCReg] = kernel->machine->ReadRegister(PCReg) + 4;
    n[NextPCReg] = kernel->machine->ReadRegister(NextPCReg) + 4;

    // put it back
    thread->setUserRegister(n);
    thread->Fork((VoidFunctionPtr)restoreFunction,(void*)0);  // User -> Kernal
    
    return (ThreadId)thread->pid;
}


void ExecRun() {
    kernel->currentThread->space->Execute();
}


SpaceId SysExec(char* buffer){
    Thread *thread = new Thread("ThreadExec");
    thread->space = new AddrSpace();   

    if(thread->space->Load((char*)buffer)){
        thread->Fork((VoidFunctionPtr)ExecRun, (void*)0);
    } 
   
    return (SpaceId)thread->pid; 
}


void SysExit(int status){    
    cout << "status: " << status << endl;
    
    kernel->currentThread->Finish();
}   


#endif /* ! __USERPROG_KSYSCALL_H__ */
