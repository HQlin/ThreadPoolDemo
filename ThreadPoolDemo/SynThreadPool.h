#pragma once
/*** 多任务单线程同步 ***/
//同一时间只有一个任务执行,后添加的任务需等待上个任务执行完成

#include "stdafx.h"
#include <vector>
using namespace std;


//工作函数-----分配给线程对象的任务
typedef UINT(*TJobFun)(WPARAM wParam, LPARAM lParam);

//回调函数-----工作函数完成后的回调函数
typedef VOID(*TJobCallback)(UINT result);

//线程类，每个对象是一个线程
class CSynThread
{
public:
	CSynThread();
	~CSynThread();
	BOOL IsWorking();   //是否有任务正在运行
	BOOL SetWorking();  //设置有任务正在运行
	VOID DoJob(TJobFun fun, WPARAM wp, LPARAM lp, TJobCallback cb);    //执行一个工作函数
	
	//任务完成事件
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
	HANDLE _EventWork;			//任务完成事件
	BOOL bIsWorking;			//任务状态
	TJobFun jobFun;             //工作函数
	TJobCallback jobCallback;   //回调函数
	WPARAM wParam;              //参数1
	LPARAM lParam;              //参数2
	HANDLE hThread;             //线程句柄
	VOID jobDone();             //任务已完成
	static DWORD WINAPI ThreadProc(LPARAM lParam);  //真正的线程函数
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

