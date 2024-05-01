#include "billing_service.h"
#include "tools.h"

void LogIn(Cards* c,Billings* b)
{
    printf("----------------------- 上机 -------------------------\n");
    char id[MAXLEN];
    InputID(id);
    Card* cd;
    if((cd=getCard(c,id))==NULL)
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
    if((cd=getCard(c,id))==NULL)
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