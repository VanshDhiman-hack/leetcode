class Solution {
public:
    static const int DRAW = 0;
    static const int MOUSE = 1;
    static const int CAT = 2;

    int catMouseGame(vector<vector<int>>& graph) {
        int n = graph.size();

        vector<vector<vector<int>>> color(
            n, vector<vector<int>>(n, vector<int>(2, DRAW)));

        vector<vector<vector<int>>> degree(
            n, vector<vector<int>>(n, vector<int>(2, 0)));

        for (int m = 0; m < n; m++) {
            for (int c = 0; c < n; c++) {
                degree[m][c][0] = graph[m].size();

                degree[m][c][1] = graph[c].size();
                for (int nxt : graph[c])
                    if (nxt == 0)
                        degree[m][c][1]--;
            }
        }

        queue<array<int, 4>> q;

        for (int c = 1; c < n; c++) {
            color[0][c][0] = MOUSE;
            color[0][c][1] = MOUSE;
            q.push({0, c, 0, MOUSE});
            q.push({0, c, 1, MOUSE});
        }

        for (int i = 1; i < n; i++) {
            color[i][i][0] = CAT;
            color[i][i][1] = CAT;
            q.push({i, i, 0, CAT});
            q.push({i, i, 1, CAT});
        }

        while (!q.empty()) {
            auto [m, c, turn, result] = q.front();
            q.pop();

            vector<array<int, 3>> parents;

            if (turn == 0) { // mouse moved last, so parent is cat's turn
                for (int pc : graph[c]) {
                    if (pc == 0) continue;
                    parents.push_back({m, pc, 1});
                }
            } else { // cat moved last, so parent is mouse's turn
                for (int pm : graph[m]) {
                    parents.push_back({pm, c, 0});
                }
            }

            for (auto &p : parents) {
                int pm = p[0], pc = p[1], pt = p[2];

                if (color[pm][pc][pt] != DRAW)
                    continue;

                if ((pt == 0 && result == MOUSE) ||
                    (pt == 1 && result == CAT)) {

                    color[pm][pc][pt] = result;
                    q.push({pm, pc, pt, result});
                } else {
                    degree[pm][pc][pt]--;
                    if (degree[pm][pc][pt] == 0) {
                        color[pm][pc][pt] = (pt == 0 ? CAT : MOUSE);
                        q.push({pm, pc, pt, color[pm][pc][pt]});
                    }
                }
            }
        }

        return color[1][2][0];
    }
};