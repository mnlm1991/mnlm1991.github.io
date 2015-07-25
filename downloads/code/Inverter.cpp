#include<cstdio>
#include<set>
#include<queue>
#include<cstdlib>
#include<cstring>
using namespace std;

int dir[4][2] = 
{
	{0, -1},
	{0, 1 },
	{-1, 0},
	{1,  0}
};
const int bool_size = 1000;
typedef bool ull[bool_size];
struct Qnode
{
	ull ans;
	ull sum;
	int idx;
};
const int max_size = 10000;
ull bit[max_size];
void xor_array(bool *a, bool *b, bool *ans, int size)
{
	for (int i = 0; i < size; ++i)
	{
		ans[i] = a[i] ^ b[i];
	}
}
bool all_true(bool *test, int size)
{
	for (int i = 0; i < size; ++i)
	{
		if (!test[i]) return false;
	}
	return true;
}
void solve(int n)
{
	int max_bit = n * n;
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			memset(&bit[i * n + j], 0, sizeof(bool) * max_bit);
			bit[i * n + j][i * n + j] = true;
			for (int k = 0; k < 4; ++k)
			{
				int v = i + dir[k][0];
				int u = j + dir[k][1];
				if (u >= 0 && u < n && v >= 0 && v < n)
				{
					bit[i * n + j][v * n + u] = true;
				}
			}
		}
	}
	Qnode tmp;
	memset(tmp.ans, 0, sizeof(bool)*max_bit);
	memset(tmp.sum, 0, sizeof(bool)*max_bit);
	tmp.idx = n;
	queue<Qnode> que;
	for (int i = 0; i < (1 << n); ++i)
	{
		memset(tmp.sum, 0, sizeof(bool) * max_bit);
		memset(tmp.ans, 0, sizeof(bool) * max_bit);
		for (int j = 0; j < n; j++)
		{
			if (i & (1 << j)) 
			{
				tmp.ans[j] = true;
				xor_array(tmp.sum, bit[j], tmp.sum, max_bit);
			}
		}
		que.push(tmp);
	}
	while (!que.empty())
	{
		Qnode u = que.front();
		que.pop();
		int i = u.idx;
		if (i >= n * n) continue;
		Qnode next = u;
		next.idx = u.idx + 1;
		xor_array(next.sum, bit[i], next.sum, max_bit);
		next.ans[i] = true;
		if (all_true(next.sum, max_bit)) 
		{
			printf("ans:%d\n" , n);
			for (int i = 0; i < n; ++i)
				for (int j = 0; j < n; ++j)
				{
					if (next.ans[i * n + j ])
					{
						printf("%d, %d\n", i, j);
					}
				}
			continue;
		}
		if (u.sum[i - n])
		{
			next = u;
			next.idx++;
			que.push(next);
		}
		else 
		{
			que.push(next);
		}
	}
}
int main()
{
	int n;
	while (scanf("%d", &n) != EOF)
	{
		solve(n);
	}
}
