#include <Python.h>
#include <iostream>
#include <Windows.h>
#include <cmath>
#include <string>

using namespace std;

/*
Description:
	To call this function, simply pass the function name in Python that you wish to call.
Example:
	callProcedure("printsomething");
Output:
	Python will print on the screen: Hello from python!
Return:
	None
*/
void CallProcedure(string pName)
{
	char* procname = new char[pName.length() + 1];
	std::strcpy(procname, pName.c_str());

	Py_Initialize();
	PyObject* my_module = PyImport_ImportModule("python_code");
	PyErr_Print();
	PyObject* my_function = PyObject_GetAttrString(my_module, procname);
	PyObject* my_result = PyObject_CallObject(my_function, NULL);
	Py_Finalize();

	delete[] procname;
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("PrintMe","Test");
Output:
	Python will print on the screen:
		You sent me: Test
Return:
	100 is returned to the C++
*/
int callIntFunc(string proc, string param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	char* paramval = new char[param.length() + 1];
	std::strcpy(paramval, param.c_str());


	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"python_code");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(z)", paramval);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;
	delete[] paramval;


	return _PyLong_AsInt(presult);
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("doublevalue",5);
Return:
	25 is returned to the C++
*/
int callIntFunc(string proc, int param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"python_code");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(i)", param);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;

	return _PyLong_AsInt(presult);
}

int main() {

	int menuInput = 0;
	int var = 0;

	while (menuInput != 3) {
		cout << "SYSTEM MENU" << endl;
		cout << "===============" << endl;
		cout << "1. Display a Multiplication Table." << endl;
		cout << "2. Double a Value." << endl;
		cout << "3. Exit." << endl;
		cout << "Enter your selection as a number 1, 2, or 3." << endl;

		while (!(cin >> menuInput)) {
			cin.clear();
			cin.ignore(128, '\n');
			cout << "ERROR: Invalid input value." << endl;
			cout << "Enter your selection as a number 1, 2, or 3.";
		}

		if (menuInput == 1) {
			cout << "Enter an integer to multiply: ";
			while (!(cin >> var)) {
				cin.clear();
				cin.ignore(128, '\n');
				cout << "ERROR: Invalid input value." << endl;
				cout << "Enter an integer to multiply: ";
			}

			callIntFunc("MultTable", var);
		}
		else if (menuInput == 2) {
			cout << "Enter an integer to double: ";
			while (!(cin >> var)) {
				cin.clear();
				cin.ignore(128, '\n');
				cout << "ERROR: Invalid input value." << endl;
				cout << "Enter an integer to double: ";
			}

			cout << var << " doubled is: " << callIntFunc("DoubleInt", var) << endl << endl;

		}
		else {

			cout << "ERROR: Invalid input value." << endl;

		}
	}

	return 0;
}

/*
void main()
{
	CallProcedure("printsomething");
	cout << callIntFunc("PrintMe", "House") << endl;
	cout << callIntFunc("SquareValue", 2);

}
*/

/*
#include <iostream>
#include <stdio.h>
#include <string>
#include <Python.h>

using namespace std;

int main() {

	cout << "Start 1 \n";
	Py_Initialize();
	cout << "2\n";
	PyObject* my_module = PyImport_ImportModule("python_code");
	cerr << my_module << "\n";
	PyErr_Print();
	cout << "3\n";
	PyObject* my_function = PyObject_GetAttrString(my_module, "printsomething");
	cout << "4\n";
	PyObject* my_result = PyObject_CallObject(my_function, NULL);
	Py_Finalize();

	return 0;
}
*/