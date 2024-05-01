#include "tools.h"
#include "card_service.h"
#include "billing_service.h"
#include "record_service.h"

//card

int initCard(Cards* c)
{
    c->tail=NULL;
    c->head=c->tail;
    FILE *fc;
    if((fc=fopen("card_file.txt","r"))==NULL)
    {
        return 0;
    }
    int i=0;
    char line[1024];
    char Start[40],End[40],Last[40];
    while(fgets(line,sizeof(line),fc)!=NULL)
    {
        Card* ic = (Card*)malloc(sizeof(Card));
        sscanf(line,"%[^##]##%[^##]##%d##%[^##]##%[^##]##%f##%[^##]##%d##%f##%d\n",ic->aId,ic->aPwd,&ic->nStatus,Start,End,&ic->fTotalUse,Last,&ic->nUseCount,&ic->fBalance,&ic->nDel);
        if(ic->nDel==1) continue;
        ic->tStart = (time_t)string_to_time(Start);
        ic->tEnd = (time_t)string_to_time(End);
        ic->tLast = (time_t)string_to_time(Last);
        ic->next1=NULL;
        InsertCard(c,ic);
        ++i;
    }
    fclose(fc);
    return i;
}

int saveCard(Cards* c)
{
    FILE *fp;
    Card* ic = c->head;
    if((fp = fopen("card_file.txt","w")) == NULL)
    {
        printf("卡片数据保存失败！\n");
        return 0;
    }
    if(ic==NULL)
    {
        return 0;
    }
    int i=0;
    while(ic!=NULL)
    {
        ic->next1=NULL;
        char sStart[40];
        char sEnd[40];
        char sLast[40];
        time_to_string(ic->tStart,sStart,sizeof(sStart)/sizeof(char));
        time_to_string(ic->tEnd,sEnd,sizeof(sEnd)/sizeof(char));
        time_to_string(ic->tLast,sLast,sizeof(sLast)/sizeof(char));
        fprintf(fp,"%s##%s##%d##%s##%s##%.1f##%s##%d##%.1f##%d\n",ic->aId,ic->aPwd,ic->nStatus,sStart,sEnd,ic->fTotalUse,sLast,ic->nUseCount,ic->fBalance,ic->nDel);
        Card *p = ic;
        ic=ic->next;
        free(p);
        ++i;
    }
    fclose(fp);
    return i;
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

int vague_search(Cards *c,Cards* ret,char* txt,int txt_size)
{
    Card* p=c->head;
    int sign=1;
    ret->tail=NULL;
    ret->head=ret->tail;
    while(p!=NULL)
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
        c->head->next=NULL;
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
        c->head->next1=NULL;
    }
}

// billing

Billing* CreateBilling(char id[40])
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

int initBill(Billings *b)
{
    b->tail=NULL;
    b->head = b->tail;
    FILE *fb;
    if((fb=fopen("billing_file.txt","r"))==NULL)
    {
        return 0;
    }
    int i=0;
    char line[1024];
    char Start[40],End[40];
    while(fgets(line,sizeof(line),fb)!=NULL)
    {
        Billing* ib = (Billing*)malloc(sizeof(Billing));
        sscanf(line,"%[^##]##%[^##]##%[^##]##%f##%d##%d\n",ib->aCardName,Start,End,&ib->fAmount,&ib->nStatus,&ib->nDel);
        if(ib->nDel==1) continue;
        ib->tStart = (time_t)string_to_time(Start);
        ib->tEnd = (time_t)string_to_time(End);
        ib->next1=NULL;
        InsertBilling(b,ib);
        ++i;
    }
    fclose(fb);
    return i;
}

int saveBill(Billings* b)
{
    FILE *fp;
    Billing* ib = b->head;
    if((fp = fopen("billing_file.txt","w")) == NULL)
    {
        printf("账单数据保存失败！\n");
        return 0;
    }
    if(ib==NULL)
    {
        return 0;
    }
    int i=0;
    while(ib!=NULL)
    {
        char sStart[40];
        char sEnd[40];
        time_to_string(ib->tStart,sStart,sizeof(sStart)/sizeof(char));
        time_to_string(ib->tEnd,sEnd,sizeof(sEnd)/sizeof(char));
        fprintf(fp,"%s##%s##%s##%.1f##%d##%d\n",ib->aCardName,sStart,sEnd,ib->fAmount,ib->nStatus,ib->nDel);
        ib->next1=NULL;
        Billing *p = ib;
        ib=ib->next;
        free(p);
        ++i;
    }
    fclose(fp);
    return i;
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
        b->head->next = NULL;
    }
}

void InsertBilling1(Billings* b,Billing* newb)
{
    if(b->head)
    {
        b->tail->next1=newb;
        b->tail=b->tail->next1;
        b->tail->next1=NULL;
    }
    else
    {
        b->head=b->tail=newb;
        b->head->next1 = NULL;
    }
}

int calcu_bills(Billings* b,Billings* nb,char *id,time_t start,time_t end)
{
    Billing *ib = b->head;
    nb->tail = NULL;
    nb->head = nb->tail;// 一定要初始化，否则发生空指针问题
    int sign = 0;
    while(ib!=NULL)
    {
        if(strcmp(ib->aCardName,id)==0 && ib->nStatus==1 && ib->tEnd > start && ib->tEnd < end)
        {
            InsertBilling1(nb,ib);
            sign = 1;
        }
        ib=ib->next;
    }
    return sign;
}

// charge

Charge* CreateCharge(char id[40],int st,float money)
{
    Charge* newM = (Charge*)malloc(sizeof(struct Charge));
    strcpy(newM->aCardName,id);
    time(&(newM->tTime));
    newM->nStatus=st;
    newM->fMoney = money;
    newM->nDel=0;
}

int initCharge(Charges* m)
{
    m->tail=NULL;
    m->head = m->tail;
    FILE *fp;
    if((fp=fopen("record_file.txt","r"))==NULL)
    {
        return 0;
    }
    int i=0;
    char line[1024];
    char sTime[40];
    while(fgets(line,sizeof(line),fp)!=NULL)
    {
        Charge* im = (Charge*)malloc(sizeof(Charge));
        sscanf(line,"%[^##]##%[^##]##%d##%f##%d\n",im->aCardName,sTime,&im->nStatus,&im->fMoney,&im->nDel);
        if(im->nDel==1) continue;
        im->tTime = (time_t)string_to_time(sTime);
        im->next1=NULL;
        InsertCharge(m,im);
        ++i;
    }
    fclose(fp);
    return i;
}

int saveCharge(Charges *m)
{
    FILE *fp;
    Charge *im = m->head;
    if((fp = fopen("record_file.txt","w")) == NULL)
    {
        printf("充值退费数据保存失败！\n");
        return 0;
    }
    if(im==NULL)
    {
        return 0;
    }
    int i=0;
    while(im!=NULL)
    {
        im->next1=NULL;
        char sTime[40];
        time_to_string(im->tTime,sTime,sizeof(sTime)/sizeof(char));
        fprintf(fp,"%s##%s##%d##%.1f##%d\n",im->aCardName,sTime,im->nStatus,im->fMoney,im->nDel);
        Charge *p = im;
        im=im->next;
        free(p);
        ++i;
    }
    fclose(fp);
    return i;
}

void InsertCharge(Charges* m,Charge* newM)
{
    if(m->head)
    {
        m->tail->next=newM;
        m->tail=m->tail->next;
        m->tail->next=NULL;
    }
    else
    {
        m->head=m->tail=newM;
        m->head->next = NULL;
    }
}

void InsertCharge1(Charges* m,Charge* newM)
{
    if(m->head)
    {
        m->tail->next1=newM;
        m->tail=m->tail->next1;
        m->tail->next1=NULL;
    }
    else
    {
        m->head=m->tail=newM;
        m->head->next1 = NULL;
    }
}

double calcu_Money(Charges *m,time_t st,time_t ed)
{
    Charge *im = m->head;
    double money = 0;
    while(im!=NULL)
    {
        if(im->tTime > st && im->tTime < ed)
        {
            if(im->nStatus==0) money+=im->fMoney;
            if(im->nStatus==1) money-=im->fMoney;
        }
        im=im->next;
    }
    return money;
}

// tool

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
    strftime(strTime,size,"%Y-%m-%d %H:%M",timeinfo);
}

time_t string_to_time(char* strTime)
{
    struct tm timeInfo = {0};
    int year,mon,mday,hour,min;
    sscanf(strTime,"%d-%d-%d %d:%d",&year,&mon,&mday,&hour,&min);
    timeInfo.tm_year = year - 1900;
    timeInfo.tm_mon = mon - 1;
    timeInfo.tm_mday = mday;
    timeInfo.tm_hour = hour;
    timeInfo.tm_min = min;
    return mktime(&timeInfo);
}

time_t getTime(int year,int mon,int mday)
{
    struct tm timeInfo = {0};
    timeInfo.tm_year = year - 1900;
    timeInfo.tm_mon = mon - 1;
    timeInfo.tm_mday = mday;
    return mktime(&timeInfo);
}

void initSystem(Cards* c,Billings* b,Charges* m)
{
    int cNum = initCard(c);
    int bNum = initBill(b);
    int mNum = initCharge(m);
    printf("好像连上了，\n获得了%d条卡片数据\n",cNum);
    printf("获得了%d条收费数据\n",bNum);
    printf("获得了%d条充值退费数据\n",mNum);
    system("pause");
}

void save(Cards* c,Billings* b,Charges* m)
{
    int cNum = saveCard(c);
    int bNum = saveBill(b);
    int mNum = saveCharge(m);
    printf("保存了%d条卡片数据\n",cNum);
    printf("保存了%d条收费数据\n",bNum);
    printf("保存了%d条充值退费数据\n",mNum);
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
    int price = 100;
    return deltaTime * price / 3600;
}

Card* getCard(Cards* c,char* id)
{
    Card* p=c->head;
    while(p!=NULL)
    {
        if(strcmp(p->aId,id)==0) return p;
        p=p->next;
    }
    return NULL;
}