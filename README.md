OSS - Operating system simulator
==

This is the operating system project git.


RESUME:

This simulator can handle memory gestion (ram and virtual) and process scheduling.
A user can enter new processes, and see their execution and access to memory and how it is handled.


HOWTO:

To compile the program, just type "make" into the dirfile folder.
To execute it, type "./OSS.run".

First, your are asked to type the size of the ram, virtual memory, page frames size and quantum.
Then, you can add new processes, see the memory and processes executing.

The dynamic of the program (called monitoring) is printed in a new terminal, automatically opened.


DESCRIPTION:

The process scheduling is done with the Round Robin algorithm allowing priorities and quantum.
Each process has a fixed size and duration, and each execution will lead into an access of one of the memory pages of the process.

The memory gestion is done with the second chance algorithm, and handles ram and virtual memory.
A new process has its memory added into the virtual memory (according to its number of pages).
When an access to a page of the process is done, it will go to the ram (and the old page will go into the virtual memory).


IMPLEMENTATION:

dirfile:
	Affichage.c
	main.c
	makefile
	Memoire.c
	Processus.c

include:
	DeclarationVariablesGlobales.h
	include.h
	Memoire.h
	Processus.h

The main program is main.c, makefile and include are here for the compilation.

We created a struct for both memory and processes, containing the informations needed per process or page.

Ram and virtual memory are represented as arrays of the SMemoire struct ; they are global variables.
The processes are represented as an array (for priority) of array (for the list) of SProcessus struct.
The processes are in their order of execution.

We used threads in order to have both scheduling and display (new processes...) at the same time.
That way, the scheduling is done in background.


