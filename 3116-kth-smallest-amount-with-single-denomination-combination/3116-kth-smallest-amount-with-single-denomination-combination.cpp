class Solution {
public:
    long long findKthSmallest(vector<int>& coins, int k) {
        int n = coins.size();

        // Remove redundant denominations.
        // If a coin is a multiple of another coin,
        // it doesn't create any new amounts.
        sort(coins.begin(), coins.end());

        vector<int> a;

        for (int x : coins) {
            bool redundant = false;

            for (int y : a) {
                if (x % y == 0) {
                    redundant = true;
                    break;
                }
            }

            if (!redundant)
                a.push_back(x);
        }

        coins = a;
        n = coins.size();

        // Count distinct amounts <= x
        // divisible by at least one coin.
        auto count = [&](long long x) -> long long {
            long long ans = 0;

            for (int mask = 1; mask < (1 << n); mask++) {
                long long lcm = 1;
                int bits = 0;
                bool overflow = false;

                for (int i = 0; i < n; i++) {
                    if (mask & (1 << i)) {
                        bits++;

                        long long g = std::gcd(lcm, (long long)coins[i]);

                        // Avoid overflow.
                        lcm = lcm / g * coins[i];

                        if (lcm > x) {
                            overflow = true;
                            break;
                        }
                    }
                }

                if (overflow || lcm > x)
                    continue;

                long long cnt = x / lcm;

                if (bits & 1)
                    ans += cnt;
                else
                    ans -= cnt;
            }

            return ans;
        };

        // The answer is at most min(coins) * k.
        long long lo = 1;
        long long hi = 1LL * coins[0] * k;

        while (lo < hi) {
            long long mid = lo + (hi - lo) / 2;

            if (count(mid) >= k)
                hi = mid;
            else
                lo = mid + 1;
        }

        return lo;
    }
};