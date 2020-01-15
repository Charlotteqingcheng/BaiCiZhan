// 数据结构2.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <iomanip>
using namespace std;
int a[10] = { 0 };
struct node
{
private:
	int data;
	node* next;
	friend class linklist;
};
class linklist
{
public:
	linklist() {};
	linklist(int a[], int n);
	~linklist() {};
	int printlist();
private:
	node* first;
	node* p;
};
linklist::linklist(int a[], int n)
{
	int i;
	frist = 0;
	p = first->next;
	cout << "请分别为各个元素依次赋值" << endl;
	for (i = 1; i <= n; i++)
	{
		cin >> a[i];
		p->data = a[i];
		p = p->next;
	}
}
int linklist::printlist()
{
	p= first->next;
	while (p != NULL)
	{
		cout << p->data;
		p = p->next;
	}
	return 0;
}
int main()
{
	int h;
	cout << "请输入你想要的输入的链表元素个数" << endl;
	cin >> h;
	linklist A(a, h);
	A.printlist();
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//1．随机产生或键盘输入一组元素，建立一个带头结点的单向链表（无序）。
//2．遍历单向链表。
//3．把单向链表中元素逆置（不允许申请新的结点空间）。
//4．在单向链表中删除所有的偶数元素结点。
//5．编写在非递减有序链表中插入一个元素使链表元素仍有序的函数，并利用该函数建立一个非递减有序单向链表。
//6．利用算法5建立两个非递减有序单向链表，然后合并成一个非递增链表。
//7．编写一个主函数, 调试上述算法。
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
