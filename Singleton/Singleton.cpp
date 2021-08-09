// Singleton.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <mutex>
using namespace std;

class CSingleton
{
private:
	//Avoid default construction of object.
	CSingleton() {};
	//Avoid default copying of object.
	CSingleton(CSingleton &objCSingleton) { };
	//Avoid assignment of object.
	void operator = (CSingleton &objCSingleton) {};

	static CSingleton *pCSingleton;
	static mutex m_mutex;
public:
	static CSingleton *GetInstance()
	{
		// no need to aquire lock every time as it will slow down object returning.
		if (nullptr == pCSingleton)
		{
			lock_guard<mutex> lock(m_mutex);
			//again need to check initialization as multiple threads might be waiting on mutex
			//and one by one they will get schedule and need to restrict single object.
			if (nullptr == pCSingleton)
			{
				pCSingleton = new CSingleton();
			}
		}

		return pCSingleton;
	}

	void Print()
	{
		cout << "Inside print function" << endl;
	}
};

CSingleton* CSingleton::pCSingleton = nullptr;
mutex CSingleton::m_mutex;

int main()
{
	CSingleton::GetInstance()->Print();
}

//Output:
/*
Inside print function
*/
