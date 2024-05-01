#define _CRT_SECURE_NO_WARNINGS //消除vs开发环境中使用scanf（）函数引起的
#include <stdio.h>
#include <string.h>
#include<time.h>
#include<stdlib.h>
/*#include "model.h"
#include "service.h"
#include "global.h"
#include "tool.h"*/
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
	
	
	do {
		//输出菜单
		outputMenu();
		scanf("%d", &nSelection);
		//清除输入流缓存
		fflush(stdin);
		//输出选择的菜单编号
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
void outputMenu(void) {
	//输出系统菜单
	printf("----------菜单----------\n");
	printf("1.添加卡\n");
	printf("2.查询卡\n");
	printf("3.上机\n");
	printf("4.下机\n");
	printf("5.充值\n");
	printf("6.退费\n");
	printf("7.查询统计\n");
	printf("8.注销卡\n");
	printf("0.退出\n");
	//提示选择菜单编号
	printf("请选择菜单项编号（0·8）：");
}
void add() {
	printf("----------添加卡----------\n");
	printf("请输入卡号<长度为1·18>：\n");
	char name[50];
	scanf("%s", name);
			while (strlen(name)>18 ) {
				if (strlen(name) > 18) {
					printf("卡号大于18位，请重新输入：\n");
					scanf("%s", name);
				}
			}
	char password[50];
	printf("请输入密码<长度为1·8>：\n");
	scanf("%s", password);
	while (strlen(password) > 8|| strlen(password)<1) {
		if (strlen(name) > 18) {
			printf("密码超过8位，请重新输入密码<长度1·8>：\n");
			scanf("%s", password);
		}
	}
	float amount;
	printf("请输入开卡金额<RMB>:\n");
	scanf("%f", &amount);
	printf("添加卡信息成功!\n");

}
void query() {
	printf("----------查询卡----------\n");
	printf("请输入查询的卡号<长度为1·18>：\n");
}