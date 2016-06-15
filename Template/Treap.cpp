#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <ctime>
using namespace std;


// made by xiper
// updata time : 2015 / 11 / 25
// test status : ��

/*
ʹ�÷���:
  treap.init();  //�������,���ÿ��һ��treap�����ͱ������һ��
  init();   //�������,���ÿ��Caseֻ��Ҫ����һ��

  treap.insert( val ) // ����ֵval ,�����������ͬ��ֵ
  treap.kth( k ) // �ҵ� k ��ע���ǵ� k ��),����ʧ���򷵻�-1
  treap.remove( val ) // ɾ��ֵval��������������Ӱ��
  treap.size() // ����treap��Ŀǰ�ڵ�����
  treap.count_less(x) // ����treap���ϸ�С�� x ����Ŀ
  treap.rank(x) // ����ĳ������ rank , ĳ������ rank ����Ϊ �ϸ�С�������� + 1
*/


const static int TreapSize = 1e4 + 500;
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

//������� init() �����ڳ�ʼ����ʱ��,�ɵ��õľ�̬�ڴ���Q������,��һ��ջ
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

	// ������� find (trep.root , x )
	// ��treap�в���Ԫ�� x , ���ҳɹ�����true , ʧ�ܷ���false
	bool find(node * o ,int x){
		while(o){
			int d = o->cmp(x);
			if(d==-1) return true;
			o=o->ch[d];
		}
		return false;
	}

	//����ĳ��Ԫ�� x 
	void insert(int x){
		process_insert(root,x);
		treapsz++;
	}

	//ɾ��ĳ��Ԫ�� x ,�� x ��������Ӱ��
	void remove(int x){
		process_remove(root,x);
		treapsz--;
	}

	//���� treap Ŀǰ�Ľڵ���Ŀ
	int size(){
		return treapsz;
	}

	//�ҵ� k ���Ԫ�أ�δ�ҵ��򷵻�-1
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

	//�����ϸ�С�� x ����������
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

	//��ȡĳ������ rank
	//ĳ������rank����Ϊ �ϸ�С�����������Ŀ + 1
	int rank(int x){
		return count_less(x) + 1;
	}
}treap;


int main(int argc,char *argv[]){
	treap.init();init();
	int n;
	cin>>n;
	while(n--){
		int tt;
		cin>>tt;
		treap.insert(tt);
	}	
	return 0;
}
