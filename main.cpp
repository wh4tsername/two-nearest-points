#include <algorithm>
#include <iostream>
#include <vector>

struct Point {
  int x_;
  int y_;
};

long long find_distance_squared(const Point &first, const Point &second) {
  return (second.x_ - first.x_) * (second.x_ - first.x_) +
         (second.y_ - first.y_) * (second.y_ - first.y_);
}

long long find_set_min_distance(const std::vector<Point> &points,
                                size_t left_border, size_t right_border) {
  size_t index_difference = right_border - left_border;

  if (index_difference == 2) {
    long long dist1 =
        find_distance_squared(points[left_border], points[left_border + 1]);
    long long dist2 =
        find_distance_squared(points[left_border + 1], points[right_border]);
    long long dist3 =
        find_distance_squared(points[left_border], points[right_border]);

    return std::min(std::min(dist1, dist2), dist3);
  }
  if (index_difference == 1) {
    return find_distance_squared(points[left_border], points[right_border]);
  }

  long long distance = std::min(
      find_set_min_distance(
          points, left_border,
          left_border + static_cast<size_t>(index_difference / 2)),
      find_set_min_distance(
          points, left_border + static_cast<size_t>(index_difference / 2) + 1,
          right_border));

  size_t close_set_left_border = left_border + index_difference / 2;
  while ((points[static_cast<size_t>(left_border + index_difference / 2)].x_ -
              points[close_set_left_border].x_ <
          distance) &&
         (close_set_left_border != 0)) {
    --close_set_left_border;
  }

  size_t close_set_right_border = left_border + index_difference / 2 + 1;
  while ((-points[static_cast<size_t>(left_border + index_difference / 2)].x_ +
              points[close_set_right_border].x_ <
          distance) &&
         (close_set_right_border != right_border)) {
    ++close_set_right_border;
  }

  std::vector<Point> closest_set(points.begin() + close_set_left_border,
                                 points.begin() + close_set_right_border + 1);
  std::sort(closest_set.begin(), closest_set.end(),
            [](const Point &lhs, const Point &rhs) { return lhs.y_ < rhs.y_; });

  long long new_min_distance = distance;
  for (size_t i = 0; i < closest_set.size(); ++i) {
    size_t lower_bound = i;
    while ((closest_set[lower_bound].y_ > closest_set[i].y_ - distance) &&
           (lower_bound != 0)) {
      --lower_bound;
    }

    for (size_t j = lower_bound; j < i; ++j) {
      long long current_distance =
          find_distance_squared(closest_set[i], closest_set[j]);
      if (new_min_distance > current_distance) {
        new_min_distance = current_distance;
      }
    }
  }

  return new_min_distance;
}

int main() {
  size_t num_points = 0;
  std::cin >> num_points;

  std::vector<Point> points(num_points);
  for (size_t i = 0; i < num_points; ++i) {
    std::cin >> points[i].x_ >> points[i].y_;
  }

  std::sort(points.begin(), points.end(),
            [](const Point &lhs, const Point &rhs) {
              return lhs.x_ < rhs.x_ || (lhs.x_ == rhs.x_ && lhs.y_ < rhs.y_);
            });

  std::cout << find_set_min_distance(points, 0, num_points - 1) << std::endl;

  return 0;
}
