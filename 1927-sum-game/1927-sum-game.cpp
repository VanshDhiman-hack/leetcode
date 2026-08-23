class Solution {
public:
    bool sumGame(string num) {
        int n = num.size();
        int diff = 0;
        int qLeft = 0, qRight = 0;

        for (int i = 0; i < n / 2; i++) {
            if (num[i] == '?')
                qLeft++;
            else
                diff += num[i] - '0';
        }

        for (int i = n / 2; i < n; i++) {
            if (num[i] == '?')
                qRight++;
            else
                diff -= num[i] - '0';
        }

        int qDiff = qLeft - qRight;

        // Bob can force equality only when the required
        // difference can exactly be compensated.
        if (qDiff % 2 != 0)
            return true;

        return diff != -9 * qDiff / 2;
    }
};