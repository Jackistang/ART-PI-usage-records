# LVGL - 事件

## 概述

LVGL 里定义了一系列用户可能感兴趣的事件，就比如一个对象被点击、被拖拽或者其值发送了改变。用户可以注册回调函数来响应这些事件。实践中与下述代码相似：

```C
lv_obj_t * btn = lv_btn_create(lv_scr_act(), NULL);
lv_obj_set_event_cb(btn, my_event_cb);   /*Assign an event callback*/

...

static void my_event_cb(lv_obj_t * obj, lv_event_t event)
{
    switch(event) {
        case LV_EVENT_PRESSED:
            printf("Pressed\n");
            break;

        case LV_EVENT_SHORT_CLICKED:
            printf("Short clicked\n");
            break;

        case LV_EVENT_CLICKED:
            printf("Clicked\n");
            break;
    }

       /*Etc.*/
}
```

## 事件类型

### 通用事件

所有的对象都会接收通用事件。

#### 与输入设备相关的事件

用户按下或松开一个对象时会发送这些事件。Pointers, Keypad, Encoder, Button 输入设备都有这些事件：

| 事件                             | 描述                                                         |
| :------------------------------- | ------------------------------------------------------------ |
| **LV_EVENT_PRESSED**             | 该对象已被按下                                               |
| **LV_EVENT_PRESSING**            | 该对象正在被按下（按下时连续发送）                           |
| **LV_EVENT_PRESS_LOST**          | 输入设备仍被按下，但是焦点不在对象上了                       |
| **LV_EVENT_SHORT_CLICKED**       | 按下时间超过 `LV_INDEV_LONG_PRESS_TIME` 之前松开。拖拽中不会产生 |
| **LV_EVENT_LONG_PRESSED**        | 按下时间超过 `LV_INDEV_LONG_PRESS_TIME` 。拖拽中不会产生     |
| **LV_EVENT_LONG_PRESSED_REPEAT** | 按下 `LV_INDEV_LONG_PRESS_TIME` 时间之后，每隔 `LV_INDEV_LONG_PRESS_REP_TIME` 时间产生一次。拖拽中不会产生 |
| **LV_EVENT_CLICKED**             | 松开时产生。拖拽中不会产生                                   |
| **LV_EVENT_RELEASED**            | 无论对象是否在拖拽中，对象每次被松开时产生。在对象外部按下和滑出对象后松开，则不会产生该事件。此时会产生 `LV_EVENT_PRESS_LOST` |

##### 与 pointer 相关

TODO

##### 与 keypad 和 encoder 相关

TODO

#### 普通事件

| 事件                | 描述                                                   |
| ------------------- | ------------------------------------------------------ |
| **LV_EVENT_DELETE** | 对象被删除时产生，便于用户在对象删除时释放申请的数据。 |

### 特殊事件

TODO

## 自定义数据

发送的事件可以包含自定义数据，在事件的回调函数里用 `lv_event_get_data()` 接口获取自定义的数据。

一般有两种类型数据：

- `uint32_t *` 和 `int32_t *`，用于数字数据。
- `char *` 和 `const char *` ，用于文本数据。

## 手动发送事件

### 任意事件

TODO

### 刷新事件

TODO