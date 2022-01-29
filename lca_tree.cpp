#include <bits/stdc++.h>
using namespace std;

/*
https://www.spoj.com/problems/LCA/
https://judge.yosupo.jp/problem/lca
*/
void dfs(vector<int> v[], int level[], int src, int dis = 0){
    level[src]=dis;
   // cout<<src<<" "<<"here"<<endl;
    for(auto x: v[src]){
        dfs(v,level, x, dis+1);
    }
}
void solve(int test_number){
    int n; cin>>n;
    vector<int> v[n+1];
    int par[n+1][25];
    for(int i=0;i<=n;++i){
        par[i][0]=i;
    }
    for(int i=1;i<=n;++i){
        int _zs; cin>>_zs;
        for(int j=0;j<_zs;++j){
            int x; cin>>x;
            v[i].push_back(x);
            par[x][0]=i;
        }
    }
    for(int j=1;j<25;++j){
        for(int i=1;i<=n;++i){
            par[i][j]=par[par[i][j-1]][j-1];
        }
    }
    int root; 
    for(int i=1;i<=n;++i)if(par[i][0]==i)root=i;
    int level[n+1];
    memset(level,-1,sizeof(level));
    dfs(v, level, root);
    int q; cin>>q;
    cout<<"Case "<<test_number<<":"<<endl;
    while(q--){
        int u,w;
        cin>>u>>w;
        if(level[u]<level[w]){
            swap(u,w);
        }
        if(level[u]!=level[w]){
            for(int j=20;j>=0;--j){
                if(level[u]==level[w])break;
                int xx = par[u][j];
                if(level[xx] >= level[w]){
                    u = xx;
                }
            }
        }
        if(u==w){
            cout<<u<<endl;
            continue;
        }
        for(int j=20;j>=0;--j){
            if(par[u][j]!=par[w][j]){
                u = par[u][j];
                w = par[w][j];
            }
        }
        cout<<par[u][0]<<endl;
    }
    
}

void solve(){
    int n; cin>>n;
    int q; cin>>q;
    vector<int> v[n+1];
    int par[n+1][26];
    for(int i=0;i<=n;++i){
        par[i][0]=i;
    }
    for(int i=1;i<n;++i){
        int b; cin>>b;
        v[b+1].push_back(i+1);
        par[i+1][0]=b+1;
    }
    for(int j=1;j<=25;++j){
        for(int i=1;i<=n;++i){
            par[i][j]=par[par[i][j-1]][j-1];
        }
    }
    int root; 
    for(int i=1;i<=n;++i)if(par[i][0]==i)root=i;
    //cout<<root<<endl;
    int level[n+1];
    memset(level,-1,sizeof(level));
    dfs(v, level, 1);
    //int q; cin>>q;
   // cout<<"Case "<<test_number<<":"<<endl;
    while(q--){
        int u,w;
        cin>>u>>w;
        u++;
        w++;
        if(level[u]<level[w]){
            swap(u,w);
        }
        if(level[u]!=level[w]){
            for(int j=25;j>=0;--j){
                if(level[u]==level[w])break;
                int xx = par[u][j];
                if(level[xx] >= level[w]){
                    u = xx;
                }
            }
        }
        if(u==w){
            cout<<u-1<<endl;
            continue;
        }
        for(int j=25;j>=0;--j){
            if(par[u][j]!=par[w][j]){
                u = par[u][j];
                w = par[w][j];
            }
        }
        cout<<par[u][0]-1<<endl;
    }
    
}

int main() {
	// your code goes here
	int t; cin>>t;
	for(int i=1;i<=t;++i){
	    solve(i);
	}
  /* solve(); */
  return 0;
}
