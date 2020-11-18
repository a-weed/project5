/*
  Alex Weeden
  Project 5
  rr.c

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* file includes */
#include "scheduler.h"
#include "cmdinput.h"

void rrRun (task_t tasks[], int size, int timeQuantum) {
  uInt clock = 0;
  uInt i = 0;
  uInt q = 0;
  uInt nextFree = 0;

  int readyQ[size];
  int finishQ[size];
  int turnQ[size];

  int done = 0;
  DONE:
  while (done != 1) {
    if (!(tasks[i].arrivalTime > clock)) {
      tasks[i].quantumTime = timeQuantum;
      readyQ[i] = 1;
      turnQ[nextFree] = i;
      nextFree++;
      i++;
    }
    if (readyQ[turnQ[0]] == 1) {
      readyQ[turnQ[0]] = 2;
      tasks[turnQ[0]].startTime = clock;
      tasks[turnQ[0]].origBurst = tasks[turnQ[0]].burstTime;
    }
    if (readyQ[turnQ[0]] == 2) {
      printf("<time %u> process %u is running\n", clock, tasks[turnQ[0]].pid);
      tasks[turnQ[0]].burstTime--;
      tasks[turnQ[0]].quantumTime--;
      clock++;
    }
    int j;
    if (tasks[turnQ[0]].burstTime == 0) {
      finishQ[turnQ[0]] = 1;
      tasks[turnQ[0]].finTime = clock;
      printf("<time %u> process %u is finished -->\n", clock, tasks[turnQ[0]].pid);
      readyQ[turnQ[0]] = 3;
      for (j =0; j < nextFree - 1; j++) {
        turnQ[j] = turnQ[j+1];
      }
      nextFree--;
      turnQ[nextFree] = 0;
      goto SKIP;
    }
    if (tasks[turnQ[0]].quantumTime == 0) {
      tasks[turnQ[0]].quantumTime = timeQuantum;
      turnQ[nextFree] = turnQ[0];
      for (j=0; j <= nextFree; j++) {
        turnQ[j] = turnQ[j+1];
      }
      turnQ[nextFree] = 0;
    }

    int k;
    SKIP:
    for (k =0; k < size; k++) {
      done = 1;
      if (finishQ[k] == 0) {
        done = 0;
        goto DONE;

      }
    }


  }
  tasks[0].exitTime = clock;
  printf("<time %u> All processes have finished\n", clock);

}