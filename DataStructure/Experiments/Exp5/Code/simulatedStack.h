#ifndef __SIMULATEDSTACK_H__
#define __SIMULATEDSTACK_H__

#include "stack.h"
Status simulatedStack(char* inputStr) {
	SqStack S;
	S.InitStack();
	char* p = inputStr;
	while (*p != '\0') {
		if (*p == 'S') {//��'S'����ȥ
			S.Push(*p);
		}
		else if (*p == 'X') {
			char val; S.Pop(val);
			if (val == ERROR)return ERROR;
		}
		p++;
	}
	if (S.stackSize != 0) return ERROR;//������ƥ������
	return OK;
}
#endif