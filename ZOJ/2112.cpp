#include<iostream>
#include<cstring>
#include<algorithm>
#include<vector>
#include<cstdlib>
#include<set>
#include<climits>
#include<ctime>
#include<stack>
#include<cstdio>
#include<cmath>
#define MAX_N 50004
#define MAX_M 10004
#define MAX_S 233
using namespace std;

const static int TreapSize = MAX_N+MAX_M;
struct node{
    node * ch[2];
    int key , v , s , cnt ;
    int cmp(int x) const{
        if(key==x) return -1;
        return x < key ? 0 : 1;
    }
};

node nt[TreapSize];
int Q[TreapSize] , sz ;

//必须调用 init() 函数在初始化的时候,可调用的静态内存在Q数组中,是一个栈
void init(){
    srand(time(NULL));
    for(int i = 0 ; i < TreapSize ; ++ i) Q[i] = i;sz = TreapSize;
}

struct Treap
{
    node * root;
    int treapsz;

    void init(){
        root=0;treapsz=0;
    }

    void push_up(node * o){
        o->s=o->cnt;
        if(o->ch[0]) o->s+=o->ch[0]->s;
        if(o->ch[1]) o->s+=o->ch[1]->s;
    }

    void init_node(node * x,int key){
        x->ch[0]=x->ch[1]=0;x->s=x->cnt=1;
        x->key=key,x->v=rand();
    }

    inline int Get_idx(node * f){
        return f-nt;
    }
    // d = 0 , Left - rotate ; d = 1 , right - rotate
    inline void rotate(node * & o , int d){
        node * f = o->ch[d^1];
        o->ch[d^1] = f->ch[d] , f->ch[d] = o;
        push_up(o) ; push_up(f);
        o = f;
    }

    void process_insert(node *& u , int x){
        if(!u){
            init_node(nt + Q[--sz] , x );
            u = nt + Q[sz];
        }
        else if(u->key == x){
            u->cnt ++ ;
        }
        else{
            int d = x < u->key ? 0 : 1;
            process_insert(u->ch[d],x);
            if(u->ch[d]->v > u->v) rotate( u , d ^ 1 );
        }
        push_up(u);
    }

    void process_remove(node *&u ,int x){
        if(!u){
            treapsz++;
            return;
        }
        int d = u->cmp(x);
        if(d==-1){
            if (u->ch[0] && u->ch[1]){
                int d = u->ch[0]->v > u->ch[1]->v ? 1 : 0;
                rotate( u , d );
                process_remove( u -> ch[d] , x);
            }
            else{
                int d2;
                if(!u->ch[0]) d2 = 1;
                else d2 = 0;
                u->cnt--;
                if(!u->cnt){
                    Q[sz++] = Get_idx(u);
                    u = u->ch[d2];
                }
            }
        }
        else process_remove( u->ch[d] , x );
        if(u) push_up(u);
    }

    // 带入参数 find (trep.root , x )
    // 在treap中查找元素 x , 查找成功返回true , 失败返回false
    bool find(node * o ,int x){
        while(o){
            int d = o->cmp(x);
            if(d==-1) return true;
            o=o->ch[d];
        }
        return false;
    }

    //插入某个元素 x
    void insert(int x){
        process_insert(root,x);
        treapsz++;
    }

    //删除某个元素 x ,若 x 不存在无影响
    void remove(int x){
        process_remove(root,x);
        treapsz--;
    }

    //返回 treap 目前的节点数目
    int size(){
        return treapsz;
    }

    //找第 k 大的元素，未找到则返回-1
    int kth(int k){
        node * u = root;
        while(u && u->s>=k && k >= 1){
            int s = u->ch[1] ? u->ch[1]->s : 0;
            if(k>=s+1&&k<=s+u->cnt) return u->key;
            else if(k<=s) u = u -> ch[1];
            else{
                k -= (s + u->cnt);
                u=u->ch[0];
            }
        }
        return -1;
    }

    //计算严格小于 x 的数的数量
    int count_less(int x){
        node * o = root;
        int s = 0;
        while(o){
            int d = o->cmp(x);
            if(d==1) s += o->ch[0]?o->ch[0]->s+o->cnt:o->cnt;
            else if(d==-1) s += o->ch[0]?o->ch[0]->s:0;
            if(d==-1) break;
            o=o->ch[d];
        }
        return s;
    }

    //获取某个数的 rank
    //某个数的rank定义为 严格小于这个数的数目 + 1
    int rank(int x){
        return count_less(x) + 1;
    }
};

int a[MAX_N];
int N;

struct BlockArray{
	int blockSize,blockNum;
	struct Block{
		int L,R;
		Treap tr;
		Block(){}
		Block(int l,int r):L(l),R(r){
			tr.init();
		}
	}Ar[MAX_S];
	BlockArray(){
		blockSize=sqrt(N)+1;
		blockNum=0;
		for(int i=1;i<=N;i+=blockSize){
			Ar[++blockNum]=Block(i,i+blockSize-1);
		}
	}
	int getInd(int i){
		return (i-1)/blockSize+1;
	}
	void build(){
		for(int i=1;i<=N;i++)
			Ar[getInd(i)].tr.insert(a[i]);
	}
	//change a[t] to x
	void update(int t,int x){
		int i=t;
		t=getInd(t);
		Ar[t].tr.remove(a[i]);
		Ar[t].tr.insert(x);
		a[i]=x;
	}
	//How many numbers are less than x from l to r
	int query(int l,int r,int x){
		int res=0;
		for(int i=getInd(l);i<=getInd(r);i++){
			if(l<=Ar[i].L&&Ar[i].R<=r)
				res+=Ar[i].tr.count_less(x);
			else{
				int s=max(l,Ar[i].L),t=min(r,Ar[i].R);
				for(int j=s;j<=t;j++)if(a[j]<x)res++;
			}
		}
		return res;
	}
}block;

int M;
int T;

struct Qu{
	char op[2];
	int s,t,x;
}allOp[MAX_M];

vector<int> vec;
int Hash[MAX_N+MAX_M];

int main(){
	//freopen("data.txt","r",stdin);
	//freopen("WA.txt","w",stdout);
	scanf("%d",&T);
	while(T--){
		vec.clear();
		scanf("%d%d",&N,&M);
		for(int i=1;i<=N;i++){
			scanf("%d",&a[i]);
			vec.push_back(a[i]);
		}
		for(int i=1;i<=M;i++){
			scanf("%s",allOp[i].op);
			if(allOp[i].op[0]=='Q')scanf("%d%d%d",&allOp[i].s,&allOp[i].t,&allOp[i].x);
			else{
				scanf("%d%d",&allOp[i].t,&allOp[i].x);
				vec.push_back(allOp[i].x);
			}
		}
		sort(vec.begin(),vec.end());
		for(int i=1;i<=N;i++){
			int tmp=a[i];
			a[i]=lower_bound(vec.begin(),vec.end(),a[i])-vec.begin();
			Hash[a[i]]=tmp;
		}
		for(int i=1;i<=M;i++)
			if(allOp[i].op[0]=='C'){
				int tmp=allOp[i].x;
				allOp[i].x=lower_bound(vec.begin(),vec.end(),tmp)-vec.begin();
				Hash[allOp[i].x]=tmp;
			}
		init();
		block=BlockArray();	
		block.build();
		//cout<<block.blockSize<<endl;
		for(int i=1;i<=M;i++){
			if(allOp[i].op[0]=='Q'){
				int l=-1,r=MAX_N+MAX_M;
				while(r-l>1){
					int m=(r+l)>>1;
					if(block.query(allOp[i].s,allOp[i].t,m)<=allOp[i].x-1)
						l=m;
					else 
						r=m;
				}
				printf("%d\n",Hash[l]);
			}
			else
				block.update(allOp[i].t,allOp[i].x);
		}
	}
	return 0;
}


