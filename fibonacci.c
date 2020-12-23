#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <omp.h>

// Libreia GMP utilizacda para numero mayores a los que puede
// ejecutar las variables convencionales
#include <gmp.h>

// "numeros" guarda los resultados de fibonacci
mpz_t numeros[400];

/*
* Metodo que imprime y factoriza el numero de "numero[]"
* Recibe la posicion del fib
*
*/
void factorize(int n) {
    mpz_t resultado[100];
    mpz_t ca;
    mpz_init(ca);
    mpz_t div;
    mpz_init(div);
    mpz_t nuevo;
    mpz_init(nuevo);
    mpz_set(nuevo, numeros[n]);
    mpz_t num;
    mpz_init(num);
    mpz_set(num, numeros[n]);
    // Inicializa resultado []
    for (int i = 0; i < 100; i++) {
        mpz_init(resultado[i]);
    }
    int pos = 0;
    bool factorizable = true;

    if (mpz_cmp_ui(nuevo, 1) == 0 || mpz_cmp_ui(nuevo, 0) == 0) {
        factorizable = false;
    }
    while (factorizable) {
        if (mpz_cmp_ui(nuevo, 1) == 0 || mpz_cmp_ui(nuevo, 0) == 0) {
            factorizable = false;
        }
        else {
            mpz_set_ui(div, 2);
            if (mpz_cdiv_r_ui(div, nuevo, 2) == 0) {
                mpz_cdiv_q_ui(nuevo,nuevo, 2);
                mpz_set_ui(resultado[pos], 2);
                pos++;
            }
            else {
                bool dd = true;
                mpz_t mul;
                mpz_init_set_ui(mul, 3);
                mpz_set_ui(ca, 3);
                mpz_mul(mul, ca, ca);
                while (mpz_cmp(mul, nuevo) < 0) {
                    mpz_cdiv_r(div, nuevo, ca);
                    if ((mpz_cmp_ui(div, 0) == 0)) {
                        mpz_cdiv_q(nuevo, nuevo, ca);
                        mpz_set(resultado[pos], ca);
                        pos++;
                        dd = false;
                        break;
                    }
                    mpz_add_ui(ca, ca, 2);
                }
                mpz_clear(mul);

                if (dd) {
                    mpz_set(resultado[pos], nuevo);
                    break;
                }
            }
        }
    }
    mpz_t instancia;
    mpz_init(instancia);
    bool posible = false;
    int cantidad = 0;
    printf("%d : ", n);
    mpz_out_str(stdout, 10, num);
    printf(" = ");

    {
        if (mpz_cmp_ui(num, 0) == 0 || mpz_cmp_ui(num, 1) == 0) {
            mpz_out_str(stdout, 10, num);
        }
        else {
            mpz_set(instancia, resultado[0]);
            cantidad = 0;
            for (int i = 0; i < 100; i++) {
                if (mpz_cmp(instancia, resultado[i]) == 0) {
                    cantidad++;
                }
                else {
                    if (cantidad == 1) {
                        mpz_out_str(stdout, 10, instancia);
                    }
                    else {
                        mpz_out_str(stdout, 10, instancia);
                        printf("^%d", cantidad);
                    }
                    mpz_set(instancia, resultado[i]);
                    cantidad = 1;
                    if (mpz_cmp_ui(instancia, 0) == 0) {
                        break;
                    }
                    printf(" X ");
                }
            }
        }
        printf("\n");
        mpz_clear(*resultado);
        mpz_clear(instancia);
        mpz_clear(ca);
    }
}

/*
* Metodo fib suma los numeros anteriores
*
*/
void fib(int n) {

    // Verifica si la posicion es la inicial o la primera
    if (n == 1 || n == 0) {
        mpz_set_ui(numeros[1], 1);
        mpz_set_ui(numeros[0], 0);
        factorize(0);
        factorize(1);
        return;
    }
    else {
        // Crea el numero fibonacci anterior
#pragma task
        fib(n - 1);

        // Suma los dos anteriores numeros
#pragma taskwait
        {
            mpz_add(numeros[n], numeros[n - 1], numeros[n - 2]);
            factorize(n);
        }
        return;

    }
}
int main(int argc, char** argv) {
    for (int i = 0; i < 400; i++) {
        mpz_init(numeros[i]);
    }
    // Crea todo los numero de fibonacci, usar OMP lo hace muy lento
#pragma omp parallel
    {
#pragma omp single
        fib(300);
    }
}


