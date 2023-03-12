#ifndef __QUES2_H__
#define __QUES2_H__
#include <stdio.h>
#include <stdlib.h>
#define ParamType double //ϵ������������

struct equationNode {//����ʽÿһ��
	int power = 0;//����
	ParamType param = 0;//ϵ��
	equationNode* next = NULL;
};

struct equation {//����ʽ
	int nodeNum = 0;//����
	equationNode* minPow = NULL, * maxPow = NULL;//ָ����ͽ׵Ľڵ����߽׵Ľڵ�

	void InsertNode(ParamType param, int power) {
		equationNode* newNode = (equationNode*)malloc(sizeof(equationNode)); newNode->param = param; newNode->power = power; newNode->next = NULL;
		if (nodeNum == 0) {//����Ϊ0
			maxPow = newNode;
			minPow = newNode;
		}
		else {//���Ȳ�Ϊ0
			if (power < minPow->power) {//�Ƚ��Ƿ����СֵС
				newNode->next = minPow;
				minPow = newNode;
			}
			else if (power > maxPow->power) {//�Ƚ��Ƿ�����ֵ��
				maxPow->next = newNode;
				maxPow = newNode;
			}
			else {
				for (equationNode* pointer = minPow; pointer != NULL; pointer = pointer->next) {
					if (pointer->power == power) {
						pointer->param += param;
						nodeNum--;//��������nodeNum++��Ӱ�죨��Ϊ����ʵ������ͬ�ݽڵ�ĺϲ���
						break;
					}
					else if (power > pointer->power && power < pointer->next->power) {//����Ѱ�Һ��ʵ�λ��
						newNode->next = pointer->next;
						pointer->next = newNode;
						break;
					}
				}
			}
		}
		nodeNum++;
	}

	void ShowEquation() {
		equationNode* nodePointer = minPow;
		printf("��ǰ����ʽΪ:\n");
		for (int i = 0; i < nodeNum; i++) {
			if (i != 0)	printf(nodePointer->param > 0 ? " + " : " - ");
			printf("%5.2lf", nodePointer->param > 0 ? nodePointer->param : -(nodePointer->param));
			printf(nodePointer->power == 0 ? "" : "x^%d", nodePointer->power);
			nodePointer = nodePointer->next;
		}
		printf("\n");
	}

	void MergeEquation(equation& Ea, equation& Eb, equation& Ec) {
		equationNode* pointer = Ea.minPow;
		while (pointer != NULL) {//��������ʽa�����������
			Ec.InsertNode(pointer->param, pointer->power);
			pointer = pointer->next;
		}
		pointer = Eb.minPow;
		while (pointer != NULL) {//��������ʽb�����������
			Ec.InsertNode(pointer->param, pointer->power);
			pointer = pointer->next;
		}
	}
};
int ques2_demo() {
	equation ea, eb, ec;
	ea.InsertNode(2.13, 4);
	ea.InsertNode(-14.3, 3);
	ea.InsertNode(6.28, 2);
	ea.InsertNode(3.14, 0);
	ea.ShowEquation();

	eb.InsertNode(3.14, 4);
	eb.InsertNode(6.28, 3);
	eb.InsertNode(-14.3, 2);
	eb.InsertNode(2.13, 0);
	eb.ShowEquation();

	ec.MergeEquation(ea, eb, ec);
	ec.ShowEquation();
	return 0;
}
#endif