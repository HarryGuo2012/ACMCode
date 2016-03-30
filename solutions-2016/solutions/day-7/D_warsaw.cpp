#include <bits/stdc++.h>

using namespace std;
#define MP make_pair
#define PB push_back
#define LL long long
#define int LL
#define PII pair<int,int>
#define VI vector<int>
#define FI first
#define SE second
#define st FI
#define nd SE
#define FOR(i,a,b) for (int i = (a); i <= (b); i++)
#define REP(i,n) FOR(i,0,(int)(n)-1)
#define RE(i,n) FOR(i,1,n)
#define R(i,n) REP(i,n)
#define ALL(x) (x).begin(), (x).end()
#define SZ(x) ((int)(x).size())
#define LD long double

template<class C> void mini(C& _a4, C _b4) { _a4 = min(_a4, _b4); }
template<class C> void maxi(C& _a4, C _b4) { _a4 = max(_a4, _b4); }

template<class TH> void _dbg(const char *sdbg, TH h) { cerr << sdbg << "=" << h << endl; }
template<class TH, class... TA> void _dbg(const char *sdbg, TH h, TA... a) {
  while(*sdbg != ',')cerr << *sdbg++; cerr << "=" << h << ","; _dbg(sdbg+1, a...);
}

#ifdef LOCAL
#define debug(...) _dbg(#__VA_ARGS__, __VA_ARGS__)
#define debugv(C) {cout<<#C<<"="; for(auto&cc:C)cerr<<cc<<",";cerr<<endl;}
#else
#define debug(...) (__VA_ARGS__)
#define debugv(C) {}
#define cerr if(0)cout
#endif

#define MAX 200010

struct ciag{
  int a,il,b;
  bool add(int x){
    if(il == 1){
      b = x-a;
      il = 2;
      return 1;
    }
    if(a + il * b == x){
      il++;
      return 1;
    }
    return 0;
  }
  int ost(){
    return a + (il-1) * b;
  }
};

int exgcd(int a,int b,int &x,int &y){
  if(a < b)return exgcd(b,a,y,x);
  if(b==0){
    x = 1;
    y = 0;
    return a;
  }
  int xp;
  int pom=exgcd(b,a%b,xp,x);
  y=xp-x*(a/b);
  return pom;
}

int floordiv(int a, int b) {
  if (b < 0) { a = -a; b = -b; }
  int d = a / b, m = a - d * b;
  if (m < 0) { d--; }
  return d;
}

int ceildiv(int a, int b) {
  int r = floordiv(a, b);
  if (a % b != 0) { r++; }
  return r;
}

ciag marek(ciag a,ciag b){
  ciag wynik;
  int n, m, da = b.a - a.a;
  int g = exgcd(a.b, b.b, n, m);
  //debug(a.b, b.b, n, m);
  
  if (da % g != 0) { return {1,0,1}; }
  n *= (da / g);
  //debug(n);
  
  wynik.b = a.b / g * b.b;
  int elem = a.a + a.b * n;
  int maxA = a.ost(), maxB = b.ost();
  
  int minIle = max(ceildiv(a.a - elem, wynik.b),
                   ceildiv(b.a - elem, wynik.b));
  int maxIle = min(floordiv(maxA - elem, wynik.b),
                   floordiv(maxB - elem, wynik.b));
  
  if (minIle > maxIle) { return {1,0,1}; }
  wynik.a = elem + minIle * wynik.b;
  wynik.il = maxIle - minIle + 1;
  
  return wynik;
}

vector<vector<ciag>> ciagi[MAX];
int n,q;
vector<pair<PII,int>> x;
string z;
vector<int> wys[MAX];
int kmr[19][MAX];
void mapuj(int j){
  sort(ALL(x));
  int id = 0;
  R(i,SZ(x)){
    if(i && x[i-1].FI != x[i].FI)id ++;
    kmr[j][x[i].SE] = id;
    wys[id].PB(x[i].SE);
  }
  ciagi[j].resize(id+1);
  R(i,id+1){
    for(int el:wys[i]){
      if(ciagi[j][i].empty() || !ciagi[j][i].back().add(el))
        ciagi[j][i].PB({el,1,0});
    }
    wys[i].clear();
  }
}
void licz_kmr(){
  R(i,n)
    x.PB({{(int)z[i],0},i});
  mapuj(0);
  int krok = 1;
  int j = 0;
  while(krok < n){
    x.clear();
    R(i,n-krok){
      x.PB({{kmr[j][i],kmr[j][i+krok]},i});
    }
    mapuj(++j);
    krok *= 2;
  }
}
int pierw(int j,int typ,int pocz){
  int po = -1;
  int ko = SZ(ciagi[j][typ]);
  while(po+1 != ko){
    int m = (po+ko)/2;
    if(ciagi[j][typ][m].ost() >= pocz){
      ko = m;
    }else
      po = m;
  }
  return ko;
}

ciag przetnij(ciag xx,ciag y,int a,int b,int k){
  xx.a = b - xx.ost();
  y.a = k + y.a - a;
  if(xx.il == 1)xx.b = 1;
  if(y.il == 1)y.b = 1;
  return ciag(marek(xx,y));
}

bool spr(int a,int b,int j){
  int k = 1 << j;
  int aa = kmr[j][a];
  int bb = kmr[j][b-k];
  int pa = pierw(j,aa,b-2*k);
  int pbb = pierw(j,bb,a);
  int res = 0;
  while(pa < SZ(ciagi[j][aa])){
    if(ciagi[j][aa][pa].a > b - k)
      break;
    int pb = pbb;
    while(pb < SZ(ciagi[j][bb])){
      if(ciagi[j][bb][pb].a > a + k){
        break;
      }
      ciag pom = przetnij(ciagi[j][aa][pa],ciagi[j][bb][pb],a,b,k);
      if(pom.il != 0){
        int wyn = pom.ost();
        int lim = min(2*k,b-a-1);
        if(wyn > lim){
          int cof = (wyn - lim + pom.b -1) / pom.b;
          wyn -= cof * pom.b;
        }
        if(pom.a <= wyn)
          maxi(res,wyn);
      }
      pb++;
    }
    pa++;
  }
  if(res >= k){
    cout << res << "\n";
    return 1;
  }
  return 0;
}

void zap(int a,int b){
  int j = 0;
  int dl = b-a;
  while((1<<(j+1)) < dl)j++;
  while(j >= 0 && !spr(a,b,j))j--;
  if(j == -1){
    cout << 0 << "\n";
  }
}


void testuj_marek() {
  int a1, b1, il1, a2, b2, il2;
  cin >> a1 >> il1 >> b1 >> a2 >> il2 >> b2;
  ciag a{a1,il1,b1};
  ciag b{a2,il2,b2};
  ciag xx = marek(a, b);
  
  cout << xx.a << " " << xx.il << " " << xx.b << endl;
}


#undef int
int main() {
#define int LL
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout << fixed << setprecision(11);
  cerr << fixed << setprecision(11);
  
  cin >> n >> q >> z;
  licz_kmr();
  R(i,q){
    int a,b;
    cin >> a >> b;
    zap(a-1,b);
  }
  
  return 0;
}
