/*

  Harjoitus 1

  Optimoi sini-funktion käsittely. Älä muuta kääntäjäoptioita.
  Vertaa alkuperäistä ja optimoitua versiota:

  - kuinka paljon enemmän muistia optimoitu versio kuluttaa?
  - kuinka paljon nopeammin optimoitu versio toimii?

  Käännös: gcc sin.c -lm -o sin

*/

#include <stdio.h>
#include <time.h>
#include <math.h>

#define DEG_TO_RAD(A) (A / 57.296)
#define ITERATIONS 1000000


int main()
{
    clock_t t1, t2;
    unsigned i, a;
    double val;

    double sin_t[360];
    for (int i = 0; i < 360; i++)
    {
        sin_t[i] = sin(DEG_TO_RAD(i));;
    }

    t1 = clock();
    for (i = 0; i < ITERATIONS; ++i)
    {
        for (a = 0; a < 360; ++a)
        {
            /*
              OptimizeIt!
            */
            val = sin_t[a];
        }
    }
    t2 = clock();
    printf("%.1fs\n", (t2 - t1) / (float)CLOCKS_PER_SEC);

    return 0;
}
