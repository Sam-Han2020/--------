#define _CRT_SECURE_NO_WARNINGS //����vs����������ʹ��scanf�������������
#include "model.h"
#include<time.h>
//��time��t����תΪ�ַ����� ��ʽΪ��-��-�� ʱ ����
void timeToString(time_t t, char* pBuf) {
	struct tm* pTimeInfo;
	pTimeInfo = localtime(&t);
	strftime(pBuf, 20, "%Y-%m-%d %H:%M", pTimeInfo);
}