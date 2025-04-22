#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <iomanip>
#include <functional>

using namespace std;

struct Punto {
    double t;
    double x;
    double v;
    double a;
};

double posicion(double t) {
    return 5 + 13.4 * t - 7.36 * t * t + 0.8 * pow(t, 3);
}

double velocidad(double t) {
    return 13.4 - 14.72 * t + 2.4 * t * t;
}

double aceleracion(double t) {
    return -14.72 + 4.8 * t;
}

//b)
void encontrarIntervalos(const vector<Punto>& datos, const string& descripcion, const function<bool(const Punto&)>& condicion, ofstream& archivo) {
    bool activo = false;
    double inicio = 0;

    cout << "\n" << descripcion << ":\n";
    archivo << "\n" << descripcion << ":\n";
    
    for (size_t i = 0; i < datos.size(); ++i) {
        if (condicion(datos[i]) && !activo) {
            inicio = datos[i].t;
            activo = true;
        }
        else if (!condicion(datos[i]) && activo) {
            cout << "  desde t = " << fixed << setprecision(2) << inicio
                << "s hasta t = " << datos[i].t << "s\n";
            archivo << "  desde t = " << fixed << setprecision(2) << inicio
                << "s hasta t = " << datos[i].t << "s\n";
            activo = false;
        }
    }
    
    if (activo) {
        cout << "  desde t = " << fixed << setprecision(2) << inicio
            << "s hasta t = " << datos.back().t << "s\n";
        archivo << "  desde t = " << fixed << setprecision(2) << inicio
            << "s hasta t = " << datos.back().t << "s\n";
    }
}

int main() {
    vector<Punto> datos;
    double dt = 0.01;

    ofstream fx("x_data.txt"), fv("v_data.txt"), fa("a_data.txt");
    ofstream resultados("resultados_intervalos.txt");
    
    //a)
    for (double t = 0; t <= 7.0; t += dt) {
        double xt = posicion(t);
        double vt = velocidad(t);
        double at = aceleracion(t);
        datos.push_back({ t, xt, vt, at });
    
        fx << t << " " << xt << "\n";
        fv << t << " " << vt << "\n";
        fa << t << " " << at << "\n";
    }
    
    fx.close(); fv.close(); fa.close();
    
    //b)
    encontrarIntervalos(datos, "(b) Posición positiva (x > 0)", [](const Punto& p) { return p.x > 0; }, resultados);
    //c)
    encontrarIntervalos(datos, "(c) Posición negativa (x < 0)", [](const Punto& p) { return p.x < 0; }, resultados);
    //d)
    encontrarIntervalos(datos, "(d) Movimiento hacia +x (v > 0)", [](const Punto& p) { return p.v > 0; }, resultados);
    //e)
    encontrarIntervalos(datos, "(e) Movimiento hacia -x (v < 0)", [](const Punto& p) { return p.v < 0; }, resultados);
    //f)
    encontrarIntervalos(datos, "(f) Velocidad aumentando (a > 0)", [](const Punto& p) { return p.a > 0; }, resultados);
    //g)
    encontrarIntervalos(datos, "(g) Velocidad disminuyendo (a < 0)", [](const Punto& p) { return p.a < 0; }, resultados);
    //h)
    encontrarIntervalos(datos, "(h) Rapidez aumentando (v * a > 0)", [](const Punto& p) { return p.v * p.a > 0; }, resultados);
    //i)
    encontrarIntervalos(datos, "(i) Rapidez disminuyendo (v * a < 0)", [](const Punto& p) { return p.v * p.a < 0; }, resultados);
    
    resultados.close();
    
    //a)
    system("gnuplot -persist -e \""
        "set title 'x(t), v(t), a(t)';"
        "set multiplot layout 1,3 title 'Gráficas de Movimiento';"
        "set xlabel 'Tiempo (s)';"
        "plot 'x_data.txt' with lines title 'x(t)' lw 2;"
        "plot 'v_data.txt' with lines title 'v(t)' lw 2;"
        "plot 'a_data.txt' with lines title 'a(t)' lw 2;"
        "unset multiplot\"");
    
    return 0;
}