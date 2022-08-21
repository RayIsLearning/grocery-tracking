#include <Python.h>
#include <iostream>
#include <Windows.h>
#include <cmath>
#include <string>
#include <fstream>
#include <iomanip>

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
	PyObject* my_module = PyImport_ImportModule("python_mods.PythonCode");
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
	pName = PyUnicode_FromString((char*)"PythonCode");
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
	pName = PyUnicode_FromString((char*)"PythonCode");
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
	/*
	My code below. All logic is within the PrintMenu function. Python functions are called after verifying user input.
	*/

void PrintMenu() {
	ifstream fileIn;		//for reading the DAT file
	int menuOption = 0;		//to hold user selection in memory
	int itemTotal = 0;		//to count total items the user is looking for
	int totalWords = 0;		
	int numItems = 0;		//to store and print in c++
	string nameItems;		//to store and print in c++
	string research;		//to send to python

	while (menuOption != 4) {										//while loop for menu
		std::cout << "[1] Sales per item.\n";						//print statements for menu
		std::cout << "[2] Sales of a specific item\n";				
		std::cout << "[3] Histogram based on item sales\n";
		std::cout << "[4] Quit\n";
		std::cin >> menuOption;										//user input

		if (menuOption == 1) {
			std::cout << "sales per item, calling script...\n";		
			CallProcedure("my_function");							//calls python function if user selects 1
			break;													//break statement to prevent infinate loop 
		}
		if (menuOption == 2) {
			std::cout << "What item are you looking for?\n";
			std::cin >> research;
			itemTotal = callIntFunc("SearchTotal", research);		//calls python function if user selects 2
			std::cout << itemTotal << " " << research << " were sold today.\n";  //returns "sales" from python script and prints/formats in c++
			break;													//break statement to prevent infinate loop 
		}
		if (menuOption == 3) {
			std::cout << "generating plot...\n";
			CallProcedure("Plotter");								//calls python function if user selects 3
			fileIn.open("frequency.dat");							//opens DAT file
			fileIn >> nameItems;									//reads first string
			fileIn >> numItems;										//reads first int
			while (!fileIn.fail()) {								//iterates through the list and stores values
				std::cout << std::left << nameItems << std::setw(10);
				for (int i = 0; i < numItems; i++){					//converts numbers to special char
					std::cout << std::right << "$";
			}
				
				std::cout << "\n";
				fileIn >> nameItems;
				fileIn >> numItems;
				

			}
			fileIn.close();											//closes DAT file

			break;													//break statement to prevent infinate loop 
		}
		if (menuOption == 4) {										//ends program by user request
			std::cout << "ending program\n";
			exit(1);
			break;													//break statement to prevent infinate loop 
		}
		else if (menuOption >= 5) {
			std::cout << "please select a valid option\n";			//informs user that input is not valid
			break;													//break statement to prevent infinate loop 
		}
		{

		}

	}
}
	

			

int main()
{

	PrintMenu(); //runs menu program

	return 0;
}