class Solution {
public:
    long long solve(vector<int>& nums, int k, bool multiply) {
        auto convert = [&](int x) -> long long {
            if (multiply) return 1LL * x * k;
            if (x >= 0) return x / k;
            return -((-x) / k); // ceil(x/k) for negatives
        };

        const long long NEG = -(1LL << 60);

        long long dp0 = nums[0];
        long long dp1 = convert(nums[0]);
        long long dp2 = NEG;

        long long ans = max(dp0, dp1);

        for (int i = 1; i < nums.size(); i++) {
            long long normal = nums[i];
            long long changed = convert(nums[i]);

            long long ndp0 = max(dp0 + normal, normal);

            long long ndp1 = max({
                dp0 + changed,
                dp1 + changed,
                changed
            });

            long long ndp2 = max(
                dp1 + normal,
                dp2 + normal
            );

            dp0 = ndp0;
            dp1 = ndp1;
            dp2 = ndp2;

            ans = max({ans, dp0, dp1, dp2});
        }

        return ans;
    }

    long long maxSubarraySum(vector<int>& nums, int k) {
        return max(solve(nums, k, true), solve(nums, k, false));
    }
};