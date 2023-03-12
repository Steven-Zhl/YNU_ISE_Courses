#include <stdio.h>
#include "stack.h" //ջ
#include "queue.h" //����
#include "matchBrackets.h" //ƥ������
#include "simulatedStack.h" //ģ����ջ��ջ
void demo1() {
	SqStack S;
	S.InitStack();//������ջ
	S.ShowStack();//չʾ
	S.Push('a');//������ջ
	S.Push('b');
	S.Push('c');
	S.ShowStack();//չʾ
	char Sa, Sb, Sc;
	S.Pop(Sa); S.Pop(Sb); S.Pop(Sc);
	printf("%c,%c,%c\n",Sa,Sb,Sc);//���γ�ջ
	S.ShowStack();//չʾ
}
void demo2() {
	LinkQueue Q;
	Q.InitQueue();//�����ն�
	Q.ShowQueue();//չʾ
	Q.EnQueue('a');//������ջ
	Q.EnQueue('b');
	Q.EnQueue('c');
	Q.ShowQueue();//չʾ
	char Qa, Qb, Qc;
	Q.DeQueue(Qa); Q.DeQueue(Qb); Q.DeQueue(Qc);
	printf("%c,%c,%c\n", Qa, Qb, Qc);//���γ�ջ
	Q.ShowQueue();//չʾ
}
void demo3(char a[]) {
	//char a[9] = "(ab)[{}]";
	int res=matchStr(a);
	if (res == OK)
		printf("OK");
	else
		printf("ERROR");
}
void demo4() {
	circleQueue Q;
	Q.InitQueue();
	Q.ShowQueue();
	Q.EnQueue('a');
	Q.EnQueue('b');
	Q.EnQueue('c');
	Q.ShowQueue();
	char Q1, Q2, Q3;
	Q.DeQue(Q1); Q.DeQue(Q2); Q.DeQue(Q3);
	printf("%c,%c,%c\n", Q1, Q2, Q3);//���γ�ջ
	Q.ShowQueue();//չʾ
}
void demo5(char a[]) {
	//char a[9] = "SSXXSXSX";
	int res=simulatedStack(a);
	if (res == OK)
		printf("OK");
	else
		printf("ERROR");
}
int main() {
	char a[9] = "SSSXXXXS";
	demo5(a);
}