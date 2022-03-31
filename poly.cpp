#include "poly.h"
#include <iostream>
#include <cmath>
#include <unordered_map>
Poly::Poly() : table_of_coefficient_() {
}
Poly::Poly(std::map<size_t, int64_t> coefficient) : table_of_coefficient_(std::move(coefficient)) {
}
Poly::Poly(std::vector<int64_t> coefficient) {
    for (size_t i = 0; i < coefficient.size(); ++i) {
        if (coefficient[i]) {
            table_of_coefficient_[i] = coefficient[i];
        }
    }
}
int64_t Poly::operator()(const int64_t value) const {
    int64_t result = 0;
    size_t current_degree = 0;
    int64_t value_in_degree = 1;
    for (const auto& elements : table_of_coefficient_) {
        while (current_degree != elements.first) {
            value_in_degree *= value;
            ++current_degree;
        }
        result += elements.second * value_in_degree;
    }
    return result;
}
bool Poly::operator==(const Poly& other) const {
    return this->table_of_coefficient_ == other.table_of_coefficient_;
}
bool Poly::operator!=(const Poly& other) const {
    return !(other == *this);
}
Poly Poly::operator-(const Poly& other) const {
    Poly result = *this;
    result -= other;
    return result;
}
Poly Poly::operator+(const Poly& other) const {
    Poly result = *this;
    result += other;
    return result;
}
Poly& Poly::operator+=(const Poly& other) {
    for (const auto& [degree, coefficient] : other.table_of_coefficient_) {
        auto value = this->table_of_coefficient_.emplace(degree, coefficient);
        if (!value.second) {
            value.first->second += coefficient;
        }
        if (!value.first->second) {
            this->table_of_coefficient_.erase(value.first);
        }
    }
    return *this;
}
Poly& Poly::operator-=(const Poly& other) {
    for (const auto& [degree, coefficient] : other.table_of_coefficient_) {
        auto value = this->table_of_coefficient_.emplace(degree, -coefficient);
        if (!value.second) {
            value.first->second -= coefficient;
        }
        if (!value.first->second) {
            this->table_of_coefficient_.erase(value.first);
        }
    }
    return *this;
}
Poly Poly::operator*(const Poly& other) const {
    Poly result_of_multiplication;
    for (auto [degree, coefficient] : this->table_of_coefficient_) {
        for (auto [other_degree, other_coefficient] : other.table_of_coefficient_) {
            auto value = result_of_multiplication.table_of_coefficient_.emplace(degree + other_degree,
                                                                                coefficient * other_coefficient);
            if (!value.second) {
                value.first->second += coefficient * other_coefficient;
                if (!value.first->second) {
                    result_of_multiplication.table_of_coefficient_.erase(value.first);
                }
            }
        }
    }
    return result_of_multiplication;
}
void Poly::operator=(const Poly& other) {
    this->table_of_coefficient_.clear();
    for (const auto& element : other.table_of_coefficient_) {
        this->table_of_coefficient_.emplace(element);
    }
}
Poly Poly::operator-() const {
    Poly answer;
    answer.table_of_coefficient_.clear();
    for (auto [degree, coefficient] : this->table_of_coefficient_) {
        answer.table_of_coefficient_.emplace(degree, -coefficient);
    }
    return answer;
}
std::ostream& operator<<(std::ostream& stream, const Poly& poly) {
    stream << "y = ";
    for (auto it = std::rbegin(poly.table_of_coefficient_); it != std::rend(poly.table_of_coefficient_); ++it) {
        if (it->first == 0) {
            stream << it->second;
        } else {
            stream << it->second << "x^" << it->first << " + ";
        }
    }
    if (poly.table_of_coefficient_.empty()) {
        stream << "0";
    }
    return stream;
}
