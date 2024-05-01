#pragma once

#include "service.h"

void delString (char* txt);
void printTime(time_t tt);
void time_to_string(time_t tt,char* strTime,int size);
void initSystem(Cards* c,Billings* b);
void save(Cards* c);
Card* search(Cards* c,char* id);
void PrintCard(Cards *c);
void InsertCard(Cards* c,Card* newc);
void InsertBilling(Billings* b,Billing* newb);
Billings* CreateBilling(char *id);
Billing* searchLoginBill(Billings* b,char* id);
void InsertCard1(Cards* c,Card* newc);
int vague_search(Cards *c,Cards* ret,char* txt,int txt_size);
int get_size(char* txt);
void InputID(char* id);
void InputPWD(char* pwd);
double CalcuPrice(time_t tStart,time_t tEnd);