#define _CRT_SECURE_NO_WARNINGS //消除vs开发环境中使用scanf（）函数引起的
#include"model.h"
#include<stdio.h>
#include<malloc.h>
#include<string.h>
Card aCard[50];
int nCount = 0;
int addCard(Card card) {
    aCard[nCount] = card;
    nCount++;
    return nCount;
}
Card* queryCard(const char*pName ) {
    char aTime[20] = { 0 };
    for (int i = 0; i < nCount; i++) {
       
        if (strcmp(pName, aCard[i].aName) == 0) {
            //timeToString(aCard[i].tLast, aTime);
            return &aCard[i];
        }
        else {
            printf("未找到该卡信息");
        }

   }
}