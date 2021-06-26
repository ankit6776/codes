#include <bits/stdc++.h>
using namespace std;
using cd = complex<double>;
const double PI = acos(-1);
 
void fft(vector<cd> &v, bool invert){
    if(v.size()==1)return;
    vector<cd> a,b;
    for(int i=0;2*i<v.size();++i){
        a.push_back(v[2*i]);
        b.push_back(v[2*i+1]);
    }
    fft(a,invert);
    fft(b,invert);
    int n = v.size();
    cd w(1);
    double angle = 2*PI/n;
    cd wn(cos(angle),(invert ? -1 : 1)*sin(angle));
    for(int i=0;2*i<n;++i){
        v[i]=a[i]+w*b[i];
        v[i+n/2] = a[i]-w*b[i];
        w*=wn;
        if(invert){
            v[i]/=2;
            v[i+n/2]/=2;
        }
    }
    
}
vector<long long> mul(vector<int> &a, vector<int> &b){
    vector<cd> fa(a.begin(),a.end());
    vector<cd> fb(b.begin(),b.end());
    int n=1;
    while(n<fa.size()+fb.size()){
        n<<=1;
    }
    fa.resize(n);
    fb.resize(n);
    fft(fa, false);
    fft(fb, false);
    for(int i=0;i<fa.size();++i){
        fa[i]*=fb[i];
    }
    fft(fa,true);
    vector<long long> res;
    for(int i=0;i<fa.size();++i){
        res.push_back(round(fa[i].real()));
    }
    return res;
}
int main() {
    int t; cin>>t;
    while(t--){
        int n; cin>>n;
        vector<int> a(n+1),b(n+1);
        for(int i=0;i<=n;++i)cin>>a[i];
        for(int i=0;i<=n;++i)cin>>b[i];
        vector<long long> c = mul(a,b);
        for(int i=0;i<c.size()&&i<2*n+1;++i){
            cout<<c[i]<<" ";
        }
        cout<<endl;
    }
	return 0;
}
