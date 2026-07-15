#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iomanip>
using namespace std;

const double PI = acos(-1.0);
const double eps = 1e-9;

int main() {
    int n;
    cin >> n;
    double r[1000], x[1000], y[1000];
    for (int i = 0; i < n; i++) {
        cin >> r[i] >> x[i] >> y[i];
    }
    double ans = 0.0;
    for (int i = 0; i < n; i++) {
        vector<pair<double, double>> intervals;
        bool fully_covered = false;
        for (int j = i + 1; j < n; j++) {
            double dx = x[i] - x[j];
            double dy = y[i] - y[j];
            double d = sqrt(dx*dx + dy*dy);
            if (r[j] >= r[i] && d <= r[j] - r[i] + eps) {
                fully_covered = true;
                break;
            }
            if (d >= r[i] + r[j] - eps) continue;
            if (d <= fabs(r[i] - r[j]) + eps) continue;
            double alpha = atan2(y[j] - y[i], x[j] - x[i]);
            double costheta = (r[i]*r[i] + d*d - r[j]*r[j]) / (2 * r[i] * d);
            if (costheta > 1.0) costheta = 1.0;
            if (costheta < -1.0) costheta = -1.0;
            double beta = acos(costheta);
            double start = alpha - beta;
            double end = alpha + beta;
            if (start < 0) start += 2 * PI;
            if (end < 0) end += 2 * PI;
            if (start > end) {
                intervals.push_back(make_pair(0, end));
                intervals.push_back(make_pair(start, 2 * PI));
            } else {
                intervals.push_back(make_pair(start, end));
            }
        }
        if (fully_covered) {
            continue;
        }
        if (intervals.empty()) {
            ans += 2 * PI * r[i];
        } else {
            sort(intervals.begin(), intervals.end());
            vector<pair<double, double>> merged;
            double curStart = intervals[0].first;
            double curEnd = intervals[0].second;
            for (int k = 1; k < intervals.size(); k++) {
                if (intervals[k].first <= curEnd + eps) {
                    if (intervals[k].second > curEnd) {
                        curEnd = intervals[k].second;
                    }
                } else {
                    merged.push_back(make_pair(curStart, curEnd));
                    curStart = intervals[k].first;
                    curEnd = intervals[k].second;
                }
            }
            merged.push_back(make_pair(curStart, curEnd));
            double total_covered = 0.0;
            for (auto &p : merged) {
                total_covered += p.second - p.first;
            }
            ans += (2 * PI - total_covered) * r[i];
        }
    }
    cout << fixed << setprecision(3) << ans << endl;
    return 0;
}