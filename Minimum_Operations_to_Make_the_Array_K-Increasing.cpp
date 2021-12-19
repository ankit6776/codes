class Solution {
public:
    int bb(int fi, int la, int x, vector<int> &hh, vector<int> &ss) {

    int mid;
    while(la > fi)
    {
        int mid = fi + (la - fi) / 2;
        if(hh[ss[mid]] > x)
            la = mid;
        else
            fi = mid + 1;
    }
    return fi; 
    }

    int ff( vector<int> &hh) {

        int i, k, ind;
        int n=hh.size();
        vector<int> ss;
        for(int i=0;i<n+1;++i)ss.push_back(0);
        ind = 1;
        ss[1] = 0;
        for (i = 1; i < n; i++) {

            if (hh[i] >= hh[ss[ind]]) {

                ind++;
                ss[ind] = i; 

            }
            else {
                k = bb(1, ind, hh[i], hh,ss);

                if (hh[ss[k]] >= hh[i]) { 
                    ss[k] = i;
                }
            }
        }
        return ind;
    }
    int f(vector<int> &v){
        return v.size()-ff(v);
    }
    int kIncreasing(vector<int>& arr, int k) {
        int ans = 0;
        int i=0;
        while(i<k) {
            vector<int> v;
            for(int j=i;j<arr.size();j=j+k){
                v.push_back(arr[j]);
            }
            ans = ans + f(v);
            v.clear();
            i++;
        }
        return ans;
    }
};
