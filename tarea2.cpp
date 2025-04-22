#include <iostream>
#include <vector>
#include <cmath>
#include <utility>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <numeric>
#include <gnuplot-iostream.h> 

using namespace std;

double x(double t) {
    return 5 + 13.4*t - 7.36*pow(t, 2) + 0.8*pow(t, 3);
}

double v(double t) {
    return 13.4 - 14.72*t + 2.4*pow(t, 2);
}

double a(double t) {
    return -14.72 + 4.8*t;
}

double raiz(double (*f)(double), double t_min, double t_max, double eps = 1e-6) {
    double t1 = t_min;
    double t2 = t_max;
    while (t2 - t1 > eps) {
        double mid = (t1 + t2)/2;
        if (f(t1) * f(mid) < 0) {
            t2 = mid;
        } else {
            t1 = mid;
        }
    }
    return (t1 + t2)/2;
}

vector<double> raices(double (*f)(double), double t_start = 0, double t_end = 7, double step = 0.1) {
    vector<double> roots;
    for (double t = t_start; t <= t_end; t += step) {
        if (f(t) * f(t + step) < 0) {
            roots.push_back(raiz(f, t, t + step));
        }
    }

    sort(roots.begin(), roots.end());
    roots.erase(unique(roots.begin(), roots.end(), [](double a, double b) {
        return abs(a - b) < 1e-3;
    }), roots.end());
    return roots;
}

vector<pair<double, double>> intervalos(const vector<double> &roots, double (*f)(double), bool (*condition)(double)) {
    vector<pair<double, double>> intervals;
    vector<double> critical_points = roots;
    critical_points.insert(critical_points.begin(), 0);
    critical_points.push_back(7);
    
    for (size_t i = 0; i < critical_points.size() - 1; i++) {
        double t_test = (critical_points[i] + critical_points[i+1]) / 2;
        if (condition(f(t_test))) {
            intervals.emplace_back(critical_points[i], critical_points[i+1]);
        }
    }
    return intervals;
}

int main() {
    Gnuplot gp;
    ofstream data_file("data.txt");
    for (double t = 0; t <= 7; t += 0.1) {
        data_file << t << " " << x(t) << " " << v(t) << " " << a(t) << "\n";
    }
    data_file.close();

    gp << "set multiplot layout 1,3\n";
    gp << "set title 'Posición vs tiempo'\n";
    gp << "plot 'data.txt' using 1:2 with lines title 'x(t)'\n";
    gp << "set title 'Velocidad vs tiempo'\n";
    gp << "plot 'data.txt' using 1:3 with lines title 'v(t)'\n";
    gp << "set title 'Aceleración vs tiempo'\n";
    gp << "plot 'data.txt' using 1:4 with lines title 'a(t)'\n";
    gp << "unset multiplot\n";

    auto x_roots = raices(x);
    auto v_roots = raices(v);
    auto a_roots = raices(a);

    cout << fixed << setprecision(3);
    cout << "Raíces de x(t): ";
    for (auto root : x_roots) cout << root << " ";
    cout << "\n";

    auto x_positive = intervalos(x_roots, x, [](double val) { return val > 0; });
    auto x_negative = intervalos(x_roots, x, [](double val) { return val < 0; });

    auto v_positive = intervalos(v_roots, v, [](double val) { return val > 0; });
    auto v_negative = intervalos(v_roots, v, [](double val) { return val < 0; });

    auto a_positive = intervalos(a_roots, a, [](double val) { return val > 0; });
    auto a_negative = intervalos(a_roots, a, [](double val) { return val < 0; });

    vector<double> speed_critical = v_roots;
    speed_critical.insert(speed_critical.end(), a_roots.begin(), a_roots.end());
    sort(speed_critical.begin(), speed_critical.end());
    speed_critical.erase(unique(speed_critical.begin(), speed_critical.end(), [](double a, double b) {
        return abs(a - b) < 1e-3;
    }), speed_critical.end());

    vector<pair<double, double>> speed_increasing, speed_decreasing;
    speed_critical.insert(speed_critical.begin(), 0);
    speed_critical.push_back(7);
    
    for (size_t i = 0; i < speed_critical.size() - 1; i++) {
        double t_test = (speed_critical[i] + speed_critical[i+1]) / 2;
        double v_val = v(t_test);
        double a_val = a(t_test);
        if (v_val * a_val > 0) {
            speed_increasing.emplace_back(speed_critical[i], speed_critical[i+1]);
        } else if (v_val * a_val < 0) {
            speed_decreasing.emplace_back(speed_critical[i], speed_critical[i+1]);
        }
    }

    cout << "\n(b) Intervalos x(t) > 0:\n";
    for (auto interval : x_positive) {
        cout << "[" << interval.first << ", " << interval.second << "] ";
    }

    cout << "\n\n(c) Intervalos x(t) < 0:\n";
    for (auto interval : x_negative) {
        cout << "[" << interval.first << ", " << interval.second << "] ";
    }

    cout << "\n\n(d) Movimiento dirección positiva:\n";
    for (auto interval : v_positive) {
        cout << "[" << interval.first << ", " << interval.second << "] ";
    }

    cout << "\n\n(e) Movimiento dirección negativa:\n";
    for (auto interval : v_negative) {
        cout << "[" << interval.first << ", " << interval.second << "] ";
    }

    cout << "\n\n(f) Velocidad aumentando:\n";
    for (auto interval : a_positive) {
        cout << "[" << interval.first << ", " << interval.second << "] ";
    }

    cout << "\n\n(g) Velocidad disminuyendo:\n";
    for (auto interval : a_negative) {
        cout << "[" << interval.first << ", " << interval.second << "] ";
    }

    cout << "\n\n(h) Rapidez aumentando:\n";
    for (auto interval : speed_increasing) {
        cout << "[" << interval.first << ", " << interval.second << "] ";
    }

    cout << "\n\n(i) Rapidez disminuyendo:\n";
    for (auto interval : speed_decreasing) {
        cout << "[" << interval.first << ", " << interval.second << "] ";
    }

    return 0;
}