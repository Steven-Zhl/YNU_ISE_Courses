#ifndef __QUEUE_H__
#define __QUEUE_H__

#include <stdio.h>
#include <stdlib.h>

#define QUEUE_INIT_SIZE 100  //��ʼ����
#define QUEUE_INCREMENT 10 //����
#define QElemType char
#define OK 0
#define ERROR -1
#define Status int//���Ա�ʾ�����Ĳ���״̬

//������
typedef struct QNode {
	QElemType data = 0;//������
	struct QNode* next = NULL;//ָ����
}QNode, * QueuePtr;

struct LinkQueue {
	int queueSize = 0;
	QueuePtr front = NULL;//��ͷָ��
	QueuePtr rear = NULL;//��βָ��

	Status InitQueue() {
		QNode* node = (QNode*)malloc(sizeof(QNode));
		node->data = 0;
		node->next = NULL;
		front = node;
		rear = node;
		return OK;
	}

	Status EnQueue(QElemType e) {
		if (queueSize == 0) {
			rear->data = e;
		}
		else {
			QNode* node = (QNode*)malloc(sizeof(QNode));
			node->data = e;
			node->next = NULL;
			rear->next = node;
			rear = rear->next;
		}
		queueSize++;
		return OK;
	}

	Status DeQueue(QElemType& e) {
		if (queueSize != 0) {
			e = front->data;
			QNode* removeNode = front;
			front = front->next;
			free(removeNode);
			queueSize--;
			return OK;
		}
		else {
			printf("�ӿգ��޷����ӣ�");
			return ERROR;
		}
	}

	Status ShowQueue() {
		if (queueSize == 0)	printf("��ǰ��Ϊ��\n");
		else {
			printf("��ǰջ��Ԫ��Ϊ��");
			for (QNode* ptr = front; ptr != rear; ptr = ptr->next) {
				printf("%c->", ptr->data);
			}
			printf("%c", rear->data);
			printf("(�ɶ�������β)\n");
		}
		return OK;
	}
};

//ѭ������
struct circleQueue {
	int frontIndex;//��Ҫ��¼frontָ���index���Ա��ڽ��Count�ҵ���β
	int lenLimitation = 0;//������������ȣ����е�ʵ������������ֵ����Ҫ����
	QElemType* Q;//���б���
	QElemType* front = NULL;//ͷָ��
	int Count = 0;//������

	Status InitQueue() {
		if (Q = (QElemType*)malloc(QUEUE_INIT_SIZE * sizeof(QElemType))) {
			lenLimitation = QUEUE_INIT_SIZE;
			for (int i = 0; i < QUEUE_INIT_SIZE; i++) {//��ʼ����������
				Q[i] = 45;//45�ǡ�-����ASCii
			}
			frontIndex = 0;
			front = &Q[frontIndex];//����ͷָ��
			return OK;
		}
		else
			return ERROR;
	}

	int EndIndex() {
		if (frontIndex + Count <= lenLimitation) {//����û��ѭ��
			return frontIndex + Count - 1;
		}
		else {//�����Ѿ�ѭ������
			return frontIndex + Count - lenLimitation - 1;
		}
		//��ʵ����return frontIndex + Count <= lenLimitation ? frontIndex + Count - 1 : frontIndex + Count - lenLimitation - 1;
	}

	Status EnQueue(QElemType val) {
		if (Count == 0) {
			Q[frontIndex] = val;
		}
		else if (Count < lenLimitation) {
			Q[EndIndex() == lenLimitation - 1 ? 0 : EndIndex() + 1] = val;
		}
		else {//���Ȳ�����
			Q = (QElemType*)realloc(Q, (QUEUE_INIT_SIZE + QUEUE_INCREMENT) * sizeof(QElemType));
			front = &Q[frontIndex];//���¶�λָ��
			lenLimitation += QUEUE_INCREMENT;//�޸Ķ�����
			EnQueue(val);
		}
		Count++;
		return OK;
	}

	QElemType DeQue(QElemType& e) {
		if (Count != 0) {
			e = Q[frontIndex];
			Q[frontIndex] = 45;//�ع�δ��ʼ��״̬
			frontIndex++;
			Count--;
			return OK;
		}
		else {
			printf("�ӿգ��޷����ӣ�");
			e = ERROR;
			return ERROR;
		}
	}

	Status ShowQueue() {
		if (Count == 0) {
			printf("��ǰ����Ϊ��\n");
			return ERROR;
		}
		else {
			printf("��ǰ����Ԫ��Ϊ��");
			for (int num = 0; num < Count; num++) {
				printf("%c", Q[frontIndex + num < lenLimitation ? frontIndex + num : frontIndex + num - lenLimitation]);
				if (num != Count-1) {
					printf("->");
				}
			}
			printf("(�ɶ�������β��\n");
		}
		return OK;
	}
};
#endif