#include <iostream>
#include <vector>
#include <limits>

using namespace std;

class Matriz {
private:
    vector<vector<double>> datos;
    int filas;
    int columnas;

public:
    // Constructor por defecto.
    Matriz() : filas(0), columnas(0) {}

    // Constructor con dimensiones.
    Matriz(int f, int c) : filas(f), columnas(c) {
        datos.resize(filas, vector<double>(columnas, 0));
    }

    // Método para redimensionar.
    void redimensionar(int f, int c) {
        filas = f;
        columnas = c;
        datos.resize(filas, vector<double>(columnas, 0));
    }

    // Método para entrada de datos.
    void leerMatriz() {
        cout << "Ingrese los elementos de la matriz (" << filas << "x" << columnas << "):\n";
        for (int i = 0; i < filas; i++) {
            for (int j = 0; j < columnas; j++) {
                while (!(cin >> datos[i][j])) {
                    cout << "Entrada inválida. Ingrese un número: ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
            }
        }
    }

    // Método para mostrar matriz.
    void mostrarMatriz() {
        for (int i = 0; i < filas; i++) {
            for (int j = 0; j < columnas; j++) {
                cout << datos[i][j] << "\t";
            }
            cout << endl;
        }
    }

    // Operación de suma.
    Matriz operator+(const Matriz& otra) {
        if (filas != otra.filas || columnas != otra.columnas) {
            throw invalid_argument("Las dimensiones de las matrices no coinciden para la suma.");
        }

        Matriz resultado(filas, columnas);
        for (int i = 0; i < filas; i++) {
            for (int j = 0; j < columnas; j++) {
                resultado.datos[i][j] = datos[i][j] + otra.datos[i][j];
            }
        }
        return resultado;
    }

    // Operación de multiplicación.
    Matriz operator*(const Matriz& otra) {
        if (columnas != otra.filas) {
            throw invalid_argument("Las dimensiones no son compatibles para la multiplicación.");
        }

        Matriz resultado(filas, otra.columnas);
        for (int i = 0; i < filas; i++) {
            for (int j = 0; j < otra.columnas; j++) {
                for (int k = 0; k < columnas; k++) {
                    resultado.datos[i][j] += datos[i][k] * otra.datos[k][j];
                }
            }
        }
        return resultado;
    }
};

void limpiarBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int main() {
    int opcion;
    do {
        cout << "\nCALCULADORA DE MATRICES\n";
        cout << "1. Sumar matrices.\n";
        cout << "2. Multiplicar matrices.\n";
        cout << "3. Salir.\n";
        cout << "Seleccione una opción: ";
        
        while (!(cin >> opcion) || opcion < 1 || opcion > 3) {
            cout << "Opción inválida. Ingrese 1, 2 o 3: ";
            limpiarBuffer();
        }

        if (opcion == 3) break;

        int filas1, columnas1, filas2, columnas2;

        cout << "\nIngrese dimensiones de la primera matriz:\n";
        cout << "Filas: ";
        while (!(cin >> filas1) || filas1 <= 0) {
            cout << "Valor inválido. Ingrese un número positivo: ";
            limpiarBuffer();
        }
        cout << "Columnas: ";
        while (!(cin >> columnas1) || columnas1 <= 0) {
            cout << "Valor inválido. Ingrese un número positivo: ";
            limpiarBuffer();
        }

        Matriz m1(filas1, columnas1);
        m1.leerMatriz();

        cout << "\nIngrese dimensiones de la segunda matriz:\n";
        cout << "Filas: ";
        while (!(cin >> filas2) || filas2 <= 0) {
            cout << "Valor inválido. Ingrese un número positivo: ";
            limpiarBuffer();
        }
        cout << "Columnas: ";
        while (!(cin >> columnas2) || columnas2 <= 0) {
            cout << "Valor inválido. Ingrese un número positivo: ";
            limpiarBuffer();
        }

        Matriz m2(filas2, columnas2);
        m2.leerMatriz();

        try {
            switch (opcion) {
                case 1: {
                    Matriz resultado = m1 + m2;
                    cout << "\nResultado de la suma:\n";
                    resultado.mostrarMatriz();
                    break;
                }
                case 2: {
                    Matriz resultado = m1 * m2;
                    cout << "\nResultado de la multiplicación:\n";
                    resultado.mostrarMatriz();
                    break;
                }
            }
        } catch (const invalid_argument& e) {
            cout << "\nError: " << e.what() << endl;
        }

        cout << "\nPresione 'Enter' para continuar...";
        limpiarBuffer();
        cin.get();

    } while (opcion != 3);

    cout << "¡Hasta luego!" << endl;
    return 0;
}