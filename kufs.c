/*******************************************************************/
/* COMP 304 Project 3 : File Systems
/* Spring 2015
/* Koç University
/* 
/* Mehmet Cagatay Barin     
/*
/*******************************************************************/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <stddef.h>
#include "kufs.h"

int parseCommand(char inputBuffer[], char *args[]);

int main(void){
    char inputBuffer[50]; 
    char *args[50];	        /* buffer to hold the command entered */
	int shouldRun = 1;
	mountKUFS();     /* Initial mount command for KUFS to process the disk emulator. */

	while(shouldRun){
		shouldRun = parseCommand(inputBuffer, args);
		if (strncmp(inputBuffer, "exit", 4) == 0){
      		shouldRun = 0;     /* Exiting from KUFS*/
		}
		else if (strncmp(inputBuffer, "ls", 2) == 0){
			ls();
		}
		else if (strncmp(inputBuffer, "md", 2) == 0){
			md(args[1]);
		}
		else if (strncmp(inputBuffer, "cd", 2) == 0){
			cd(args[1]);
		}
		else if (strncmp(inputBuffer, "stats", 5) == 0){
			stats();
		}
		else if (strncmp(inputBuffer, "rd", 2) == 0){
			rd();
		}
		else if (strncmp(inputBuffer, "display", 7) == 0){
			display(args[1]);
		}
		else if (strncmp(inputBuffer, "create", 6) == 0){
			create(args[1]);
		}
		else if (strncmp(inputBuffer, "rm", 2) == 0){
			rm(args[1]);
		}else {
			printf("Unknown command!\n");
		}
	}
	return 0;
}





int parseCommand(char inputBuffer[], char *args[])
{
    int length,		/* # of characters in the command line */
      i,		/* loop index for accessing inputBuffer array */
      start,		/* index where beginning of next command parameter is */
      ct,	        /* index of where to place the next parameter into args[] */
      command_number;	/* index of requested command number */

    ct = 0;

    /* read what the user enters on the command line */
    do {
	  printPrompt();
	  fflush(stdout);
	  length = read(STDIN_FILENO,inputBuffer,50);
    }
    while (inputBuffer[0] == '\n'); /* swallow newline characters */

    /**
     *  0 is the system predefined file descriptor for stdin (standard input),
     *  which is the user's screen in this case. inputBuffer by itself is the
     *  same as &inputBuffer[0], i.e. the starting address of where to store
     *  the command that is read, and length holds the number of characters
     *  read in. inputBuffer is not a null terminated C-string.
     */
    start = -1;
    if (length == 0)
      exit(0);            /* ^d was entered, end of user command stream */

  

    /**
     * Parse the contents of inputBuffer
     */

    for (i=0;i<length;i++) {
      /* examine every character in the inputBuffer */

      switch (inputBuffer[i]){
      case ' ':
      case '\t' :               /* argument separators */
	if(start != -1){
	  args[ct] = &inputBuffer[start];    /* set up pointer */
	  ct++;
	}
	inputBuffer[i] = '\0'; /* add a null char; make a C string */
	start = -1;
	break;

      case '\n':                 /* should be the final char examined */
	if (start != -1){
	  args[ct] = &inputBuffer[start];
	  ct++;
	}
	inputBuffer[i] = '\0';
	args[ct] = NULL; /* no more arguments to this command */
	break;

      default :             /* some other character */
	if (start == -1)
	  start = i;
      } /* end of switch */
    }    /* end of for */

    return 1;

}

