# Im-Select-Imm

## 介绍

原版im-select可以切换输入法， 但是不能切换中英文。
这个版本可以在第二个参数中切换中英文和全角半角。
二进制位于 `此目录/out/` 中

## 使用方式

### 下载

### 获取当前输入法的key

```shell
/path/to/im-select-imm.exe
Out: [当前输入法]-[输入法的当前模式]
```

### 切换输入法

```shell
/path/to/im-select.exe [目标输入法]  
Or
/path/to/im-select.exe [目标输入法] [目标输入法的目标模式]
Or
/path/to/im-select.exe [目标输入法]-[目标输入法的目标模式] # 部分插件下只允许一个参数
Or
/path/to/im-select.exe -d 50 [目标输入法]-[目标输入法的目标模式] # 在切换输入法和模式之间插入延迟，默认30ms，可能可以改善一部分人无效的情况
```
## 已测试输入法

1. 新旧微软拼音
2. 新微软日语输入法

### 对于微软输入法

```
For  Microsoft Old Chinese IME(Win10 and Previous) :
    0: English
    1: Chinese
For  Microsoft New Chinese IME(Win11) :
    0: English / Half Shape
    1: Chinese / Half Shape
    1024: English / Full Shape (虽然存在此模式，但实际仍然为半角)
    1025: Chinese / Full Shape
```
