class Solution {
public:
    long long maxSum(vector<int>& nums, int k, int mul) {
        sort(nums.begin(), nums.end(), greater<int>());

        vector<long long> pref(k + 1, 0);
        for (int i = 0; i < k; i++)
            pref[i + 1] = pref[i] + nums[i];

        long long ans = pref[k]; // multiply nothing

        long long weighted = 0;

        for (int m = 1; m <= k; m++) {
            weighted += 1LL * nums[m - 1] * (mul - (m - 1));

            long long normal = pref[k] - pref[m];

            ans = max(ans, weighted + normal);
        }

        return ans;
        
    }
};