#include<stdio.h>
#include<Windows.h>
#include<iostream>
#include<vector>
#include<thread>
using namespace std;

void myprint(int inum)
{
	cout << "myprint线程开始执行了，线程编号 = " << inum << endl;
	//干各种事情
	cout << "myprint线程结束执行了，线程编号 = " << inum << endl;
	return;
}

int main()
{
	vector<thread> mythreads;
	for (int i = 0; i < 5; i++)
	{
		mythreads.push_back(thread(myprint, i));
	}
	for (auto iter = mythreads.begin(); iter != mythreads.end(); ++iter)
	{
		iter->join();
	}
	cout << "main主函数执行结束！" << endl; 
}