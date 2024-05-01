#include <stdio.h>
#include "service.h"
#include "tools.h"


void ShowStatistics(Cards *c , Billings *b , Charges *m)
{
    printf("--------------------- ��ѯͳ�� -----------------------\n");
    printf("��ѡ��\n");
    printf("1 - ���Ѽ�¼��ѯ\n");
    printf("2 - ͳ����Ӫҵ��\n");
    printf("3 - ͳ����Ӫҵ��\n");
    int a=0;
    while(a!=1 && a!=2 && a!=3)
    {
        char ch[4];
        scanf("%s",ch);
        a = ch[0]-'0';
        if(a==1 || a==2 || a==3) break;
        printf("���������룡\n");
    }
    if(a==1)
    {
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
            int year,mon,date;
            printf("�����뿪ʼ����(�� �� �� �ÿո�ָ�):");
            scanf("%d %d %d",&year,&mon,&date);
            time_t st = getTime(year,mon,date);
            printf("�������������(�� �� �� �ÿո�ָ�):");
            scanf("%d %d %d",&year,&mon,&date);
            time_t ed = getTime(year,mon,date);
            Billings nb;
            int k = calcu_bills(b,&nb,id,st,ed);
            if(k==0)
            {
                printf("û���ҵ��ÿ������Ѽ�¼!\n");
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
                    printf("����\t����\t�ϻ�ʱ��\t\t�»�ʱ��\n");
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
            printf("�������!\n");
        }    
    }
    else if(a==2)
    {
        int year,mon,date;
        printf("�����뿪ʼ����(�� �� �� �ÿո�ָ�):");
        scanf("%d %d %d",&year,&mon,&date);
        time_t st = getTime(year,mon,date);
        printf("�������������(�� �� �� �ÿո�ָ�):");
        scanf("%d %d %d",&year,&mon,&date);
        time_t ed = getTime(year,mon,date);
        double money = calcu_Money(m,st,ed);
        printf("�ö�ʱ���ڵ�Ӫҵ����: %.1fԪ\n",money);
    }
    else if(a==3)
    {
        int year,mon=1,date=1;
        printf("���������:");
        scanf("%d",&year);
        for(int i=0;i<12;++i)
        {
            time_t st = getTime(year,mon+i,date);
            time_t ed = getTime(year,mon+i+1,date);
            double money = calcu_Money(m,st,ed);
            printf("%d�µ�Ӫҵ����: %.1fԪ\n",i+1,money);
        }
    }
    system("pause");
}

void Exit(Cards *c,Billings *b,Charges *m)
{
    printf("���ڱ�������ing������\n");
    save(c,b,m);
    printf("��л��ʹ�üƷѹ���ϵͳ\n");
    system("pause");
}

void showDefault()
{
    printf("������������������\n");
    system("pause");
}
