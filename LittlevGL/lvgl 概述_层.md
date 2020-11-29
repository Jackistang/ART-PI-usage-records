# 层

## 创建顺序

默认情况下，lvgl 绘制的旧对象在底层，新对象在顶层。

例如，我们依次添加对象 button1 和 button2 ，并且这两个对象有一部分重叠，会发现 button2 对象覆盖了部分 button1 对象。

<img src="picture/layers.png" alt="../_images/layers.png" style="zoom:67%;" />

## 置于顶层

有三种方法可以将对象置于顶层：

- 使用 `lv_obj_set_top(obj, true)` 。设置了该属性后，如果 `obj` 或它的任意子对象被点击了，lvgl 会自动地将该对象置于顶层。PC 上也是类似的，当一个位于底层的窗口被点击了，它会自动地置于顶层。
- 使用 `lv_obj_move_foreground(obj)` 明确地告诉 lvgl 将对象置于顶层。类似的，可以用 `lv_obj_move_background(obj)` 将对象置于底层。
- 当 `lv_obj_set_parent(obj, new_parent)` 被使用，`obj` 会在 `new_parent` 对象的顶层。

## 顶层和系统层 (Top and sys layers)

TODO