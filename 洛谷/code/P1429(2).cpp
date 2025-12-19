#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <chrono>
#include <random>

using namespace std;

struct Point {
    double x, y;
};

int main() {
    int n;
    scanf("%d", &n);
    vector<Point> points(n);
    for (int i = 0; i < n; i++) {
        scanf("%lf %lf", &points[i].x, &points[i].y);
    }

    unsigned seed = chrono::steady_clock::now().time_since_epoch().count();
    mt19937 gen(seed);
    uniform_real_distribution<double> dis(0.0, 2.0 * acos(-1.0));
    double theta = dis(gen);

    double cos_t = cos(theta);
    double sin_t = sin(theta);

    vector<Point> rotated(n);
    for (int i = 0; i < n; i++) {
        double x = points[i].x;
        double y = points[i].y;
        rotated[i].x = x * cos_t - y * sin_t;
        rotated[i].y = x * sin_t + y * cos_t;
    }

    sort(rotated.begin(), rotated.end(), [](const Point& a, const Point& b) {
        if (a.x == b.x) {
            return a.y < b.y;
        }
        return a.x < b.x;
    });

    double min_dist_sq = 1e20;

    for (int i = 0; i < n; i++) {
        int end_index = min(i + 6, n);
        for (int j = i + 1; j < end_index; j++) {
            double dx = rotated[i].x - rotated[j].x;
            double dy = rotated[i].y - rotated[j].y;
            double dist_sq = dx * dx + dy * dy;
            if (dist_sq < min_dist_sq) {
                min_dist_sq = dist_sq;
            }
        }
    }

    double min_dist = sqrt(min_dist_sq);
    printf("%.4f\n", min_dist);

    return 0;
}