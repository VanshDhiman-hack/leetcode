class Solution {
public:
    long long sumAndMultiply(int n) {
        vector<int> digits;

        if (n == 0) return 0;

        while (n > 0) {
            int d = n % 10;
            if (d != 0)
                digits.push_back(d);
            n /= 10;
        }

        long long x = 0;
        long long sum = 0;

        for (int i = digits.size() - 1; i >= 0; i--) {
            x = x * 10 + digits[i];
            sum += digits[i];
        }

        return x * sum;
    }
};