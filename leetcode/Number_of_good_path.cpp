//https://leetcode.com/problems/number-of-good-paths/

// Template reference: https://github.com/ankit6776/CPP_LIBRARIES/blob/master/src/segTree.hpp
template<typename T> inline T Max(T a, T b){return a>b?a:b;}
template<typename T> inline T Min(T a, T b){return a<b?a:b;}
template<typename T> inline T __Gcd(T a, T b){ return b==0 ? a : __Gcd(b,a%b);}
template<typename T> struct SegTree {
    long long int N;
    vector<T> v;
    vector<T> seg;
    void init(int st, int end, int ind){
        if(st==end){
            seg[ind]=v[st];
            return;
        }
        int mid = (st+end)/2;
        init(st,mid,2*ind+1);
        init(mid+1,end, 2*ind+2);
        seg[ind]=f(seg[2*ind+1],seg[2*ind+2]);
    }
    T f(T a, T b){
        return a>b?a:b;

    }
    void pre() {
        seg.resize(4*N);
        init(0,N-1,0);
    }

    void point_update(int p, T x) {
        point_update_query(0,0,N-1,p,x);
    }

    T update_function(T x, T y){
        return f(x,y);
    }

    void point_update_query(int node, int st, int en, int ind, T x) {
        if(ind<st||ind>en)return;
        if(st==en) {
            seg[node] = update_function(seg[node], x);
            return;
        }
        int mid = (st+en)/2;
        ind<=mid ? point_update_query(2*node+1, st, mid, ind, x) : point_update_query(2*node+2, mid+1, en, ind, x);
        seg[node]=f(seg[2*node+1],seg[2*node+2]);
    }

    T query(int l,int r){
        return _query(0,l,r,0,N-1);
    }

    T _query(int node, int l,int r, int st,int en){
        if(l>en||r<st)return 0; // replace INF with zero for sum query
        if(st>=l&&en<=r)return seg[node];
        int mid = (st+en)/2;
        return f(_query(2*node+1,l,r,st,mid),_query(2*node+2,l,r,mid+1,en));
    }

};

class Solution {
public:
    
    vector<int> parent, depth, heavy, head, pos;
    int cur_pos;
    const static int N = 50000;
    set<int> g[N];
    int par[N],sub[N];
    int n;
    vector<int> vv[N];
    long long res = 0;

    /**
     * Use template like follow test code.
     * 
     * 
    #include<iostream>
    #include<../src/segTree.hpp>
    using namespace std;

    int main(){
        long long N; cin>>N;
        int q; cin>>q;
        const long long MOD = 1000000007;
        vector<long long> V(N);
        for(int i=0;i<N;++i)cin>>V[i];
        SegTree<long long> ss;
        ss.v = V;
        ss.N = N;
        ss.pre();
        while(q--){
            int l,r; cin>>l>>r;
            long long res = ss.query(l,r-1);
            cout<<res<<endl;
        }
    }
     * 
     * 
     * 
     * */
    
    // Heavy light decomposition: https://cp-algorithms.com/graph/hld.html#implementation

    int dfs(int v, vector<vector<int>> const& adj) {
        int size = 1;
        int max_c_size = 0;
        for (int c : adj[v]) {
            if (c != parent[v]) {
                parent[c] = v, depth[c] = depth[v] + 1;
                int c_size = dfs(c, adj);
                size += c_size;
                if (c_size > max_c_size)
                    max_c_size = c_size, heavy[v] = c;
            }
        }
        return size;
    }

    void decompose(int v, int h, vector<vector<int>> const& adj) {
        head[v] = h, pos[v] = cur_pos++;
        if (heavy[v] != -1)
            decompose(heavy[v], h, adj);
        for (int c : adj[v]) {
            if (c != parent[v] && c != heavy[v])
                decompose(c, c, adj);
        }
    }

    void init(vector<vector<int>> const& adj) {
        int n = adj.size();
        parent = vector<int>(n);
        depth = vector<int>(n);
        heavy = vector<int>(n, -1);
        head = vector<int>(n);
        pos = vector<int>(n);
        cur_pos = 0;

        dfs(0, adj);
        decompose(0, 0, adj);
    }

    int query(int a, int b, SegTree<int> ss) {
        int res = 0;
        for (; head[a] != head[b]; b = parent[head[b]]) {
            if (depth[head[a]] > depth[head[b]])
                swap(a, b);
            int cur_heavy_path_max = ss.query(pos[head[b]], pos[b]);
            res = max(res, cur_heavy_path_max);
        }
        if (depth[a] > depth[b])
            swap(a, b);
        int last_heavy_path_max = ss.query(pos[a], pos[b]);
        res = max(res, last_heavy_path_max);
        return res;
    }

    /**
     *  Centroid decomposition part and lca preprocess
     * */


    // void dfs0(int u)
    // {
    // 	for(auto it=g[u].begin();it!=g[u].end();it++)
    // 		if(*it!=DP[0][u])
    // 		{
    // 			DP[0][*it]=u;
    // 			level[*it]=level[u]+1;
    // 			dfs0(*it);
    // 		}
    // }
    // void preprocess()
    // {
    // 	level[0]=0;
    // 	DP[0][0]=0;
    // 	dfs0(0);
    // 	for(int i=1;i<LOGN;i++)
    // 		for(int j=0;j<n;j++)
    // 			DP[i][j] = DP[i-1][DP[i-1][j]];
    // }
    // int lca(int a,int b)
    // {
    // 	if(level[a]>level[b])swap(a,b);
    // 	int d = level[b]-level[a];
    // 	for(int i=0;i<LOGN;i++)
    // 		if(d&(1<<i))
    // 			b=DP[i][b];
    // 	if(a==b)return a;
    // 	for(int i=LOGN-1;i>=0;i--)
    // 		if(DP[i][a]!=DP[i][b])
    // 			a=DP[i][a],b=DP[i][b];
    // 	return DP[0][a];
    // }
    // int dist(int u,int v)
    // {
    // 	return level[u] + level[v] - 2*level[lca(u,v)];
    // }


    // Centroid decomposition: https://threadsiiithyderabad.quora.com/Centroid-Decomposition-of-a-Tree
    int nn;
    void dfs1(int u,int p)
    {
        sub[u]=1;
        nn++;
        for(auto it=g[u].begin();it!=g[u].end();it++)
            if(*it!=p)
            {
                dfs1(*it,u);
                sub[u]+=sub[*it];
            }
    }
    int dfs2(int u,int p)
    {
        for(auto it=g[u].begin();it!=g[u].end();it++)
            if(*it!=p && sub[*it]>nn/2)
                return dfs2(*it,u);
        return u;
    }
    void decompose(int root,int p)
    {
        nn=0;
        dfs1(root,root);
        int centroid = dfs2(root,root);
        if(p==-1)p=centroid;
        par[centroid]=p;
        for(auto it=g[centroid].begin();it!=g[centroid].end();it++)
        {
            g[*it].erase(centroid);
            decompose(*it,centroid);
        }
        g[centroid].clear();
    }
  
    // Result function.
    void dfs3(set<int> g[], int src, int p, SegTree<int> ss, vector<int> &val) {
        map<int, int> mp;
        mp.clear();
        long long ff = 0;
        for(auto it = g[src].begin(); it!=g[src].end(); ++it) {
            if(*it!=p) {
                dfs3(g, *it, src, ss, val);
                for(auto x: vv[*it]) {
                    vv[src].push_back(x);
                    int max_value = query(x, src, ss);
                    if(max_value == val[x]) {
                        mp[max_value]++;
                    }
                    if(max_value == val[x] && max_value == val[src]) {
                        res++;
                    }
                }
            }
        }
        map<int,int> mp2;
        mp2.clear();
        for(auto it = g[src].begin(); it!=g[src].end(); ++it) {
            if(*it!=p) {
                mp2.clear();
                for(auto x: vv[*it]) {
                   int max_value = query(x, src, ss);
                    if(max_value == val[x]) {
                        mp2[max_value]++;
                    }
                }
                for(auto x: mp2) {
                    ff = ff + (x.second)*(mp[x.first]-x.second);
                }
            }
        }
        mp2.clear();
        mp.clear();
        res++;
        res = res + ff/2;
        vv[src].push_back(src);

    }
    
    int numberOfGoodPaths(vector<int>& val, vector<vector<int>>& edges) {
        n = val.size();
        vector<vector<int> > v(n);
        for(int i=0;i<edges.size();++i){
            int a=edges[i][0];
            int b=edges[i][1];
            v[a].push_back(b);
            v[b].push_back(a);
            g[a].insert(b);
            g[b].insert(a);
        }
        init(v);
        SegTree<int> ss;
        ss.N = n;
        vector<int> cd(n);
        for(int i=0;i<n;++i){
            cd[pos[i]]=val[i];
        }
        ss.v = cd;
        ss.pre();
        
        decompose(0,-1);
        int centroid = -1;
        for(int i=0;i<n;++i){
            g[i].clear();
        }
        for(int i=0;i<n;++i){
            if(par[i]!=i){
                g[i].insert(par[i]);
                g[par[i]].insert(i);
            } else centroid = i;
        }
        dfs3(g, centroid, centroid, ss, val);
        return res;
    }
};
