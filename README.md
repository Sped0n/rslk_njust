## 介绍与感谢

南理工微机实验代码

基于[先前学长的贡献](https://gitee.com/adsh223/rslk_-ccs)，学长在bilibili也有[教学视频](https://www.bilibili.com/video/BV1cZ4y1r71Y)，基础一般的同学可以看看。

## 实现功能（基于driverlib）

* 按键输入侦测 `button.c`
* 呼吸灯 `breath_led.c`
* 循迹 `track.c`
* 时钟延时控制 `CLK.c`
* LED灯控制 `LED.c`
* 碰撞开关避障 `bump.c`
* ADC输入 `ADC.c`
* 红外测距避障 `distance.c`
* 电机控制 `motor.c`
* 人工PWM（基于`TimerA`控制）`mpwm.c`
* 红外遥控 `remote.c`

## 环境准备

### CCS

#### driverlib下载

TI官网链接：https://dr-download.ti.com/software-development/driver-or-library/MD-qriP7Wfm4e/3.21.00.05/msp432_driverlib_3_21_00_05.zip

#### 创建项目

> 如果先前创建项目请自行导入`driverlib`文件
>
> 用下面的方式可以免去导入`driverlib`的麻烦，**但请务必按照步骤操作**

* 下载解压后用CCS文件选项下的导入工程导入如下路径的工程文件
  ```bash
  examples/MSP432P4xx/empty_projects/driverlib_empty_project
  ```

#### 项目设置

* 如果想导入其他源码，请使用文件选项下的导入文件进行导入，**不要自行复制文件到源码文件夹**
* 将CCS的编译选项由默认的C89改为C11
* 将项目默认编码由GBK改为UTF-8（可选）

### PlatformIO

> **注意**：
>
> 目前tirtos环境的中断配置存在问题，参见[此issue](https://github.com/zceemja/platform-timsp432/issues/3)，如果需要使用中断功能，请使用CCS编译源码，不含中断的代码可以在PlatformIO上编译烧录。

#### 简单介绍

[PlatformIO](https://platformio.org/)是一款跨平台的物联网开发的生态环境，主流的编辑器（VS Code/CLion）只要装上本插件就可以化身为一款强大的MCU开发平台，支持绝大多数流行的单片机平台，如stm32/esp32。

#### 配置信息

```ini
platform = timsp432
board = lpmsp432p401r
framework = tirtos
```

> `driverlib`无需导入，tirtos环境自带。

## 效果

![IMB_izxJc1](https://img.sped0nwen.com/image/2022/12/16/ph35up-0.gif "循线测试")

![IMB_dUO5es](https://img.sped0nwen.com/image/2022/12/16/qt4nwv-0.gif "系统测试")

## 文档

### ADC

#### `void ADC_init(void)`

ADC初始化

#### `void ADC_In17_12_16(uint32_t *ch17, uint32_t *ch12, uint32_t *ch16)`

读取三个红外测距传感器数据

### CLK

#### `void CLK_init(void)`

延时模块初始化

#### `void SysTick_Init(void)`

系统时钟初始化

#### `void delay_us(uint32_t us)`

微秒延迟

#### `void delay_ms(uint32_t ms)`

毫秒延迟

#### `void delay_s(uint32_t s)`

秒延迟

### LED

#### `void LED_init(void)`

LED模块初始化

#### `void RED_on(void)`

打开单色红灯

#### `void RED_off(void)`

关闭单色红灯

#### `void RGB_on(uint8_t color)`

向红/绿/蓝端口输出高电平

#### `void RGB_off(uint8_t color)`

向红/绿/蓝端口输出低电平

#### `void RGB_clear(void)`

清空RGB颜色

#### `void RGB_pure(uint8_t color)`

RGB显示颜色切换

> 颜色表：
>
> ```c
> #define RED 1
> #define GREEN 2
> #define BLUE 3
> #define PURPLE 4
> #define YELLOW 5
> #define CYAN 6
> #define WHITE 7
> ```

### bump

#### `void bump_init(void)`

碰撞开关避障模块初始化

#### `void bump_control_right(uint32_t timer)`

向右避障动作，timer为时间变量，**可以考虑用`CLK`中的delay来重写**

#### `void bump_control_left(uint32_t timer)`

向左避障动作，timer为时间变量，**可以考虑用`CLK`中的delay来重写**

#### `void bump(uint8_t status)`

碰撞状态判断及应对

#### `void bump_enable(void)`

打开碰撞避障功能

#### `void bump_disable(void)`

关闭碰撞避障功能

#### `void PORT4_IRQHandler(void)`

碰撞开关中断主方程

### button

#### `void button_basic_init(void)`

按键初始化（无中断）

#### `uint8_t get_button_state(uint8_t position)`

获取左/右按键输入状态

#### `void button_interrupt_init(void)`

按键初始化（带中断）

### distance

#### `void distance_init(void)`

红外测距模块初始化

#### `void read_distance(void)`

获取测距距离

#### `void distance(void)`

避障函数

#### `void distance_test(void)`

避障测试（联动LED）

### motor

#### `void motor_init(void)`

电机初始化

#### `void motor_start(void)`

电机启动

#### `void motor_stop(void)`

电机关闭

#### `void motor_forward(uint8_t speed)`

前进函数，`speed`为最大100的正整数

#### `void motor_backward(uint8_t speed)`

前进函数，`speed`为最大100的正整数

#### `void motor_right(uint8_t speed, double_t ratio)`

前进右转函数，`speed`为最大100的正整数，`ratio`为大于1的浮点数

#### `void motor_left(uint8_t speed, double_t ratio)`

前进左转函数，`speed`为最大100的正整数，`ratio`为大于1的浮点数

#### `void spin_right(uint8_t speed)`

原地右转函数，`speed`为最大100的正整数

#### `void spin_left(uint8_t speed)`

原地左转函数，`speed`为最大100的正整数

### mpwm（manual PWM）

#### `void mpwm_init(void)`

mpwm初始化

#### `void RGB_mpwm_output(uint8_t selectColor, uint16_t strength, uint8_t PulseWidth, uint16_t lastMul)`

* `selectColor`：参照LED里的`RGB_pure`
* `strength`：LED强度
* `PulseWidth`：PWM脉宽
* `lastMul`：重复次数/持续时间


#### `void breath_init(void)`

呼吸灯初始化

### remote

> **按键键值说明：**
>
> ![img.png](https://github.com/Sped0n/rslk_njust/blob/main/doc/img.png?raw=true)

#### `void remote_init(void)`

红外遥控初始化

#### `void TA2_N_IRQHandler(void)`

遥控按键中断

#### `uint8_t remote_scan(void)`

扫描键值扫描并返回

### track

#### `void track_init(void)`

循迹初始化

#### `void track_scan(void)`

扫描红外循迹传感器返回值

#### `void vertical_left(void)`

直角/锐角左弯

#### `void vertical_right(void)`

直角/锐角右弯

#### `void track(void)`

循迹主方程

#### `void track_test(void)`

循迹测试（联动LED）
