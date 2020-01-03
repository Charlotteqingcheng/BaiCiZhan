// ConsoleApplication1（算法）.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

/*#include <iostream>
using namespace std;
const int N = 7;
void matrixchain(int* p, int n, int m[N][N], int s[N][N])
{
	int i;
	n = n - 1;
	for (i = 1; i <= n; i++)
		m[i][i] = 0;
	for (int r = 2; r <= n; r++)
	{
		for (i = 1; i <= n - r + 1; i++)
		{
			int j = i + r - 1;
			m[i][j] = m[i + 1][j] + p[i - 1] * p[i] * p[j];
			s[i][j] = i;
			for (int k = i + 1; k < j; k++)
			{
				int t = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];
				if (t < m[i][j])
				{
					m[i][j] = t;
					s[i][j] = k;
				}
			}
		}
	}
	for (i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
			cout << s[i][j] << " ";
		cout << endl;
	}

}
void traceback(int i, int j, int s[N][N])
{
	if (i == j)
		cout << "A" << i;
	else
	{
		cout << "(";
		traceback(i, s[i][j], s);
		traceback(s[i][j] + 1, j, s);
		cout << ")";
	}
}
int main()
{
	int p[N] = { 30,35,15,5,10,20,25 };
	int m[N][N], s[N][N];
	matrixchain(p, N, m, s);
	traceback(1, N - 1, s);
	std::cout << "Hello World!\n";
}
*/
/*背包问题*/
/*#include<stdio.h>
#include<cstdlib>
int V[200][200];//前i个物品装入容量为j的背包中获得的最大价值
int max(int a, int b)
{
	if (a >= b)
		return a;
	else return b;
}

int KnapSack(int n, int w[], int v[], int x[], int C)
{
	int i, j;
	for (i = 0; i <= n; i++)
		V[i][0] = 0;
	for (j = 0; j <= C; j++)
		V[0][j] = 0;
	for (i = 0; i < n; i++) {
		for (j = 0; j < C + 1; j++) {
			if (j < w[i])
				V[i][j] = V[i - 1][j];
			else
				V[i][j] = max(V[i - 1][j], V[i - 1][j - w[i]] + v[i]);
		}
	}
	j = C;
	for (i = n - 1; i >= 0; i--)
	{
		if (V[i][j] > V[i - 1][j])
		{
			x[i] = 1;
			j = j - w[i];
		}
		else
			x[i] = 0;
	}
	printf("选中的物品是:\n");
	for (i = 0; i < n; i++)
		printf("%d ", x[i]);
	printf("\n");
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < C + 1; j++) {
			printf("%d\t ", V[i][j]);
			if (j == C) {
				printf("\n");
			}
		}
	}
	return V[n - 1][C];

}

int main()
{
	int s;//获得的最大价值
	int w[5] = { 2,2,6,5,4 };//物品的重量
	int v[5] = { 6,3,5,4,6 };//物品的价值
	int x[5];//物品的选取状态
	int n = 5;
	int C = 10;//背包最大容量

	s = KnapSack(n, w, v, x, C);

	printf("最大物品价值为:\n");
	printf("%d\n", s);
	system("pause");
	return 0;

}
*/
#include <iostream>
using namespace std;
/*void functionD(int *p,int n,int **m,int **s) 
{
	for (int i=1 ; i <= n; i++){
		m[i][i]=0;//将单个矩阵相乘的次数设为0 
	} 
	for(int r=2 ; r <= n; r++) {//r为矩阵链的规模 
		for(int i=1; i<=n-r+1;i++){//i为前边界 
			int j=i+r-1;//j为后边界 
			m[i][j]=m[i][i]+m[i+1][j]+p[i-1]*p[i]*p[j];//记录断点在i处时所需要的乘法次数 
			s[i][j]=i;//将断点初始化在i处 
			for(int k=i+1;k<j;k++){
				int t=m[i][k]/*实现重叠子问题的利用*//*+m[k+1][j]+p[i-1]*p[k]*p[j];
				if(t<m[i][j]) {//如果新的断点的乘法次数小于原来的次数 
					m[i][j]=t;//更新最少乘法次数 
					s[i][j]=k;//保存最佳断点位置 
				}
			} 
		}
	}
}
*/
/*int main()
{


	cout<<"最少乘法次数为"<<7<<endl;
	return 0;
}
*/
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<queue>
const int INF = 100000;
const int MAX_N = 22;
using namespace std;
//n*n的一个矩阵
int n;
int cost[MAX_N][MAX_N];//最少3个点，最多MAX_N个点
struct Node
{
	bool visited[MAX_N];//标记哪些点走了
	int s;//第一个点
	int s_p;//第一个点的邻接点
	int e;//最后一个点
	int e_p;//最后一个点的邻接点
	int k;//走过的点数
	int sumv;//经过路径的距离
	int lb;//目标函数的值（目标结果）
	bool operator <(const Node& p)const
	{
		return p.lb < lb;//目标函数值小的先出队列
	}
};
priority_queue<Node> pq;//创建一个优先队列
int low, up;//下界和上界
bool dfs_visited[MAX_N];//在dfs过程中搜索过

						//确定上界,利用dfs（属于贪心算法），贪心法的结果是一个大于实际值的估测结果
int dfs(int u, int k, int l)//当前节点，目标节点，已经消耗的路径
{
	if (k == n) return l + cost[u][1];//如果已经检查了n个节点，则直接返回路径消耗+第n个节点回归起点的消耗
	int minlen = INF, p;
	for (int i = 1; i <= n; i++)
	{
		if (!dfs_visited[i] && minlen > cost[u][i])//取与所有点的连边中最小的边
		{
			minlen = cost[u][i];//找出对于每一个节点，其可达节点中最近的节点
			p = i;
		}
	}
	dfs_visited[p] = true;//以p为下一个节点继续搜索
	return dfs(p, k + 1, l + minlen);
}
void get_up()
{
	dfs_visited[1] = true;//以第一个点作为起点
	up = dfs(1, 1, 0);
}
//用这种简单粗暴的方法获取必定小于结果的一个值
void get_low()
{
	//取每行最小值之和作为下界
	low = 0;
	for (int i = 1; i <= n; i++)
	{
		//创建一个等同于map的临时数组，可用memcpy
		int tmpA[MAX_N];
		for (int j = 1; j <= n; j++)
		{
			tmpA[j] = cost[i][j];
		}
		sort(tmpA + 1, tmpA + 1 + n);//对临时的数组进行排序
		low += tmpA[1];
	}
}
int get_lb(Node p)
{
	int ret = p.sumv * 2;//路径上的点的距离的二倍
	int min1 = INF, min2 = INF;//起点和终点连出来的边
	for (int i = 1; i <= n; i++)
	{
		//cout << p.visited[i] << endl;
		if (!p.visited[i] && min1 > cost[i][p.s])
		{
			min1 = cost[i][p.s];
		}
		//cout << min1 << endl;
	}
	ret += min1;
	for (int i = 1; i <= n; i++)
	{
		if (!p.visited[i] && min2 > cost[p.e][i])
		{
			min2 = cost[p.e][i];
		}
		//cout << min2 << endl;
	}
	ret += min2;
	for (int i = 1; i <= n; i++)
	{
		if (!p.visited[i])
		{
			min1 = min2 = INF;
			for (int j = 1; j <= n; j++)
			{
				if (min1 > cost[i][j])
					min1 = cost[i][j];
			}
			for (int j = 1; j <= n; j++)
			{
				if (min2 > cost[j][i])
					min2 = cost[j][i];
			}
			ret += min1 + min2;
		}
	}
	return (ret + 1) / 2;
}

int solve()
{
	//贪心法确定上界
	get_up();
	//取每行最小的边之和作为下界
	//cout << up << endl;//test
	get_low();
	//cout << low << endl;//test
	//设置初始点,默认从1开始
	Node star;
	star.s = 1;//起点为1
	star.e = 1;//终点为1
	star.k = 1;//走过了1个点
	for (int i = 1; i <= n; i++)
	{
		star.visited[i] = false;
	}
	star.visited[1] = true;
	star.sumv = 0;//经过的路径距离初始化
	star.lb = low;//让目标值先等于下界    
	int ret = INF;//ret为问题的解
	pq.push(star);//将起点加入队列
	while (pq.size())
	{

		Node tmp = pq.top(); pq.pop();
		if (tmp.k == n - 1)//如果已经走过了n-1个点
		{
			//找最后一个没有走的点
			int p;
			for (int i = 1; i <= n; i++)
			{
				if (!tmp.visited[i])
				{
					p = i;//让没有走的那个点为最后点能走的点
					break;
				}
			}
			int ans = tmp.sumv + cost[p][tmp.s] + cost[tmp.e][p];//已消耗+回到开始消耗+走到P的消耗
			//如果当前的路径和比所有的目标函数值都小则跳出
			if (ans <= tmp.lb)
			{
				ret = min(ans, ret);
				break;
			}
			//否则继续求其他可能的路径和，并更新上界
			else
			{
				up = min(up, ans);//上界更新为更接近目标的ans值
				ret = min(ret, ans);
				continue;
			}
		}
		//当前点可以向下扩展的点入优先级队列
		Node next;
		for (int i = 1; i <= n; i++)
		{
			if (!tmp.visited[i])
			{
				//cout << "test" << endl;
				next.s = tmp.s;//沿着tmp走到next，起点不变            
				next.sumv = tmp.sumv + cost[tmp.e][i];//更新路径和                
				next.e = i;//更新最后一个点                
				next.k = tmp.k + 1;//更新走过的顶点数                
				for (int j = 1; j <= n; j++) next.visited[j] = tmp.visited[j];//tmp经过的点也是next经过的点
				next.visited[i] = true;//自然也要更新当前点
				//cout << next.visited[i] << endl;
				next.lb = get_lb(next);//求目标函数
				//cout << next.lb << endl;
				if (next.lb > up) continue;//如果大于上界就不加入队列
				pq.push(next);//否则加入队列
			}
		}
	}
	return ret;
}
int main()
{
	cin >> n;
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			cin >> cost[i][j];
			if (i == j)
			{
				cost[i][j] = INF;
			}
		}
	}
	cout << solve() << endl;
	return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
