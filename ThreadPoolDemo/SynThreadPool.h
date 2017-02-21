#pragma once
/*** �������߳�ͬ�� ***/
//ͬһʱ��ֻ��һ������ִ��,����ӵ�������ȴ��ϸ�����ִ�����

#include "stdafx.h"
#include <vector>
using namespace std;


//��������-----������̶߳��������
typedef UINT(*TJobFun)(WPARAM wParam, LPARAM lParam);

//�ص�����-----����������ɺ�Ļص�����
typedef VOID(*TJobCallback)(UINT result);

//�߳��࣬ÿ��������һ���߳�
class CSynThread
{
public:
	CSynThread();
	~CSynThread();
	BOOL IsWorking();   //�Ƿ���������������
	BOOL SetWorking();  //������������������
	VOID DoJob(TJobFun fun, WPARAM wp, LPARAM lp, TJobCallback cb);    //ִ��һ����������
	
	//��������¼�
	void SetWorkEvent(){ SetEvent(_EventWork); }
	void ResetWorkEvent(){ ResetEvent(_EventWork); }
	bool WaitWorkEvent(DWORD dwWaitTime){
		if(WaitForSingleObject(_EventWork, dwWaitTime)!= WAIT_OBJECT_0)
		{
			return false;
		}
		return true;
	}
private:
	HANDLE _EventWork;			//��������¼�
	BOOL bIsWorking;			//����״̬
	TJobFun jobFun;             //��������
	TJobCallback jobCallback;   //�ص�����
	WPARAM wParam;              //����1
	LPARAM lParam;              //����2
	HANDLE hThread;             //�߳̾��
	VOID jobDone();             //���������
	static DWORD WINAPI ThreadProc(LPARAM lParam);  //�������̺߳���
};


class CSynThreadPool
{
public:
	CSynThreadPool(void);
	~CSynThreadPool(void);

	BOOL PushJob(TJobFun jobFun, WPARAM wParam = NULL, LPARAM lParam = NULL, TJobCallback callback = NULL);

private:
	CSynThread* thread;
};

