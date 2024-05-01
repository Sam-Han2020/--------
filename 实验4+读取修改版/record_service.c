#include "record_service.h"
#include "tools.h"

void InsertMoney(Cards* c,Charges* m)
{
    printf("----------------------- 充值 -------------------------\n");
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
        if(cd->nStatus == 2)
        {
            printf("该卡已注销，无法进行充值操作！\n");
            system("pause");
            return ;
        }
        float balance=0;
        while(1)
        {
            printf("请输入充值金额<单次充值金额为1-100RMB>:");
            scanf("%f",&balance);
            if(balance<1 || balance>100)
                printf("数据非法，请重新输入!\n");
            else
                break;
        }
        Charge* im = CreateCharge(id,0,balance);
        InsertCharge(m,im);
        time(&(cd->tEnd));
        cd->fBalance+=balance;
        printf("------------------- 充值信息如下 ---------------------\n");
        printf("卡号\t充值金额\t余额\n");
        printf("%s\t%.1lf\t\t%.1lf\n",cd->aId,balance,cd->fBalance);
    }
    else
    {
        printf("密码错误!\n");
    }
    system("pause");
}

void GetMoney(Cards* c,Charges* m)
{
    printf("----------------------- 退费 -------------------------\n");
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
        if(cd->fBalance <= 0)
        {
            printf("你的卡余额不足，无法进行退费操作!\n");
            system("pause");
            return ;
        }
        float balance=0;
        while(1)
        {
            printf("请输入退费金额<单次充值金额为1-100RMB>:");
            scanf("%f",&balance);
            if(balance<1 || balance>100)
                printf("数据非法，请重新输入!\n");
            else 
                break;
        }
        if(cd->fBalance - balance <= 0)
        {
            printf("你的卡余额不足，是否进行全额退费操作?\n");
            printf("是 - 1 ; 否 - 2\n");
            int c=0;
            while(c!=1 && c!=2)
            {
                char ch[4];
                scanf("%s",ch);
                c = ch[0]-'0';
                if(c==1 || c==2) break;
                printf("请重新输入！\n");
            }
            if(c==1) balance = cd->fBalance;
            if(c==2) return ;
        }
        Charge* im = CreateCharge(id,1,balance);
        InsertCharge(m,im);
        time(&(cd->tEnd));
        cd->fBalance-=balance;
        printf("------------------- 退费信息如下 ---------------------\n");
        printf("卡号\t退费金额\t余额\n");
        printf("%s\t%.1lf\t\t%.1lf\n",cd->aId,balance,cd->fBalance);
    }
    else
    {
        printf("密码错误!\n");
    }
    system("pause");
}