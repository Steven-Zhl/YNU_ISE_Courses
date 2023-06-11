#ifndef __QUES4_H__
#define __QUES4_H__
#include <stdio.h>
#include <stdlib.h>
#define ElemType int

struct node {
	ElemType val = 0;
	node* next = NULL;
};

struct list {
	int len = 0;
	node* head = NULL, * tail = NULL;

	void InsertNode(ElemType val) {
		node* newNode = (node*)malloc(sizeof(node)); newNode->val = val; newNode->next = NULL;
		if (len == 0) {//����Ϊ0
			head = newNode;
			tail = newNode;
		}
		else {//���Ȳ�Ϊ0
			if (val < head->val) {
				newNode->next = head;
				head = newNode;
			}
			else if (val > tail->val) {
				tail->next = newNode;
				tail = newNode;
			}
			else {
				for (node* p = head; p != NULL; p = p->next) {
					if ((val > p->val && val < p->next->val) || val == p->val) {
						newNode->next = p->next;
						p->next = newNode;
						break;
					}
				}
			}
		}
		len++;
	}

	void ShowList() {
		node* p = head;
		printf("��ǰ����Ϊ��");
		while (p != NULL) {
			printf("%d", p->val);
			if (p->next != NULL) printf(" -> ");
			p = p->next;
		}
		printf("\n");
	}
};

void ques4_demo() {//�����������ҡ��������Ԫ��
	list l1, l2;
	l1.InsertNode(4);
	l1.InsertNode(7);
	l1.InsertNode(1);
	l1.InsertNode(5);
	l1.ShowList();

	l2.InsertNode(5);
	l2.InsertNode(7);
	l2.InsertNode(2);
	l2.ShowList();

	int len = 0;
	ElemType* res = (ElemType*)malloc(len * sizeof(ElemType));

	for (node* i = l1.head; i != NULL; i = i->next) {
		for (node* j = l2.head; j != NULL; j = j->next) {
			if (i->val == j->val) {//�����ظ���
				len++;
				res = (ElemType*)realloc(res, len * sizeof(ElemType));
				res[len - 1] = i->val;
			}
		}
	}
	printf("�������о����ڵ�Ԫ�أ�");
	for (int i = 0; i < len; i++) {
		printf("%d ", res[i]);
	}
}
#endif