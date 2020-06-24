#include<Python.h>
#include <iostream>
using namespace std;
//封装python函数
int great_function_from_python(int a);

int main(int argc, char *argv[])
{
    //初始化python解释器
    int res = 0;
    Py_Initialize();
    // 将Python工作路径切换到待调用模块所在目录，一定要保证路径名的正确性
    // 2、初始化python系统文件路径，保证可以访问到 py文件
    string path = "'/home/ganggang/Documents/cpppython-test/useEmbedString'";
    string python_file_path = "sys.path.append(";
    python_file_path = python_file_path + path + ")" ;
    const char* c_python_file_path = python_file_path.c_str();
    PyRun_SimpleString("import sys");
    PyRun_SimpleString(c_python_file_path);
    //调用python
    res = great_function_from_python(195);
    //销毁解释器
    Py_Finalize();
    cout<<res<<endl;
    return 0;
}

int great_function_from_python(int a){
    //封装python函数
    int res = 0;
	PyObject *pName,*pModule,*pFunc;
	PyObject *pArgs,*pValue;
	/*  import  */
	//模块名
	const char *pModuleName = "great_module";
	//函数名
    const char *pFunction = "great_function";
    pName = PyUnicode_DecodeFSDefault(pModuleName);
	pModule = PyImport_Import(pName);
	//释放指针
    Py_DECREF(pName);
    if (pModule != NULL){
        cout<<"find module: "<<endl;
        /*  指向函数  */
        pFunc = PyObject_GetAttrString(pModule,pFunction);
        if (pFunc && PyCallable_Check(pFunc)) {
            cout<<"find function"<<endl;
            /*　build args  */
            //传入参数，有几个参数写几个
            pArgs = PyTuple_New(1);
            //传入参数，将其传入pArgs中
            PyTuple_SetItem(pArgs,0,PyLong_FromLong(a));
            /*  call回调  */
            pValue = PyObject_CallObject(pFunc,pArgs);
            Py_DECREF(pArgs);
            if (pValue != NULL) {
                printf("Result of call: %ld\n", PyLong_AsLong(pValue));
                return PyLong_AsLong(pValue);
                Py_DECREF(pValue);
            }
            else {
                Py_DECREF(pFunc);
                Py_DECREF(pModule);
                PyErr_Print();
                fprintf(stderr,"Call failed\n");
                return 1;
            }
        }
        else {
            if (PyErr_Occurred())
                PyErr_Print();
            fprintf(stderr, "Cannot find function \n");
        }
        Py_XDECREF(pFunc);
        Py_DECREF(pModule);
    }
    else{
        printf("can not open module:\n");
        PyErr_Print();
        return 1;
    }
	return res;
}