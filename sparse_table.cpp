template <class T = int> class sparse_table { // 0-indexed
    int lg(int x) {
        int lo = 0, hi = 30, ans;
        while(lo <= hi) {
            int mid = lo + hi >> 1;
            if((1 << mid) <= x) {
                ans = x;
                lo = mid + 1;
            } else hi = mid - 1;
        }
        return ans;
    }

    T op(T a, T b) {
        return gcd(a, b);
    }
 
    int n;
    vector<vector<T>> st;

public:    
    sparse_table() {}
 
    sparse_table(vector<T> v) {
        n = v.size();
        st = vector<vector<T>>(log2(n)+1, vector<T>(n));
        st[0] = v;
        for (int i=1; i<st.size(); i++) {
            for (int j=0; j+(1<<i)<=n; j++) st[i][j] = op(st[i-1][j], st[i-1][j+(1<<(i-1))]);
        }
    } 
 
    T query(int l, int r) { // inclusive range
        if(l > r) return 0;
        int sz = log2(r-l+1);
        return op(st[sz][l], st[sz][r-(1<<sz)+1]);
    }
};