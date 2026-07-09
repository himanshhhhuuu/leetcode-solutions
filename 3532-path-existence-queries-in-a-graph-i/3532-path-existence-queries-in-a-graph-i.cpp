class Solution {
public:
    vector<bool> pathExistenceQueries(int n, vector<int>& nums, int maxDiff, vector<vector<int>>& queries) {
        vector<int> comp(n);
        int id = 0;
        comp[0] = 0;
        for (int i = 1; i < n; i++) {
            if (nums[i] - nums[i-1] > maxDiff) {
                id++;
            }
            comp[i] = id;
        }
        
        vector<bool> answer;
        answer.reserve(queries.size());
        for (auto& q : queries) {
            int u = q[0], v = q[1];
            answer.push_back(comp[u] == comp[v]);
        }
        
        return answer;
    }
};