#include "billing_service.h"
#include "tools.h"

void LogIn(Cards* c,Billings* b)
{
    printf("----------------------- �ϻ� -------------------------\n");
    char id[MAXLEN];
    InputID(id);
    Card* cd;
    if((cd=getCard(c,id))==NULL)
    {
        printf("û���ҵ���Ӧ���û���\n");
        system("pause");
        return ;
    }
    char pwd[MAXLEN];
    InputPWD(pwd);
    if(strcmp(cd->aPwd,pwd)==0)
    {
        if(cd->fBalance<0)
        {
            printf("���Ŀ���Ƿ�ѣ��뵽������Ա������\n");
            printf("Ƿ�ѽ��: %.1lf\n",-(cd->fBalance));
            system("pause");
            return ;
        }
        if(cd->nStatus==1)
        {
            printf("�����ϻ���!\n");
            system("pause");
            return ;
        }
        printf("�ϻ�ing...\n");
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
        printf("------------------- �ϻ���Ϣ���� ---------------------\n");
        printf("����\t���\t�ϻ�ʱ��\n");
        printf("%s\t%.1f\t%s\n",lgif.aCardName,lgif.fBalance,time);
    }
    else
    {
        printf("�������!\n");
    }
    system("pause");
}

void LogOff(Cards* c,Billings* b)
{
    printf("----------------------- �»� -------------------------\n");
    char id[MAXLEN];
    InputID(id);
    Card* cd;
    if((cd=getCard(c,id))==NULL)
    {
        printf("û���ҵ���Ӧ���û���\n");
        system("pause");
        return ;
    }
    char pwd[MAXLEN];
    InputPWD(pwd);
    if(strcmp(cd->aPwd,pwd)==0)
    {
        if(cd->nStatus==0)
        {
            printf("��û�ϻ���!\n");
            system("pause");
            return ;
        }
        Billing* targetB = searchLoginBill(b,id);
        if(targetB == NULL)
        {
            printf("û���ҵ���Ӧ�����Ѽ�¼!\n");
            system("pause");
            return ;
        }
        printf("�»�ing...\n");
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
            printf("------------------- �»���Ϣ���� ---------------------\n");
            printf("����\t����\t���\t�ϻ�ʱ��\t\t�»�ʱ��\n");
            printf("%s\t%.1lf\t%.1lf\t%s\t%s\n",cd->aId,price,cd->fBalance,time1,time2);
        }
        else
        {
            printf("���Ŀ���Ƿ�ѣ��뵽������Ա������\n");
            printf("Ƿ�ѽ��: %.1lf\n",-(cd->fBalance));
            printf("����\t����\t�ϻ�ʱ��\t\t�»�ʱ��\n");
            printf("%s\t%.1lf\t%s\t%s\n",cd->aId,price,time1,time2);
        }
    }
    else
    {
        printf("�������!\n");
    }
    system("pause");
}