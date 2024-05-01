#pragma once
#ifndef model_h
#define model_h
#include <time.h>
typedef struct Card {
	char aName[18];//����
	char aPwd[8];//����
	int nStatus;//0δ�ϻ� 1�����ϻ� 2��ע�� 3ʧЧ
	time_t tEnd;//���Ľ�ֹʱ��
	time_t tStart;//����ʱ��
	float fTotalUse;//�ۼƽ��
	time_t tLast;//���ʹ��ʱ��
	int nUseCount;//ʹ�ô���
	float fBalance;//���
	int nDel;//0-δɾ�� 1-ɾ��
	struct Card* next;
}Card;
//�Ʒ���Ϣ�ṹ��
typedef struct billing {       //�Ʒ���Ϣ

    char number[18];    //����
    time_t timeStart;      //�ϻ�ʱ��
    time_t timeEnd;      //�»�ʱ��
    float fAmount;      //���ѽ��
    int status;      //����״̬ 0-δ���� 1-�Ѿ�����
    int del;      //ɾ����ʶ 0-δɾ�� 1-ɾ��

    struct billing* next;

}billing;
#endif