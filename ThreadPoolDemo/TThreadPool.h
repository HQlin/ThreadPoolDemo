#pragma once
/*** ��������߳��첽 ***/
//ͬһʱ��ɶ�����ִ�У������񳬹��߳��������Զ��½��̣߳�������ӵ��߳�ִ����ɻ��Զ�����

#include "stdafx.h"
#include <vector>
using namespace std;

//��������-----������̶߳��������
typedef UINT(*TJobFun)(WPARAM wParam, LPARAM lParam);

//�ص�����-----����������ɺ�Ļص�����
typedef VOID(*TJobCallback)(UINT result);

//�߳��࣬ÿ��������һ���߳�
class CTThread
{
public:
	CTThread(int type);
	~CTThread();
	BOOL IsWorking();   //�Ƿ���������������
	BOOL SetWorking();  //������������������
	VOID DoJob(TJobFun fun, WPARAM wp, LPARAM lp, TJobCallback cb);    //ִ��һ����������

private:
	int  m_type;				//1Ϊ��������߳�
	BOOL bIsWorking;			//����״̬
	TJobFun jobFun;             //��������
	TJobCallback jobCallback;   //�ص�����
	WPARAM wParam;              //����1
	LPARAM lParam;              //����2
	HANDLE hThread;             //�߳̾��
	VOID jobDone();             //���������
	static DWORD WINAPI ThreadProc(LPARAM lParam);  //�������̺߳���
};


class CTThreadPool
{
public:
	CTThreadPool(int size = 2);
	~CTThreadPool();
	BOOL PushJob(TJobFun jobFun, WPARAM wParam = NULL, LPARAM lParam = NULL, TJobCallback callback = NULL);
	int GetPoolSeze();

private:
	vector<CTThread *> threadVector;
};