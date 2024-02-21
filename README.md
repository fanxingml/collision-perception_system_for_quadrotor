# PVDF_STM32&ROS&PCB

## PCB
直接打印就行，可以代替无人机的碳板。
![PCB外形](/fig/pcb.png "pcb外形")

## STM32部分
用CubeIDE编写，直接编译烧录即可，或者使用\PCB\PVDF_Drone.bin直接烧录。

## ROS部分
需要先
```
sudo apt install ros-noetic-serial
```

打开ROS功能包需要先
```
sudo chmod 777 /dev/ttyUSB0
```
再开启节点
