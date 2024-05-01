#include "tools.h"

void delString (char* txt)
{
    for(int i=0;i<strlen(txt);++i) txt[i]='\0';
}

void printTime(time_t tt)
{
    struct tm * timeinfo;
    timeinfo = localtime(&tt);
    char strTime[40];
    strftime(strTime,sizeof(strTime),"%Y年%m月%d日 %H:%M",timeinfo);
    printf(strTime);
}

void time_to_string(time_t tt,char* strTime,int size)
{
    struct tm * timeinfo;
    timeinfo = localtime(&tt);
    strftime(strTime,size,"%Y-%m-%d %H:%M:%S",timeinfo);
}

void cardcpy(Card* b,Card* a)
{
    strcpy(b->aId,a->aId);
    strcpy(b->aPwd,a->aPwd);
    b->fBalance = a->fBalance;
    b->fTotalUse = a->fTotalUse;
    b->nDel = a->nDel;
    b->nStatus = a->nStatus;
    b->nUseCount = a->nUseCount;
    b->tEnd = a->tEnd;
    b->tLast = a->tLast;
    b->tStart = a->tStart;
}

void initSystem(Cards* c,Billings* b)
{
    c->tail=NULL;
    c->head=c->tail;
    b->tail=NULL;
    b->head = b->tail;
    FILE *fp;
    if((fp=fopen("card_file.txt","r"))==NULL)
    {
        return ;
    }
    int i=0;
    char line[1024];
    long int Start,End,LastTime;
    while(fgets(line,sizeof(line),fp)!=NULL)
    {
        Card* ic = (Card*)malloc(sizeof(Card));
        sscanf(line,"%[^##]##%[^##]##%d##%ld##%ld##%f##%ld##%d##%f##%d\n",ic->aId,ic->aPwd,&ic->nStatus,&Start,&End,&ic->fTotalUse,&LastTime,&ic->nUseCount,&ic->fBalance,&ic->nDel);
        ic->tStart=(time_t)Start;
        ic->tEnd=(time_t)End;
        ic->tLast=(time_t)LastTime;
        ic->next1=NULL;
        InsertCard(c,ic);
        ++i;
    }
    system("cls");
    printf("好像连上了，获得了%d条数据\n",i);
    system("pause");
}

void save(Cards* c)
{
    FILE *fp,*fd;
    Card* ic = c->head;
    int i=0;
    if(ic==NULL)
    {
        return ;
    }
    if((fp = fopen("card_file.txt","w")) == NULL)
    {
        printf("数据保存失败！\n");
        return ;
    }
    while(ic!=NULL)
    {
        ic->next1=NULL;
        long int sstart=ic->tStart;
        long int send=ic->tEnd;
        long int slast=ic->tLast;
        fprintf(fp,"%s##%s##%d##%ld##%ld##%.1f##%ld##%d##%.1f##%d\n",ic->aId,ic->aPwd,ic->nStatus,sstart,send,ic->fTotalUse,slast,ic->nUseCount,ic->fBalance,ic->nDel);
        Card *p = ic;
        ic=ic->next;
        free(p);
        ++i;
    }
    fclose(fp);
    printf("主人，保存了%d条数据\n",i);
}

Card* search(Cards* c,char* id)
{
    Card* p=c->head;
    while(p!=NULL)
    {
        if(strcmp(p->aId,id)==0) return p;
        p=p->next;
    }
    return NULL;
}

Billing* searchLoginBill(Billings* b,char* id)
{
    Billing* p=b->head;
    while(p!=NULL)
    {
        if(strcmp(p->aCardName,id)==0 && p->nStatus==0) return p;
        p=p->next;
    }
    return NULL;
}

void get_next(char *txt,int *next,int txt_size)
{
    int j=0,k=-1;
    next[j]=-1;
    while(j<txt_size-1)
    {
        if(k==-1 ||txt[j]==txt[k])
        {
            ++j;++k;
            next[j]=k;
        }
        else k=next[k];
    }
}

int index_KMP(char* txt,char *id,int id_size,int txt_size)
{
    int next[txt_size-1];
    get_next(txt,next,txt_size);
    int i=0,j=0;
    while(i<id_size-1 && j<txt_size-1)
    {
        if(j==-1 || id[i]==txt[j]) ++i,++j;
        else j=next[j];
    }
    if(j>=txt_size-1) return i-txt_size+1;
    else return -1;
}

int get_size(char* txt)
{
    int i=0;
    while(txt[i]!='\0') ++i;
    return i+1;
}

int vague_search(Cards *c,Cards* ret,char* txt,int txt_size)
{
    Card* p=c->head;
    int sign=1;
    ret->tail=NULL;
    ret->head=ret->tail;
    while(p!=c->tail->next)
    {
        int idx=index_KMP(txt,p->aId,get_size(p->aId),txt_size);
        // printf("%d\n",idx);
        if(idx!=-1)
        {
            InsertCard1(ret,p);
            sign=0;
        }
        p=p->next;
    }
    if(sign) return 0;
    return 1;
}

void PrintCard(Cards *c)
{
    Card* p=c->head;
    while(p!=NULL)
    {
        printf("%s\t%s\t%d\t%.1f\n",p->aId,p->aPwd,p->nStatus,p->fBalance);
        p=p->next;
    }
}

void InsertCard1(Cards* c,Card* newc)
{
    if(c->head)
    {
        c->tail->next1=newc;
        c->tail=c->tail->next1;
        c->tail->next1=NULL;
    }
    else
    {
        c->head=c->tail=newc;
    }
}

void InsertCard(Cards* c,Card* newc)
{
    if(c->head)
    {
        c->tail->next=newc;
        c->tail=c->tail->next;
        c->tail->next=NULL;
    }
    else
    {
        c->head=c->tail=newc;
    }
}

void InsertBilling(Billings* b,Billing* newb)
{
    if(b->head)
    {
        b->tail->next=newb;
        b->tail=b->tail->next;
        b->tail->next=NULL;
    }
    else
    {
        b->head=b->tail=newb;
    }
}

Billing* CreateBilling(char *id)
{
    Billing* newB = (Billing*)malloc(sizeof(struct Billing));
    strcpy(newB->aCardName,id);
    time(&(newB->tStart));
    time(&(newB->tEnd));
    newB->fAmount = 0;
    newB->nStatus = 0;
    newB->nDel = 0;
    return newB;
}

// Charge

void InputID(char* id)
{
    while(1)
    {
        printf("请输入卡号<长度为1~18>:");
        scanf("%s",id);
        if(strlen(id)>MAXLEN-1)
        {
            printf("卡号过长，请重新输入!\n");
            delString(id);
        }
        else 
            break;
    }
}

void InputPWD(char* pwd)
{
    while(1)
    {
        printf("请输入密码<长度为1~18>:");
        scanf("%s",pwd);
        if(strlen(pwd)>MAXLEN-1)
        {
            printf("密码过长，请重新输入!\n");
            delString(pwd);
        }
        else 
            break;
    }
}

double CalcuPrice(time_t tStart,time_t tEnd)
{
    double deltaTime = tEnd - tStart;
    int price = 10;
    return deltaTime * price / 3600;
}