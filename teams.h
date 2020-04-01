//
// Created by scannell on 4/27/19.
//

#ifndef UNTITLED_TEAMS_H
#define UNTITLED_TEAMS_H
#include "player.h"

// Gryffindor
pthread_t seekerG, keeperG;
pthread_t beaterG_1, beaterG_2;
pthread_t chaserG_1, chaserG_2, chaserG_3;

// Slytherin
pthread_t seekerS, keeperS;
pthread_t beaterS_1, beaterS_2;
pthread_t chaserS_1, chaserS_2, chaserS_3;

// Players
struct Player chaserG_1_s = {.thread = &chaserG_1, .team = "Gryffindor", .name = "Angelina Johnson", .playing = true};
struct Player chaserG_2_s = {.thread = &chaserG_2, .team = "Gryffindor", .name = "Alicia Spinnet", .playing = true};
struct Player chaserG_3_s = {.thread = &chaserG_3, .team = "Gryffindor", .name = "Katie Bell", .playing = true};
struct Player chaserS_1_s = {.thread = &chaserS_1, .team = "Slytherin", .name = "Marcus Flint", .playing = true};
struct Player chaserS_2_s = {.thread = &chaserS_2, .team = "Slytherin", .name = "Graham Montague", .playing = true};
struct Player chaserS_3_s = {.thread = &chaserS_3, .team = "Slytherin", .name = "Cassius Warrington", .playing = true};
struct Player seekerG_s = {.thread = &seekerG, .team = "Gryffindor", .name = "Harry Potter", .playing = true};
struct Player seekerS_s = {.thread = &seekerS, .team = "Slytherin", .name = "Draco Malfoy", .playing = true};
struct Player keeperG_s = {.thread = &keeperG, .team = "Gryffindor", .name = "Oliver Wood", .playing = true};
struct Player keeperS_s = {.thread = &keeperS, .team = "Slytherin", .name = "Miles Bletchley", .playing = true};
struct Player beaterG_1_s = {.thread = &beaterG_1, .team = "Gryffindor", .name = "Fred Weasley", .playing = true};
struct Player beaterG_2_s = {.thread = &beaterG_2, .team = "Gryffindor", .name = "George Weasley", .playing = true};
struct Player beaterS_1_s = {.thread = &beaterS_1, .team = "Slytherin", .name = "Peregrine Derrick", .playing = true};
struct Player beaterS_2_s = {.thread = &beaterS_2, .team = "Slytherin", .name = "Lucian Bole", .playing = true};

// Array of pointers to all of the player structs
struct Player *players[14] = {&chaserG_1_s, &chaserG_2_s, &chaserG_3_s,
                              &chaserS_1_s, &chaserS_2_s, &chaserS_3_s,
                              &seekerG_s, &seekerS_s, &keeperG_s, &keeperS_s,
                              &beaterG_1_s, &beaterG_2_s, &beaterS_1_s, &beaterS_2_s};

static int gryffindor = 0;
static int slytherin = 0;
pthread_t gryffindor_goal;
pthread_t slytherin_goal;

#endif //UNTITLED_TEAMS_H
