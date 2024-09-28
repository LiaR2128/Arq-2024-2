#include <iostream>
#include <cmath>
using namespace std;

int main() {
    int length, multiplicand[10000], multiplier[10000];
    cout << "Por favor, ingrese la longitud de los vectores: ";
    cin >> length;

    // Verificar si el tamaño del bit es 1
    if (length == 1) {
        cout << "Ingrese el valor del multiplicando: ";
        cin >> multiplicand[0];
        cout << "-----------------------------\n";
        cout << "Ingrese el valor del multiplicador: ";
        cin >> multiplier[0];

        int result = multiplicand[0] * multiplier[0];
        cout << "El resultado de la multiplicación binaria es: " << result << endl;
        return 0;
    }
    // Verificar si el usuario ingresó 0 como longitud
    else if (length == 0) {
        cout << "La longitud del vector no puede ser 0." << endl;
        return 0;
    }

    // Rellenar el multiplicando en formato binario
    for (int i = 0; i < length; i++) {
        cout << "Ingrese el valor del multiplicando (bit " << i + 1 << "): ";
        cin >> multiplicand[i];
    }

    cout << "------------------------\n";

    // Rellenar el multiplicador en formato binario
    for (int j = 0; j < length; j++) {
        cout << "Ingrese el valor del multiplicador (bit " << j + 1 << "): ";
        cin >> multiplier[j];
    }

    // Convertir los números binarios a decimales para realizar la multiplicación
    int decimal1 = 0, exponent1 = 0;
    for (int k = length - 1; k >= 0; k--) {
        decimal1 += multiplicand[k] * pow(2, exponent1);
        exponent1++;
    }

    int decimal2 = 0, exponent2 = 0;
    for (int m = length - 1; m >= 0; m--) {
        decimal2 += multiplier[m] * pow(2, exponent2);
        exponent2++;
    }

    // Multiplicar los decimales y convertir el resultado nuevamente a binario
    int product = decimal1 * decimal2;
    int binaryResult[1000], index = 0;

    while (product > 0) {
        binaryResult[index] = product % 2;
        product /= 2;
        index++;
    }

    // Mostrar el resultado en formato binario
    cout << "El resultado de la multiplicación binaria es: ";
    for (int n = index - 1; n >= 0; n--) {
        cout << binaryResult[n];
    }
    cout << endl;

    return 0;
}