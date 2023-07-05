#ifndef __MANAGE_H__
#define __MANAGE_H__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "display.h"
#include "manage.h"



//��ȡ�ļ���������ѧ������
int file_lineNum() {
	FILE* accountFile = fopen(filePath, "r");
	fseek(accountFile, 0, SEEK_SET);
	char sep = fgetc(accountFile);
	int lineNum = sep == EOF ? 0 : 1;//����һ�о�ΪEOF��˵������Ϊ0������һ�в�ΪEOF��������1��
	while (sep != EOF)
	{
		if (sep == '\n')
		{
			lineNum++;
		}
		sep = fgetc(accountFile);
	}
	fclose(accountFile);
	return lineNum;
}

//��ȡ�ض��е��û���Ϣ
char* file_content(int lineNum) {
	FILE* accountFile = fopen(filePath, "r");//�ļ�ָ��
	char line[3 * LEN_LIMIT + 3];//ÿ�е�ԭ����
	fseek(accountFile, 0, SEEK_SET);//����궨λ���ļ���ͷ
	//ֻ��Ŀ������С�ڵ�����������ʱ����ܽ��ж�ȡ
	if (lineNum <= file_lineNum()) {
		for (int i = 0; i < lineNum; i++) {
			fscanf(accountFile, "%s", line);
			fgetc(accountFile);//����
		}
	}
	fclose(accountFile);
	return line;
}

//����д���ļ��ĺ������������أ���һ���Ǹ�д���������޸����ݣ��ڶ���׷�ӣ�������ע��
void file_InContent(user* users, int userNum) {
	FILE* accountFile = fopen(filePath, "w");
	fseek(accountFile, 0, SEEK_SET);
	for (int i = 0; i < userNum; i++) {
		fputs(users[i].getContent(), accountFile);
		if (i != userNum - 1) { fprintf(accountFile, "\n"); }
	}
	fclose(accountFile);
}
void file_InContent(user& user) {
	FILE* accountFile = fopen(filePath, "a");
	fseek(accountFile, 0, SEEK_END);
	fputs("\n", accountFile);
	fputs(user.getContent(), accountFile);
	fclose(accountFile);
}

//�жϵ�¼�Ƿ�ɹ������˺������Ƿ��ܹ��鵽
int checkLogin(char* account, char* password, user* allUser) {
	for (int i = 0; i < file_lineNum(); i++) {
		if (!strcmp(allUser[i].account, account) && !strcmp(allUser[i].password, password)) {
			return i;
		}
	}
	return -1;
}

//ɾ��allUser�е�thisUser
void removeUser(user* allUser, int userNum,user* thisUser) {
	for (int i = 0; i < userNum; i++) {
		if (&allUser[i] == thisUser) {
			for (int j = i; j < userNum-1; j++) {
				strcpy(allUser[j].account, allUser[j + 1].account);
				strcpy(allUser[j].userName, allUser[j + 1].userName);
				strcpy(allUser[j].password, allUser[j + 1].password);
			}
			allUser = (user*)realloc(allUser, sizeof(user) * (userNum - 1));
			break;
		}
	}
}
#endif