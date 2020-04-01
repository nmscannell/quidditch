//
// Created by scannell on 4/27/19.
//

#ifndef UNTITLED_SIGNALHANDLERS_H
#define UNTITLED_SIGNALHANDLERS_H
#include "teams.h"
#include "balls.h"
#include <string.h>
#include <signal.h>
#include <stdio.h>

void hitOrScored(int signo);
void caughtQuaffle(int signo);
void saved(int signo);
#endif //UNTITLED_SIGNALHANDLERS_H
