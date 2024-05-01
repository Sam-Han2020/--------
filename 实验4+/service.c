#include <stdio.h>
#include "service.h"
#include "tools.h"

void ReadCard(Cards *c)
{
    printf("----------------------- 添加卡 -----------------------\n");
    Card* newc = (Card*)malloc(sizeof(Card));
    char id[MAXLEN];
    char pwd[MAXLEN];
    float balance;
    InputID(id);
    if(search(c,id)!=NULL)
    {
        printf("这个卡已经有啦\n");
        system("pause");
        return ;
    }
    strcpy(newc->aId,id);
    InputPWD(pwd);
    strcpy(newc->aPwd,pwd);
    while(1)
    {
        printf("请输入业务金额<数值为1~100>:");
        scanf("%f",&balance);
        if(balance<1 || balance>100)
            printf("数据非法，请重新输入!\n");
        else 
            break;
    }
    newc->fBalance=balance;
    newc->nStatus=0;
    newc->fTotalUse=0;
    newc->nUseCount=0;
    newc->nDel=0;
    newc->next=NULL;
    newc->next1=NULL;
    time(&(newc->tStart));
    newc->tEnd = newc->tLast = newc->tStart;
    struct tm * tend = localtime(&newc->tEnd);
    tend->tm_year += 5;
    newc->tEnd = mktime(tend);
    printf("请确认：\n");
    printf("-----添加卡的信息如下-----\n");
    printf("卡号\t密码\t状态\t开卡金额\n");
    printf("%s\t%s\t%d\t%.1f\n",newc->aId,newc->aPwd,newc->nStatus,newc->fBalance);
    system("pause");
    InsertCard(c,newc);
    printf("开卡成功(=·ω·=)\n");
    system("pause");
}

void SearchCard(Cards* c)
{
    printf("----------------------- 查询卡 -----------------------\n");
    char id[MAXLEN];
    InputID(id);
    Cards ics;
    int k=vague_search(c,&ics,id,get_size(id));
    if(k==0)
    {
        printf("什么也没有找到QAQ\n");
        system("pause");
        return ;
    }
    printf("-----查询到的卡的信息如下-----\n");
    Card* ic = ics.head;
    while(ic!=ics.tail->next1)
    {
        char time[40];
        time_to_string(ic->tLast,time,sizeof(time));
        printf("卡号\t状态\t余额\t累计使用\t使用次数\t上次使用时间\n");
        printf("%s\t%d\t%.1f\t%.1f\t\t%d\t\t%s\n",ic->aId,ic->nStatus,ic->fBalance,ic->fTotalUse,ic->nUseCount,time);
        ic=ic->next1;
    }
    system("pause");
    Card* ic0 = c->head;
    while(ic0!=NULL)
    {
        ic0->next1=NULL;
        ic0=ic0->next;
    }
}

void LogIn(Cards* c,Billings* b)
{
    printf("----------------------- 上机 -------------------------\n");
    char id[MAXLEN];
    InputID(id);
    Card* cd;
    if((cd=search(c,id))==NULL)
    {
        printf("没有找到对应的用户！\n");
        system("pause");
        return ;
    }
    char pwd[MAXLEN];
    InputPWD(pwd);
    if(strcmp(cd->aPwd,pwd)==0)
    {
        if(cd->fBalance<0)
        {
            printf("您的卡已欠费，请到工作人员处处理\n");
            printf("欠费金额: %.1lf\n",-(cd->fBalance));
            system("pause");
            return ;
        }
        if(cd->nStatus==1)
        {
            printf("你在上机呢!\n");
            system("pause");
            return ;
        }
        printf("上机ing...\n");
        cd->nStatus=1;
        ++cd->nUseCount;
        Billing* newB = CreateBilling(id);
        cd->tLast = newB->tStart;
        InsertBilling(b,newB);
        LoginInfo lgif;
        strcpy(lgif.aCardName,id);
        lgif.tLogin = newB->tStart;
        lgif.fBalance = cd->fBalance;
        char time[40];
        time_to_string(lgif.tLogin,time,sizeof(time));
        printf("------------------- 上机信息如下 ---------------------\n");
        printf("卡号\t余额\t上机时间\n");
        printf("%s\t%.1f\t%s\n",lgif.aCardName,lgif.fBalance,time);
    }
    else
    {
        printf("密码错误!\n");
    }
    system("pause");
}

void LogOff(Cards* c,Billings* b)
{
    printf("----------------------- 下机 -------------------------\n");
    char id[MAXLEN];
    InputID(id);
    Card* cd;
    if((cd=search(c,id))==NULL)
    {
        printf("没有找到对应的用户！\n");
        system("pause");
        return ;
    }
    char pwd[MAXLEN];
    InputPWD(pwd);
    if(strcmp(cd->aPwd,pwd)==0)
    {
        if(cd->nStatus==0)
        {
            printf("你没上机呢!\n");
            system("pause");
            return ;
        }
        Billing* targetB = searchLoginBill(b,id);
        if(targetB == NULL)
        {
            printf("没有找到对应的消费记录!\n");
            system("pause");
            return ;
        }
        printf("下机ing...\n");
        cd->nStatus=0;
        time(&(targetB->tEnd));
        cd->tLast = targetB->tEnd;
        double price = CalcuPrice(targetB->tStart,targetB->tEnd);
        // printf("price = %.3lf\n",price);
        cd->fTotalUse+=price;
        cd->fBalance-=price;
        targetB->fAmount = price;
        targetB->nStatus = 1;
        char time1[40];
        time_to_string(targetB->tStart,time1,sizeof(time1));
        char time2[40];
        time_to_string(targetB->tEnd,time2,sizeof(time2));
        if(cd->fBalance>=0)
        {
            printf("------------------- 下机信息如下 ---------------------\n");
            printf("卡号\t消费\t余额\t上机时间\t\t下机时间\n");
            printf("%s\t%.1lf\t%.1lf\t%s\t%s\n",cd->aId,price,cd->fBalance,time1,time2);
        }
        else
        {
            printf("您的卡已欠费，请到工作人员处处理\n");
            printf("欠费金额: %.1lf\n",-(cd->fBalance));
            printf("卡号\t消费\t上机时间\t\t下机时间\n");
            printf("%s\t%.1lf\t%s\t%s\n",cd->aId,price,time1,time2);
        }
    }
    else
    {
        printf("密码错误!\n");
    }
    system("pause");
}

void InsertMoney()
{
    printf("----------------------- 充值 -------------------------\n");
    system("pause");
}

void GetMoney()
{
    printf("----------------------- 退费 -------------------------\n");
    system("pause");
}

void ShowStatistics()
{
    printf("--------------------- 查询统计 -----------------------\n");
    system("pause");
}

void SignOff()
{
    printf("----------------------- 注销卡 -----------------------\n");
    system("pause");
}

void Exit(Cards* c)
{
    printf("正在保存数据ing。。。\n");
    save(c);
    printf("感谢你使用计费管理系统\n");
    system("pause");
}

void showDefault()
{
    printf("输入有误，请重新输入\n");
    system("pause");
}
