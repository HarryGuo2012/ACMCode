#include<iostream>
#include<queue>
#include<vector>
#include<algorithm>
#include<map>
#include<string>
using namespace std;

long long factory[9] = { 0, 1, 2, 6, 24, 120, 720, 5040, 40320 };
int ma[1000000];
bool visit[1000000];
int dx[4] = { 1, 0, -1, 0 }, dy[4] = { 0, 1, 0, -1 };

struct node
{
    vector<int> num;
    int step;
    int pos;
    node(vector<int> _num, int _step, int _pos)
	{
            num = _num;
            step = _step;
            pos = _pos;
	}
};

int has(vector<int> v)
{
    int temp = 0;
    for (int i = 0; i < 9; i++)
    {
        int cou = 0;
        for (int j = 0; j<i; j++)
            if (v[j]>v[i]) cou++;
        temp += factory[i] * cou;
    }
    return temp;
}

void bfs()
{
    queue<node> que;
    vector<int> start = { 1, 2, 3, 4, 5, 6, 7, 8, 0 };
    que.push(node(start, 0, 8));
    int Tstart = has(start);
    ma[Tstart] = 0;
    visit[Tstart] = 1;
    while (!que.empty())
    {
        node now = que.front();
        que.pop();
        int pos = now.pos;
        for (int i = 0; i < 4; i++)
        {
            int nx = pos / 3 + dx[i];
            int ny = pos % 3 + dy[i];
            int np = nx * 3 + ny;
            vector<int> nowNum;
            if (nx < 3 && nx >= 0 && ny < 3 && ny >= 0)
            {
                nowNum=now.num;
                int temp = nowNum[pos];
                nowNum[pos] = nowNum[np];
                nowNum[np] = temp;
                int hashNum = has(nowNum);
                if (!visit[hashNum])
                {
                    visit[hashNum] = 1;
                    ma[hashNum] = now.step + 1;
                    que.push(node(nowNum, now.step + 1, np));
                }
            }
        }
    }
}

int main()
{
    bfs();
    int T;
    scanf("%d", &T);
    while (T--) {
        vector<int> number;
        for (int i = 0; i < 9; i++) {
            char c;
            cin >> c;
            if (c != 'x') number.push_back(c - '0');
            else number.push_back(0);
        }
        int hashNumber = has(number);
        if (!visit[hashNumber])
            cout << -1 << endl;
        else
            cout << ma[hashNumber] << endl;
    }
    return 0;
}