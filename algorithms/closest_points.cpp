#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

class Point {
public:
    double x;
    double y;

    double distance(const Point& other) {
        double a = x - other.x;
        double b = y - other.y;
        return sqrt(a * a + b * b);
    }

    friend ostream& operator<<(ostream& os, const Point& p) {
        os << "(" << p.x << ", " << p.y << ")";
        return os;
    }
};

double pair_distance(pair<Point, Point> pq) {
    return pq.first.distance(pq.second);
}

// px: points sorted by x coordinate
// py: points sorted by y coordinate
pair<Point, Point> _closest_pair(vector<Point> px, vector<Point> py) {
    // When there's three points, brute force.
    if (px.size() <= 3) {
        double min_distance = INFINITY;
        pair<Point, Point> closest_pair;
        for (int i = 1; i < px.size(); i++) {
            for (int j = 0; j < i; j++) {
                Point q = px[i];
                Point r = px[j];
                double distance = q.distance(r);
                if (distance < min_distance) {
                    min_distance = distance;
                    closest_pair = make_pair(q, r);
                }
            };
        }
        return closest_pair;
    }

    // Left and right
    vector<Point> qx(px.begin(), px.begin() + px.size() / 2);
    vector<Point> rx(px.begin() + px.size() / 2, px.end());
    vector<Point> qy = {};
    vector<Point> ry = {};
    for (auto p: py) { // suppose that all x's are different.
        if (p.x <= qx.back().x) {
            qy.push_back(p);
        } else {
            ry.push_back(p);
        }
    }

    auto q_pair = _closest_pair(qx, qy);
    auto r_pair = _closest_pair(rx, ry);
    auto closest_pair = (pair_distance(q_pair) < pair_distance(r_pair)) ? q_pair : r_pair;
    auto min_distance = pair_distance(closest_pair);

    // Middle
    double middle = (qx.back().x + rx.front().x) / 2;
    vector<Point> sy;

    for (auto p: py) {
        if (p.x >= middle - min_distance && p.x <= middle + min_distance) {
            sy.push_back(p);
        }
    }

    for (int i = 0; i < sy.size() - 1; i++) {
        for (int j = i + 1; j <= i + 7 && j < sy.size(); j++) {
            double distance = sy[i].distance(sy[j]);
            if (distance < min_distance) {
                min_distance = distance;
                closest_pair = make_pair(sy[i], sy[j]);
            }
        }
    }
    return closest_pair;
}

pair<Point, Point> closest_pair(vector<Point> v) {
    auto xsorted_cmp = [](const Point &p, const Point &q) {
        return p.x < q.x || (p.x == q.x && p.y < q.y);
    };
    sort(v.begin(), v.end(), xsorted_cmp);
    vector<Point> xsorted(v);
    auto ysorted_cmp = [](const Point &p, const Point &q) {
        return p.y < q.y || (p.y == q.y && p.x < q.x);
    };
    sort(v.begin(), v.end(), ysorted_cmp);
    vector<Point> ysorted(v);

    return _closest_pair(xsorted, ysorted);
}

int main() {
    vector<Point> points = {{1, 3}, {4, 6}, {7, 9}, {2.11, 4}, {5, 7}, {8, 10.1}};
    pair<Point, Point> result = closest_pair(points);
    cout << "Closest pair: {" << result.first << ", " << result.second << "}" << '\n';

    return 0;
}
