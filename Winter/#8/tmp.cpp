#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>
#define MAX 1007

using namespace std;

int n,m,s,d,h;
int ans_h , ans_d;

struct Edge
{
    int v,w,h,next;
}e[MAX*MAX];

int head[MAX];
int dis[MAX];
int cc;

void add ( int u , int v , int h , int w )
{
    e[cc].v = v;
    e[cc].w = w;
    e[cc].h = h;
    e[cc].next = head[u];
    head[u] = cc++;
}

bool used[MAX];

bool bfs ( int mid )
{
    memset ( used , 0 , sizeof ( used ) );
    queue<int> q;
    q.push ( s );
    while ( !q.empty( ) )
    {
        int u = q.front();
        q.pop ( );
        if ( u == d ) return true;
        for ( int i = head[u]; ~i ; i = e[i].next )
        {
            if ( e[i].h != -1 && e[i].h < mid ) continue;
            int v = e[i].v;
            if ( used[v] ) continue;
            used[v] = true;
            q.push ( v );
        }
    }
    return false;
}


int get_h ( int h  )
{
    int left = 0 , right = h, mid;
    while ( left != right )
    {
        mid = (left+right+1) >> 1;
        if ( bfs ( mid ) ) left = mid;
        else right = mid-1;
    }
    return left;
}

struct cmp
{
    bool operator () ( const int& a , const int &b ) const 
    {
        return dis[a] > dis[b];
    }
};

void dijkstra ( )
{
    memset ( used , 0 , sizeof ( used ) );
    memset ( dis , 0x3f , sizeof ( dis ) );
    priority_queue<int,vector<int>,cmp> q;
    q.push ( s );
    dis[s] = 0;
    while ( !q.empty( ) )
    {
        int u = q.top();
        q.pop ( );
        used[u] = true;
        for ( int i = head[u] ; ~i ; i = e[i].next )
        {
            if ( e[i].h != -1 && e[i].h < ans_h ) continue;
            int v = e[i].v;
            if ( !used[v] && dis[v] > dis[u] + e[i].w )
            {
                dis[v] = dis[u] + e[i].w;
                q.push ( v );
            }
        }
    }
}

int main ( )
{
    int u,v,h,w,c=1;
    bool flag = false;
    while ( ~scanf ( "%d%d" , &n , &m ) )
    {
        if ( !n && !m ) break;
        if ( flag ) puts ("");
        else flag = true;
        memset ( head , -1 , sizeof ( head ) );
        cc = 0;
        for ( int i = 0 ; i < m ; i++ )
        {
            scanf ( "%d%d%d%d" , &u , &v , &h , & w );
            add ( u , v , h , w );
            add ( v , u , h , w );
        }
        scanf ( "%d%d%d" , &s , &d , &h );
        printf ( "Case %d:\n" , c++ );
        if ( !bfs ( 0 ) ) 
        {
            puts ( "cannot reach destination" );
            continue; 
        }
        ans_h = get_h( h );
        dijkstra ( );
        ans_d = dis[d];
        printf ( "maximum height = %d\n" , ans_h );
        printf ( "length of shortest route = %d\n" , ans_d );
    }
}