class Solution {
public:
    static const long long MOD = 1000000007;
    int size_;
    vector<long long> treeVal, treeLen;
    vector<long long> pow10;
    
    pair<long long,long long> combine(long long av, long long al, long long bv, long long bl) {
        long long val = (av * pow10[bl] + bv) % MOD;
        return {val, al + bl};
    }
    
    pair<long long,long long> query(int l, int r) {
        l += size_;
        r += size_ + 1;
        long long resl_v = 0, resl_l = 0;
        long long resr_v = 0, resr_l = 0;
        while (l < r) {
            if (l & 1) {
                auto res = combine(resl_v, resl_l, treeVal[l], treeLen[l]);
                resl_v = res.first; resl_l = res.second;
                l++;
            }
            if (r & 1) {
                r--;
                auto res = combine(treeVal[r], treeLen[r], resr_v, resr_l);
                resr_v = res.first; resr_l = res.second;
            }
            l >>= 1;
            r >>= 1;
        }
        return combine(resl_v, resl_l, resr_v, resr_l);
    }
    
    vector<int> sumAndMultiply(string s, vector<vector<int>>& queries) {
        int n = s.size();
        vector<int> digits(n);
        for (int i = 0; i < n; i++) digits[i] = s[i] - '0';
        
        vector<long long> prefix(n + 1, 0);
        for (int i = 0; i < n; i++) prefix[i+1] = prefix[i] + digits[i];
        
        pow10.assign(n + 1, 1);
        for (int i = 1; i <= n; i++) pow10[i] = (pow10[i-1] * 10) % MOD;
        
        size_ = 1;
        while (size_ < n) size_ *= 2;
        if (size_ == 0) size_ = 1;
        
        treeVal.assign(2 * size_, 0);
        treeLen.assign(2 * size_, 0);
        
        for (int i = 0; i < n; i++) {
            int d = digits[i];
            if (d != 0) {
                treeVal[size_ + i] = d;
                treeLen[size_ + i] = 1;
            }
        }
        
        for (int i = size_ - 1; i >= 1; i--) {
            auto res = combine(treeVal[2*i], treeLen[2*i], treeVal[2*i+1], treeLen[2*i+1]);
            treeVal[i] = res.first;
            treeLen[i] = res.second;
        }
        
        vector<int> answer;
        answer.reserve(queries.size());
        for (auto& q : queries) {
            int l = q[0], r = q[1];
            auto res = query(l, r);
            long long xMod = res.first;
            long long sSum = (prefix[r+1] - prefix[l]) % MOD;
            long long ans = (xMod * sSum) % MOD;
            answer.push_back((int)ans);
        }
        
        return answer;
    }
};