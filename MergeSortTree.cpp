class Solution {
public:
    
    //Generalize Merge Sort Tree Implementation
    // https://leetcode.com/problems/count-number-of-rectangles-containing-each-point/
    
    
    // Constraints:

    // 1 <= rectangles.length, points.length <= 5 * 104
    // rectangles[i].length == points[j].length == 2
    // 1 <= li, xj <= 1e9
    // 1 <= hi, yj <= 1e9. .... /**Extended constraints.**/
    // All the rectangles are unique.
    // All the points are unique.
    vector<pair<int, int> > vv[1000000];
    void build(vector<pair<int,int> > &v, int st, int en, int ind){
        if(st==en){
            vector<pair<int,int> > pp;
            pp.push_back(make_pair(v[st].second, v[st].first));
            vv[ind] = pp;
            return;
        }
        int mid = (st+en)/2;
        build(v, st, mid, 2*ind);
        build(v, mid+1, en, 2*ind+1);
        vv[ind].resize(en-st+1);
        merge(vv[2*ind].begin(), vv[2*ind].end(), vv[2*ind+1].begin(), vv[2*ind+1].end(), vv[ind].begin());
    }
    
    int f(int st, int en, int l1, int r1, int ind, int val){
        if(st>r1||en<l1){
            return 0;
        }
        if(st>=l1&&en<=r1){
            return vv[ind].size() - (lower_bound(vv[ind].begin(), vv[ind].end(), make_pair(val, 0)) - vv[ind].begin());
        }
        int mid = (st+en)/2;
        return f(st, mid, l1, r1, 2*ind, val) + f(mid+1, en, l1, r1, 2*ind+1, val);
    }
    vector<int> countRectangles(vector<vector<int>>& r, vector<vector<int>>& p) {
        set<int> ss;
        for(int i=0;i<r.size();++i){
            ss.insert(r[i][0]);
            ss.insert(r[i][1]);
        }
        for(int i=0;i<p.size();++i){
            ss.insert(p[i][0]);
            ss.insert(p[i][1]);
        }
        map<int,int> mp;
        int j=1;
        for(auto x: ss){
            mp[x]=j++;
        }
        vector<pair<int,int> > v;
        for(int i=0;i<r.size();++i){
            int l1 = mp[r[i][0]];
            int l2 = mp[r[i][1]];
            v.push_back(make_pair(l1,l2));
        }
        sort(v.begin(),v.end());
        build(v, 0, v.size()-1, 1);
        vector<int> res;
        for(int i=0;i<p.size();++i){
            int l1 = mp[p[i][0]];
            int l2 = mp[p[i][1]];
            int ind = lower_bound(v.begin(),v.end(), make_pair(l1, 0)) - v.begin();
            if(ind == v.size()) {
                res.push_back(0);
                continue;
            }
            res.push_back(f(0, v.size()-1, ind, v.size()-1, 1, l2));
        }
        return res;
        
        
    }
};
