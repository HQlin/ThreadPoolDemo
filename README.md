ThreadPoolDemo
===

��������߳��첽 �� �������߳�ͬ��
---

* �������
    * C++
* ���ʽ��ͣ�һ��������һ���߳�ִ�У�
    * ��������߳��첽
        * ͬһʱ��ɶ�����ִ�У������񳬹��߳��������Զ��½��̣߳�������ӵ��߳�ִ����ɻ��Զ�����
    * �������߳�ͬ��
        * ͬһʱ��ֻ��һ������ִ��,����ӵ�������ȴ��ϸ�����ִ�����
* ����˵�� 
    * ʹ�ö�������߳��첽
       	* CTThreadPool* asyn_ThreadPool = new CTThreadPool(1);
        * asyn_ThreadPool->PushJob((TJobFun)CalJob, 2000, NULL, NULL);
        * asyn_ThreadPool->PushJob((TJobFun)CalJob, 3000, NULL, NULL);
        * asyn_ThreadPool->PushJob((TJobFun)CalJob, 1000, NULL, NULL);  
    * ʹ�ö������߳�ͬ��
       	* CSynThreadPool* syn_ThreadPool = new CSynThreadPool();
       	* syn_ThreadPool->PushJob((TJobFun)CalJob, 2000, NULL, NULL);
       	* syn_ThreadPool->PushJob((TJobFun)CalJob, 3000, NULL, NULL);
       	* syn_ThreadPool->PushJob((TJobFun)CalJob, 1000, NULL, NULL);
* �������
   *    
   ![](https://github.com/HQlin/ThreadPoolDemo/blob/master/img/interface.png "�������")