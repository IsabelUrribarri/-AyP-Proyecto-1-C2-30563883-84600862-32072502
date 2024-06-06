#include <iostream>
#include <cmath>

using namespace std;

const float g = 9.81;

void leerDatos(int &Xo, int &Yo, int &Vo, int &theta, int &M) {
    cin >> Xo >> Yo >> Vo >> theta >> M;

    // Validaciones de entrada
    while (cin.fail() || Vo <= 0 || M <= 0 || theta < 0 || theta > 180) {
        cin.clear(); // Limpiar el estado de error
        while (cin.get() != '\n'); // Descartar la entrada invalida
        cout << "Datos de entrada invalidos\n";
        exit(0);
    }
}

void calcularResultados(int Xo, int Yo, int Vo, int theta, int M, char canonID) {
    float Vx = Vo * cos(theta * M_PI / 180.0);
    float Vy = Vo * sin(theta * M_PI / 180.0);
    float H = (Vy * Vy) / (2 * g);
    float T = 2 * Vy / g;

    cout << "Los proyectiles del canon " << canonID << " subiran hasta " << (int)round(H) << " metros antes de comenzar a caer.\n";
    cout << "Estos impactaran contra el suelo pasados " << (int)round(T) << " segundos luego de ser disparados.\n";

    for (int i = 0; i < M; ++i) {
        int X, Y;
        cin >> X >> Y;

        // Validaciones de entrada
        while (cin.fail()) {
            cin.clear(); // Limpiar el estado de error
            while (cin.get() != '\n'); // Descartar la entrada invalida
            cout << "Datos de entrada invalidos\n";
            exit(0);
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

            if ((int)round(yImpacto) == (int)round(Y)) {
                cout << "Objetivo " << (i + 1) << " destruido por el canon " << canonID << " en " << (int)round(tImpacto) << " segundos\n";
            } else {
                float ajuste = atan((Y - Yo) / (float)(X - Xo)) * 180.0 / M_PI - theta;
                cout << "Reajuste de " << (int)round(ajuste) << " grados requerido en el canon " << canonID << "\n";
            }
        }
    }
    cout << "=" << endl;
}

int main() {
    int N;
    cin >> N;

    // Validacion de entrada
    while (cin.fail() || N <= 0) {
        cin.clear(); // Limpiar el estado de error
        while (cin.get() != '\n'); // Descartar la entrada invalida
        cout << "Datos de entrada invalidos\n";
        exit(0);
    }

    for (int i = 0; i < N; ++i) {
        int Xo, Yo, Vo, theta, M;
        leerDatos(Xo, Yo, Vo, theta, M);
        char canonID = 'A' + i;
        calcularResultados(Xo, Yo, Vo, theta, M, canonID);
    }

    return 0;
}