class Solution {
public:
    int maxNumberOfFamilies(int n, vector<vector<int>>& reservedSeats) {
        unordered_map<int, int> mp;

        // Store reservations only for seats 2 to 9.
        for (auto &seat : reservedSeats) {
            int row = seat[0];
            int col = seat[1];

            if (col >= 2 && col <= 9) {
                mp[row] |= (1 << col);
            }
        }

        // All rows not present in mp are completely free.
        long long ans = 2LL * (n - mp.size());

        for (auto &[row, mask] : mp) {
            bool left  = !(mask & ((1 << 2) | (1 << 3) |
                                   (1 << 4) | (1 << 5)));

            bool middle = !(mask & ((1 << 4) | (1 << 5) |
                                    (1 << 6) | (1 << 7)));

            bool right = !(mask & ((1 << 6) | (1 << 7) |
                                   (1 << 8) | (1 << 9)));

            if (left && right) {
                // Can place two groups: 2-5 and 6-9
                ans += 2;
            }
            else if (left || middle || right) {
                // Can place one group
                ans += 1;
            }
        }

        return (int)ans;
    }
};
