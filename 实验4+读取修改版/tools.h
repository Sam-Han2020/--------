#pragma once

#include "service.h"

// card

int initCard(Cards* c);
int saveCard(Cards* c);
void cardcpy(Card* b,Card* a);
Card* getCard(Cards* c,char* id);
int vague_search(Cards *c,Cards* ret,char* txt,int txt_size);
void PrintCard(Cards *c);
void InsertCard(Cards* c,Card* newc);
void InsertCard1(Cards* c,Card* newc);

// bill

Billing* CreateBilling(char id[40]);
int initBill(Billings *b);
int saveBill(Billings* b);
Billing* searchLoginBill(Billings* b,char* id);
void InsertBilling(Billings* b,Billing* newb);
void InsertBilling1(Billings* b,Billing* newb);
int calcu_bills(Billings* b,Billings* nb,char *id,time_t start,time_t end);

// charge

Charge* CreateCharge(char id[40],int st,float money);
int initCharge(Charges* m);
void InsertCharge(Charges* m,Charge* newM);
int saveCharge(Charges *m);
void InsertCharge(Charges* m,Charge* newM);
void InsertCharge1(Charges* m,Charge* newM);
double calcu_Money(Charges *m,time_t st,time_t ed);

// tool

void delString (char* txt);
void printTime(time_t tt);
void time_to_string(time_t tt,char* strTime,int size);
long int string_to_time(char* strTime);
time_t getTime(int year,int mon,int mday);
void initSystem(Cards* c,Billings* b,Charges* m);
void save(Cards* c,Billings* b,Charges* m);
void get_next(char *txt,int *next,int txt_size);
int index_KMP(char* txt,char *id,int id_size,int txt_size);
int get_size(char* txt);
void InputID(char* id);
void InputPWD(char* pwd);
double CalcuPrice(time_t tStart,time_t tEnd);
