#include <string>
#include <vector>
#include <random>
#include <set>
#include <deque>
#include <cmath>
#include <map>
#pragma once

class Poly {
public:
    int64_t operator()(const int64_t value) const;
    bool operator==(const Poly& other) const;
    void operator=(const Poly& other);
    bool operator!=(const Poly& other) const;
    Poly& operator+=(const Poly& other);
    Poly& operator-=(const Poly& other);
    Poly operator-(const Poly& other) const;
    Poly operator+(const Poly& other) const;
    Poly operator*(const Poly& other) const;
    friend std::ostream& operator<<(std::ostream& stream, const Poly& poly);
    Poly operator-() const;
    Poly();
    Poly(std::vector<int64_t> coefficient);
    Poly(std::map<size_t, int64_t> coefficient);

private:
    std::map<size_t, int64_t> table_of_coefficient_;
};
