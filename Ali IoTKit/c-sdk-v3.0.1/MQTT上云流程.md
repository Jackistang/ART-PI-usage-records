# MQTT 上云流程

c-sdk-v3.0.1 [MQTT API](https://code.aliyun.com/edward.yangx/public-docs/wikis/user-guide/linkkit/Prog_Guide/API/MQTT_Provides) 。

以下流程来自于 `c-sdk-v3.0.1/src/mqtt/examples/mqtt_example.c` 文件。

## 添加三元组

三元组也就是 ProductKey，DeviceName，DeviceSecret，这是物联网云平台给某个产品里的某个设备颁布的产品证书，物联网节点靠这个三元组接入云平台。

由于 c-sdk-v3.0.1 抽象了硬件和操作系统，因此需要在自己移植好的操作系统接口里添加三元组，一般在 `c-sdk-v3.0.1/wrappers/os/xxx/HAL_OS_xxx.c` 文件里，格式如下：

```C
char _product_key[IOTX_PRODUCT_KEY_LEN + 1]       = "a1RIsMLz2BJ";
char _product_secret[IOTX_PRODUCT_SECRET_LEN + 1] = "fSAF0hle6xL0oRWd";
char _device_name[IOTX_DEVICE_NAME_LEN + 1]       = "example1";
char _device_secret[IOTX_DEVICE_SECRET_LEN + 1]   = "RDXf67itLqZCwdMCRrw0N5FHbv5D7jrE";
```

## 构造 MQTT 连接参数

c-sdk 里 MQTT 的连接参数由 `iotx_mqtt_param_t` 结构体表示，其中包括

- MQTT 服务器的主机名（`host`）
- MQTT 连接的端口（`port`）
- MQTT 超时重传的间隔（`request_timeout_ms`）
- MQTT 的清除会话标志（`clean_session`）
- MQTT 心跳包间隔（`keepalive_interval_ms`）
- MQTT 写缓冲区大小（`write_buf_size`）
- MQTT 读缓冲区大小（`read_buf_size`）
- MQTT 事件回调函数（`handle_event.h_fp`）

*注意：上述选项除了“事件回调函数”一定要配置外，其他选项可以保持值为 0，c-sdk 会选择默认值进行配置。*

连接参数配置完成后，就可以调用 `IOT_MQTT_Construct()`函数来建立连接了，函数返回值是连接的句柄（`handle`）。

## 订阅发布

建立连接后，就可以进行订阅 `IOT_MQTT_Subscribe()`和发布 `IOT_MQTT_Publish_Simple()` 的操作了。

