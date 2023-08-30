#include<stdio.h>
#include<Windows.h>
#include<iostream>
#include<list>
#include<thread>
using namespace std;
// 这个代码是错误范例，说明边读边写有问题
class A
{
public:
	// 把收到的消息入到队列的线程
	void inMsgRecvQueue()
	{
		for (int i = 0; i < 100000; i++)
		{
			cout << "inMsg执行，插入一个元素" << i << endl;
			msgRecvQueue.push_back(i); //假设这个数字就是收到的命令，则将其直接放到消息队列里
		}
	}

	// 把数据从消息队列中取出的线程
	void outMsgRecvQueue()
	{
		for (int i = 0; i < 100000; i++)
		{
			if (!msgRecvQueue.empty())
			{
				int command = msgRecvQueue.front(); //返回第一个元素但不检查元素存在与否
				msgRecvQueue.pop_front(); //移除第一个元素但不返回
				//这里可以考虑处理数据
				//...
			}
			else
			{
				cout << "outMsg执行了，但目前消息队列中是空元素" << i << endl;
			}

		}
		cout << "end" << endl;
	}
private:
	std::list<int> msgRecvQueue;  //容器（收消息队列），专门用于代表玩家给咱们发过来的命令
};

int main()
{
	A myobja;
	std::thread myOutnMsgObj(&A::outMsgRecvQueue, &myobja); //注意这里第二个参数必须是引用（用std::ref也行）才能保证线程里用的是同一个对象
	std::thread myInMsgObj(&A::inMsgRecvQueue, &myobja);
	myInMsgObj.join();
	myOutnMsgObj.join();
	cout << "main主函数执行结束" << endl;
}