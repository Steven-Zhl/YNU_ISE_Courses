#ifndef _MATRIX_H_
#define _MATRIX_H_
#include <limits.h>
#include <string.h>
#include<stdlib.h>
#include <queue>
using namespace std;
/*
	�ڽӾ���������������20*20����ʵ�ʲ�һ����ʹ����ô�࣬������ҪΪ���õĲ��ָ�ֵ��
	����ͼ����Ȩͼ�����ڽӾ���ֵΪ0���ɣ�����������Ȩͼ�����ڽӾ���ֵΪ���͵����ֵ��
*/
#define INFINITY INT_MAX//���ֵ
#define MAX_VERTEX_NUM 20//��󶥵����
#define VRType int //������ϵ����int��ʾ
#define VertexType char //��������

//ͼ���ͱ�ǣ�����ͼ��������������ͼ��������
enum GraphKind { DG, DN, UDG, UDN };

//�ߵļ��ϣ�Ϊ�˹���ͼ��������һ����������
struct Arc {
	VertexType startPoint;
	VertexType endPoint;
	VRType weight = 1;
};

//�ڽӾ�������
typedef struct ArcCell {
	VRType adj;//�����ϵ���߻򻡣���ͼ��1\0��ʾ�Ƿ����ڣ���ΪȨֵ
	//InfoType* info;//�߻򻡵������Ϣָ��
}ArcCell, AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];

//ͼ���ͣ�һ��ͼ�������㼯�ϣ��㼯V�����ڽӾ��󣨱߼�E��������������/����������ͼ���ͱ��
struct Mgraph {
	VertexType* vexs = (VertexType*)malloc(MAX_VERTEX_NUM * sizeof(VertexType));//��������
	AdjMatrix arcs;//�ڽӾ���
	int vexnum = 0, arcnum = 0;//ͼ�Ķ������ͱ߻���
	GraphKind kind;//ͼ�����ͱ�־
	bool structState = false;
	bool visited[MAX_VERTEX_NUM] = { false };

	//����ͼ���ڽӾ���
	void structGraphByMatrix(VertexType* vertex, int vertexNum, Arc* arc, int arcNum, GraphKind type) {

		vexnum = vertexNum; arcnum = arcNum;//����
		kind = type;//����
		for (int i = 0; i < MAX_VERTEX_NUM; i++) {
			vexs[i] = i < vexnum ? vertex[i] : 0;
		}
		//�����ڽӾ���
		//1.��ʼ���ڽӾ���
		for (int i = 0; i < MAX_VERTEX_NUM; i++) {
			for (int j = 0; j < MAX_VERTEX_NUM; j++) {
				arcs[i][j].adj = (type == DG || type == UDG) ? 0 : INFINITY;
			}
		}
		//2.���ݱ߼�Ϊ�ڽӾ���ֵ
		for (int i = 0; i < arcnum; i++) {
			int row = findIndex(arc[i].startPoint);//����<vexs[2], vexs[5]>�Ͷ�Ӧarcs[2][5]������Ϊ2������Ϊ5
			int column = findIndex(arc[i].endPoint);
			if (type == UDN || type == UDG) {
				arcs[row][column].adj = type == UDG ? 1 : arc[i].weight;
				arcs[column][row].adj = type == UDG ? 1 : arc[i].weight;
			}
			else {
				arcs[row][column].adj = type == DG ? 1 : arc[i].weight;
			}
		}
		structState = true;//ȷ������ɹ���
	}

	//����ֵ������Ԫ���ھ����е�λ��
	int findIndex(VertexType val) {
		for (int i = 0; i < vexnum; i++) {
			if (vexs[i] == val) {
				return i;
			}
		}
		return -1;
	}

	//չʾ�ڽӾ���
	void showArcs() {
		if (structState) {
			for (int i = 0; i < vexnum; i++) {
				for (int j = 0; j < vexnum; j++) {
					printf("%10d ", arcs[i][j].adj);
				}
				printf("\n");
			}
		}
		else {
			printf("����δ�����ظ�ͼ\n");
		}
	}

	//������ȱ���
	void DFS() {
		memset(visited, false, sizeof(visited));

		for (int i = 0; i < vexnum; i++)
			if (visited[i] == false)
				DFS_Traverse(i);
	}

	//DFS�ĵݹ�
	void DFS_Traverse(int v) {
		printf("%c", vexs[v]);
		visited[v] = true;
		int adj = FindAdjVertex(v);
		while (adj != -1) {
			if (visited[adj] == false)
				DFS_Traverse(adj);

			adj = FindAdjVertex(v);
		}
	}

	//������ȱ���
	void BFS() {
		memset(visited, false, sizeof(visited));

		for (int i = 0; i <= vexnum; i++)
			if (visited[i] == false)
				BFS_Traverse(i);
	}

	//BFS�ĵݹ麯��
	void BFS_Traverse(int v) {

		queue<int> myqueue;
		int adj, temp;

		printf("%c", vexs[v]);
		visited[v] = true;
		myqueue.push(v);

		while (!myqueue.empty()) {    //���зǿձ�ʾ���ж���δ������    

			temp = myqueue.front();  //��ö���ͷԪ��    
			myqueue.pop();         //ͷԪ�س���    

			adj = FindAdjVertex(temp);
			while (adj != -1)
			{
				if (visited[adj] == false)
				{
					printf("%c", vexs[adj]);
					visited[adj] = true;
					myqueue.push(adj);   //����    
				}
				adj = FindAdjVertex(temp);
			}
		}
	}

	//���Ҹõ���ڽӵ�
	int FindAdjVertex(int x) {
		if (kind == UDG) {
			for (int i = 0; i <= vexnum; i++)
				if (arcs[x][i].adj == 1 && visited[i] == false)
					return i;
		}
		return -1;//��ʾ�������ڽӵ�
	}

	//�ж��ܷ���ɫ�������Ͼ�������������ȱ��������ձ������������ǰ����ڽӵ�������ɫ���ڱ���������һ�������ڽӵ���ɫ�͵�ǰ��ɫ��ͬ����������жϲ��У�
	bool IfCouldAddColor() {
		int color[MAX_VERTEX_NUM];//ÿ���������ɫ��ǣ�0��Ϊ��ɫ1��1��Ϊ��ɫ2��-1��Ϊδ��ɫ״̬
		memset(visited, false, sizeof(visited));
		memset(color, -1, sizeof(color));//��¼��ɫ��ͬʱҲ��visited���������
		int satisfy = 1;
		for (int i = 0; i < vexnum; i++)
			if (color[i] == -1)
				addColor(i, color, 0);

		memset(visited, false, sizeof(visited));
		for (int i = 0; i < vexnum; i++)
			if (visited[i] == false)
				satisfy *= checkColor(i, color);

		return satisfy;
	}

	//�ݹ麯��:�ݹ����ɫ
	void addColor(int index, int* arr, int color) {

		arr[index] = color;//����ǰ����ɫ
		visited[index] = true;
		int adj = FindAdjVertex(index);//��ȡ����ǰ����ڽӵ�
		while (adj != -1) {//��������ڽӵ�
			if (visited[adj] == false)//����ڽӵ�͵�ǰ�����ɫ��ͬ��������ݹ�
				addColor(adj, arr, abs(1 - color));//�ڽӵ㻻����ɫ
			adj = FindAdjVertex(index);
		}
	}

	//�����ɫ
	bool checkColor(int index, int* colorArr) {
		queue<int> adjVertex;
		for (int i = 0; i < vexnum; i++) {
			if (arcs[index][i].adj == 1) {
				if (colorArr[index] == colorArr[i] && index != i)
					return false;
			}
		}
		return true;
	}

	//Ѱ·
	bool findArcs(int startVertex, int endVertex) {
		memset(visited, false, sizeof(visited));

		DFS_Traverse(startVertex);
		return (visited[endVertex] == true);
	}

	int Prime(int v)///��С�����������v
	{
		memset(visited, false, sizeof(visited));
		int d[MAX_VERTEX_NUM];//��¼�ӵ�ǰ����������СȨֵ
		int sum = 0;//��С·����
		for (int i = 0; i < vexnum; i++)
			d[i] = arcs[v][i].adj;
		d[v] = 0;
		visited[v] = true;//��Ǳ�����

		for (int i = 1; i < vexnum; i++)///һ��n���㣬Ҫ��n-1����
		{
			int minn = INFINITY, k=v;//minn����СȨ�ߣ�k�����Ӧ��index
			for (int j = 0; j < vexnum; j++)///������u��U,w��V-U�ı�(u,w)��E���ҵ�һ��Ȩֵ��С�ı�
			{
				if (minn > d[j] && visited[j] == false)
				{
					k = j;
					minn = d[j];
				}
			}
			visited[k] = true;///���˵������С��������
			sum += d[k];
			for (int j = 0; j < vexnum; j++)//���²�����С�������ĵ�ı�Ȩֵ���Ա��ҵ���һ��Ȩֵ��С�ı�
			{
				if (visited[j] == false && d[j] > arcs[k][j].adj)
					d[j] = arcs[k][j].adj;
			}
		}
		return sum;///�������ɵ���С��������Ȩֵ��
	}

};
#endif