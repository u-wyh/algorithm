#include <algorithm>
#include <cmath>
#include <functional>
#include <iostream>
#include <numeric>
#include <vector>
using namespace std;

int gcd(int a,int b){
    return b==0?a:gcd(b,a%b);
}

struct Frac {
    long long p, q;

    Frac(long long _p = 0, long long _q = 1) : p(_p), q(_q) {
        norm();
    }

    void norm() {
        if (q < 0) {
            p = -p;
            q = -q;
        }
        long long g = gcd(llabs(p), llabs(q));
        if (g) {
            p /= g;
            q /= g;
        }
    }

    bool isZero() const {
        return p == 0;
    }

    long double val() const {
        return (long double)p / q;
    }
};

Frac operator+(const Frac &a, const Frac &b) {
    return Frac(a.p * b.q + b.p * a.q, a.q * b.q);
}

Frac operator-(const Frac &a, const Frac &b) {
    return Frac(a.p * b.q - b.p * a.q, a.q * b.q);
}

Frac operator*(const Frac &a, long long b) {
    return Frac(a.p * b, a.q);
}

Frac operator*(const Frac &a, const Frac &b) {
    return Frac(a.p * b.p, a.q * b.q);
}

Frac operator/(const Frac &a, const Frac &b) {
    return Frac(a.p * b.q, a.q * b.p);
}

struct Var {
    int r, c, ub;
};

int a[4][4];
int rowRem[4], colRem[4], diagRem[2];
int rowCnt[4], colCnt[4], diagCnt[2];
vector<Var> vars;
vector<vector<int>> coefInt;

int calcRank(const vector<int> &cols) {
    const double EPS = 1e-9;
    vector<vector<double>> mat(10, vector<double>(cols.size()));
    for (int r = 0; r < 10; r++) {
        for (int c = 0; c < (int)cols.size(); c++) {
            mat[r][c] = coefInt[r][cols[c]];
        }
    }

    int rank = 0;
    for (int c = 0; c < (int)cols.size(); c++) {
        int pivot = -1;
        for (int r = rank; r < 10; r++) {
            if (fabs(mat[r][c]) > EPS) {
                pivot = r;
                break;
            }
        }
        if (pivot == -1) continue;

        swap(mat[rank], mat[pivot]);
        double div = mat[rank][c];
        for (int j = c; j < (int)cols.size(); j++) mat[rank][j] /= div;

        for (int r = 0; r < 10; r++) {
            if (r == rank || fabs(mat[r][c]) <= EPS) continue;
            double f = mat[r][c];
            for (int j = c; j < (int)cols.size(); j++) {
                mat[r][j] -= f * mat[rank][j];
            }
        }
        rank++;
    }
    return rank;
}

bool betterProduct(const vector<int> &x, const vector<int> &y) {
    const long long INF = (1LL << 62);
    long long px = 1, py = 1;

    for (int id : x) {
        if (px > INF / max(1, vars[id].ub)) return false;
        px *= max(1, vars[id].ub);
    }
    for (int id : y) {
        if (py > INF / max(1, vars[id].ub)) return true;
        py *= max(1, vars[id].ub);
    }
    return px < py;
}

bool solveLinear() {
    int n = vars.size();
    vector<int> allCols(n);
    iota(allCols.begin(), allCols.end(), 0);
    int rank = calcRank(allCols);
    int freeCnt = n - rank;

    vector<int> bestFree;
    for (int mask = 0; mask < (1 << n); mask++) {
        if (__builtin_popcount((unsigned)mask) != freeCnt) continue;

        vector<int> pivots, freeCols;
        for (int i = 0; i < n; i++) {
            if (mask >> i & 1) freeCols.push_back(i);
            else pivots.push_back(i);
        }

        if (calcRank(pivots) != rank) continue;
        if (bestFree.empty() || betterProduct(freeCols, bestFree)) {
            bestFree = freeCols;
        }
    }

    vector<int> isFree(n), order;
    for (int id : bestFree) isFree[id] = 1;
    for (int i = 0; i < n; i++) {
        if (!isFree[i]) order.push_back(i);
    }
    sort(bestFree.begin(), bestFree.end(), [](int x, int y) {
        return vars[x].ub < vars[y].ub;
    });
    for (int id : bestFree) order.push_back(id);

    vector<int> rhs = {
        rowRem[0], rowRem[1], rowRem[2], rowRem[3],
        colRem[0], colRem[1], colRem[2], colRem[3],
        diagRem[0], diagRem[1]
    };

    vector<vector<Frac>> mat(10, vector<Frac>(n + 1));
    for (int r = 0; r < 10; r++) {
        for (int c = 0; c < n; c++) {
            mat[r][c] = Frac(coefInt[r][order[c]]);
        }
        mat[r][n] = Frac(rhs[r]);
    }

    int cur = 0;
    for (int c = 0; c < n && cur < 10; c++) {
        int pivot = -1;
        for (int r = cur; r < 10; r++) {
            if (!mat[r][c].isZero()) {
                pivot = r;
                break;
            }
        }
        if (pivot == -1) continue;

        swap(mat[cur], mat[pivot]);
        Frac div = mat[cur][c];
        for (int j = c; j <= n; j++) mat[cur][j] = mat[cur][j] / div;

        for (int r = 0; r < 10; r++) {
            if (r == cur || mat[r][c].isZero()) continue;
            Frac f = mat[r][c];
            for (int j = c; j <= n; j++) {
                mat[r][j] = mat[r][j] - mat[cur][j] * f;
            }
        }
        cur++;
    }

    vector<vector<Frac>> co(rank, vector<Frac>(freeCnt));
    vector<Frac> b(rank);
    for (int i = 0; i < rank; i++) {
        b[i] = mat[i][n];
        for (int j = 0; j < freeCnt; j++) {
            co[i][j] = mat[i][rank + j];
        }
    }

    vector<int> freeVal(freeCnt), ans(n);

    auto stillPossible = [&](int depth) {
        for (int i = 0; i < rank; i++) {
            long double mn = b[i].val(), mx = b[i].val();

            for (int j = 0; j < depth; j++) {
                long double t = co[i][j].val() * freeVal[j];
                mn -= t;
                mx -= t;
            }

            for (int j = depth; j < freeCnt; j++) {
                int ub = vars[order[rank + j]].ub;
                long double c = co[i][j].val();
                if (c >= 0) {
                    mn -= c * ub;
                    mx -= c;
                } else {
                    mn -= c;
                    mx -= c * ub;
                }
            }

            int ubPivot = vars[order[i]].ub;
            if (mx < 1.0L - 1e-12 || mn > ubPivot + 1e-12) return false;
        }
        return true;
    };

    function<bool(int)> dfs = [&](int depth) {
        if (!stillPossible(depth)) return false;

        if (depth == freeCnt) {
            for (int i = 0; i < freeCnt; i++) {
                ans[order[rank + i]] = freeVal[i];
            }

            for (int i = 0; i < rank; i++) {
                Frac x = b[i];
                for (int j = 0; j < freeCnt; j++) {
                    x = x - co[i][j] * freeVal[j];
                }
                if (x.q != 1 || x.p < 1 || x.p > vars[order[i]].ub) return false;
                ans[order[i]] = (int)x.p;
            }

            for (int i = 0; i < n; i++) {
                a[vars[i].r][vars[i].c] = ans[i];
            }
            return true;
        }

        int id = order[rank + depth];
        for (int v = 1; v <= vars[id].ub; v++) {
            freeVal[depth] = v;
            if (dfs(depth + 1)) return true;
        }
        return false;
    };

    return dfs(0);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    bool fixedCell[4][4] = {};

    for (int i = 0; i < 4; i++) cin >> rowRem[i];
    for (int i = 0; i < 4; i++) cin >> colRem[i];
    cin >> diagRem[0] >> diagRem[1];

    for (int t = 0; t < 4; t++) {
        int r, c, v;
        cin >> r >> c >> v;
        a[r][c] = v;
        fixedCell[r][c] = true;
    }

    for (int i = 0; i < 4; i++) {
        rowCnt[i] = colCnt[i] = 4;
    }
    diagCnt[0] = diagCnt[1] = 4;

    for (int r = 0; r < 4; r++) {
        for (int c = 0; c < 4; c++) {
            if (!fixedCell[r][c]) continue;

            int v = a[r][c];
            rowRem[r] -= v;
            colRem[c] -= v;
            rowCnt[r]--;
            colCnt[c]--;

            if (r == c) {
                diagRem[0] -= v;
                diagCnt[0]--;
            }
            if (r + c == 3) {
                diagRem[1] -= v;
                diagCnt[1]--;
            }
        }
    }

    for (int r = 0; r < 4; r++) {
        for (int c = 0; c < 4; c++) {
            if (fixedCell[r][c]) continue;

            int ub = min(rowRem[r] - rowCnt[r] + 1, colRem[c] - colCnt[c] + 1);
            if (r == c) ub = min(ub, diagRem[0] - diagCnt[0] + 1);
            if (r + c == 3) ub = min(ub, diagRem[1] - diagCnt[1] + 1);
            vars.push_back({r, c, ub});
        }
    }

    coefInt.assign(10, vector<int>(vars.size()));
    for (int i = 0; i < (int)vars.size(); i++) {
        int r = vars[i].r, c = vars[i].c;
        coefInt[r][i] = 1;
        coefInt[4 + c][i] = 1;
        if (r == c) coefInt[8][i] = 1;
        if (r + c == 3) coefInt[9][i] = 1;
    }

    solveLinear();

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (j) cout << ' ';
            cout << a[i][j];
        }
        cout << '\n';
    }

    return 0;
}
