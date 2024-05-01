#pragma once
#include <stdio.h>
#include <time.h>
#include <string.h>
#define MAXLEN 18
#define SIZE 100

typedef struct card
{
    char aId[MAXLEN];
    char aPwd[MAXLEN];
    int nStatus;
    time_t tStart;
    time_t tEnd;
    float fTotalUse;
    time_t tLast;
    int nUseCount;
    float fBalance;
    int nDel;
} Card;

typedef struct Cards
{
    int num;
    Card cards[SIZE];
}Cards;

void save(Cards* c);
void initSystem(Cards* c);
void initSystem2(Cards* c);
void ReadCard(Cards* c);
void SearchCard(Cards* c);
void LogIn();
void LogOff();
void InsertMoney();
void GetMoney();
void ShowStatistics();
void SignOff();
void Exit(Cards* c);
void showDefault();