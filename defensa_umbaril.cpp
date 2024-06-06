#include <iostream>
#include <cmath>

using namespace std;

const float g = 9.81;

void leerDatos(int &Xo, int &Yo, int &Vo, int &theta, int &M) {
    cout << "Ingrese la posicion inicial (Xo Yo), velocidad inicial (Vo), angulo (theta) y numero de objetivos (M):\n";
    cin >> Xo >> Yo >> Vo >> theta >> M;

    // Validaciones de entrada
    while (cin.fail() || Vo <= 0 || M <= 0) {
        cin.clear(); // Limpiar el estado de error
        while (cin.get() != '\n') ; // Descartar la entrada inválida
        cout << "Entrada invalida. Por favor, ingrese nuevamente:\n";
        cin >> Xo >> Yo >> Vo >> theta >> M;
    }
}

void calcularResultados(int Xo, int Yo, int Vo, int theta, int M) {
    float Vx = Vo * cos(theta * M_PI / 180.0);
    float Vy = Vo * sin(theta * M_PI / 180.0);
    float H = (Vy * Vy) / (2 * g);
    float T = 2 * Vy / g;

    cout << "Los proyectiles subiran hasta " << round(H) << " metros antes de comenzar a caer.\n";
    cout << "Estos impactaran contra el suelo pasados " << round(T) << " segundos luego de ser disparados.\n";
    
    for(int i = 0; i < M; ++i) {
        int X, Y;
        cout << "Ingrese la posicion del objetivo " << (i + 1) << " (X Y):\n";
        cin >> X >> Y;

        // Validaciones de entrada
        while (cin.fail()) {
            cin.clear(); // Limpiar el estado de error
            while (cin.get() != '\n') ; // Descartar la entrada inválida
            cout << "Entrada invalida. Por favor, ingrese nuevamente:\n";
            cin >> X >> Y;
        }

        if (X == Xo && Y == Yo) {
            cout << "Canon destruido\n";
            break;
        } else if (X < Xo) {
            cout << "Posicion Comprometida\n";
        } else if (Y <= Yo) {
            cout << "Enemigos en las murallas\n";
        } else {
            float tImpacto = (X - Xo) / Vx;
            float yImpacto = Yo + Vy * tImpacto - 0.5 * g * tImpacto * tImpacto;
            
            if (round(yImpacto) == round(Y)) {
                cout << "Objetivo " << (i + 1) << " destruido en " << round(tImpacto) << " segundos\n";
            } else {
                cout << "Reajuste de " << round(atan((Y - Yo) / (X - Xo)) * 180.0 / M_PI - theta) << " grados requerido\n";
            }
        }
    }
}

int main() {
    int N;
    cout << "Ingrese el numero de canones:\n";
    cin >> N;

    // Validación de entrada
    while (cin.fail() || N <= 0) {
        cin.clear(); // Limpiar el estado de error
        while (cin.get() != '\n') ; // Descartar la entrada inválida
        cout << "Entrada invalida. Por favor, ingrese un numero valido de canones:\n";
        cin >> N;
    }

    for(int i = 0; i < N; ++i) {
        int Xo, Yo, Vo, theta, M;
        leerDatos(Xo, Yo, Vo, theta, M);
        calcularResultados(Xo, Yo, Vo, theta, M);
    }
    
    return 0;
}
