/*******************************************************************************
 技术支持：zyy6569@163.com
 电    话：15927557560
 QQ群    ：376440003
 本人承接Labview、MFC的上位机项目 嵌入式设计项目 VLC项目 
 1588协议项目 Marvell6095F/broadcom53262 Switch项目 欢迎来电来函咨询！
 CAN/485/以太网转换设备，串口服务器 尽在http://xstrive.taobao.com
 公司网址：www.xstrive.com
 迅思维科技版权所有
*******************************************************************************/

使用说明:
1.编译程序;
2.成功后找到win32srvdemo.exe(注意:不是直接运行此程序),在debug或release目录中,
复制下路径,如..win32srvdemo\debug\win32srvdemo.exe;
3.开始->运行->cmd->回车 输入sc create test binPath= 上面的路径
4.开始->运行->services.msc->回车 找到test并启动->OK了
5.成功后应该可以看到d:\test.txt文件