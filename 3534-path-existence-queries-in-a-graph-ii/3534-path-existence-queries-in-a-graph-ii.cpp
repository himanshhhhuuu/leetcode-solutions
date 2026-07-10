class Solution {
public:
    vector<int> pathExistenceQueries(int n, vector<int>& nums, int maxDiff, vector<vector<int>>& queries) {
        // Get sorted order of indices by nums value
        vector<int> order(n);
        iota(order.begin(), order.end(), 0);
        sort(order.begin(), order.end(), [&](int a, int b){
            return nums[a] < nums[b];
        });

        vector<int> v(n), pos(n);
        for (int i = 0; i < n; i++) {
            v[i] = nums[order[i]];
            pos[order[i]] = i;
        }

        // reach[i] = farthest index j (sorted) such that v[j] - v[i] <= maxDiff
        vector<int> reach(n);
        int j = 0;
        for (int i = 0; i < n; i++) {
            if (j < i) j = i;
            while (j + 1 < n && v[j+1] - v[i] <= maxDiff) j++;
            reach[i] = j;
        }

        // component id based on gaps
        vector<int> comp(n, 0);
        for (int i = 1; i < n; i++) {
            comp[i] = comp[i-1] + ((v[i] - v[i-1] > maxDiff) ? 1 : 0);
        }

        // binary lifting table
        int LOG = max(1, (int)floor(log2(max(1, n))) + 1);
        vector<vector<int>> up(LOG, vector<int>(n));
        up[0] = reach;
        for (int k = 1; k < LOG; k++) {
            for (int i = 0; i < n; i++) {
                up[k][i] = up[k-1][up[k-1][i]];
            }
        }

        int q = queries.size();
        vector<int> ans(q);
        for (int idx = 0; idx < q; idx++) {
            int u = queries[idx][0], w = queries[idx][1];
            int p = pos[u], qq = pos[w];
            if (p == qq) {
                ans[idx] = 0;
                continue;
            }
            if (p > qq) swap(p, qq);

            if (comp[p] != comp[qq]) {
                ans[idx] = -1;
                continue;
            }

            int cur = p;
            long long jumps = 0;
            for (int k = LOG - 1; k >= 0; k--) {
                if (up[k][cur] < qq) {
                    cur = up[k][cur];
                    jumps += (1LL << k);
                }
            }
            ans[idx] = (int)(jumps + 1);
        }

        return ans;
    }
};
