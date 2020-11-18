/*
  Alex Weeden
  Project 5
  analysis.c

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* file includes */
#include "scheduler.h"
#include "cmdinput.h"

void analyzeTime (task_t finArray[], int size, stat_t stats[]) {
  int i = 0;
  double wait, resp, tat, cpuUsage;
  while (i < size) {
    finArray[i].tatTime = finArray[i].finTime - finArray[i].arrivalTime;
    finArray[i].waitTime = finArray[i].tatTime - finArray[i].burstTime;
    finArray[i].resTime = finArray[i].startTime - finArray[i].arrivalTime;
    stats[0].avgTAT += finArray[i].tatTime;
    stats[0].avgWait += finArray[i].waitTime;
    stats[0].avgResp += finArray[i].resTime;
    stats[0].totalBurst += finArray[i].origBurst;
    i++;
  }
  stats[0].avgTAT = stats[0].avgTAT / size;
  stats[0].avgWait = stats[0].avgWait / size;
  stats[0].avgResp = stats[0].avgResp / size;
  stats[0].usage = (finArray[0].exitTime / stats[1].totalBurst) * 100;




}