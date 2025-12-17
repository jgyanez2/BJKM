#include <iostream>  // Libreria estandar para entrada y salida (cin, cout)
#include <vector>    // Libreria para usar el contenedor vector (arreglo dinamico)
#include <numeric>   // Libreria para operaciones numericas adicionales
#include <cmath>     // Libreria para funciones matematicas
#include <iomanip>   // Libreria para manipular el formato de salida (setprecision)
#include <algorithm> // Libreria para algoritmos estandar (aunque aqui usamos logica propia)

using namespace std;

// ==========================================
// FUNCIONES MATEMATICAS AUXILIARES
// ==========================================

// Funcion auxiliar para calcular el factorial de un numero (n!)
// Tambien lleva la cuenta de operaciones elementales realizadas.
long long factorial(int n, long long& count) {
    // Casos base: factorial de negativo es 0 (error), de 0 o 1 es 1.
    if (n < 0) return 0;
    if (n == 0 || n == 1) return 1;

    long long res = 1;
    count++; // Contamos la asignacion inicial

    // Ciclo que multiplica desde 2 hasta n
    for (int i = 2; i <= n; i++) {
        res *= i;   // Operacion principal: multiplicacion
        count += 2; // Contamos la multiplicacion y el incremento del ciclo
    }
    return res;
}

// Funcion para calcular Combinaciones: C(n, k)
// Representa cuantos subconjuntos de tamaño k se pueden formar de n elementos.
long long combinaciones(int n, int k, long long& op_count) {
    // Validacion: k no puede ser negativo ni mayor que n
    if (k < 0 || k > n)
        return 0;
    
    // Optimizacion matematica: C(n, k) es igual a C(n, n-k).
    // Si k es grande, calculamos el complemento para hacer menos multiplicaciones.
    if (k > n / 2) {
        k = n - k;
    }
    
    long long loop_op_count = 0;
    long long res = 1;
    loop_op_count++;

    // Algoritmo eficiente para calcular combinaciones sin calcular factoriales gigantes
    // Formula iterativa: res = res * (n - i) / (i + 1)
    for (int i = 0; i < k; ++i) {
        res = res * (n - i) / (i + 1);
        loop_op_count += 4; // Contamos multiplicacion, division, resta y control del ciclo
    }
    loop_op_count++;
    op_count += loop_op_count; // Sumamos al contador global de operaciones
    return res;
}

// Funcion para calcular Permutaciones: P(n, k)
// Importa el orden de los elementos.
long long permutaciones(int n, int k, long long& count) {
    if (k < 0 || k > n)
        return 0;

    long long res = 1;
    count++; // Inicializacion res = 1

    // Formula simplificada: n * (n-1) * ... * (n-k+1)
    for (int i = 0; i < k; ++i) {
        res *= (n - i);
        count += 3; // Contamos Multiplicacion, resta y operacion del ciclo
    }
    return res;
}

// Estructura para representar a un estudiante
struct Estudiante {
    int id;                 // Identificador del estudiante
    bool es_grupo_especial; // Bandera para saber si pertenece al grupo especial (para Laplace)
};

// ==========================================
// LOGICA PRINCIPAL DEL PROGRAMA
// ==========================================

void ejecutar_programa() {
    int n, k;
    long long total_operaciones = 0; // Variable acumuladora para medir eficiencia

    // --- ENCABEZADO E INGRESO DE DATOS ---
    cout << "========================================" << endl;
    cout << "     GESTION DE COMITES ESTUDIANTILES   " << endl;
    cout << "========================================" << endl;
    
    // Pedimos datos al usuario con saltos de linea claros
    cout << "Ingrese el numero total de estudiantes (n): ";
    cin >> n;
    
    cout << "Ingrese el tamano del comite (k): ";
    cin >> k;
    
    cout << "----------------------------------------" << endl;

    // Crear vector de estudiantes (requisito de la orden)
    // Inicializamos a todos como NO pertenecientes al grupo especial por defecto
    vector<Estudiante> estudiantes(n);
    for (int i = 0; i < n; ++i) {
        estudiantes[i].id = i + 1;
        estudiantes[i].es_grupo_especial = false; 
    }

    // --- 1. CALCULO DE COMBINACIONES ---
    cout << "\n1. Calculo de Combinaciones" << endl;
    // Llamamos a la funcion y pasamos total_operaciones por referencia para contar pasos
    long long num_comites = combinaciones(n, k, total_operaciones);

    cout << "> Formula: C(n, k) = n! / (k! * (n-k)!)" << endl;
    cout << "Con n = " << n << " y k = " << k << ", el numero de comites distintos es: " << num_comites << endl;

    // --- 2. CALCULO DE PERMUTACIONES ---
    cout << "\n2. Calculo de Permutaciones" << endl;
    
    // Permutacion Lineal: Importa el orden en una fila
    long long num_ordenaciones = permutaciones(k, k, total_operaciones);
    cout << "> Permutacion Lineal (P(k, k) = k!):" << endl;
    cout << "Formas de ordenar a los " << k << " integrantes en linea: " << num_ordenaciones << endl;

    // Permutacion Circular: Importa el orden en un circulo (mesa redonda)
    // Formula: (k-1)! porque rotaciones se consideran iguales
    long long perm_circular = (k > 0) ? factorial(k - 1, total_operaciones) : 0;
    cout << "> Permutacion Circular (P_c(k) = (k-1)!):" << endl;
    cout << "Formas de sentar a los " << k << " integrantes en una mesa: " << perm_circular << endl;

    // --- 3. PROBABILIDAD (REGLA DE LAPLACE) ---
    cout << "\n3. Probabilidad con la Regla de Laplace" << endl;
    int m;
    cout << "Ingrese numero de estudiantes en Grupo Especial (m): ";
    cin >> m;

    // Validacion basica de entrada
    if (m < 0 || m > n) {
        cout << "Error: m debe estar entre 0 y n." << endl;
        return; // Salimos si el dato es incorrecto
    }
    
    // Marcamos a los primeros m estudiantes como 'especiales' en el vector
    for (int i = 0; i < m; ++i) {
        estudiantes[i].es_grupo_especial = true;
    }

    cout << "> Laplace: P(E) = Casos Favorables / Casos Totales" << endl;
    
    // Estrategia: Calcular probabilidad usando el COMPLEMENTO.
    // P(al menos uno) = 1 - P(ninguno)
    // Primero calculamos cuantos comites se pueden formar SOLO con los NO especiales.
    int n_no_especial = n - m;
    long long comites_sin_especial = 0;
    
    if (k <= n_no_especial) {
        comites_sin_especial = combinaciones(n_no_especial, k, total_operaciones);
    } else {
        comites_sin_especial = 0; // Si el comite es mas grande que los disponibles, es imposible hacer uno sin especiales
    }

    // Restamos para obtener los casos favorables (comites con al menos un especial)
    long long comites_con_al_menos_uno = num_comites - comites_sin_especial;
    
    // Calculo final de probabilidad (protegemos division por cero)
    double probabilidad_laplace = (num_comites > 0) ? (double)comites_con_al_menos_uno / num_comites : 0.0;

    // Mostramos resultados detallados
    cout << "Total comites (Casos Totales): " << num_comites << endl;
    cout << "Comites SIN especiales (Desfavorables): " << comites_sin_especial << endl;
    cout << "Comites CON al menos un especial (Favorables): " << comites_con_al_menos_uno << endl;
    
    cout << fixed << setprecision(6); // Ajustamos decimales
    cout << "Probabilidad P(al menos uno): " << probabilidad_laplace << endl;

    // --- 4. TEOREMA DE BAYES ---
    cout << "\n4. Aplicacion del Teorema de Bayes" << endl;
    cout << "> Escenario: Probabilidad de que el comite sea del Grupo A dado que aprobo." << endl;

    // Definimos probabilidades base (Hardcoded segun ejemplo de la orden)
    double p_a = 0.60;              // Probabilidad de ser del Grupo A
    double p_b = 1.0 - p_a;         // Probabilidad de ser del Grupo B (Complemento)
    double p_aprueba_dado_a = 0.85; // P(Aprueba|A)
    double p_aprueba_dado_b = 0.70; // P(Aprueba|B)

    // 1. Probabilidad Total de Aprobar (Denominador de Bayes)
    double p_aprueba = (p_aprueba_dado_a * p_a) + (p_aprueba_dado_b * p_b); 
    total_operaciones += 3; // Contamos las operaciones aritmeticas

    // 2. Aplicacion de Bayes: P(A|Aprueba) = (P(Aprueba|A) * P(A)) / P(Aprueba)
    double p_a_dado_aprueba = (p_aprueba_dado_a * p_a) / p_aprueba; 
    total_operaciones += 2; // Contamos operaciones

    cout << fixed << setprecision(4);
    cout << "P(A): " << p_a << " | P(B): " << p_b << endl;
    cout << "P(Aprueba|A): " << p_aprueba_dado_a << " | P(Aprueba|B): " << p_aprueba_dado_b << endl;
    cout << "P(Aprueba): " << p_aprueba << endl;
    cout << "Resultado Bayes P(A|Aprueba): " << p_a_dado_aprueba << endl;

    // --- 5. ANALISIS DE EFICIENCIA ---
    cout << "\n5. Analisis de Eficiencia" << endl;
    // Mostramos cuantas operaciones elementales (sumas, restas, mult, asignaciones) contamos
    cout << "Total de operaciones basicas contadas: " << total_operaciones << endl;
    // Conclusion sobre complejidad algoritmica
    cout << "Crecimiento estimado: Lineal O(k) (proporcional al tamano del comite)" << endl;
    cout << "========================================" << endl;
}

int main() {
    // Funcion principal limpia, solo llama a la logica del programa
    ejecutar_programa();
    return 0;
}
