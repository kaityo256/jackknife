#pragma once
#include <algorithm>
#include <cassert>
#include <numeric>
#include <vector>

namespace jackknife {

typedef std::vector<double> vd;

double sum(vd &r) {
  return std::accumulate(r.begin(), r.end(), 0.0);
}

double average(vd &r) {
  return sum(r) / r.size();
}

template <class V, class F>
V transform_all(V &v, F f) {
  V r(v.size());
  std::transform(v.begin(), v.end(), r.begin(), f);
  return r;
}

template <class F>
double resample_a1(vd &r1, F f) {
  int n = r1.size();
  double r_jk = 0.0;
  for (int i = 0; i < n; i++) {
    double r1_i = (sum(r1) - r1[i]) / (n - 1);
    r_jk += f(r1_i);
  }
  r_jk /= n;
  double r1_ave = average(r1);
  double r_all = f(r1_ave);
  return n * r_all - (n - 1) * r_jk;
}

template <class F>
double resample_a2(vd &r1, vd &r2, F f) {
  int n = r1.size();
  double r_jk = 0.0;
  for (int i = 0; i < n; i++) {
    double r1_i = (sum(r1) - r1[i]) / (n - 1);
    double r2_i = (sum(r2) - r2[i]) / (n - 1);
    r_jk += f(r1_i, r2_i);
  }
  r_jk /= n;
  double r1_ave = average(r1);
  double r2_ave = average(r2);
  double r_all = f(r1_ave, r2_ave);
  return n * r_all - (n - 1) * r_jk;
}

template <class F>
double resample_a3(vd &r1, vd &r2, vd &r3, F f) {
  int n = r1.size();
  double r_jk = 0.0;
  for (int i = 0; i < n; i++) {
    double r1_i = (sum(r1) - r1[i]) / (n - 1);
    double r2_i = (sum(r2) - r2[i]) / (n - 1);
    double r3_i = (sum(r3) - r3[i]) / (n - 1);
    r_jk += f(r1_i, r2_i, r3_i);
  }
  r_jk /= n;
  double r1_ave = average(r1);
  double r2_ave = average(r2);
  double r3_ave = average(r3);
  double r_all = f(r1_ave, r2_ave, r3_ave);
  return n * r_all - (n - 1) * r_jk;
}

template <class F>
double resample_a1_bin(vd &r1, int bin_size, F f) {
  const int n = r1.size();
  assert(n % bin_size == 0);
  vd r1_p;
  for (int i = 0; i < n; i += bin_size) {
    double r1_i = std::accumulate(r1.begin() + i, r1.begin() + i + bin_size, 0.0);
    r1_i /= bin_size;
    r1_p.push_back(r1_i);
  }
  return resample_a1(r1_p, f);
}

template <class F>
double resample_a2_bin(vd &r1, vd &r2, int bin_size, F f) {
  const int n = r1.size();
  assert(n % bin_size == 0);
  vd r1_p, r2_p;
  for (int i = 0; i < n; i += bin_size) {
    double r1_i = std::accumulate(r1.begin() + i, r1.begin() + i + bin_size, 0.0);
    r1_i /= bin_size;
    r1_p.push_back(r1_i);

    double r2_i = std::accumulate(r2.begin() + i, r2.begin() + i + bin_size, 0.0);
    r2_i /= bin_size;
    r2_p.push_back(r2_i);
  }
  return resample_a2(r1_p, r2_p, f);
}

template <class F>
double resample_a3_bin(vd &r1, vd &r2, vd &r3, int bin_size, F f) {
  const int n = r1.size();
  assert(n % bin_size == 0);
  vd r1_p, r2_p, r3_p;
  for (int i = 0; i < n; i += bin_size) {
    double r1_i = std::accumulate(r1.begin() + i, r1.begin() + i + bin_size, 0.0);
    r1_i /= bin_size;
    r1_p.push_back(r1_i);

    double r2_i = std::accumulate(r2.begin() + i, r2.begin() + i + bin_size, 0.0);
    r2_i /= bin_size;
    r2_p.push_back(r2_i);

    double r3_i = std::accumulate(r3.begin() + i, r3.begin() + i + bin_size, 0.0);
    r3_i /= bin_size;
    r3_p.push_back(r3_i);
  }
  return resample_a3(r1_p, r2_p, r3_p, f);
}

} // namespace jackknife