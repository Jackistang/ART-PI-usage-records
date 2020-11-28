# lvgl 移植

## littleVGL 特点

- 内置控件
- 高级图形效果：动画，反锯齿，透明度，平滑滚动
- 支持多种输入设备：touchpad, mouse, keyboard, encoder**(?)** 等 **[TODO]**
- 支持 UTF-8 编码
- 支持多个和多种显示设备，例如同步显示在多个彩色屏或单色屏上 **[TODO]**
- **完全自定制的图形元素**  **[UNKONWN]**
- 硬件独立于任何微控制器或显示器  **[UNKONWN]**
- 可以缩小到最小内存（64 kb Flash, 16 kb RAM）

> 64 kB flash and 8 kB RAM is enough for a simple user inteface.

- 支持操作系统、外部存储和 GPU（非必须）**[TODO]**
- 仅仅**单个帧缓存设备**就可以呈现高级视觉特效。
- 使用 C 编写以获得最大兼容性（兼容 C++）
- 支持 PC 模拟器（常用）
- 为加速 GUI 设计，提供教程，案例和主题，支持响应式布局 **[UNKONWN]**
- 提供了在线和离线文档
- 基于自由和开源的 MIT 协议

> ## Features
>
> - Powerful [building blocks](https://docs.lvgl.io/latest/en/html/widgets/index.html): buttons, charts, lists, sliders, images, etc.
> - Advanced graphics: animations, anti-aliasing, opacity, smooth scrolling
> - Use [various input devices](https://docs.lvgl.io/latest/en/html/overview/indev.html): touchscreen, mouse, keyboard, encoder, buttons, etc.
> - Use [multiple displays](https://docs.lvgl.io/latest/en/html/overview/display.html): e.g. monochrome and color display
> - Hardware independent to use with any microcontroller or display
> - Scalable to operate with little memory (64 kB Flash, 10 kB RAM)
> - Multi-language support with UTF-8 handling, Bidirectional and Arabic script support
> - Fully customizable graphical elements via [CSS-like styles](https://docs.lvgl.io/latest/en/html/overview/style.html)
> - OS, External memory and GPU are supported but not required
> - Smooth rendering even with a [single frame buffer](https://docs.lvgl.io/latest/en/html/porting/display.html)
> - Written in C for maximal compatibility (C++ compatible)
> - Micropython Binding exposes [LVGL API in Micropython](https://blog.lvgl.io/2019-02-20/micropython-bindings)
> - [Simulator](https://docs.lvgl.io/latest/en/html/get-started/pc-simulator.html) to develop on PC without embedded hardware
> - [Examples](https://github.com/lvgl/lvgl/blob/master/lv_examples) and tutorials for rapid development
> - [Documentation](http://docs.lvgl.io/) and API references

## littleVGL 要求

- 16、 32 或 64 位的单片机（微控制器）或处理器  
- 微处理器的主频最好高于 16MHZ  
- Flash/ROM:如果只用 littleVGL 核心组件的话,则至少需要 64kB 的容量,如果想完整使用的话,最好保证 180kB 以上的容量  
- RAM：
  - 静态 RAM: 大约 8 到 16 kB,这取决于你所用的组件功能和 objects 控件对象类型  
  - 栈: 至少为 2Kb,一般推荐值为 4kB  
  - 动态数据(堆): 至少 4kB,如果你用到了多个或多种控件的话,那么最好设置为 16kB 以上,这个是可以通过 lv_conf.h 配置文件中的 LV_MEM_SIZE 宏来定义的  
  - 显示缓冲区: 至少要比”水平分辨率像素”要大,一般推介值为 10 倍的”水平分辨率像素”,取个例子,假如我们屏幕的水平分辨率为480个像素,采用16位的颜色深度进行显示,即一个像素占 2 个字节,那么推介的显示缓冲区大小为 10*480*2=9600 个字节  
- C99 或更新的编译器,如果是用 keil 开发的话,一定得勾选”c99”模式,否则编译会报错的  
- 基本的 c(或者 c++)语言知识,如:指针,结构体,回调函数  

## 移植

- 将 lvgl 库文件导入工程
- 修改 lv_conf.h 和 lv_ex_conf.h 配置文件
- 添加定时器，为 littleVGL 提供心跳节拍
- 修改 lv_port_disp_template.c，lv_port_disp_template.h 文件
- 修改 lv_port_indev_template.c，lv_port_indev_template.h 文件
- 移植官方的演示例程