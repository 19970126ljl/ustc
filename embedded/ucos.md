# ucos note

ISR(Interrupt Service Routine)

典型任务是一个无限循环
```
void mytask(void *pdata)
{
   for (;;) {
   do something;
   waiting;
   do something;
   }
}
```

*task status:*

waiting  dormant(被删除后) ready running 

一个函数具有*可重入性*：   
1.只改变局部变量  
2.进入函数关中断，退出函数开中断  
3.用信号量禁止函数在使用时再次被调用  

解决*优先级反转*：
优先级继承

使共享资源满足*互斥*：  
1.关中断  
2.使用 TAS(测试并置位) 指令  
3.禁止任务切换
4.利用信号量


TCB任务控制块保存任务属性，任务的栈用来保存任务的工作环境。

所有的TCB分为两条链表，空闲链表和使用链表

OSEventTaskWait  使一个任务进入等待态：  
1.把TCB的事件指针指向该事件块  
2.改变就绪表的位  
3.改变等待任务表的位


OSEventTaskRdy  使一个任务进入就绪态  
1.通过等待任务表找到优先级最高的任务，并改变等待任务表 
2.将TCB的Dly置0，事件指针指向NULL
3.改变TCB的状态为就绪态并改变就绪表的位

OSInit 功能  
1.完成一般变量的初始化  
2.就绪表的初始化  
3.空闲任务链表的初始化  
4.空闲事件链表的初始化  
5.相关功能参数的初始化  
6.创建OSTaskIdle  
7.创建OSInitTaskStat

OSStart 功能  
获得一个最高优先级的就绪任务
启动这个任务

OS_TASK_SW()  
1.将寄存器入栈  
2.把sp存到TCB  
3.拿到最高优先级的TCB的sp  
4.恢复所有寄存器


用户中断服务子程序：
1.保存所有的寄存器  
2.调用OSIntEnter() (OSIntNesting ++)  
3.如果没有中断嵌套，保存TCB的sp  
4.清中断源  
5.执行中断服务程序  
6.调用OSIntExit  
7.恢复所有寄存器  

OSStartHighRdy()    
检查是否在OSStart之后调用  
把当前TCB地址设为最高优先级地址  
恢复所有寄存器(arm:spsr cpsr r0-15)  


OSTaskCreate()  
检查prio是否合法(大小范围，是否相同优先级)  
把TCBPriTbl相应为置1  
初始化栈  
初始化TCB  
开始调度  

SIntCtxSw()  
关中断IRQ与FRQ  
将处理器模式改为SVC模式  
将中断栈上保存的寄存器保存到SVC的栈上  
开中断  
找到当前优先级最高的任务，设为当前任务并恢复上下文

