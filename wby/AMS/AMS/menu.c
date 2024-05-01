#define _CRT_SECURE_NO_WARNINGS //消除vs开发环境中使用scanf（）函数引起的
#include <stdio.h>
#include<time.h>
#include<stdlib.h>
#include"model.h"
#include "card_service.h"
#include"tool.h"
#include"menu.h"
void outputMenu(void) {
	//输出系统菜单
	printf("----------菜单----------\n");
	printf("1.添加卡\n");
	printf("2.查询卡\n");
	printf("3.上机\n");
	printf("4.下机\n");
	printf("5.充值\n");
	printf("6.退费\n");
	printf("7.查询统计\n");
	printf("8.注销卡\n");
	printf("0.退出\n");
	//提示选择菜单编号
	printf("请选择菜单项编号（0·8）：");
}
void add(Card* card) {
        int i = 0;
        Card* pNew = (Card*)malloc(sizeof(Card));

        printf("\n----------添加卡-----------\n");

        printf("请输入卡号(长度为1~18)：");
        char number[18] = { 0 };   // 输入的卡号
        scanf("%s", number);
        strcpy(pNew->aName, number);
        printf("请输入密码(长度为1~8)：");
        char password[9] = { 0 };    // 输入的密码
        scanf("%s", password);
        strcpy(pNew->aPwd, password);

        printf("请输入开卡金额(RMB)：");
        float m;
        scanf("%f", &m);
        pNew->fBalance = m;

        pNew->fTotalUse = pNew->fBalance;    
        pNew->nDel = 0;                     // 删除标识
        pNew->nStatus = 0;                  // 卡状态
        pNew->nUseCount = 0;                // 使用次数
        pNew->tStart = pNew->tEnd = pNew->tLast = time(NULL);
        printf("\n------添加的卡信息如下------\n");
        printf("卡号\t\t密码\t\t状态\t\t开卡金额\t\n");
        printf("%s\t\t%s\t\t%d\t\t%.1f\t\t\n", pNew->aName, pNew->aPwd,pNew->nStatus, pNew->fBalance);
        printf("\n");
        addCard(*pNew);

}
void query(Card *card) {
        printf("\n----------查询卡-----------\n");
        Card* aCard = NULL;
        printf("请输入要查询的卡号(长度为1~18)：");
        char number[18] = { 0 };   // 输入的卡号
        char aTime[20] = {0};
        scanf("%s", number);
        aCard=queryCard(number);
        timeToString(aCard->tLast, aTime);
        printf("卡号\t\t状态\t\t余额\t\t累计使用金额\t使用次数\t上次使用时间\n");
        printf("%s\t\t%d\t\t%0.2f\t\t%0.2f\t\t%d\t\t%s\n", aCard->aName, aCard->nStatus, aCard->fBalance, aCard->fTotalUse, aCard->nUseCount,aTime);
        system("pause");
}