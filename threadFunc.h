//
// Created by scannell on 4/27/19.
//

#ifndef UNTITLED_THREADFUNC_H
#define UNTITLED_THREADFUNC_H
#include "teams.h"
#include "balls.h"
//#include "signalHandlers.h"
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>

void *quaffleAct(void *arg);
void *bludger(void *arg);
void *snitchAct(void *arg);
void *goal(void *arg);
void *beater(void *arg);
void *seeker(void *arg);
void *keeper(void *arg);
void *chaser(void *arg);
#endif //UNTITLED_THREADFUNC_H
