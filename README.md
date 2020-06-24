c++调用Python3.6

## TODO

1. 如何使用

## 方式

c++调用python有两种方式

1. 调用python模块

   见usePythonScript文件夹

2. 纯嵌入

   见useEmbed文件夹

3. 官方文档

   ```html
   https://docs.python.org/zh-cn/3.6/extending/embedding.html
   ```

4. 

## 总结

```
所有Python元素，module、function、tuple、string等等，实际上都是PyObject。C语言里操纵它们，一律使用PyObject *。

Python的类型与C语言类型可以相互转换。Python类型XXX转换为C语言类型YYY要使用PyXXX_AsYYY函数；C类型YYY转换为Python类型XXX要使用PyXXX_FromYYY函数。

也可以创建Python类型的变量，使用PyXXX_New可以创建类型为XXX的变量。

若a是Tuple，则a[i] = b对应于 PyTuple_SetItem(a,i,b)，有理由相信还有一个函数PyTuple_GetItem完成取得某一项的值。

作者：Jerry Jho
链接：https://www.zhihu.com/question/23003213/answer/56121859
来源：知乎
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
```

## 数据转换

c++向python传递参数(3.6可用)

```c++
PyObject* args = PyTuple_New(3);
PyObject* arg1 = Py_BuildValue("i", 100); // 整数参数
PyObject* arg2 = Py_BuildValue("f", 3.14); // 浮点数参数
PyObject* arg3 = Py_BuildValue("s", "hello"); // 字符串参数
PyTuple_SetItem(args, 0, arg1);
PyTuple_SetItem(args, 1, arg2);
PyTuple_SetItem(args, 2, arg3);
```

python转c++

```c++
 PyInt_AsLong();//整数
 PyFloat_AsDouble();//浮点
 PyString_AsString();//字符串,PyUnicode_AsUTF8(pValue)
 PyUnicode_AsUTF8(pValue);//python转出c++的字符串

//还可以使用 PyArg_ParseTuple 函数来将返回值作为元组解析。
//PyArg_Parse 也是一个使用很方便的转换函数。
//PyArg_ParseTuple 和 PyArg_Parse 都使用 格式字符串
```

c++转python

```c++
 PyLong_FromLong();						//整数
```



## 问题
1. python2和python的PyString_FromString()函数不相同
    在python2中PyString_FromString()
    在python3中
    
    ```c++
    if (!(pValue = PyUnicode_FromString("A string instead of a number")))
        return NULL;
    ```
    
    
    
2. 找不到模块及python文件(已解决)

    ```c++
    //2、初始化python系统文件路径，保证可以访问到 .py文件,clion中指可执行文件同目录
    PyRun_SimpleString(``"import sys"``);
    PyRun_SimpleString(``"sys.path.append('./')"``);
    //https://www.cnblogs.com/ariel-dreamland/p/11466241.html
    ```

    ```c++
    //另一种将Python工作路径切换到待调用模块所在目录，一定要保证路径名的正确性
        string path = "~/test";
        string chdir_cmd = string("sys.path.append(\"") + path + "\")";
        const char* cstr_cmd = chdir_cmd.c_str();
        PyRun_SimpleString("import sys");
        PyRun_SimpleString(cstr_cmd);
    ————————————————
    版权声明：本文为CSDN博主「liuwons」的原创文章，遵循CC 4.0 BY-SA版权协议，转载请附上原文出处链接及本声明。
    原文链接：https://blog.csdn.net/tobacco5648/article/details/50890106
    ```

3. s

## 代码

useEmbedString传入字符串