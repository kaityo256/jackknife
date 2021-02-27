#include "jackknife.hpp"
#include <cstdio>
#include <fstream>
#include <iostream>
#include <random>
#include <string>

std::default_random_engine engine;
std::normal_distribution<> dist(0.0, 1.0);

int get_binsize(int n) {
  double min = n;
  int b = 0;
  for (int i = 1; i < n; i++) {
    if (n % i != 0) continue;
    if (fabs(i - sqrt(n)) < min) {
      b = i;
      min = fabs(i - sqrt(n));
    }
  }
  return b;
}

double normal_test1(std::vector<double> &r) {
  auto r2 = jackknife::transform_all(r, [](double x) { return x * x; });
  double r2_ave = jackknife::average(r2);
  return 1.0 / r2_ave / r2_ave;
}

double jackknife_test1(std::vector<double> &r) {
  int n = r.size();
  int bin_size = get_binsize(n);
  auto r2 = jackknife::transform_all(r, [](double x) { return x * x; });
  auto f = [](double x1) { return 1.0 / x1 / x1; };
  return jackknife::resample_a1_bin(r2, bin_size, f);
}

double normal_test2(std::vector<double> &r) {
  auto r2 = jackknife::transform_all(r, [](double x) { return x * x; });
  auto r4 = jackknife::transform_all(r, [](double x) { return x * x * x * x; });
  double r2_ave = jackknife::average(r2);
  double r4_ave = jackknife::average(r4);
  return r4_ave / r2_ave / r2_ave;
}

double jackknife_test2(std::vector<double> &r) {
  int n = r.size();
  int bin_size = get_binsize(n);
  auto r2 = jackknife::transform_all(r, [](double x) { return x * x; });
  auto r4 = jackknife::transform_all(r, [](double x) { return x * x * x * x; });
  auto f = [](double x1, double x2) { return x1 / x2 / x2; };
  return jackknife::resample_a2_bin(r4, r2, bin_size, f);
}

double normal_test3(std::vector<double> &r) {
  auto r2 = jackknife::transform_all(r, [](double x) { return x * x; });
  auto r4 = jackknife::transform_all(r, [](double x) { return x * x * x * x; });
  auto r6 = jackknife::transform_all(r, [](double x) { return x * x * x * x * x * x; });
  double r2_ave = jackknife::average(r2);
  double r4_ave = jackknife::average(r4);
  double r6_ave = jackknife::average(r6);
  return r6_ave / r4_ave / r2_ave;
}

double jackknife_test3(std::vector<double> &r) {
  int n = r.size();
  int bin_size = get_binsize(n);
  auto r2 = jackknife::transform_all(r, [](double x) { return x * x; });
  auto r4 = jackknife::transform_all(r, [](double x) { return x * x * x * x; });
  auto r6 = jackknife::transform_all(r, [](double x) { return x * x * x * x * x * x; });
  auto f = [](double x1, double x2, double x3) { return x1 / x2 / x3; };
  return jackknife::resample_a3_bin(r6, r4, r2, bin_size, f);
}

template <class F>
void test(F f_s, F f_jn, const std::string filename) {
  std::ofstream ofs(filename);
  std::vector<int> size = {16, 32, 64, 128, 256};
  size_t n_trial = 65536;
  for (auto n : size) {
    std::vector<double> v_s, v_jn;
    for (size_t i = 0; i < n_trial; i++) {
      std::vector<double> r(n);
      r = jackknife::transform_all(r, [](double) { return dist(engine); });
      v_s.push_back(f_s(r));
      v_jn.push_back(f_jn(r));
    }
    double u_s = jackknife::average(v_s);
    double u_jn = jackknife::average(v_jn);
    ofs << n << " " << u_s << " " << u_jn << std::endl;
    std::cout << n << " " << u_s << " " << u_jn << std::endl;
  }
}

int main() {
  std::cout << "# 1/<x^2>^2" << std::endl;
  std::cout << "# N Simple Jackknife" << std::endl;
  test(normal_test1, jackknife_test1, "test1.dat");
  std::cout << std::endl;
  std::cout << "# <x^4>/<x^2>^2" << std::endl;
  std::cout << "# N Simple Jackknife" << std::endl;
  test(normal_test2, jackknife_test2, "test2.dat");
  std::cout << std::endl;
  std::cout << "# <x^6>/<x^4>/<x^2>" << std::endl;
  std::cout << "# N Simple Jackknife" << std::endl;
  test(normal_test3, jackknife_test3, "test3.dat");
}
