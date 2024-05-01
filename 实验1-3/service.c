#include <stdio.h>
#include "main.h"

void delString (char* txt)
{
    for(int i=0;i<strlen(txt);++i) txt[i]='\0';
}

void printTime(time_t tt)
{
    struct tm * timeinfo;
    timeinfo = localtime(&tt);
    char strTime[40];
    strftime(strTime,sizeof(strTime),"%Y��%m��%d�� %H:%M",timeinfo);
    printf(strTime);
}

void time_to_string(time_t tt,char* strTime,int size)
{
    struct tm * timeinfo;
    timeinfo = localtime(&tt);
    strftime(strTime,size,"%Y-%m-%d %H:%M:%S",timeinfo);
}

// void initSystem(Cards* c)
// {
//     FILE *fp;
//     if((fp=fopen("card.dat","r"))==NULL)
//     {
//         c->num=0;
//         return ;
//     }
//     int i=0;
//     int* a=&i;
//     fread(a,4,1,fp);
//     fread(c,sizeof(Cards),i,fp);
//     printf("���������ˣ������%d������\n",i);
//     c->num=i;
//     system("pause");
// }

void initSystem2(Cards* c)
{
    FILE *fp;
    if((fp=fopen("card.txt","r"))==NULL)
    {
        c->num=0;
        return ;
    }
    int i=0;
    char line[1024];
    long int Start,End,LastTime;
    while(fgets(line,sizeof(line),fp)!=NULL)
    {
        // printf(line);
        sscanf(line,"%[^##]##%[^##]##%d##%ld##%ld##%f##%ld##%d##%f##%d\n",c->cards[i].aId,c->cards[i].aPwd,&c->cards[i].nStatus,&Start,&End,&c->cards[i].fTotalUse,&LastTime,&c->cards[i].nUseCount,&c->cards[i].fBalance,&c->cards[i].nDel);
        c->cards[i].tStart=(time_t)Start;
        c->cards[i].tEnd=(time_t)End;
        c->cards[i].tLast=(time_t)LastTime;
        ++i;
    }
    printf("���������ˣ������%d������\n",i);
    c->num=i;
    system("pause");
}

void test(Cards *c)
{
    for(int i=0;i<c->num;++i)
    {
        printf("%d: %s %s\n",i,c->cards[i].aId,c->cards[i].aPwd);
    }
}

void save(Cards* c)
{
    FILE *fp,*fd;
    if((fp = fopen("card.txt","w")) == NULL)
    {
        printf("���ݱ���ʧ�ܣ�\n");
        return ;
    }
    for(int i=0;i<c->num;++i)
    {
        long int sstart=c->cards[i].tStart;
        long int send=c->cards[i].tEnd;
        long int slast=c->cards[i].tLast;
        fprintf(fp,"%s##%s##%d##%ld##%ld##%.1f##%ld##%d##%.1f##%d\n",c->cards[i].aId,c->cards[i].aPwd,c->cards[i].nStatus,sstart,send,c->cards[i].fTotalUse,slast,c->cards[i].nUseCount,c->cards[i].fBalance,c->cards[i].nDel);
    }
    fclose(fp);
    if((fd = fopen("card.dat","w")) == NULL)
    {
        printf("���ݱ���ʧ�ܣ�\n");
        return ;
    }
    int *a = &c->num;
    fwrite(a,4,1,fd);
    fwrite(c,sizeof(Cards),c->num,fd);
    printf("���ˣ�������%d������\n",c->num);
}

void ReadCard(Cards* c)
{
    printf("----------------------- ��ӿ� -----------------------\n");
    if(c->num>=SIZE-1)
    {
        printf("�û�����������>w<!\n");
        system("pause");
        return;
    }
    char id[MAXLEN];
    char pwd[MAXLEN];
    float balance;
    while(1)
    {
        printf("�����뿨��<����Ϊ1~18>:");
        scanf("%s",id);
        if(strlen(id)>MAXLEN-1)
        {
            printf("���Ź���������������!\n");
            for(int i=0;i<MAXLEN;++i) id[i]='\0';
        }
        else 
            break;
    }
    if(search(c,id)!=-1)
    {
        printf("������Ѿ�����\n");
        system("pause");
        return ;
    }
    strcpy(c->cards[c->num].aId,id);
    while(1)
    {
        printf("����������<����Ϊ1~18>:");
        scanf("%s",pwd);
        if(strlen(pwd)>MAXLEN-1)
        {
            printf("�������������������!\n");
            delString(pwd);
        }
        else 
            break;
    }
    strcpy(c->cards[c->num].aPwd,pwd);
    while(1)
    {
        printf("������ҵ����<��ֵΪ1~100>:");
        scanf("%f",&balance);
        if(balance<1 || balance>100)
            printf("���ݷǷ�������������!\n");
        else 
            break;
    }
    c->cards[c->num].fBalance=balance;
    c->cards[c->num].nStatus=0;
    c->cards[c->num].fTotalUse=0;
    c->cards[c->num].nUseCount=0;
    c->cards[c->num].nDel=0;
    time(&(c->cards[c->num].tStart));
    c->cards[c->num].tEnd = c->cards[c->num].tLast = c->cards[c->num].tStart;
    // add_years(&c->cards[c->num].tEnd,5);
    struct tm * tend = localtime(&c->cards[c->num].tEnd);
    tend->tm_year += 5;
    // printf("%d\n",tend->tm_year);
    c->cards[c->num].tEnd = mktime(tend);
    // printTime(c->cards[c->num].tEnd);
    printf("��ȷ�ϣ�\n");
    printf("-----��ӿ�����Ϣ����-----\n");
    printf("����\t����\t״̬\t�������\n");
    printf("%s\t%s\t%d\t%.1f\n",c->cards[c->num].aId,c->cards[c->num].aPwd,c->cards[c->num].nStatus,c->cards[c->num].fBalance);
    ++c->num;
    system("pause");
    printf("�����ɹ�����ӭ�������������������(=���ء�=)\n");
    system("pause");
}

int search(Cards* c,char* id)
{
    int idx=-1;
    for(int i=0;i<c->num;++i)
    {
        if(strcmp(c->cards[i].aId,id)==0) idx=i; 
    }
    return idx;
}

void SearchCard(Cards* c)
{
    printf("----------------------- ��ѯ�� -----------------------\n");
    char id[MAXLEN];
    while(1)
    {
        printf("�����뿨��<����Ϊ1~18>:");
        scanf("%s",id);
        if(strlen(id)>MAXLEN-1)
        {
            printf("���Ź���������������!\n");
            delString(id);
        }
        else 
            break;
    }
    int idx = search(c,id);
    if(idx==-1)
    {
        printf("ʲôҲû���ҵ�QAQ\n");
        system("pause");
        return ;
    }
    printf("-----��ѯ���Ŀ�����Ϣ����-----\n");
    char time[40];
    time_to_string(c->cards[idx].tLast,time,sizeof(time));
    printf("����\t״̬\t���\t�ۼ�ʹ��\tʹ�ô���\t�ϴ�ʹ��ʱ��\n");
    printf("%s\t%d\t%.1f\t%.1f\t\t%d\t\t%s\n",c->cards[idx].aId,c->cards[idx].nStatus,c->cards[idx].fBalance,c->cards[idx].fTotalUse,c->cards[idx].nUseCount,time);
    system("pause");
}

void LogIn()
{
    printf("----------------------- �ϻ� -------------------------\n");
    system("pause");
}

void LogOff()
{
    printf("----------------------- �»� -------------------------\n");
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

void Exit(Cards *c)
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
