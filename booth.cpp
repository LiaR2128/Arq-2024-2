#include <iostream>
#include <cmath>
#include <bitset>
#include <string>
using namespace std;

// Función para mostrar un número en formato binario
void mostrarBinario(int valor, int longitud) {
    string bin = bitset<32>(valor).to_string().substr(32 - longitud, longitud);
    cout << bin << endl;
}

// Convertir decimal a binario manteniendo 'n' bits
int convertirDecimalABinario(int valorDecimal, int longitud) {
    return valorDecimal & ((1 << longitud) - 1); // 1 << n desplaza 1 n posiciones a la izquierda.
}

// Obtener el complemento a 2 de un número
int obtenerComplemento2(int valor, int longitud) {
    return (1 << longitud) - valor;
}

// Sumar dos números binarios usando 'n' bits
int sumaBinaria(int valor1, int valor2, int longitud) {
    int suma = valor1 + valor2;
    return suma & ((1 << longitud) - 1);
}

// Restar dos números binarios usando complemento a 2
int restaBinaria(int minuendo, int sustraendo, int longitud) {
    sustraendo = obtenerComplemento2(sustraendo, longitud); // Utiliza complemento a 2 si el resultado es negativo
    return sumaBinaria(minuendo, sustraendo, longitud); // Sumar es equivalente a restar usando complemento
}

// Desplazamiento aritmético a la derecha
int desplazarDerecha(int valor, int longitud) {
    int bitSigno = (valor >> (longitud - 1)) & 1; // Obtener el bit de signo
    int resultado = (valor >> 1) & ((1 << (longitud - 1)) - 1); // Desplazamiento a la derecha excluyendo bit de signo
    resultado |= (bitSigno << (longitud - 1)); // Restaurar el bit de signo en la posición correspondiente
    return resultado;
}

// Función para realizar multiplicación binaria con n bits
int multiplicar(int mult, int factor, int bits) {
    int M = mult;
    int A = 0;
    int Q = factor;
    int QNeg = (Q < 0) ? convertirDecimalABinario(-Q, bits) : convertirDecimalABinario(Q, bits);
    int S = (Q < 0) ? convertirDecimalABinario(-M, bits) : convertirDecimalABinario(M, bits);
    
    int bitActual = 0;
    int bitPrevio = 0;

    for(int i = 0; i < bits; i++) {
        int bitSuperior = (Q >> (bits - 1 - i)) & 1; // Obtener bit más significativo de Q

        if (bitSuperior == 1 && bitPrevio == 0) {
            A = restaBinaria(A, S, bits);
            A = desplazarDerecha(A, bits);
            Q = desplazarDerecha(Q, bits);
        } else if (bitSuperior == 0 && bitPrevio == 1) {
            A = sumaBinaria(A, S, bits);
            A = desplazarDerecha(A, bits);
            Q = desplazarDerecha(Q, bits);
        } else if ((bitSuperior == 0 && bitPrevio == 0) || (bitSuperior == 1 && bitPrevio == 1)) {
            A = desplazarDerecha(A, bits);
            Q = desplazarDerecha(Q, bits);
        }
        // Desplazar A y Q a la derecha en cada iteración
        bitPrevio = bitSuperior; // Actualizar el bit previo para la siguiente iteración
    }

    if (QNeg & (1 << (bits - 1))) {
        return obtenerComplemento2(A, bits); // Si el número original era negativo, se devuelve el complemento a 2
    }

    return A;
}

int main() {
    int numBits;
    int multiplicando;
    int multiplicador;

    cout << "Indique la cantidad de bits: ";
    cin >> numBits;

    cout << "Ingrese el multiplicando: ";
    cin >> multiplicando;

    cout << "Ingrese el multiplicador: ";
    cin >> multiplicador;

    int resultadoFinal = multiplicar(multiplicando, multiplicador, numBits);

    cout << "Resultado en decimal: " << resultadoFinal << endl;
    cout << "Resultado en binario: ";
    mostrarBinario(resultadoFinal, numBits);
    
    return 0;
}