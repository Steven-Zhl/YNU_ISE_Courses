#ifndef __MATCHBRACKETS_H__
#define __MATCHBRACKETS_H__

#include "stack.h"

Status matchStr(char* inputStr) {
	SqStack S;
	S.InitStack();
	char* p = inputStr;
	while (*p != '\0') {
		if (*p == '(' || *p == '[' || *p == '{') {//����������ȥ
			S.Push(*p);
		}
		else if (*p == ')' || *p == ']' || *p == '}') {//��������ƥ������ţ����ջ�г�һ������ƥ��
			char baseElem; S.Pop(baseElem);
			if (!((baseElem == '(' && *p == ')') || (baseElem == '[' && *p == ']') || (baseElem == '{' && *p == '}')))//���������ƥ�����һ��������򷵻�ERROR
				return ERROR;
		}
		p++;
	}
	if (S.stackSize != 0) return ERROR;//������ƥ������
	return OK;
}

#endif