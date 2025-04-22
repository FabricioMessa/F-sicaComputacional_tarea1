#include <iostream>
#include <cmath>
#include <vector>
#include <cstdlib>
#include <gnuplot-iostream.h>

using namespace std;

const double PI = 3.14159265358979323846;

// (a) 
pair<double, double> polar_a_cartesianas(double magnitud, double direccion) {
    double rad = direccion * PI / 180.0;
    double x = magnitud * cos(rad);
    double y = magnitud * sin(rad);
    return make_pair(x, y);
}

// (b)
pair<double, double> cartesianas_a_polar(double x, double y) {
    double magnitud = sqrt(x*x + y*y);
    double direccion = atan2(y, x) * 180.0 / PI;
    return make_pair(magnitud, direccion);
}

// (c)
tuple<double, double, double, double> suma_vectores(const vector<double>& magnitudes, const vector<double>& direcciones) {
    double x_total = 0, y_total = 0;
    for (size_t i = 0; i < magnitudes.size(); ++i) {
        auto [x, y] = polar_a_cartesianas(magnitudes[i], direcciones[i]);
        x_total += x;
        y_total += y;
    }
    auto [magnitud_res, direccion_res] = cartesianas_a_polar(x_total, y_total);
    return make_tuple(x_total, y_total, magnitud_res, direccion_res);
}

// (d)
double angulo_entre_vectores(const vector<double>& v1, const vector<double>& v2) {
    double dot_product = v1[0]*v2[0] + v1[1]*v2[1] + v1[2]*v2[2];
    double norm_v1 = sqrt(v1[0]*v1[0] + v1[1]*v1[1] + v1[2]*v1[2]);
    double norm_v2 = sqrt(v2[0]*v2[0] + v2[1]*v2[1] + v2[2]*v2[2]);
    double cos_theta = dot_product / (norm_v1 * norm_v2);
    return acos(cos_theta) * 180.0 / PI;
}

// (e)
double area_paralelogramo(const vector<double>& v1, const vector<double>& v2) {
    double cross_x = v1[1]*v2[2] - v1[2]*v2[1];
    double cross_y = v1[2]*v2[0] - v1[0]*v2[2];
    double cross_z = v1[0]*v2[1] - v1[1]*v2[0];
    return sqrt(cross_x*cross_x + cross_y*cross_y + cross_z*cross_z);
}

void graficar_vectores_2d(const vector<pair<double, double>>& vectores, const string& titulo) {
    Gnuplot gp;
    gp << "set xrange [-10:10]\nset yrange [-10:10]\n";
    gp << "set title '" << titulo << "'\n";
    gp << "plot ";
    for (size_t i = 0; i < vectores.size(); ++i) {
        gp << "'-' with vectors head filled lt " << i+2;
        if (i != vectores.size() - 1) gp << ", ";
    }
    gp << "\n";
    for (const auto& v : vectores) {
        gp << "0 0 " << v.first << " " << v.second << "\ne\n";
    }
}

int main() {
    // (a) 
    auto [x, y] = polar_a_cartesianas(5, 45);
    cout << "(a) Coordenadas cartesianas: (" << x << ", " << y << ")" << endl;
    graficar_vectores_2d({{x, y}}, "Vector en 2D");

    // (b)
    auto [magnitud, direccion] = cartesianas_a_polar(3, 4);
    cout << "(b) Magnitud: " << magnitud << ", Dirección: " << direccion << "°" << endl;

    // (c)
    vector<double> magnitudes = {2, 3, 4};
    vector<double> direcciones = {30, 90, 150};
    auto [x_res, y_res, mag_res, dir_res] = suma_vectores(magnitudes, direcciones);
    cout << "(c) Resultante: (" << x_res << ", " << y_res << "), Magnitud: " << mag_res << ", Dirección: " << dir_res << "°" << endl;
    vector<pair<double, double>> vectores;
    for (size_t i = 0; i < magnitudes.size(); ++i) {
        vectores.push_back(polar_a_cartesianas(magnitudes[i], direcciones[i]));
    }
    vectores.emplace_back(x_res, y_res);
    graficar_vectores_2d(vectores, "Suma de tres vectores");

    // (d)
    vector<double> v1 = {1, 0, 0};
    vector<double> v2 = {0, 1, 0};
    double angulo = angulo_entre_vectores(v1, v2);
    cout << "(d) Ángulo entre vectores: " << angulo << "°" << endl;

    // (e)
    double area = area_paralelogramo(v1, v2);
    cout << "(e) Área del paralelogramo: " << area << endl;

    return 0;
}