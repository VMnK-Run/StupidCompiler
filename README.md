# StupidCompiler

TJU 编译原理与技术大作业：实现C--语言的编译器前端。

## 文件结构

```
.
│  .gitignore
│  Makefile
│  README.md
|
├─data
│      01_var_defn.sy
│      02_var_defn.sy
│      03_var_defn.sy
│      04_var_defn.sy
│      05_var_defn.sy
│      grammer.txt		// 文法文件
│      README.md
│      test.sy
│  
├─include
│      FSM.h			// 有限自动机
│      SymbolTable.h		// 符号表
│      TokenCodes.h		// 种别码
│      util.h
│  
├─source
│      FSM.cpp			// 有限自动机
│      lexical.cpp		// 词法分析器
│      main.cpp			// main函数
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

+ 编译词法分析器：

  ```
  make lexical
  ```

+ 编译语法分析器:

  ```
  make syntax
  ```

+ 同时编译词法分析器和语法分析器

  ```
  make
  ```

+ 同时可以在test文件夹下编写test.cpp进行测试，编译运行方式为：

  ```
  make test
  ```

## 运行方式

+ 只运行词法分析器，并将token序列输出到lexical.txt

  ```
  make lexical-save
  ```

+ 同时运行词法分析器和语法分析器，将词法分析器结果输出到lexical.txt，将语法分析结果输出到syntax_analysis.txt

  ```
  make run
  ```

+ 清除可执行文件和输出结果

  ```
  make clean
  ```

  
