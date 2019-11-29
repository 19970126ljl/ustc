# 压测工具源码阅读

入口脚本是CNQUAL.sh

检查是否存在CNRT相关环境变量，如果没有退出

判断输入依赖库个数是否是等于3，否则提示运行./configure.sh

判断是已经被启用

判断输入参数是否合法，

本次工程实践主要是要争对mlu和风扇，因此选择power_test，和stress test，同时输入合法的板卡号以及循环次数,下面以powertest为例

CNQUAL.sh运行后且参数合法，那么会运行power_test目录下的run_test.py

power_test目录下有data_for_ddr,direct_run_onchip,right_result,run_test.py sncode_file 这几个文件

前三个文件将会在run_test.py中被使用

在run_test.py中定义了一个INT信号的处理函数，用于在收到INT信号后结束所有的进程。

在主函数中首先判断输入参数是否合法然后注册信号处理函数

所有测试的数据都被存储在 results/power_test , 有csv和txt两种格式

接下来在确认所有设备都可用后进入循环，然后创建子程序执行前面提到的direct_run_onchip文件


