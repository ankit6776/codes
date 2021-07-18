struct trie{
    struct trie* par;
    struct trie* left;
    struct trie* right;
};

void print(struct trie *rr){
    int cnt=0;
    while(rr!=NULL &&(rr->left || rr->right)){
        if(rr->left!=NULL){
            cout<<0;
            rr=rr->left;
        }
        else if(rr->right!=NULL){
            cout<<1;
            rr=rr->right;
        }
    }
}
struct trie* insert(struct trie *rr, int x){
    struct trie *zz = rr;
    for(int j=20;j>=0;--j){
        int ll = (1<<j)&x;
        if(ll){
            if(rr->right!=NULL)rr=rr->right;
            else{
                struct trie *xx = new trie();
                xx->par = rr;
                rr->right = xx;
                xx->left = NULL;
                xx->right = NULL;
                rr=xx;
            }
        }
        else{    
            if(rr->left!=NULL)rr = rr->left;
            else{
                struct trie *xx = new trie();
                xx->par = rr;
                rr->left = xx;
                xx->left = NULL;
                xx->right = NULL;
                rr=xx;
            }
        }
    }
    return zz;
}
struct trie* del(struct trie *rr, int x){
    struct trie* zz=rr;
    int i=20;
    while(i>=0&&(rr->left||rr->right)){
        if(x&(1<<i))rr=rr->right;
        else rr=rr->left;
        i--;
    }
    while(rr!=NULL && rr->left==NULL and rr->right == NULL){
       // cout<<"hello\n";
        struct trie *pp = rr;
        rr = rr->par;
        if(rr==NULL){
            return zz;
        }
        if(rr->left==pp)rr->left=NULL;
        if(rr->right==pp)rr->right = NULL;
    }
    return zz;
}
int f(struct trie *rr, int x){
    int ans = 0;
    for(int i=20;i>=0;--i){
        int zz=(1<<i)&x;
        if(zz){
            if(rr->left!=NULL){
                rr=rr->left;
                ans = ans + (1<<i);
            }
            else {
                if(rr->right!=NULL){
                    rr=rr->right;
                }
            }
        }
        else{
            if(rr->right!=NULL){
                rr=rr->right;
                ans = ans + (1<<i);
            }
            else{
                if(rr->left!=NULL)rr=rr->left;
            }
        }
    }
    return ans;
}
