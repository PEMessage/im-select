# Im-Select-Imm

## Introduce 
Orgin im-select could only change IME,
This version allow you change IME Mode in second parameter,
The pre-build exe is under the `thisdir/out/`
[中文介绍](./README_CN.md)

## Usage 

## Get Current IME key

```shell
/path/to/im-select-imm.exe
Out: [current IME]-[current Mode]
```

## Switch IME

```shell
/path/to/im-select-imm.exe [target IME]  
Or
/path/to/im-select-imm.exe [target IME]  [target IME Mode]
Or
/path/to/im-select-imm.exe [target IME]-[target IME Mode]
Or
/path/to/im-select-imm.exe -d 50 [target IME]-[target IME Mode] # add some delay, May fix some people don't work
```
## Alredy Tested IME

1. Microsoft Chinese IME(New Windows11)
2. Microsoft Chinese IME(Old Windows10)
3. Microsoft Japenese IME(New Windows11)

## For Microsoft Chinese IME

```
For  Microsoft Old Chinese IME(Win10 and Previous) :
    0: English
    1: Chinese
For  Microsoft New Chinese IME(Win11) :
    0: English / Half Shape
    1: Chinese / Half Shape
    1024: English / Full Shape(in practice still half shape) 
    1025: Chinese / Full Shape
```


