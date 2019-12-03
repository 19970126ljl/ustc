# 接口使用说明


使用以下接口要包含头文件 **../include/fanOp.h**并链接 **../lib/fanlib.so** **../lib/libcndev.so** 

//初始化

```void initialize();```

//结束释放


```void release();```


//把字符串print_str添加到文件filename末尾

```void output_data(char *filename, char *print_str);```

//停止BMC控制风扇

```void shutdownBMC();```

//设置风扇转速为 speed%100

```void set_speed(int speed);```

//获取库版本信息

```cndevLibVersionInfo_t getLibVersion();```

//获取板卡数量

```int getBoardNum();```

//获取板卡的总体使用率 ， 参数id为板卡号

```int getBoardUtilization(unsigned Id);```

// 获取板卡上的核心数量 ， 参数boardId为板卡号

```int getCoreNum(int boardId);```

//获取核心利用率，返回一个数组，每个元素对应一个核心的利用率，参数boardId为板卡号

```void getCoreUtilization(unsigned boardId,int a[]);```

//获取板卡温度，参数boardId为板卡号

```int getBoardTemperature(int boardId);```

//获取核心数量，参数boardId为板卡号

```int getClusterNum(int boardId);```

//获取核心温度，返回一个数组，每个元素对应一个核心的温度，参数boardId为板卡号

```void getClusterTemperature(int boardId,int a[]);```

//获取板卡上进程的使用情况

```cndevProcessInfo_t *processInfo()```
