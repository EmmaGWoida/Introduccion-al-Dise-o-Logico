#include <stdio.h>
#include <stdlib.h>

#define MAX_VAL 127
#define MIN_VAL -128

int validarEntrada(char,int,int); // Prototipo de la funcion
int convertirAQ7_8(char,int,int); // Prototipo de la funcion

int main()
{
    char signo; int parteEntera, parteFraccionaria;

    printf("Ingrese un nro en notacion decimal ±eee.ffff: ");
    scanf(" %c%d.%d",&signo,&parteEntera,&parteFraccionaria);

    if (validarEntrada(signo,parteEntera,parteFraccionaria) == 1){
        printf("El nro ingresado esta dentro del rango representable\n");
    } else {
        printf("El nro ingresado no esta dentro del rango representable\n");
        return 1; // El programa no resulto exitoso
    }

    int valor = convertirAQ7_8(signo,parteEntera,parteFraccionaria);
    printf("Representacion en Q(7,8) en Hexadecimal: 0x%04X\n",(unsigned short)valor);

    return 0; // El programa resulto exitoso
}

int validarEntrada(char s, int e, int f){
    int signo = 1,nro,resultado = 0; // Si resultado es 0 el nro no se encuentra dentro del rango
    if (s == '-'){
        signo = -1; // Aplicar signo
    }
    nro = ((e * 10000) + f) * signo;
    if (nro >= (MIN_VAL*10000) && nro <= (MAX_VAL*10000)){
            resultado = 1; // Si resultado es 1 el nro esta dentro del rango

    }
    return resultado;
}

int convertirAQ7_8(char s, int e, int f) {
    int signo = (s == '-') ? -1 : 1;
    // Convertimos la parte fraccionaria de base 10 a base 2 (Q8)
    int parteFraccionariaQ8 = (e << 8) + ((f * 256) / 10000);
    // Combinamos parte entera y fraccionaria
    int resultado = (e << 8) | parteFraccionariaQ8;
    return signo*resultado;
}