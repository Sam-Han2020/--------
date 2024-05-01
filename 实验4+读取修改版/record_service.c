#include "record_service.h"
#include "tools.h"

void InsertMoney(Cards* c,Charges* m)
{
    printf("----------------------- ��ֵ -------------------------\n");
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
        if(cd->nStatus == 2)
        {
            printf("�ÿ���ע�����޷����г�ֵ������\n");
            system("pause");
            return ;
        }
        float balance=0;
        while(1)
        {
            printf("�������ֵ���<���γ�ֵ���Ϊ1-100RMB>:");
            scanf("%f",&balance);
            if(balance<1 || balance>100)
                printf("���ݷǷ�������������!\n");
            else
                break;
        }
        Charge* im = CreateCharge(id,0,balance);
        InsertCharge(m,im);
        time(&(cd->tEnd));
        cd->fBalance+=balance;
        printf("------------------- ��ֵ��Ϣ���� ---------------------\n");
        printf("����\t��ֵ���\t���\n");
        printf("%s\t%.1lf\t\t%.1lf\n",cd->aId,balance,cd->fBalance);
    }
    else
    {
        printf("�������!\n");
    }
    system("pause");
}

void GetMoney(Cards* c,Charges* m)
{
    printf("----------------------- �˷� -------------------------\n");
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
        if(cd->fBalance <= 0)
        {
            printf("��Ŀ����㣬�޷������˷Ѳ���!\n");
            system("pause");
            return ;
        }
        float balance=0;
        while(1)
        {
            printf("�������˷ѽ��<���γ�ֵ���Ϊ1-100RMB>:");
            scanf("%f",&balance);
            if(balance<1 || balance>100)
                printf("���ݷǷ�������������!\n");
            else 
                break;
        }
        if(cd->fBalance - balance <= 0)
        {
            printf("��Ŀ����㣬�Ƿ����ȫ���˷Ѳ���?\n");
            printf("�� - 1 ; �� - 2\n");
            int c=0;
            while(c!=1 && c!=2)
            {
                char ch[4];
                scanf("%s",ch);
                c = ch[0]-'0';
                if(c==1 || c==2) break;
                printf("���������룡\n");
            }
            if(c==1) balance = cd->fBalance;
            if(c==2) return ;
        }
        Charge* im = CreateCharge(id,1,balance);
        InsertCharge(m,im);
        time(&(cd->tEnd));
        cd->fBalance-=balance;
        printf("------------------- �˷���Ϣ���� ---------------------\n");
        printf("����\t�˷ѽ��\t���\n");
        printf("%s\t%.1lf\t\t%.1lf\n",cd->aId,balance,cd->fBalance);
    }
    else
    {
        printf("�������!\n");
    }
    system("pause");
}