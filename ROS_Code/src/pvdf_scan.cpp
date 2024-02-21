#include <ros/ros.h>
#include <serial/serial.h>
#include <iostream>
#include <string>
#include <math.h>
#include <iostream>
#include "pvdf/pvdf_msg.h"

using namespace std;
 
int main(int argc, char** argv)
{
    ros::init(argc, argv, "pvdf_scan");
    ros::NodeHandle n;
    ros::Publisher Voltage_pub = n.advertise<pvdf::pvdf_msg>("Ori_Voltage_pub", 1000);
    
    pvdf::pvdf_msg msg_Voltage;

    //创建一个serial对象
    serial::Serial sp;
    //创建timeout
    serial::Timeout to = serial::Timeout::simpleTimeout(100);
    //设置要打开的串口名称
    sp.setPort("/dev/ttyUSB0");
    //设置串口通信的波特率
    sp.setBaudrate(115200);
    //串口设置timeout
    sp.setTimeout(to);
 
    try
    {
        //打开串口
        sp.open();
    }
    catch(serial::IOException& e)
    {
        ROS_ERROR_STREAM("Unable to open port.");
        return -1;
    }
    
    //判断串口是否打开成功
    if(sp.isOpen())
    {
        ROS_INFO_STREAM("/dev/ttyUSB0 is opened.");
    }
    else
    {
        return -1;
    }
    
    ros::Rate loop_rate(200);
    while(ros::ok())
    {
        //获取缓冲区内的字节数
        size_t n = sp.available();
        if(n!=0 && n >= 19)
        {
            uint8_t buffer[100];// There are 20 buffers.But create 100 buffer to avoid "stack smashing".
            //读出数据
            n = sp.read(buffer, n);
            if(buffer[0] == 0xaa && buffer[19] == 0xdd){
                for(int i=0; i<n; i++)
                {
                    //16进制的方式打印到屏幕
                    //std::cout << std::hex << (buffer[i] & 0xff) << " ";
                }
                uint16_t temp = 0x00;

                temp = (uint16_t)buffer[2];
                msg_Voltage.Volatge0 = (temp<<8) + buffer[3];
                
                temp = (uint16_t)buffer[4];
                msg_Voltage.Volatge1 = (temp<<8) + buffer[5];

                temp = (uint16_t)buffer[6];
                msg_Voltage.Volatge2 = (temp<<8) + buffer[7];

                temp = (uint16_t)buffer[8];
                msg_Voltage.Volatge3 = (temp<<8) + buffer[9];

                temp = (uint16_t)buffer[10];
                msg_Voltage.Volatge4 = (temp<<8) + buffer[11];

                temp = (uint16_t)buffer[12];
                msg_Voltage.Volatge5 = (temp<<8) + buffer[13];

                temp = (uint16_t)buffer[14];
                msg_Voltage.Volatge6 = (temp<<8) + buffer[15];

                temp = (uint16_t)buffer[16];
                msg_Voltage.Volatge7 = (temp<<8) + buffer[17];

                // cout Voltage0 to Voltage7
                std::cout << std::oct << msg_Voltage.Volatge0 << " " << msg_Voltage.Volatge1 << " " 
                << msg_Voltage.Volatge2 << " " << msg_Voltage.Volatge3 << " " << msg_Voltage.Volatge4 << " " 
                << msg_Voltage.Volatge5 << " " << msg_Voltage.Volatge6 << " " << msg_Voltage.Volatge7 << endl;
                Voltage_pub.publish(msg_Voltage);
            }
            else{
                continue;
            }
        }
        loop_rate.sleep();
    }
    //关闭串口
    sp.close();
    return 0;
}
