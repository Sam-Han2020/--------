#include <stdio.h>
#include "service.h"
#include "tools.h"


void ShowStatistics(Cards *c , Billings *b , Charges *m)
{
    printf("--------------------- 查询统计 -----------------------\n");
    printf("请选择\n");
    printf("1 - 消费记录查询\n");
    printf("2 - 统计总营业额\n");
    printf("3 - 统计月营业额\n");
    int a=0;
    while(a!=1 && a!=2 && a!=3)
    {
        char ch[4];
        scanf("%s",ch);
        a = ch[0]-'0';
        if(a==1 || a==2 || a==3) break;
        printf("请重新输入！\n");
    }
    if(a==1)
    {
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
            int year,mon,date;
            printf("请输入开始日期(年 月 日 用空格分隔):");
            scanf("%d %d %d",&year,&mon,&date);
            time_t st = getTime(year,mon,date);
            printf("请输入结束日期(年 月 日 用空格分隔):");
            scanf("%d %d %d",&year,&mon,&date);
            time_t ed = getTime(year,mon,date);
            Billings nb;
            int k = calcu_bills(b,&nb,id,st,ed);
            if(k==0)
            {
                printf("没有找到该卡的消费记录!\n");
                system("pause");
                return;
            }
            else
            {
                Billing * nib = nb.head;
                while(nib!=NULL)
                {
                    char time1[40],time2[40];
                    time_to_string(nib->tStart,time1,sizeof(time1)/sizeof(char));
                    time_to_string(nib->tEnd,time2,sizeof(time2)/sizeof(char));
                    printf("卡号\t消费\t上机时间\t\t下机时间\n");
                    printf("%s\t%.1lf\t%s\t%s\n",nib->aCardName,nib->fAmount,time1,time2);
                    nib=nib->next1;
                }
                nib = b->head;
                while(nib!=NULL)
                {
                    nib->next1 = NULL;
                    nib = nib->next;
                }
            }
        }
        else
        {
            printf("密码错误!\n");
        }    
    }
    else if(a==2)
    {
        int year,mon,date;
        printf("请输入开始日期(年 月 日 用空格分隔):");
        scanf("%d %d %d",&year,&mon,&date);
        time_t st = getTime(year,mon,date);
        printf("请输入结束日期(年 月 日 用空格分隔):");
        scanf("%d %d %d",&year,&mon,&date);
        time_t ed = getTime(year,mon,date);
        double money = calcu_Money(m,st,ed);
        printf("该段时间内的营业额是: %.1f元\n",money);
    }
    else if(a==3)
    {
        int year,mon=1,date=1;
        printf("请输入年份:");
        scanf("%d",&year);
        for(int i=0;i<12;++i)
        {
            time_t st = getTime(year,mon+i,date);
            time_t ed = getTime(year,mon+i+1,date);
            double money = calcu_Money(m,st,ed);
            printf("%d月的营业额是: %.1f元\n",i+1,money);
        }
    }
    system("pause");
}

void Exit(Cards *c,Billings *b,Charges *m)
{
    printf("正在保存数据ing。。。\n");
    save(c,b,m);
    printf("感谢你使用计费管理系统\n");
    system("pause");
}

void showDefault()
{
    printf("输入有误，请重新输入\n");
    system("pause");
}
