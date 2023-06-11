#ifndef __STACK_H__
#define __STACK_H__

#include <stdio.h>
#include <stdlib.h>

#define STACK_INIT_SIZE 100  //��ʼ����
#define STACK_INCREMENT 10 //����
#define SElemType char //��ʼ������Ԫ������
#define OK 0
#define ERROR -1
#define Status int//���Ա�ʾ�����Ĳ���״̬

// ˳��ջ
struct SqStack {
	int stackSize = 0;//�����ڴ洢������
	int lenLimitation = 0;//������������ȣ�ջ��ʵ������������ֵ����Ҫ����
	SElemType* S;//ջ������
	SElemType* base = NULL;//�洢��ַ
	SElemType* top = NULL;//ջ��ָ��

	Status InitStack() {
		if (S = (SElemType*)malloc(STACK_INIT_SIZE * sizeof(SElemType))) {
			lenLimitation = STACK_INIT_SIZE;
			for (int i = 0; i < STACK_INIT_SIZE; i++) {//Ϊ����ջ���г�ʼ��ֵ
				S[i] = 45;//45�ǡ�-����ASCii
			}
			base = &S[0];
			top = &S[0];
			return OK;
		}
		else
			return ERROR;
	}

	Status Push(SElemType val) {
		if (stackSize < lenLimitation) {//�ж�ջû��
			if (stackSize == 0) {//ջ����Ϊ0ʱ��ֱ�������д��룬topָ�벻��Ҫ�ƶ�
				*top = val;
				stackSize++;
			}
			else {//ջ���Ȳ�Ϊ0���Ƚ�topָ����ƣ�Ȼ���ٴ���
				top++;
				*top = val;
				stackSize++;
			}
		}
		else {//ջ��
			S = (SElemType*)realloc(S, (STACK_INIT_SIZE + STACK_INCREMENT) * sizeof(SElemType));
			base = &S[0];//���¶�λbase��topָ��
			top = &S[stackSize - 1];
			lenLimitation += STACK_INCREMENT;//�޸Ķ���������stackSize������
			Push(val);
		}
		return OK;
	}

	SElemType Pop(SElemType& e) {
		if (stackSize != 0) {
			stackSize--;
			e = *top--;
			return OK;
		}
		else {
			printf("ջ�գ��޷���ջ��");
			e = ERROR;
			return ERROR;
		}
	}

	Status ShowStack() {
		if (stackSize == 0)	printf("��ǰջΪ��\n");
		else {
			printf("��ǰջ��Ԫ��Ϊ��");
			for (SElemType* ptr = top; ptr >= base; ptr--) {
				printf("%c", *ptr);
				if (ptr != base) {
					printf("->");
				}
			}
			printf("(��ջ����ջ��)\n");
		}
		return OK;
	}
};
#endif