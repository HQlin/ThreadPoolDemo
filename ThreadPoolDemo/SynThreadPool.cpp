#include "StdAfx.h"
#include "SynThreadPool.h"

//*************线程池类******************//
CSynThreadPool::CSynThreadPool()
{
	thread = new CSynThread();
}


CSynThreadPool::~CSynThreadPool()
{
	delete thread;
}

BOOL CSynThreadPool::PushJob(TJobFun jobFun, WPARAM wParam, LPARAM lParam, TJobCallback callback)
{
	/*** 多任务单线程同步（开始） ***/
	while (true)
	{		
		if (!thread->IsWorking())
		{
			thread->SetWorking();
			thread->DoJob(jobFun, wParam, lParam, callback);
			return TRUE;
		}
		thread->ResetWorkEvent();
		thread->WaitWorkEvent(INFINITE);
		Sleep(1);//必须延迟，否则有一定几率出现后续任务无法正常执行
	}
	/*** 多任务单线程同步（结束） ***/
	return TRUE;
}

//*************线程类******************//
CSynThread::CSynThread()
	: bIsWorking(FALSE)
	, jobFun(NULL)
	, jobCallback(NULL)
	, wParam(0)
	, lParam(0)

{
	_EventWork = CreateEventW(NULL, TRUE, FALSE, NULL);
	assert(_EventWork != INVALID_HANDLE_VALUE);
	hThread = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)ThreadProc, this, 0, 0);
}


CSynThread::~CSynThread()
{
	if (hThread != INVALID_HANDLE_VALUE)
	{
		jobFun = (TJobFun)INVALID_HANDLE_VALUE;
		jobCallback = (TJobCallback)INVALID_HANDLE_VALUE;
	}
	ResumeThread(hThread);
	WaitForSingleObject(hThread, INFINITE);
	CloseHandle(hThread);
	CloseHandle(_EventWork);
}

BOOL CSynThread::IsWorking()
{
	return bIsWorking;
}

BOOL CSynThread::SetWorking()
{
	bIsWorking = TRUE;
	return 0;
}


VOID CSynThread::DoJob(TJobFun fun, WPARAM wp, LPARAM lp, TJobCallback cb)
{
	jobFun = fun;
	wParam = wp;
	lParam = lp;
	jobCallback = cb;
	ResumeThread(hThread);
	return VOID();
}

VOID CSynThread::jobDone()
{
	SetWorkEvent();
	bIsWorking = FALSE;
	SuspendThread(hThread);
	return VOID();
}

DWORD CSynThread::ThreadProc(LPARAM lParam)
{
	CSynThread* pThis = (CSynThread*)lParam;
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
		pThis->jobDone();
	}
	return 0;
}
