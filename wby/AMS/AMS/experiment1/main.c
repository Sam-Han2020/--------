#define _CRT_SECURE_NO_WARNINGS //����vs����������ʹ��scanf�������������
#include <stdio.h>
#include <string.h>
#include<time.h>
#include<stdlib.h>
/*#include "model.h"
#include "service.h"
#include "global.h"
#include "tool.h"*/
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
	
	
	do {
		//����˵�
		outputMenu();
		scanf("%d", &nSelection);
		//�������������
		fflush(stdin);
		//���ѡ��Ĳ˵����
		switch (nSelection) {
		case 1: {
			add();
			break;
		}
		case 2: {
			query();
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
void add() {
	printf("----------��ӿ�----------\n");
	printf("�����뿨��<����Ϊ1��18>��\n");
	char name[50];
	scanf("%s", name);
			while (strlen(name)>18 ) {
				if (strlen(name) > 18) {
					printf("���Ŵ���18λ�����������룺\n");
					scanf("%s", name);
				}
			}
	char password[50];
	printf("����������<����Ϊ1��8>��\n");
	scanf("%s", password);
	while (strlen(password) > 8|| strlen(password)<1) {
		if (strlen(name) > 18) {
			printf("���볬��8λ����������������<����1��8>��\n");
			scanf("%s", password);
		}
	}
	float amount;
	printf("�����뿪�����<RMB>:\n");
	scanf("%f", &amount);
	printf("��ӿ���Ϣ�ɹ�!\n");

}
void query() {
	printf("----------��ѯ��----------\n");
	printf("�������ѯ�Ŀ���<����Ϊ1��18>��\n");
}