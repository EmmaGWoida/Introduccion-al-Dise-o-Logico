#include <stdio.h>
#include <stdint.h>

int main() {
    int16_t hex_value;

    // Pedimos el número en hexadecimal
    printf("Ingrese un número hexadecimal (ej: 0XFE5C): ");
    scanf("%hx", &hex_value);  // %hx para leer un número hexadecimal de 16 bits con signo

    // Extraer la parte entera
    int16_t entero = hex_value / 256;

    // Extraer la parte fraccionaria (8 bits inferiores)
    int16_t fraccion_binaria = hex_value & 0xFF;

    // Convertir la parte fraccionaria a 4 dígitos decimales
    int16_t fraccion = (fraccion_binaria * 10000) / 256;

    // Ajuste si el número es negativo (complemento a dos)
    if (hex_value < 0 && fraccion_binaria != 0) {
        fraccion = 10000 - fraccion;  // Complemento de la parte fraccionaria
    }

    // Imprimimos el resultado en formato decimal con 3 decimales
    if (entero < -128 || entero > 127) {
        printf("Error: El nUmero no se puede representar en formato Q(7,8).\n");
        return 1;
    }
    // Imprimir resultado con 3 dígitos en la parte entera y 4 en la fraccionaria
    printf("El valor en Q(7,8) es: %d.%04d\n", entero, fraccion);

    return 0;
}
