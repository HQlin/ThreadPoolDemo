ThreadPoolDemo
===

多任务多线程异步 与 多任务单线程同步
---

* 编程语言
    * C++
* 名词解释（一个任务由一个线程执行）
    * 多任务多线程异步
        * 同一时间可多任务执行，若任务超过线程数，则自动新建线程，额外添加的线程执行完成会自动结束
    * 多任务单线程同步
        * 同一时间只有一个任务执行,后添加的任务需等待上个任务执行完成
* 程序说明 
    * 使用多任务多线程异步
       	* CTThreadPool* asyn_ThreadPool = new CTThreadPool(1);
        * asyn_ThreadPool->PushJob((TJobFun)CalJob, 2000, NULL, NULL);
        * asyn_ThreadPool->PushJob((TJobFun)CalJob, 3000, NULL, NULL);
        * asyn_ThreadPool->PushJob((TJobFun)CalJob, 1000, NULL, NULL);  
    * 使用多任务单线程同步
       	* CSynThreadPool* syn_ThreadPool = new CSynThreadPool();
       	* syn_ThreadPool->PushJob((TJobFun)CalJob, 2000, NULL, NULL);
       	* syn_ThreadPool->PushJob((TJobFun)CalJob, 3000, NULL, NULL);
       	* syn_ThreadPool->PushJob((TJobFun)CalJob, 1000, NULL, NULL);
* 程序界面
   *    
   ![](https://github.com/HQlin/ThreadPoolDemo/blob/master/img/interface.png "程序界面")