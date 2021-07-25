#include <iostream>
#include <math.h>
#include <array>
#include <omp.h>
#define N 10000

using namespace std;

long contas(int n)
{
    unsigned int seed[N];
    for (int i = 0; i < N; i++)
        seed[i] = (unsigned int)rand();
    long res = 0;
    long i = 0;
    long tmp = 0;
#pragma omp parallel for reduction(+ \
                                   : res) private(tmp, i)

    for (int j = 1; j < N; j++)
    {
        unsigned int s = seed[j];
        {
            tmp = 0;
            for (i = 1; true; i++)
            {
                if (rand_r(&s) % n == 1)
                {
                    tmp = i;
                    break;
                }
            }
        }
        res += tmp;
    }
    return ceil((double)res / N);
}

int main()
{
    srand(time(NULL));
    double chance;
    cin >> chance;
    int numero = ceil((double)100 / chance);
    long media = contas(numero);
    cout << "Fazendo " << N << " vezes demora em média " << media << " tentativas para conseguir um item de rate " << chance << "%"
         << "\n";
    return 0;
}
