
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
