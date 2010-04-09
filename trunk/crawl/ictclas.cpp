// win_cDemo.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "ICTCLAS30.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void KeyExtract(const char *sInput);
void FingerPrint(const char *sInput);

void FingerPrint(const char *sInput)
{
	//��ʼ���ִ����
	if(!ICTCLAS_Init())
	{
		printf("ICTCLAS INIT FAILED!\n");
		return ;
	}


	//�ͷŷִ������Դ
	ICTCLAS_Exit();
}

void KeyExtract(const char *sInput)
{
	//��ʼ���ִ����
	if(!ICTCLAS_Init())
	{
		printf("ICTCLAS INIT FAILED!\n");
		return ;
	}

    int nCount = ICTCLAS_GetParagraphProcessAWordCount(sInput);
	//�ִʡ���ȡ�ؼ���
	result_t *result =(result_t*)malloc(sizeof(result_t)*nCount);
	ICTCLAS_ParagraphProcessAW(nCount,result);//��ȡ����浽�ͻ����ڴ���

	//ָ����ȡ������ICTCLAS_ParagraphProcessAW����ִ�����ִ��
	unsigned long lFinger = ICTCLAS_FingerPrint();

	char buf[100];
	memset(buf, 0, 100);
	sprintf(buf, "%x", lFinger);
	printf("%s\n", buf);

	//�ؼ�����ȡ������ICTCLAS_ParagraphProcessAW����ִ�����ִ��
	result_t *resultKey = (result_t*)malloc(sizeof(result_t)*nCount);
	int nCountKey;
	ICTCLAS_KeyWord(resultKey, nCountKey);

	for (int i=0; i<nCountKey; i++)
	{
		char buf[100];
		memset(buf, 0, 100);
		int index = resultKey[i].start;
        if( resultKey[i].weight>0)
        {
            memcpy(buf,(void *)(sInput+index), resultKey[i].length);
            printf("%s\t%d\n", buf, resultKey[i].weight);
        }
	}

	free(resultKey);
	free(result);
    
	//�ͷŷִ������Դ
	ICTCLAS_Exit();
}

int main(int argc,char* argv[])
{
    const char *sInput = argv[1];
	//ָ����ȡ
	FingerPrint(sInput);

	//�ؼ�����ȡ
	KeyExtract(sInput);
	return 1;
}
