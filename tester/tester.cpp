#include <iostream>
#include <random>

#include "solver.h"

class Tester {
 public:
  void operator()(size_t num_tests, int min_length, int max_length,
                  int min_value, int max_value);

 private:
  std::vector<solver::Point> points_;

  void GeneratePoints(std::random_device& dev,
                      std::uniform_int_distribution<>& length_dist,
                      std::uniform_int_distribution<>& coordinate_dist);
  long long Solve();
};

void Tester::operator()(size_t num_tests, int min_length, int max_length,
                        int min_value, int max_value) {
  std::random_device dev;
  std::mt19937 gen(dev());
  std::uniform_int_distribution<> length_dist(min_length, max_length);
  std::uniform_int_distribution<> coordinate_dist(min_value, max_value);

  for (size_t i = 0; i < num_tests; ++i) {
    GeneratePoints(dev, length_dist, coordinate_dist);

    long long dummy_solution = Solve();
    long long alg_solution = solver::solve(points_.size(), points_);

    if (alg_solution != dummy_solution) {
      std::cout << dummy_solution << std::endl;
      std::cout << alg_solution << std::endl;
      std::cout << points_.size() << std::endl;
      for (auto&& point : points_) {
        std::cout << point.x_ << " " << point.y_ << std::endl;
      }
      exit(1);
    }
  }

  std::cout << "Stress test passed ";
  if (length_dist(dev) % 2 == 0) {
    std::cout << "(=^ ◡ ^=)" << std::endl;
  } else {
    std::cout << "\\(^_^)/" << std::endl;
  }
}

void Tester::GeneratePoints(std::random_device& dev,
                            std::uniform_int_distribution<>& length_dist,
                            std::uniform_int_distribution<>& coordinate_dist) {
  size_t length = length_dist(dev);
  points_.resize(length);

  for (auto&& point : points_) {
    point.x_ = coordinate_dist(dev);
    point.y_ = coordinate_dist(dev);
  }
}

long long Tester::Solve() {
  long long distance = UINT32_MAX;
  for (size_t i = 0; i < points_.size(); ++i) {
    for (size_t j = 0; j < points_.size(); ++j) {
      long long new_distance =
          solver::find_distance_squared(points_[i], points_[j]);
      if (i != j && new_distance < distance) {
        distance = new_distance;
      }
    }
  }

  return distance;
}

int main() {
  Tester tester;

  tester(300, 2, 10, -10, 10);
  tester(100, 2, 100, -100, 100);
  tester(30, 2, 1000, -200, 200);

  return 0;
}
