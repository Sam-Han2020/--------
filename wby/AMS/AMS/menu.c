#define _CRT_SECURE_NO_WARNINGS //����vs����������ʹ��scanf�������������
#include <stdio.h>
#include<time.h>
#include<stdlib.h>
#include"model.h"
#include "card_service.h"
#include"tool.h"
#include"menu.h"
void outputMenu(void) {
	//���ϵͳ�˵�
	printf("----------�˵�----------\n");
	printf("1.��ӿ�\n");
	printf("2.��ѯ��\n");
	printf("3.�ϻ�\n");
	printf("4.�»�\n");
	printf("5.��ֵ\n");
	printf("6.�˷�\n");
	printf("7.��ѯͳ��\n");
	printf("8.ע����\n");
	printf("0.�˳�\n");
	//��ʾѡ��˵����
	printf("��ѡ��˵����ţ�0��8����");
}
void add(Card* card) {
        int i = 0;
        Card* pNew = (Card*)malloc(sizeof(Card));

        printf("\n----------��ӿ�-----------\n");

        printf("�����뿨��(����Ϊ1~18)��");
        char number[18] = { 0 };   // ����Ŀ���
        scanf("%s", number);
        strcpy(pNew->aName, number);
        printf("����������(����Ϊ1~8)��");
        char password[9] = { 0 };    // ���������
        scanf("%s", password);
        strcpy(pNew->aPwd, password);

        printf("�����뿪�����(RMB)��");
        float m;
        scanf("%f", &m);
        pNew->fBalance = m;

        pNew->fTotalUse = pNew->fBalance;    
        pNew->nDel = 0;                     // ɾ����ʶ
        pNew->nStatus = 0;                  // ��״̬
        pNew->nUseCount = 0;                // ʹ�ô���
        pNew->tStart = pNew->tEnd = pNew->tLast = time(NULL);
        printf("\n------��ӵĿ���Ϣ����------\n");
        printf("����\t\t����\t\t״̬\t\t�������\t\n");
        printf("%s\t\t%s\t\t%d\t\t%.1f\t\t\n", pNew->aName, pNew->aPwd,pNew->nStatus, pNew->fBalance);
        printf("\n");
        addCard(*pNew);

}
void query(Card *card) {
        printf("\n----------��ѯ��-----------\n");
        Card* aCard = NULL;
        printf("������Ҫ��ѯ�Ŀ���(����Ϊ1~18)��");
        char number[18] = { 0 };   // ����Ŀ���
        char aTime[20] = {0};
        scanf("%s", number);
        aCard=queryCard(number);
        timeToString(aCard->tLast, aTime);
        printf("����\t\t״̬\t\t���\t\t�ۼ�ʹ�ý��\tʹ�ô���\t�ϴ�ʹ��ʱ��\n");
        printf("%s\t\t%d\t\t%0.2f\t\t%0.2f\t\t%d\t\t%s\n", aCard->aName, aCard->nStatus, aCard->fBalance, aCard->fTotalUse, aCard->nUseCount,aTime);
        system("pause");
}