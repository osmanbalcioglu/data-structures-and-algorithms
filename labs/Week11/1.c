
#include <stdio.h>

#define N 6

void matrisiYazdir(int matris[N][N])
{
    int i, j;

    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
            printf("%d ", matris[i][j]);
        }
        printf("\n");
    }
}

void dereceHesapla(int matris[N][N])
{
    int i, j;
    int derece, toplamDerece = 0;

    for (i = 0; i < N; i++)
    {
        derece = 0;

        for (j = 0; j < N; j++)
        {
            derece = derece + matris[i][j];
        }

        printf("%d. dugumun derecesi: %d\n", i + 1, derece);

        toplamDerece = toplamDerece + derece;
    }

    printf("Grafin genel derece toplami: %d\n", toplamDerece);
}

int bipartiteKontrol(int matris[N][N])
{
    int renk[N];
    int kuyruk[N];
    int bas, son;
    int i, dugum;

    for (i = 0; i < N; i++)
    {
        renk[i] = -1;
    }

    bas = 0;
    son = 0;

    renk[0] = 0;
    kuyruk[son] = 0;
    son++;

    while (bas < son)
    {
        dugum = kuyruk[bas];
        bas++;

        for (i = 0; i < N; i++)
        {
            if (matris[dugum][i] == 1)
            {
                if (renk[i] == -1)
                {
                    renk[i] = 1 - renk[dugum];

                    kuyruk[son] = i;
                    son++;
                }
                else if (renk[i] == renk[dugum])
                {
                    return 0;
                }
            }
        }
    }

    return 1;
}

int main()
{
    int matris[N][N] = {0};

    matris[0][1] = 1;
    matris[1][0] = 1;

    matris[0][3] = 1;
    matris[3][0] = 1;

    matris[1][2] = 1;
    matris[2][1] = 1;

    matris[2][3] = 1;
    matris[3][2] = 1;

    matris[2][5] = 1;
    matris[5][2] = 1;

    matris[3][4] = 1;
    matris[4][3] = 1;

    matris[4][5] = 1;
    matris[5][4] = 1;

    printf("\n--- GOREV 1: KOMSULUK MATRISI ---\n");

    matrisiYazdir(matris);

    printf("\n--- GOREV 2: DERECE HESAPLAMA ---\n");

    dereceHesapla(matris);

    printf("\n--- GOREV 3: BIPARTITE KONTROLU ---\n");

    if (bipartiteKontrol(matris) == 1)
    {
        printf("Graf iki parcalidir (Bipartite).\n");
    }
    else
    {
        printf("Graf iki parcali degildir.\n");
    }

    printf("\n--- GOREV 4: DINAMIK KENAR EKLEME ---\n");

    matris[1][3] = 1;
    matris[3][1] = 1;

    printf("(2,4) kenari grafa eklendi.\n");

    printf("\nYeni komsuluk matrisi:\n");

    matrisiYazdir(matris);

    printf("\nYeni derece hesaplamalari:\n");

    dereceHesapla(matris);

    printf("\nYeni Bipartite kontrolu:\n");

if (bipartiteKontrol(matris) == 1)
{
    printf("Graf iki parcalidir (Bipartite).\n");
}
else
{
    printf("Graf iki parcali degildir.\n");

    printf("\nAciklama:\n");
    printf("(2,4) kenari eklendiginde ayni renkteki ");
    printf("iki dugum komsu olmustur.\n");
    printf("Bu nedenle graf Bipartite ozelligini kaybetmistir.\n");
}

    return 0;
}

