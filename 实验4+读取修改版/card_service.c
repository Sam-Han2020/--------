#include "card_service.h"
#include "tools.h"

void ReadCard(Cards *c,Charges *m)
{
    printf("----------------------- ��ӿ� -----------------------\n");
    Card* newc = (Card*)malloc(sizeof(Card));
    char id[MAXLEN];
    char pwd[MAXLEN];
    float balance;
    InputID(id);
    if(getCard(c,id)!=NULL)
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
    Charge* im=(Charge *)malloc(sizeof(Charge));
    strcpy(im->aCardName,newc->aId);
    im->fMoney = newc->fBalance;
    im->nDel=0;
    im->next1=NULL;
    im->nStatus=0;
    im->tTime = newc->tStart;
    InsertCharge(m,im);
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

void SignOff(Cards *c,Charges *m)
{
    printf("----------------------- ע���� -----------------------\n");
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
        printf("ע���������ɻָ�,��ȷ���Ƿ�ִ�У�\n");
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
        if(c==2) return ;
        if(c==1 && cd->fBalance>=0) 
        {
            cd->nStatus = 2;
            time(&(cd->tLast));
            printf("------------------- ע����Ϣ���� ---------------------\n");
            printf("����\t�˿���\n");
            printf("%s\t%.1lf\n",cd->aId,cd->fBalance);
            Charge* im = (Charge *)malloc(sizeof(Charge));
            strcpy(im->aCardName,cd->aId);
            im->fMoney = cd->fBalance;
            im->nDel=0;
            im->next1=NULL;
            im->nStatus=1;
            im->tTime = cd->tLast;
            InsertCharge(m,im);
        }
        else if(c==1)
        {
            // cd->nStatus = 2;
            // printf("------------------- ע����Ϣ���� ---------------------\n");
            // printf("����\n");
            // printf("%s\n",cd->aId);
            printf("���ȸ���β�����ע����!\n");
        }
    }
    else
    {
        printf("�������!\n");
    }
    system("pause");
}