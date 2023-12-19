#include <deque>
#include <algorithm>
#include <cmath>

using namespace std;

class Line;

deque<Line> merge_lines(deque<Line> left, deque<Line> right);
deque<Line> get_visible_lines_recursive(deque<Line> lines);

class Line { // y = alpha * x + beta
private:
    double alpha;
    double beta;

public:
    Line(double alpha, double beta): alpha(alpha), beta(beta) { }

    double x_intersection(Line other) const {
        return -(beta - other.beta) / (alpha - other.alpha);
    }

    pair<double, double> intersection(Line other) const {
        double x = x_intersection(other);
        double y = alpha * x + beta;
        return make_pair(x, y);
    }

    bool operator <(const Line& other) const  {
        return alpha < other.alpha || (alpha == other.alpha && beta < other.beta);
    }
};

deque<Line> get_visible_lines_recursive(deque<Line> lines) {
    if (lines.size() < 3) {
        return lines;
    }

    deque<Line> left(lines.begin(), lines.begin() + lines.size() / 2);
    deque<Line> right(lines.begin() + lines.size() / 2, lines.end());

    left = get_visible_lines_recursive(left);
    right = get_visible_lines_recursive(right);
    return merge_lines(left, right);
}

deque<Line> get_visible_lines(deque<Line> lines) {
    sort(lines.begin(), lines.end());
    return get_visible_lines_recursive(lines);
}

deque<Line> merge_lines(deque<Line> left, deque<Line> right) {
    while (true) {
        pair<double, double> left_intersection;
        pair<double, double> right_intersection;
        if (left.size() > 1) {
            left_intersection = left.back().intersection(left[left.size() - 2]);
        } else {
            left_intersection = make_pair(-INFINITY, NAN);
        }
        if (right.size() > 1) {
            right_intersection = right[0].intersection(right[1]);
        } else {
            right_intersection = make_pair(INFINITY, NAN);
        }

        pair<double, double> middle_intersection = left.back().intersection(right[0]);
        if (middle_intersection.first < left_intersection.first) {
            left.pop_back();
        } else if (middle_intersection.first > right_intersection.first) {
            right.pop_front();
        } else {
            break;
        }
    }

    deque<Line> merged;
    merged.insert(merged.end(), left.begin(), left.end());
    merged.insert(merged.end(), right.begin(), right.end());
    return merged;
}

int main() {
    Line l1(-1, 2);
    Line l2(0, 1);
    Line l3(1, 1);

    deque<Line> lines = {l1, l2, l3};

    auto visible = get_visible_lines(lines);

    return 0;
}
