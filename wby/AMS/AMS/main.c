#define _CRT_SECURE_NO_WARNINGS //����vs����������ʹ��scanf�������������
#include <stdio.h>
#include <string.h>
#include<time.h>
#include<stdlib.h>
#include "model.h"
#include "service.h"
#include"menu.h"
void outputMenu();//��������
void add();
void query();
void exitApp();
void logon();
void settle();
void annul();
void addMoney();
void refundMoney();
int main() {
	int nSelection = -1;
	printf("�Ʒѹ���ϵͳ");
	printf("\n");
	Card* card=NULL;
	
	do {
		//����˵�
		outputMenu();
		scanf("%d", &nSelection);
		//�������������
		fflush(stdin);
		//���ѡ��Ĳ˵����
		switch (nSelection) {
		case 1: {
			add(card);
			break;
		}
		case 2: {
			query(card);
			break;
		}
		case 3: {
			printf("�ϻ�\n");
			break;
		}
		case 4: {
			printf("�»�\n");
			break;
		}
		case 5: {
			printf("��ֵ\n");
			break;
		}
		case 6: {
			printf("�˷�\n");
			break;
		}
		case 7: {
			printf("��ѯͳ��\n");
			break;
		}
		case 8: {
			printf("ע����\n");
			break;
		}
		case 0: {
			//exitApp();
			break;
		}
		default: {
			printf("����Ĳ˵�����д���\n");
			break;
		}
		}
	}while (nSelection !=0);
	return 0;
}


