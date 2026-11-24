
#include <stdio.h>

#define N 6
#define INF 999999

char dugumler[N] = {'A', 'B', 'C', 'D', 'E', 'F'};

void dijkstra(int matris[N][N], int baslangic,
              int mesafe[N], int onceki[N], int bilinen[N])
{
    int i, j, u, minMesafe;

    for (i = 0; i < N; i++)
    {
        mesafe[i] = INF;
        onceki[i] = -1;
        bilinen[i] = 0;
    }

    mesafe[baslangic] = 0;

    for (i = 0; i < N; i++)
    {
        minMesafe = INF;
        u = -1;

        for (j = 0; j < N; j++)
        {
            if (bilinen[j] == 0 && mesafe[j] < minMesafe)
            {
                minMesafe = mesafe[j];
                u = j;
            }
        }

        if (u == -1)
        {
            break;
        }

        bilinen[u] = 1;

        for (j = 0; j < N; j++)
        {
            if (matris[u][j] > 0 && bilinen[j] == 0)
            {
                if (mesafe[u] + matris[u][j] < mesafe[j])
                {
                    mesafe[j] = mesafe[u] + matris[u][j];
                    onceki[j] = u;
                }
            }
        }
    }
}

void yolYazdir(int onceki[N], int dugum, int baslangic)
{
    if (dugum == baslangic)
    {
        printf("%c", dugumler[dugum]);
    }
    else if (onceki[dugum] == -1)
    {
        printf("Yol bulunamadi");
    }
    else
    {
        yolYazdir(onceki, onceki[dugum], baslangic);
        printf(" -> %c", dugumler[dugum]);
    }
}

int dugumBul(char harf)
{
    int i;

    for (i = 0; i < N; i++)
    {
        if (dugumler[i] == harf)
        {
            return i;
        }
    }

    return -1;
}

void rotaYazdir(int mesafe[N], int onceki[N],
                int baslangic, int hedef)
{
    printf("\n%c dugumunden %c dugumune en kisa yol:\n",
           dugumler[baslangic], dugumler[hedef]);

    printf("Rota: ");
    yolYazdir(onceki, hedef, baslangic);

    printf("\nToplam maliyet: %d\n", mesafe[hedef]);
}

int main()
{
    int matris[N][N] = {0};

    int mesafe[N];
    int onceki[N];
    int bilinen[N];

    int i, j;
    int baslangic;
    int toplam;
    int enDusukToplam;
    char secim;

    matris[0][1] = matris[1][0] = 7;
    matris[0][2] = matris[2][0] = 5;
    matris[0][5] = matris[5][0] = 1;
    matris[1][2] = matris[2][1] = 1;
    matris[1][3] = matris[3][1] = 1;
    matris[1][4] = matris[4][1] = 3;
    matris[2][3] = matris[3][2] = 2;
    matris[2][4] = matris[4][2] = 1;
    matris[3][5] = matris[5][3] = 7;
    matris[4][5] = matris[5][4] = 2;

    printf("**********	DIJKSTRA EN KISA YOL ANALIZI	**********\n");

    printf("\n--- AGIRLIKLI KOMSULUK MATRISI ---\n\n");

    printf("   A B C D E F\n");

    for (i = 0; i < N; i++)
    {
        printf("%c  ", dugumler[i]);

        for (j = 0; j < N; j++)
        {
            printf("%d ", matris[i][j]);
        }

        printf("\n");
    }

    printf("\nBaslangic dugumunu giriniz (A-F): ");
    scanf(" %c", &secim);

    if (secim >= 'a' && secim <= 'f')
    {
        secim = secim - 32;
    }

    baslangic = dugumBul(secim);

    if (baslangic == -1)
    {
        printf("Gecersiz dugum girdiniz!\n");
        return 0;
    }

    printf("\n--- DIJKSTRA ALGORITMASI ---\n");

    dijkstra(matris, baslangic, mesafe, onceki, bilinen);

    printf("\nBaslangic dugumu: %c\n", dugumler[baslangic]);

    printf("\nDUGUM\tKNOWN\tDISTANCE\tPATH\n");

    for (i = 0; i < N; i++)
    {
        printf("%c\t%d\t", dugumler[i], bilinen[i]);

        if (mesafe[i] == INF)
        {
            printf("INF\t\t");
            printf("Yol yok\n");
        }
        else
        {
            printf("%d\t\t", mesafe[i]);
            yolYazdir(onceki, i, baslangic);
            printf("\n");
        }
    }

    printf("\n--- A DUGUMUNDEN EN KISA ROTALAR ---\n");

    dijkstra(matris, 0, mesafe, onceki, bilinen);

    rotaYazdir(mesafe, onceki, 0, 1);
    rotaYazdir(mesafe, onceki, 0, 3);

    printf("\n--- MERKEZI DUGUM TESPITI ---\n");

    enDusukToplam = INF;

    for (i = 0; i < N; i++)
    {
        dijkstra(matris, i, mesafe, onceki, bilinen);

        toplam = 0;

        for (j = 0; j < N; j++)
        {
            toplam = toplam + mesafe[j];
        }

        printf("%c dugumunun toplam maliyeti: %d\n",
               dugumler[i], toplam);

        if (toplam < enDusukToplam)
        {
            enDusukToplam = toplam;
        }
    }

    printf("\nEn dusuk toplam maliyet: %d\n", enDusukToplam);

    printf("En merkezi dugum(ler): ");

    for (i = 0; i < N; i++)
    {
        dijkstra(matris, i, mesafe, onceki, bilinen);

        toplam = 0;

        for (j = 0; j < N; j++)
        {
            toplam = toplam + mesafe[j];
        }

        if (toplam == enDusukToplam)
        {
            printf("%c ", dugumler[i]);
        }
    }

    printf("\n");

    return 0;
}

