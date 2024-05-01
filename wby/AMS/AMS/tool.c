#define _CRT_SECURE_NO_WARNINGS //消除vs开发环境中使用scanf（）函数引起的
#include "model.h"
#include<time.h>
//将time—t类型转为字符串， 格式为年-月-日 时 ：分
void timeToString(time_t t, char* pBuf) {
	struct tm* pTimeInfo;
	pTimeInfo = localtime(&t);
	strftime(pBuf, 20, "%Y-%m-%d %H:%M", pTimeInfo);
}