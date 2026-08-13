class Solution {
    struct Node {
        int len;
        int prefix;
        int suffix;
        int best;
        char leftChar;
        char rightChar;

        Node() {
            len = prefix = suffix = best = 0;
            leftChar = rightChar = '#';
        }

        Node(char c) {
            len = prefix = suffix = best = 1;
            leftChar = rightChar = c;
        }
    };

    vector<Node> seg;

    Node merge(Node a, Node b) {
        if (a.len == 0) return b;
        if (b.len == 0) return a;

        Node res;
        res.len = a.len + b.len;

        res.leftChar = a.leftChar;
        res.rightChar = b.rightChar;

        // Prefix
        res.prefix = a.prefix;
        if (a.prefix == a.len && a.rightChar == b.leftChar) {
            res.prefix = a.len + b.prefix;
        }

        // Suffix
        res.suffix = b.suffix;
        if (b.suffix == b.len && a.rightChar == b.leftChar) {
            res.suffix = b.len + a.suffix;
        }

        // Best answer inside either half
        res.best = max(a.best, b.best);

        // Combination across the boundary
        if (a.rightChar == b.leftChar) {
            res.best = max(res.best, a.suffix + b.prefix);
        }

        return res;
    }

    void build(int idx, int l, int r, string &s) {
        if (l == r) {
            seg[idx] = Node(s[l]);
            return;
        }

        int mid = (l + r) / 2;

        build(2 * idx, l, mid, s);
        build(2 * idx + 1, mid + 1, r, s);

        seg[idx] = merge(seg[2 * idx], seg[2 * idx + 1]);
    }

    void update(int idx, int l, int r, int pos, char c) {
        if (l == r) {
            seg[idx] = Node(c);
            return;
        }

        int mid = (l + r) / 2;

        if (pos <= mid)
            update(2 * idx, l, mid, pos, c);
        else
            update(2 * idx + 1, mid + 1, r, pos, c);

        seg[idx] = merge(seg[2 * idx], seg[2 * idx + 1]);
    }

public:
    vector<int> longestRepeating(string s, string queryCharacters,
                                 vector<int>& queryIndices) {
        int n = s.size();

        seg.resize(4 * n + 5);

        build(1, 0, n - 1, s);

        vector<int> ans;

        for (int i = 0; i < queryIndices.size(); i++) {
            int pos = queryIndices[i];
            char c = queryCharacters[i];

            update(1, 0, n - 1, pos, c);

            ans.push_back(seg[1].best);
        }

        return ans;
    }
};