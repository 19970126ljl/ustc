# ftp 分为主动模式和被动模式


1. 主动模式：客户机向服务端发起连接（21），服务端主动和客户端建立数据连接(20)
2. 被动模式：客户机向服务端发起连接（21），服务端发送一个端口给客户端，客户端在这个端口上建立数据连接


/etc/ftpusers 有限制登录的用户

/etc/pam.d/vsftpd 对用户的shell合法性进行检查

添加用户需要编辑 /etc/vsftpd.chroot_list


