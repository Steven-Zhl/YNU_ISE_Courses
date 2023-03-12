#ifndef __QUES3_H__
#define __QUES3_H__
#include <stdio.h>
#include <stdlib.h>

#define ElemType int

ElemType array[8] = { 2,5,6,7,8,9,3,12 };//Ϊ�˱��ڲ��ԣ�ֱ�Ӷ����˸���̬����

void ques3_demo() {//ʵ�ֲ�������������к����
	int leftEdge = 0, rightEdge = 0;
	int maxLength = 0, maxLeft = 0, maxRight;

	printf("ԭ����Ϊ��");
	for (int i = 0; i < 8; i++) {
		printf("%d ", array[i]);
	}
	printf("\n");
	for (rightEdge = 0; rightEdge < sizeof(array) / sizeof(ElemType); rightEdge++) {
		if (array[rightEdge] >= array[rightEdge + 1]) {
			if (rightEdge - leftEdge + 1 > maxLength) {
				maxLength = rightEdge - leftEdge + 1;
				maxLeft = leftEdge;
				maxRight = rightEdge;
			}
			leftEdge = rightEdge + 1;
		}
	}
	printf("����������ִ�Ϊ��\n");
	for (int i = maxLeft; i <= maxRight; i++) {
		printf("%d ", array[i]);
	}
}
#endif