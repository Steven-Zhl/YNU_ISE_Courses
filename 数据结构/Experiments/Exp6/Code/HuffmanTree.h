#ifndef _HUFFMANTREE_H_
#define _HUFFMANTREE_H_
#include<stdio.h>
#include<stdlib.h> 

struct HuffmanNode {
	int data;  //���нڵ��ֵ
	HuffmanNode* left;
	HuffmanNode* right;
};

HuffmanNode* createTree(int arr[], int length) {//������ֵ�ڵ�����鳤�ȣ�ʵ�ʵ���ֵ������
	HuffmanNode** ptrArr = (HuffmanNode**)malloc(length * sizeof(HuffmanNode*));//��Žڵ�
	HuffmanNode* ptr; HuffmanNode* newRoot = NULL;//ָ�룬�ֱ���Ϊ����ʱ�ı���ָ���ÿ�㴴���ĸ�ָ��

	for (int i = 0; i < length; i++) {  //���ι���ÿһ���ڵ㣬�������������нڵ�
		ptr = (HuffmanNode*)malloc(sizeof(HuffmanNode));
		ptr->data = arr[i];
		ptr->left = ptr->right = NULL;
		ptrArr[i] = ptr;
	}

	for (int i = 1; i < length; i++) {  //���� n-1 ��ѭ��������������  
		//min1Index��ʾɭ���о�����СȨֵ�ĸ������±�,min2indexΪ�ڶ�С���±�
		int min1Index = -1, min2Index;
		for (int j = 0; j < length; j++) {//��ֱ��ȡ��һ�±�͵ڶ��±�
			if (ptrArr[j] != NULL && min1Index == -1) {
				min1Index = j;
				continue;
			}
			if (ptrArr[j] != NULL) {
				min2Index = j;
				break;
			}
		}
		for (int j = min2Index; j < length; j++) {
			if (ptrArr[j] != NULL) {
				if (ptrArr[j]->data < ptrArr[min1Index]->data) {//���θ��£���֤min1Indexʼ��ָ����Сֵ��min2Indexָ���Сֵ
					min2Index = min1Index;
					min1Index = j;
				}
				else if (ptrArr[j]->data < ptrArr[min2Index]->data) {
					min2Index = j;
				}
			}
		}
		//����СȨֵ���ʹ���СȨֵ������һ������,newRootΪ�¸�
		newRoot = (HuffmanNode*)malloc(sizeof(HuffmanNode));
		newRoot->data = ptrArr[min1Index]->data + ptrArr[min2Index]->data;
		newRoot->left = ptrArr[min1Index];
		newRoot->right = ptrArr[min2Index];

		ptrArr[min1Index] = newRoot; //��ָ��������ָ�븳��ptrArrָ��������min1Index
		ptrArr[min2Index] = NULL; //min2Indexλ��Ϊ��
	}
	return newRoot;
}


int calcWeightLength(HuffmanNode*& rootPtr, int len) {
	if (rootPtr == NULL) { //��������0
		return 0;
	}
	else {
		if (rootPtr->left == NULL && rootPtr->right == NULL) { //���ʵ�Ҷ�ӽڵ�
			return rootPtr->data * len;
		}
		else {
			return calcWeightLength(rootPtr->left, len + 1) + calcWeightLength(rootPtr->right, len + 1); //���µݹ����
		}
	}
}

/*
void printHuffmanTreeChildNode(HuffmanTreeNode* node) {
	if (node->left == NULL && node->right == NULL) {
		printf("x=%d�ǹ��������е�Ҷ�ӽڵ�", node->data);
		printf("\n\n");
		return;
	}
	if (node->left != NULL) {
		printf("x=%d�ڹ��������е����ӽڵ���lchild=%d", node->data, node->left->data);
		printf("\n");
	}
	if (node->right != NULL) {
		printf("x=%d�ڹ��������е��Һ��ӽڵ���rchild=%d", node->data, node->right->data);
		printf("\n");
	}
	printf("\n");
}
*/
void InOrderTraverse(HuffmanNode*& rootPtr) {
	if (rootPtr == NULL) {
		return;
	}
	else {
		InOrderTraverse(rootPtr->left);
		printf("%d ", rootPtr->data);
		InOrderTraverse(rootPtr->right);
	}
}

void PreOrderTraverse(HuffmanNode*& rootPtr) {
	if (rootPtr == NULL) {
		return;
	}
	else {
		printf("%d ", rootPtr->data); //���δ�ӡ���������и����ڵ�ĺ��ӽڵ�
		PreOrderTraverse(rootPtr->left);
		PreOrderTraverse(rootPtr->right);
	}
}
#endif