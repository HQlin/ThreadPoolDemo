#pragma once
/*** 多任务多线程异步 ***/
//同一时间可多任务执行，若任务超过线程数，则自动新建线程，额外添加的线程执行完成会自动结束

#include "stdafx.h"
#include <vector>
using namespace std;

//工作函数-----分配给线程对象的任务
typedef UINT(*TJobFun)(WPARAM wParam, LPARAM lParam);

//回调函数-----工作函数完成后的回调函数
typedef VOID(*TJobCallback)(UINT result);

//线程类，每个对象是一个线程
class CTThread
{
public:
	CTThread(int type);
	~CTThread();
	BOOL IsWorking();   //是否有任务正在运行
	BOOL SetWorking();  //设置有任务正在运行
	VOID DoJob(TJobFun fun, WPARAM wp, LPARAM lp, TJobCallback cb);    //执行一个工作函数

private:
	int  m_type;				//1为额外添加线程
	BOOL bIsWorking;			//任务状态
	TJobFun jobFun;             //工作函数
	TJobCallback jobCallback;   //回调函数
	WPARAM wParam;              //参数1
	LPARAM lParam;              //参数2
	HANDLE hThread;             //线程句柄
	VOID jobDone();             //任务已完成
	static DWORD WINAPI ThreadProc(LPARAM lParam);  //真正的线程函数
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