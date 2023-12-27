#ifndef OTUS_HOMEWORK_05
#define OTUS_HOMEWORK_05

#include <limits>
#include <cmath>
#include <numeric>
#include <algorithm>

static inline double pct(const std::vector<double>& elements, double percent){
    double m_pct{};
    double i = (elements.size() - 1) * percent;
    int f = floor(i);
    int c = ceil(i);
    if (f == c) {
        m_pct = elements.at(f);
    } else {
        double d0 = elements.at(f) * (c - i);
        double d1 = elements.at(c) * (i - f);
        m_pct = d0 + d1;
    }
    return m_pct;
}

class IStatistics {
public:
    virtual ~IStatistics() = default;
    virtual void update(double next) = 0;
    virtual double eval() const = 0;
    virtual const char *name() const = 0;
};

class Min : public IStatistics { // минимальное значение из последовательности
public:
    Min() : m_min{std::numeric_limits<double>::max()} {
    }

    void update(double next) override {
        if (next < m_min) {
            m_min = next;
        }
    }

    double eval() const override {
        return m_min;
    }

    const char *name() const override {
        return "min";
    }

private:
    double m_min;
};

class Max : public IStatistics { // максимальное значение из последовательности
public:
    Max() : m_max{std::numeric_limits<double>::lowest()} {}

    void update(double next) override {
        if (next > m_max) {
            m_max = next;
        }
    }

    double eval() const override { return m_max; }
    const char *name() const override { return "max"; }

private:
    double m_max;
};

class Mean : public IStatistics { //арифметическое среднее, посчитанное на основе всех элементов последовательности
public:
    Mean() = default;

    void update(double next) override {
        m_summ += next;
        ++m_count;
    }

    double eval() const override { return m_summ / m_count; }
    const char *name() const override { return "mean"; }

private:
    double m_summ{};
    int m_count{};
};

class STD : public IStatistics { //среднеквадратическое отклонение
public:
    STD() = default;

    void update(double next) override {
        m_elements.push_back(next);
    }

    double eval() const override {
        long double mean = std::accumulate(m_elements.begin(), m_elements.end(), 0.0L) / m_elements.size();
        long double summOfSquares{};
        for (auto el: m_elements) {
            summOfSquares += powl((el - mean), 2);
        }
        return sqrtl(summOfSquares / (m_elements.size() - 1));
    }

    const char *name() const override { return "std"; }

private:
    std::vector<double> m_elements;
};


#endif 
