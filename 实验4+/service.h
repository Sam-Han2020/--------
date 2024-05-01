#pragma once
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
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
    struct card* next;
    struct card* next1;
} Card;

typedef struct cards
{
    Card *head,*tail;
}Cards;

typedef struct Billing
{
    char aCardName[18];
    time_t tStart;
    time_t tEnd;
    float fAmount;
    int nStatus;
    int nDel;
    struct Billing* next;
}Billing;

typedef struct Billings
{
    Billing *head,*tail;
}Billings;

// typedef struct BillingNode
// {
//     Billing data;
//     struct BillingNode *next;
// }BillingNode,*lpBillingNode;

typedef struct LoginInfo
{
    char aCardName[18];
    time_t tLogin;
    float fBalance;
}LoginInfo;

typedef struct SettleInfo
{
    char aCardName[18];
    time_t tStart;
    time_t tEnd;
    float fAmount;
    float fBalance;
}SettleInfo;

typedef struct Charge
{
    char aCardName[18]; // 卡号
    time_t tTime; // 充值退费的时间
    int nStatus; // 状态：0-表示充值；1-表示退费
    float fMoney; // 充值退费金额
    int nDel; // 删除标识，0-未删除,1-删除
}Charge;

void ReadCard(Cards *c);
void SearchCard(Cards* c);
void LogIn(Cards* c,Billings* b);
void LogOff(Cards* c,Billings* b);
void InsertMoney();
void GetMoney();
void ShowStatistics();
void SignOff();
void Exit(Cards* c);
void showDefault();