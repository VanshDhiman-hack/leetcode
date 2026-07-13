class Solution {
public:
    int kConcatenationMaxSum(vector<int>& arr, int k) {
        const int MOD = 1e9 + 7;

        long long totalSum = 0;
        for (int x : arr) totalSum += x;

        // Kadane on one or two copies
        long long cur = 0, best = 0;
        int times = min(2, k);

        for (int t = 0; t < times; t++) {
            for (int x : arr) {
                cur = max(0LL, cur + x);
                best = max(best, cur);
            }
        }

        if (k == 1)
            return best % MOD;

        if (totalSum > 0)
            best += (long long)(k - 2) * totalSum;

        return best % MOD;
    }
};