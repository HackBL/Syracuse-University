// stats.h 
//	Routines for managing statistics about Nachos performance.
//
// DO NOT CHANGE -- these stats are maintained by the machine emulation.
//
// Copyright (c) 1992-1996 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation 
// of liability and disclaimer of warranty provisions.

#include "copyright.h"
#include "debug.h"
#include "stats.h"

//----------------------------------------------------------------------
// Statistics::Statistics
// 	Initialize performance metrics to zero, at system startup.
//----------------------------------------------------------------------

Statistics::Statistics()
{
    totalTicks = idleTicks = systemTicks = userTicks = 0;
    numDiskReads = numDiskWrites = 0;
    numConsoleCharsRead = numConsoleCharsWritten = 0;
    numPageFaults = numPacketsSent = numPacketsRecvd = 0;
    memRefNum = numTLBHit = numTLBMiss = 0;
}

//----------------------------------------------------------------------
// Statistics::Print
// 	Print performance metrics, when we've finished everything
//	at system shutdown.
//----------------------------------------------------------------------

void
Statistics::Print()
{
    cout << "Ticks: total " << totalTicks << ", idle " << idleTicks;
		cout << ", system " << systemTicks << ", user " << userTicks <<"\n";
    //cout << "Disk I/O: reads " << numDiskReads;
		//cout << ", writes " << numDiskWrites << "\n";
		//cout << "Console I/O: reads " << numConsoleCharsRead;
    //cout << ", writes " << numConsoleCharsWritten << "\n";
    cout << "Paging: hits " << numPageHit << " faults " << numPageFaults;
    if (numPageHit + numPageFaults > 0) {
      cout << " hit rate " << (double)numPageHit / (double)(numPageFaults + numPageHit);
    }
    cout << "\n";
    cout << "TLB: hits " << numTLBHit << " misses " << numTLBMiss;
    if (numTLBHit + numTLBMiss > 0) {
      cout << " hit rate " << (double)numTLBHit / (double)(numTLBMiss + numTLBHit);
    }
    cout << "\n";
    //cout << "Network I/O: packets received " << numPacketsRecvd;
		//cout << ", sent " << numPacketsSent << "\n";
}
