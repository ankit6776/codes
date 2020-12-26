#pragma GCC optimize("Ofast,unroll-loops,no-stack-protector,fast-math")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
 
#include<bits/stdc++.h>
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<string>
 
using namespace std;
 
const int MAX_N = int(1e6) + 10;
const long long int MOD=1e9+7;
const long long int INF=1e18;
 
typedef long long int ll;
typedef unsigned long long int llu;


struct fenwick{
  int lim;
  long long int *tree;
  fenwick(int _lim){
      lim=_lim;
      tree=new long long int[lim];
  }
  void init(){
    for(int i=0;i<lim;i++){
      tree[i]=0;
    }
  }
  void update(int x,long long int v){
    while(x<lim){
      tree[x]+=v;
      x+=x&(-x);
    }
  }
  long long int query(int x){
    long long int ans=0;
    while(x>0){
      ans+=tree[x];
      x-=x&(-x);
    }
    return ans;
  }
  int _query(int k){
    int low=1;
    int high=500000;
    int ans=0;int x=k;
    while(low<=high){
      int mid=low+(high-low)/2;
      if(query(mid)>=x){
        ans=mid;
        high=mid-1;
      }else{
        low=mid+1;
      }
    }
    return ans;
  }
};
struct z_function{
  string &txt;
  int *z;
  z_function(string &_txt):txt(_txt){
    z=new int[1+txt.length()];
  }
  void cal(){
    z[0]=0;
    int l=0;
    int r=0;
    for(int i=1;i<txt.length();i++){
    //  cout<<l<<" "<<r<<endl;
      if(i>r){
        l=i;
        r=i;
        while(r<txt.length() && txt[r]==txt[r-l]){
          r++;
        }
      //  cout<<r<<" ";
        z[i]=r-l;
        r=r-1;
      }else{
              if(z[i-l]<r-i+1)
                z[i]=z[i-l];
              else{
                l=i;
                while(r<txt.length() && txt[r]==txt[r-l]){
                  r++;
                }
                z[i]=r-l;
                r=r-1;
              }
      }
    }
  }
};
/*
struct palindromic_tree{
  map<char,struct palindromic_tree*>m;
  int length;
  int end_indx;
  struct palindromic_tree* suffix;
  palindromic_tree(int _length,int _end_indx){
    length=_length;
    end_indx=_end_indx;
  }
};
class palindromic_string{
public:
  string &s;
  struct palindromic_tree* real_root;
  struct palindromic_tree* imaginary_root;
  struct palindromic_tree* curr;
  long long int *prefix;
  palindromic_string(string &_s):s(_s){
       real_root=new palindromic_tree(0,-1);
       imaginary_root=new palindromic_tree(-1,-1);
       curr=real_root;
       real_root->suffix=imaginary_root;prefix=new long long int[1+s.length()];
       imaginary_root->suffix=imaginary_root;
  }
  void add(char ch){
    int indx=s.size();
    struct palindromic_tree* temp=curr;
    s+=ch;
    while(indx-temp->length-1<0 || s[indx-temp->length-1]!=s[indx])
      temp=temp->suffix;
    if((temp->m).find(ch)!=(temp->m).end()){
      curr=(temp->m)[ch];
      return;
    }else{
      curr=new palindromic_tree((temp->length)+2,indx);
    }
 
    (temp->m)[ch]=curr;
 
    if(curr->length==1){
      curr->suffix=real_root;
      return;
    }else{
      temp=temp->suffix;
      while(indx-temp->length-1<0 || s[indx-temp->length-1]!=s[indx])
        temp=temp->suffix;
      curr->suffix=(temp->m)[ch];
    }
  }
 
  void cal(){
    prefix[0]=0;
    long long int p=29LL;
    for(int i=0;i<s.length();i++){
      prefix[i+1]=(prefix[i]+(p*s[i]))%MOD;
      p=(p*p)%MOD;
    }
  }
};
struct prime_numbers{
  int *seive;
  int len;
  prime_numbers(int _len){
    len=_len;
    seive=new int[len+1];
  }
  void init(){
    seive[0]=1;
    seive[1]=1;
  }
  void cal(){
    for(int i=2;i*i<=len;i++){
      for(int j=i*i;j<=len;j+=i){
        seive[j]=1;
      }
    }
  }
};
*/
inline ll mul(ll a,ll b){
  a=(a+MOD)%MOD;
  b=(b+MOD)%MOD;
  ll c=a*b;
  c=(c+MOD)%MOD;
  return c;
}
inline ll add(ll a,ll b){
  a=(a+MOD)%MOD;
  b=(b+MOD)%MOD;
  ll ans=(a+b);
  ans=(ans+MOD)%MOD;
  return ans;
}

ll power(ll a,ll b,ll c){
  ll ans=1;
  while(b){
    if(b&1){
      ans=mul(ans,a);
    }
    a=mul(a,a);
    b=b/2;
  }
  return ans;
}
template<class T1, class T2>
istream &operator>>(istream &in, pair<T1, T2> &P){
  in >> P.first >> P.second;
  return in;
}
 
template<class T1, class T2>
ostream &operator<<(ostream &out, const pair<T1, T2> &P){
  out << "(" << P.first << ", " << P.second << ")";
  return out;
}
template<class T>
istream &operator>>(istream &in, vector<T> &arr){
  for(auto &x: arr) in >> x;
  return in;
}
template<class T>
ostream &operator<<(ostream &out, const vector<T> &arr){
  for(auto &x: arr) out << x << ' '; cout << "\n";
  return out;
}
template<class T>
istream &operator>>(istream &in, deque<T> &arr){
  for(auto &x: arr) in >> x;
  return in;
}
template<class T>
ostream &operator<<(ostream &out, const deque<T> &arr){
  for(auto &x: arr) out << x << ' '; cout << "\n";
  return out;
}
mt19937 rnd(time(0));
struct sparse{
  int table[200005][25];
  int n;
  sparse(int len1):n(len1){
  }
  void init(int *a){
 
    for(int i=1;i<=n;i++){
      table[i][0]=a[i];
    }
 
   // cout<<table[1][0]<<endl;
 
    for(int j=1;j<25;j++){
      for(int i=1;i<=n;i++){
        if(i+(1<<j)-1<=n){
          table[i][j]=__gcd(table[i][j-1],table[i+(1<<(j-1))][j-1]);
        }
      }
    }
  }
  int find(int *a,int start,int end){
    int dis=end-start+1;
    int g=0;
    for(int j=25;j>=0;j--){
      if(dis&(1<<j)){
     //     cout<<dis<<" "<<table[start][j]<<" "<<j<<endl;
          g=__gcd(g,table[start][j]);
          start=start+(1<<j);
      }
    }
    return g;
  }
};
inline ll gcd(ll a,ll b){
  while(b)a%=b,swap(a,b);
  return a;
}
// vector<pair<int,int> >v[1000005];
// ll t[1000005];ll h[1000005]; ;;;;;;multiset<pair<ll,pair<int,pair<ll,ll> > > >s;ll A,B;bool vis[1000005];ll dis[1000005];int parent[1000005];vector<int>ans;
// ll c[1000005];
 
struct SOS{
  ll *dp;
  int limit;
  vector<int>&arr;
 
  SOS(int _limit,vector<int>&v):arr(v){
 
    limit=_limit;
    dp=new ll[(1<<limit)+10];
  }
 
  void init(){
    for(int i=0;i<(1<<limit);i++){
      dp[i]=0;
    }
    for(int i=0;i<arr.size();i++){
       dp[arr[i]]++;
    }
  }
 
  void build1(){
    for(int i=0;i<limit;i++){
      for(int j=0;j<(1<<limit);j++){
        if(j&(1<<i)){
          dp[j]=add(dp[j],dp[j^(1<<i)]);
      }
    }
  }
 }
  void build2(){
    for(int i=0;i<limit;i++){
      for(int j=(1<<limit)-1;j>=0;j--){
        if(j&(1<<i)){
          dp[j^(1<<i)]=add(dp[j^(1<<i)],dp[j]);
        }
      }
    }
  }
// }
 
};
 
// string s;
int find(int arr[],int x)
{
    while(x!=arr[x])
    {
        x=arr[x];
    }
 
    return x;
}
 
void connect(int x,int arr[],int size[],int comp[],int y)
{
    int rootA=find(arr,x);
    int rootB=find(arr,y);
    if(rootA==rootB)return;
 
    if(size[rootA]<size[rootB])
    {
        arr[rootA]=rootB;
        size[rootB]+=size[rootA];
        comp[rootB]=min(comp[rootA],comp[rootB]);
    }else{
        arr[rootB]=rootA;
        size[rootA]+=size[rootB];
        comp[rootA]=min(comp[rootA],comp[rootB]);
    }
 
 
}
struct lazylam{
  ll *tree;
  int n;
  lazylam(int size):n(size){
    tree=new ll[4*n+1];
 
  }
  void init(){
    for(int i=0;i<=4*n;i++){
     tree[i]=0;
    }
  }
  void update(int x,ll v){
    upd(1,1,n,x,v);
  }
  void upd(int nd,int st,int en,int x,ll v){
    if(st==en){
      tree[nd]+=v;
      return;
    }
    int mid=(st+en)/2;
    if(x<=mid){
      upd(2*nd,st,mid,x,v);
    }else{
      upd(2*nd+1,mid+1,en,x,v);
    }
 
    tree[nd]=tree[2*nd]+tree[2*nd+1];
  }
};
struct graph{
  vector<int> *v;
  int n;
  long long int *values;
  vector<ll> v2;
  int *start;
  int *end;
  graph(int size):n(size){
    v=new vector<int>[n+1];
    values=new ll[n+1];
    v2.resize(n+1);
    for(int i=1;i<n;i++){
      int x,y;
      cin>>x>>y;
      v[x].push_back(y);
      v[y].push_back(x);
    }
    for(int i=1;i<=n;i++){
      cin>>values[i];
    }
  }
  void dfs(){
    int gtime=0;
    start=new int[n+1];
    end=new int[n+1];
    dfs_start_end(1,0,gtime);
  }
  void dfs_start_end(int i,int p,int &gtime){
       gtime++;
       start[i]=gtime;
       v2[gtime]=(values[i]);
       for(auto it:v[i]){
        if(it!=p){
          dfs_start_end(it,i,gtime);
        }
       }
       end[i]=gtime;
  }
};
struct node{
  int x,y,z,p;
  node():x(0),y(0),z(0),p(0){}
  node(int xx,int yy,int zz,int pp):x(xx),y(yy),z(zz),p(pp){}
};
int main()
{
  char c; cin>>c;
  if(c<=90)cout<<'A';
  else cout<<'a';
  return 0;
}
