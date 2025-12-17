#include <iostream>
#include <vector>
#include <numeric>
#include <cmath>
#include <iomanip>
#include <algorithm>

using namespace std;

// Funcion auxiliar para factorial
long long factorial(int n, long long& count) {
    if (n < 0) return 0;
    if (n == 0 || n == 1) return 1;

    long long res = 1;
    count++;

    for (int i = 2; i <= n; i++) {
        res *= i;
        count += 2;
    }
    return res;
}

// Funcion para calcular combinaciones C(n, k)
long long combinaciones(int n, int k, long long& op_count) {
    if (k < 0 || k > n)
        return 0;
    // Optimizacion C(n,k)
    if (k > n / 2) {
        k = n - k;
    }

    long long loop_op_count = 0;
    long long res = 1;
    loop_op_count++;

    for (int i = 0; i < k; ++i) {
        res = res * (n - i) / (i + 1);
        loop_op_count += 4; // Comparacion/Incremento/Calculo
    }
    loop_op_count++;
    op_count += loop_op_count;
    return res;
}

// Funcion para calcular permutaciones P(n, k)
long long permutaciones(int n, int k, long long& count) {
    if (k < 0 || k > n)
        return 0;

    long long res = 1;
    count++; // Inicializacion res = 1

    for (int i = 0; i < k; ++i) {
        res *= (n - i);
        count += 3; // Multiplicacion, resta y ciclo
    }
    return res;
}

struct Estudiante {
    int id;
    bool es_grupo_especial;
};

void ejecutar_programa() {
    int n, k;
    long long total_operaciones = 0;

    cout << "========================================" << endl;
    cout << "     GESTION DE COMITES ESTUDIANTILES   " << endl;
    cout << "========================================" << endl;

    // AQUI ESTA EL CAMBIO VISUAL PARA QUE NO SE AMONTONE
    cout << "Ingrese el numero total de estudiantes (n): ";
    cin >> n;

    cout << "Ingrese el tamano del comite (k): ";
    cin >> k;

    cout << "----------------------------------------" << endl;

    // Crear vector (requisito de la orden)
    vector<Estudiante> estudiantes(n);
    for (int i = 0; i < n; ++i) {
        estudiantes[i].id = i + 1;
        estudiantes[i].es_grupo_especial = false;
    }

    // 1. Calculo de Combinaciones
    cout << "\n1. Calculo de Combinaciones" << endl;
    long long num_comites = combinaciones(n, k, total_operaciones);

    cout << "> Formula: C(n, k) = n! / (k! * (n-k)!)" << endl;
    cout << "Con n = " << n << " y k = " << k << ", el numero de comites distintos es: " << num_comites << endl;

    // 2. Calculo de Permutaciones
    cout << "\n2. Calculo de Permutaciones" << endl;
    long long num_ordenaciones = permutaciones(k, k, total_operaciones);
    cout << "> Permutacion Lineal (P(k, k) = k!):" << endl;
    cout << "Formas de ordenar a los " << k << " integrantes en linea: " << num_ordenaciones << endl;

    // Permutacion Circular: P_c(k) = (k-1)!
    long long perm_circular = (k > 0) ? factorial(k - 1, total_operaciones) : 0;
    cout << "> Permutacion Circular (P_c(k) = (k-1)!):" << endl;
    cout << "Formas de sentar a los " << k << " integrantes en una mesa: " << perm_circular << endl;

    // 3. Probabilidad con Regla de Laplace
    cout << "\n3. Probabilidad con la Regla de Laplace" << endl;
    int m;
    cout << "Ingrese numero de estudiantes en Grupo Especial (m): ";
    cin >> m;

    if (m < 0 || m > n) {
        cout << "Error: m debe estar entre 0 y n." << endl;
        return;
    }

    // Asignar grupo especial en el vector
    for (int i = 0; i < m; ++i) {
        estudiantes[i].es_grupo_especial = true;
    }

    cout << "> Laplace: P(E) = Casos Favorables / Casos Totales" << endl;
    int n_no_especial = n - m;
    long long comites_sin_especial = 0;
    if (k <= n_no_especial) {
        comites_sin_especial = combinaciones(n_no_especial, k, total_operaciones);
    } else {
        comites_sin_especial = 0;
    }

    long long comites_con_al_menos_uno = num_comites - comites_sin_especial;
    double probabilidad_laplace = (num_comites > 0) ? (double)comites_con_al_menos_uno / num_comites : 0.0;

    cout << "Total comites (Casos Totales): " << num_comites << endl;
    cout << "Comites SIN especiales (Desfavorables): " << comites_sin_especial << endl;
    cout << "Comites CON al menos un especial (Favorables): " << comites_con_al_menos_uno << endl;
    cout << fixed << setprecision(6);
    cout << "Probabilidad P(al menos uno): " << probabilidad_laplace << endl;

    // 4. Teorema de Bayes
    cout << "\n4. Aplicacion del Teorema de Bayes" << endl;
    cout << "> Escenario: Probabilidad de que el comite sea del Grupo A dado que aprobo." << endl;

    double p_a = 0.60;
    double p_b = 1.0 - p_a;
    double p_aprueba_dado_a = 0.85;
    double p_aprueba_dado_b = 0.70;

    double p_aprueba = (p_aprueba_dado_a * p_a) + (p_aprueba_dado_b * p_b);
    total_operaciones += 3;

    double p_a_dado_aprueba = (p_aprueba_dado_a * p_a) / p_aprueba;
    total_operaciones += 2;

    cout << fixed << setprecision(4);
    cout << "P(A): " << p_a << " | P(B): " << p_b << endl;
    cout << "P(Aprueba|A): " << p_aprueba_dado_a << " | P(Aprueba|B): " << p_aprueba_dado_b << endl;
    cout << "P(Aprueba): " << p_aprueba << endl;
    cout << "Resultado Bayes P(A|Aprueba): " << p_a_dado_aprueba << endl;

    // 5. Analisis de operaciones
    cout << "\n5. Analisis de Eficiencia" << endl;
    cout << "Total de operaciones basicas contadas: " << total_operaciones << endl;
    cout << "Crecimiento estimado: Lineal O(k) (proporcional al tamano del comite)" << endl;
    cout << "========================================" << endl;
}

int main() {
    // ELIMINE LAS LINEAS DE OPTIMIZACION (cin.tie y sync_with_stdio)
    // PARA QUE LOS MENSAJES SALGAN EN ORDEN CORRECTO.

    ejecutar_programa();

    return 0;
}
