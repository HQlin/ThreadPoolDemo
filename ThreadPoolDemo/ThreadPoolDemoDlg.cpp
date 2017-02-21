
// ThreadPoolDemoDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ThreadPoolDemo.h"
#include "ThreadPoolDemoDlg.h"
#include "afxdialogex.h"
#include "TThreadPool.h"
#include "SynThreadPool.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

unsigned int CalJob(WPARAM wParam, LPARAM lParam);//�߳�����

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CThreadPoolDemoDlg �Ի���




CThreadPoolDemoDlg::CThreadPoolDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CThreadPoolDemoDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CThreadPoolDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CThreadPoolDemoDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_ASYN, &CThreadPoolDemoDlg::OnBnClickedBtnAsyn)
	ON_BN_CLICKED(IDC_BTN_SYN, &CThreadPoolDemoDlg::OnBnClickedBtnSyn)
END_MESSAGE_MAP()


// CThreadPoolDemoDlg ��Ϣ�������

BOOL CThreadPoolDemoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CThreadPoolDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CThreadPoolDemoDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CThreadPoolDemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CThreadPoolDemoDlg::OnBnClickedBtnAsyn()
{
	//��������߳��첽
	CTThreadPool* asyn_ThreadPool = new CTThreadPool(1);
	asyn_ThreadPool->PushJob((TJobFun)CalJob, 2000, NULL, NULL);
	asyn_ThreadPool->PushJob((TJobFun)CalJob, 3000, NULL, NULL);
	asyn_ThreadPool->PushJob((TJobFun)CalJob, 1000, NULL, NULL);
}


void CThreadPoolDemoDlg::OnBnClickedBtnSyn()
{
	//�������߳�ͬ��
	CSynThreadPool* syn_ThreadPool = new CSynThreadPool();
	syn_ThreadPool->PushJob((TJobFun)CalJob, 2000, NULL, NULL);
	syn_ThreadPool->PushJob((TJobFun)CalJob, 3000, NULL, NULL);
	syn_ThreadPool->PushJob((TJobFun)CalJob, 1000, NULL, NULL);
}

//�߳�����
unsigned int CalJob(WPARAM wParam, LPARAM lParam)
{
	Sleep(wParam);
	CString str;
	str.Format(L"Sleep : %d" ,wParam);
	AfxMessageBox(str);
	return 0;
}
