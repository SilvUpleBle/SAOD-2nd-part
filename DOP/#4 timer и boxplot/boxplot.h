#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
template <typename T>
class boxplot
{
    public:
        boxplot() = delete;
        ~boxplot() = delete;
        static T min(std::vector<T> x, size_t size)
        {
            std::sort(x.begin(), x.end());
            T q1 = x[0.25 * size];
            T q3 = x[0.75 * size];
            return q1 - 1.5 * (q3 - q1);
        }

        static T median(std::vector<T> x, size_t size)
        {
            if (size == 2) return (x[0] + x[1]) / 2.0;
            std::sort(x.begin(), x.end());
            if (size % 2 != 0)
                return (double)x[size / 2];
            return (double)(x[(size - 1) / 2] + x[size / 2]) / 2.0;

        }

        static T mean(std::vector<T> x, size_t size)
        {
            T sr = 0;
            for (auto el : x)
            {
                sr += el;
            }
            sr = sr / size;
            return sr;
        }

        static T lq(std::vector<T> x, size_t size)
        {
            std::sort(x.begin(), x.end());
            double med = median(x, size);
            std::vector<T> vec;
            for (auto el : x)
            {
                if (el < med)
                {
                    vec.push_back(el);
                }
                else break;
            }
            size_t vec_size = vec.size();
            return median(vec, vec_size);
        }

        static T uq(std::vector<T> x, size_t size)
        {
            std::sort(x.begin(), x.end());
            double med = median(x, size);
            std::vector<T> vec;
            for (auto el : x)
            {
                if (el > med)
                {
                    vec.push_back(el);
                }
            }
            size_t vec_size = vec.size();
            return median(vec, vec_size);
        }

        static T stddev(std::vector<T> x, size_t size)
        {
            T out = 0;
            T sr = mean(x, size);
            for (auto el : x)
            {
                out += (el - sr) * (el - sr);
            }
            out = (double)(out / size);
            out = std::sqrt(out);
            return out;

        }

        static T max(std::vector<T> x, size_t size)
        {
            std::sort(x.begin(), x.end());
            T q1 = x[0.25 * size];
            T q3 = x[0.75 * size];
            return q3 - 1.5 * (q1 - q3);
        }

        static std::vector<T> out(std::vector<T> x, size_t size)
        {
            std::vector<T> vec;
            for (auto el : x)
            {
                if (el < boxplot::min(x, size) || el > boxplot::max(x, size)) vec.push_back(el);
            }
            return vec;
        }
};

