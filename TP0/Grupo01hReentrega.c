#include <stdio.h>
#include <stdint.h>

#define MAX_Q7_8 127
#define MIN_Q7_8 -128
#define MAX_Q0_15 0.999969  // para orientación

int ejerF(char);
int validarEntrada(char, int, int);
int convertirAQ7_8(char, int, int);
int convertirAQ0_15(char, int, int);
int convertirAQ16_15(char, int, int);
int ejerG(int);

int main() {
    int m_q15 = ejerF('m');  // Q(0,15)
    if (m_q15 == 1) return 1;

    int b_q7_8 = ejerF('b');  // Q(7,8)
    if (b_q7_8 == 1) return 1;

    int x_q16_15 = ejerF('x');  // Q(16,15)
    if (x_q16_15 == 1) return 1;

    // Multiplicación: m * x (Q(0,15) * Q(16,15) = Q(16,30))
    int64_t producto = (int64_t)m_q15 * x_q16_15;

    // Ajuste de escala: Q(16,30) >> 15 → Q(16,15)
    int32_t mx_q16_15 = (int32_t)(producto >> 15);

    // Convertir b (Q(7,8)) a Q(16,15): b << 7
    int32_t b_convertido = b_q7_8 << 7;

    // Sumar y obtener y en Q(16,15)
    int32_t y_q16_15 = mx_q16_15 + b_convertido;

    printf("y = 0x%08X\n", (uint32_t)y_q16_15);
    ejerG(y_q16_15);

    return 0;
}

// Ingreso de datos decimal ±eee.ffff
int ejerF(char param) {
    char signo;
    int parteEntera, parteFraccionaria;
    int valor;

    printf("Ingrese %c en notacion decimal ±eee.ffff: ", param);
    scanf(" %c%d.%d", &signo, &parteEntera, &parteFraccionaria);

    if (param == 'm') {
        valor = convertirAQ0_15(signo, parteEntera, parteFraccionaria);
        printf("Representación en Q(0,15): 0x%08X\n", valor);
    } else if (param == 'b') {
        if (!validarEntrada(signo, parteEntera, parteFraccionaria)) {
            printf("Error: b fuera del rango Q(7,8)\n");
            return 1;
        }
        valor = convertirAQ7_8(signo, parteEntera, parteFraccionaria);
        printf("Representación en Q(7,8): 0x%04X\n", (uint16_t)valor);
    } else {
        valor = convertirAQ16_15(signo, parteEntera, parteFraccionaria);
        printf("Representación en Q(16,15): 0x%08X\n", valor);
    }

    return valor;
}

// Valida entrada en rango Q(7,8)
int validarEntrada(char s, int e, int f) {
    int signo = (s == '-') ? -1 : 1;
    int nro = ((e * 10000) + f) * signo;
    return (nro >= (MIN_Q7_8 * 10000) && nro <= (MAX_Q7_8 * 10000));
}

// Conversiones
int convertirAQ7_8(char s, int e, int f) {
    int signo = (s == '-') ? -1 : 1;
    int decimal = (e << 8) + ((f * 256 + 5000) / 10000);
    return signo * decimal;
}

int convertirAQ0_15(char s, int e, int f) {
    if (e != 0) return 0; // en Q(0,15) no se permiten enteros
    int signo = (s == '-') ? -1 : 1;
    return signo * ((f * 32768 + 5000) / 10000);
}

int convertirAQ16_15(char s, int e, int f) {
    int signo = (s == '-') ? -1 : 1;
    return signo * ((e << 15) + ((f * 32768 + 5000) / 10000));
}

// Mostrar en notación decimal ±eee.ffff
int ejerG(int valor) {
    int negativo = (valor < 0);
    if (negativo) valor = -valor;

    int parte_entera = valor >> 15;
    int fraccion = ((valor & 0x7FFF) * 10000 + 16384) / 32768;

    if (negativo) printf("El valor en Q(16,15) es: -%d.%04d\n", parte_entera, fraccion);
    else printf("El valor en Q(16,15) es: %d.%04d\n", parte_entera, fraccion);

    return 0;
}
