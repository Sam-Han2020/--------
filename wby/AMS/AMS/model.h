#pragma once
#ifndef model_h
#define model_h
#include <time.h>
typedef struct Card {
	char aName[18];//卡号
	char aPwd[8];//密码
	int nStatus;//0未上机 1正在上机 2已注销 3失效
	time_t tEnd;//卡的截止时间
	time_t tStart;//开卡时间
	float fTotalUse;//累计金额
	time_t tLast;//最后使用时间
	int nUseCount;//使用次数
	float fBalance;//余额
	int nDel;//0-未删除 1-删除
	struct Card* next;
}Card;
//计费信息结构体
typedef struct billing {       //计费信息

    char number[18];    //卡号
    time_t timeStart;      //上机时间
    time_t timeEnd;      //下机时间
    float fAmount;      //消费金额
    int status;      //消费状态 0-未结算 1-已经结算
    int del;      //删除标识 0-未删除 1-删除

    struct billing* next;

}billing;
#endif