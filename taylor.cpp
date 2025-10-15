#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <cmath>
#include <iomanip>

struct Polinomio {
    std::vector<double> coeficientes;
    std::string texto;
};

long double factorial(int n) {
    if (n == 0) {
        return 1;
    }
    long double result = 1;
    for (int i = 1; i <= n; ++i) {
        result *= i;
    }
    return result;
}

double evaluar(const Polinomio& p, double x) {
    double resultado = 0.0;
    for (size_t i = 0; i < p.coeficientes.size(); ++i) {
        if (p.coeficientes[i] != 0) {
            resultado += p.coeficientes[i] * pow(x, i);
        }
    }
    return resultado;
}

std::string generarTextoPolinomio(const std::vector<double>& coefs) {
    if (coefs.empty()) {
        return "0";
    }

    std::stringstream ss;
    bool primerTermino = true;

    for (int i = coefs.size() - 1; i >= 0; --i) {
        if (coefs[i] == 0) continue;

        if (!primerTermino && coefs[i] > 0) {
            ss << " + ";
        } else if (coefs[i] < 0) {
            ss << (primerTermino ? "-" : " - ");
        }

        double absCoef = std::abs(coefs[i]);
        if (absCoef != 1 || i == 0) {
            ss << absCoef;
        }

        if (i > 0) {
            ss << "x";
            if (i > 1) {
                ss << "^" << i;
            }
        }
        primerTermino = false;
    }
    return ss.str();
}


Polinomio derivar(const Polinomio& p) {
    Polinomio derivada;
    if (p.coeficientes.size() <= 1) {
        derivada.texto = "0";
        return derivada;
    }

    std::vector<double> nuevos_coeficientes(p.coeficientes.size() - 1);
    for (size_t i = 1; i < p.coeficientes.size(); ++i) {
        nuevos_coeficientes[i - 1] = p.coeficientes[i] * i;
    }

    derivada.coeficientes = nuevos_coeficientes;
    derivada.texto = generarTextoPolinomio(nuevos_coeficientes);
    return derivada;
}

std::string obtenerPrefijoFuncion(int orden) {
    if (orden == 0) return "f(x) = ";
    std::string prefijo = "f";
    prefijo.append(orden, '\'');
    prefijo += "(x) = ";
    return prefijo;
}


int main() {
    Polinomio p_actual;
    p_actual.coeficientes = {-20, 8, -3, 5};
    p_actual.texto = generarTextoPolinomio(p_actual.coeficientes);

    double punto_central = 1.0;
    double punto_a_estimar = 2.0;
    int max_orden = 10;

    double suma_acumulada = 0.0;

    std::cout << std::left << std::setw(8) << "Orden"
              << std::setw(35) << "Funcion"
              << std::setw(28) << "Evaluacion a punto central"
              << std::setw(20) << "Termino de la Serie"
              << std::setw(20) << "Suma Acumulada" << std::endl;
    std::cout << std::string(111, '-') << std::endl;

    for (int orden = 0; orden <= max_orden; ++orden) {

        double evaluacion_en_centro = evaluar(p_actual, punto_central);

        double termino_serie = evaluacion_en_centro / factorial(orden) * pow(punto_a_estimar - punto_central, orden);

        suma_acumulada += termino_serie;

        std::cout << std::left << std::setw(8) << orden
                  << std::setw(35) << (obtenerPrefijoFuncion(orden) + p_actual.texto)
                  << std::setw(28) << evaluacion_en_centro
                  << std::setw(20) << termino_serie
                  << std::setw(20) << suma_acumulada << std::endl;

        p_actual = derivar(p_actual);
    }

    return 0;
}
