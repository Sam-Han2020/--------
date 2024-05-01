#define _CRT_SECURE_NO_WARNINGS //消除vs开发环境中使用scanf（）函数引起的
#include <stdio.h>
#include <string.h>
#include<time.h>
#include<stdlib.h>
#include "model.h"
#include "service.h"
#include"menu.h"
void outputMenu();//函数声明
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
	printf("计费管理系统");
	printf("\n");
	Card* card=NULL;
	
	do {
		//输出菜单
		outputMenu();
		scanf("%d", &nSelection);
		//清除输入流缓存
		fflush(stdin);
		//输出选择的菜单编号
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
			printf("上机\n");
			break;
		}
		case 4: {
			printf("下机\n");
			break;
		}
		case 5: {
			printf("充值\n");
			break;
		}
		case 6: {
			printf("退费\n");
			break;
		}
		case 7: {
			printf("查询统计\n");
			break;
		}
		case 8: {
			printf("注销卡\n");
			break;
		}
		case 0: {
			//exitApp();
			break;
		}
		default: {
			printf("输入的菜单序号有错误！\n");
			break;
		}
		}
	}while (nSelection !=0);
	return 0;
}


