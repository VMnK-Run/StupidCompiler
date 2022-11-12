# StupidCompiler

TJU 编译原理与技术大作业：实现C--语言的编译器前端。

## 文件结构

```
.
│  .gitignore
│  Makefile
│  README.md
│  test.sy			// 默认解析文件
|
├─data
│      01_var_defn.sy
│      02_var_defn.sy
│      03_var_defn.sy
│      04_var_defn.sy
│      05_var_defn.sy
│      grammer.txt		// 文法文件
│      README.md
│  
├─include
│      FSM.h			// 有限自动机
│      SymbolTable.h	// 符号表
│      TokenCodes.h		// 种别码
│      util.h
│  
├─source
│      FSM.cpp			// 有限自动机
│      lexical.cpp		// 词法分析器
│      SymbolTable.cpp	// 符号表实现
│      syntax.cpp		// 语法分析器
│      util.cpp
│  
└─test
        Makefile
        README.md
        test.cpp
```

## 文件说明

+ data/test.sy为当前分析文件，其余.sy文件为样例数据
+ 词法分析结果可输出致lexical.txt，保存token序列
+ 语法分析结果分为first集、follow集、预测分析表和分析结果，分别输出到一个txt文件

## 编译方式

+ 编译生成词法分析器：（仅生成lexical.exe文件）

  ```
  make lexical
  ```

+ 编译生成语法分析器：（仅生成syntax.exe文件）

  ```
  make syntax
  ```

+ 同时编译出词法分析器和语法分析器：（生成lexical.exe和syntax.exe）

  ```
  make
  ```

+ 同时可以在test文件夹下编写test.cpp进行测试，编译运行方式为：

  ```
  make test
  ```

## 运行方式


+ 词法分析器运行方式：

  + 不指定文件名，解析主目录下的test.sy文件：
  
    ```
    .\lexical.exe
    ```
  
  + 指定文件名，如解析与lexical.exe同一目录下的source.sy文件，可采用：
  
    ```
    .\lexical.exe  source.sy
    ```
  词法分析器的输出为lexical.txt，存放解析的token序列，另一输出为符号表SymbolTable.txt。
+ 语法分析器运行方式：

  ```
  .\syntax.exe
  ```

  注：必须先运行词法分析器得到lexical.txt后才能运行语法分析器。

+ 同时运行词法分析器和语法分析器，解析主目录下的默认文件test.sy，将词法分析器结果输出到lexical.txt，将语法分析结果输出到syntax_analysis.txt。（注：若采用该指令，无法指定文件名解析其他文件，仅可替换test.sy文件中的内容进行测试。）

  ```
  make run
  ```

+ 清除可执行文件和输出结果

  ```
  make clean
  ```

  
