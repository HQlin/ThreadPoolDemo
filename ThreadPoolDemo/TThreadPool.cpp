#include "stdafx.h"
#include "TThreadPool.h"

//*************线程池类******************//
CTThreadPool::CTThreadPool(int size)
{
	threadVector.clear();
	for (int i = 0; i < size; i++)
	{
		CTThread *thread = new CTThread(0);
		threadVector.push_back(thread);
	}
}


CTThreadPool::~CTThreadPool()
{
	vector<CTThread *>::iterator it = threadVector.begin();
	for ( ; it != threadVector.end(); )
	{
		CTThread *thread = *it++;
		delete thread;
	}
}

BOOL CTThreadPool::PushJob(TJobFun jobFun, WPARAM wParam, LPARAM lParam, TJobCallback callback)
{
	/*** 多任务多线程异步（开始） ***/
	vector<CTThread *>::iterator it = threadVector.begin();
	for (; it != threadVector.end(); it++)
	{
		CTThread *thread = *it;
		if (!thread->IsWorking())
		{
			thread->SetWorking();
			thread->DoJob(jobFun, wParam, lParam, callback);
			return TRUE;
		}
	}
	CTThread *thread = new CTThread(1);
	thread->SetWorking();
	threadVector.push_back(thread);
	thread->DoJob(jobFun, wParam, lParam, callback);
	/*** 多任务多线程异步（结束） ***/
	/*** 多任务单线程同步（开始） ***/
	//while (true)
	//{
	//	vector<CTThread *>::iterator it = threadVector.begin();
	//	CTThread *thread = *it;
	//	if (!thread->IsWorking())
	//	{
	//		thread->SetWorking();
	//		thread->DoJob(jobFun, wParam, lParam, callback);
	//		return TRUE;
	//	}
	//	Sleep(10);
	//}
	/*** 多任务单线程同步（结束） ***/
	return TRUE;
}

int CTThreadPool::GetPoolSeze()
{
	return threadVector.size();
}

//*************线程类******************//
CTThread::CTThread(int type)
	: bIsWorking(FALSE)
	, jobFun(NULL)
	, jobCallback(NULL)
	, wParam(0)
	, lParam(0)

{
	m_type = type;
	hThread = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)ThreadProc, this, 0, 0);
}


CTThread::~CTThread()
{
	if (hThread != INVALID_HANDLE_VALUE)
	{
		jobFun = (TJobFun)INVALID_HANDLE_VALUE;
		jobCallback = (TJobCallback)INVALID_HANDLE_VALUE;
	}
	ResumeThread(hThread);
	WaitForSingleObject(hThread, INFINITE);
	CloseHandle(hThread);
}

BOOL CTThread::IsWorking()
{
	return bIsWorking;
}

BOOL CTThread::SetWorking()
{
	bIsWorking = TRUE;
	return 0;
}


VOID CTThread::DoJob(TJobFun fun, WPARAM wp, LPARAM lp, TJobCallback cb)
{
	jobFun = fun;
	wParam = wp;
	lParam = lp;
	jobCallback = cb;
	ResumeThread(hThread);
	return VOID();
}

VOID CTThread::jobDone()
{
	bIsWorking = FALSE;
	SuspendThread(hThread);
	return VOID();
}

DWORD CTThread::ThreadProc(LPARAM lParam)
{
	CTThread* pThis = (CTThread*)lParam;
	while (true)
	{
		if (pThis->jobFun == INVALID_HANDLE_VALUE || pThis->jobCallback == INVALID_HANDLE_VALUE)
		{
			break;
		}
		if (pThis->jobFun == NULL && pThis->jobCallback == NULL)
		{
			pThis->jobDone();
			continue;
		}
		UINT ret = pThis->jobFun(pThis->wParam, pThis->lParam);
		if (pThis->jobCallback)
		{
			pThis->jobCallback(ret);
		}
		//额外添加线程执行完任务则结束线程
		if(1 == pThis->m_type)
			break;
		pThis->jobDone();
	}
	return 0;
}