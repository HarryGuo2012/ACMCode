#include<climits>
#include<cstdio>
#define max(a,b) a>b?a:b
using namespace std;

#define MAXN 126000

template<typename Type>
class Heap{
private:
    int  size;
    Type data[MAXN+1];
    void siftdown( int pos );
        
public:
    Heap();
    void push( Type key );
    void pop();
    Type top();
    void make_heap();
    bool empty();
    void clear();
    int  get_size();
};

template<typename Type>
Heap<Type>::Heap(){
    size= 0; }
    
template<typename Type>
int Heap<Type>::get_size(){
    return size; }

template<typename Type>
bool Heap<Type>::empty(){
    return size== 0;}
    
template<typename Type>
void Heap<Type>::clear(){
    size= 0; }

template<typename Type>
void Heap<Type>::siftdown( int pos ){
    while( pos<<1<= size ){
        int t= pos<<1; 
        if( (pos<<1)+ 1<= size && data[(pos<<1)+1]<data[t] ) t= (pos<<1)+ 1;
        if( data[t]<data[pos] ){
            Type tmp= data[t]; data[t]= data[pos]; data[pos]= tmp;
            pos= t; }
        else break;
    }
}

template<typename Type>
void Heap<Type>::push( Type key ){
    data[++size]= key;
    int pos= size;
    while( pos> 1 ){
        if( data[pos>>1]> data[pos] ){
            Type tmp= data[pos]; 
            data[pos]= data[pos>>1]; data[pos>>1]= tmp;
            pos>>= 1; }
        else break;
    }
}

template<typename Type>
void Heap<Type>::pop(){
    Type tmp= data[1]; data[1]= data[size];
    data[size]= tmp; size--;
    siftdown(1);
}

template<typename Type>
Type Heap<Type>::top()
{
    return data[1];
}
int n,a;
double x;
int r=0;
int tt,i;
int ma=-1;

Heap<int> que;

int main()
{
    scanf("%d",&n);
    for(i=0;i<(n+2)/2;i++)
    {
        scanf("%d",&a);
        que.push(a);
        ma=max(ma,a);
    }

    for(i=0;i<n-(n+2)/2;i++)
    {
        scanf("%d",&a);
        if(a>=ma)r++;
        if(a>que.top()&&a<ma)
        {
            que.pop();
            que.push(a);
        }
    }
    tt=que.get_size()+r-1-n/2;
    if(n%2)
    {
        for(i=0;i<tt;i++)que.pop();
        x=que.top();
        printf("%.1lf\n",x);
    }
    else
    {
        for(i=0;i<tt;i++)que.pop();
       
        x=(double)que.top();
        que.pop();
        x+=(double)que.top();
        x/=2.0;
        printf("%.1lf\n",x);
    }
    return 0;
}
