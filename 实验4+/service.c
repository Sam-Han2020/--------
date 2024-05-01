#include <stdio.h>
#include "service.h"
#include "tools.h"

void ReadCard(Cards *c)
{
    printf("----------------------- ��ӿ� -----------------------\n");
    Card* newc = (Card*)malloc(sizeof(Card));
    char id[MAXLEN];
    char pwd[MAXLEN];
    float balance;
    InputID(id);
    if(search(c,id)!=NULL)
    {
        printf("������Ѿ�����\n");
        system("pause");
        return ;
    }
    strcpy(newc->aId,id);
    InputPWD(pwd);
    strcpy(newc->aPwd,pwd);
    while(1)
    {
        printf("������ҵ����<��ֵΪ1~100>:");
        scanf("%f",&balance);
        if(balance<1 || balance>100)
            printf("���ݷǷ�������������!\n");
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
    printf("��ȷ�ϣ�\n");
    printf("-----��ӿ�����Ϣ����-----\n");
    printf("����\t����\t״̬\t�������\n");
    printf("%s\t%s\t%d\t%.1f\n",newc->aId,newc->aPwd,newc->nStatus,newc->fBalance);
    system("pause");
    InsertCard(c,newc);
    printf("�����ɹ�(=���ء�=)\n");
    system("pause");
}

void SearchCard(Cards* c)
{
    printf("----------------------- ��ѯ�� -----------------------\n");
    char id[MAXLEN];
    InputID(id);
    Cards ics;
    int k=vague_search(c,&ics,id,get_size(id));
    if(k==0)
    {
        printf("ʲôҲû���ҵ�QAQ\n");
        system("pause");
        return ;
    }
    printf("-----��ѯ���Ŀ�����Ϣ����-----\n");
    Card* ic = ics.head;
    while(ic!=ics.tail->next1)
    {
        char time[40];
        time_to_string(ic->tLast,time,sizeof(time));
        printf("����\t״̬\t���\t�ۼ�ʹ��\tʹ�ô���\t�ϴ�ʹ��ʱ��\n");
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
    printf("----------------------- �ϻ� -------------------------\n");
    char id[MAXLEN];
    InputID(id);
    Card* cd;
    if((cd=search(c,id))==NULL)
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
    if((cd=search(c,id))==NULL)
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

void InsertMoney()
{
    printf("----------------------- ��ֵ -------------------------\n");
    system("pause");
}

void GetMoney()
{
    printf("----------------------- �˷� -------------------------\n");
    system("pause");
}

void ShowStatistics()
{
    printf("--------------------- ��ѯͳ�� -----------------------\n");
    system("pause");
}

void SignOff()
{
    printf("----------------------- ע���� -----------------------\n");
    system("pause");
}

void Exit(Cards* c)
{
    printf("���ڱ�������ing������\n");
    save(c);
    printf("��л��ʹ�üƷѹ���ϵͳ\n");
    system("pause");
}

void showDefault()
{
    printf("������������������\n");
    system("pause");
}
