
#include <stdio.h>

#define N 6
#define OGRENCI 4

char dersler[N][3] = {"d0", "d1", "d2", "d3", "d4", "d5"};

void grafikOlustur(int ogrenciler[OGRENCI][3],
                   int dersSayisi[OGRENCI],
                   int matris[N][N])
{
    int i, j, k;
    int a, b;

    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
            matris[i][j] = 0;
        }
    }

    for (i = 0; i < OGRENCI; i++)
    {
        for (j = 0; j < dersSayisi[i]; j++)
        {
            for (k = j + 1; k < dersSayisi[i]; k++)
            {
                a = ogrenciler[i][j];
                b = ogrenciler[i][k];

                matris[a][b] = 1;
                matris[b][a] = 1;
            }
        }
    }
}

void matrisiYazdir(int matris[N][N])
{
    int i, j;

    printf("    ");

    for (i = 0; i < N; i++)
    {
        printf("%s ", dersler[i]);
    }

    printf("\n");

    for (i = 0; i < N; i++)
    {
        printf("%s  ", dersler[i]);

        for (j = 0; j < N; j++)
        {
            printf("%d   ", matris[i][j]);
        }

        printf("\n");
    }
}

void dereceHesapla(int matris[N][N], int derece[N])
{
    int i, j;

    for (i = 0; i < N; i++)
    {
        derece[i] = 0;

        for (j = 0; j < N; j++)
        {
            derece[i] += matris[i][j];
        }

        printf("%s dersinin derecesi: %d\n",
               dersler[i], derece[i]);
    }
}

void sirala(int derece[N], int sira[N])
{
    int i, j, gecici;

    for (i = 0; i < N; i++)
    {
        sira[i] = i;
    }

    for (i = 0; i < N - 1; i++)
    {
        for (j = i + 1; j < N; j++)
        {
            if (derece[sira[j]] > derece[sira[i]])
            {
                gecici = sira[i];
                sira[i] = sira[j];
                sira[j] = gecici;
            }
        }
    }
}

int welchPowell(int matris[N][N])
{
    int derece[N];
    int sira[N];
    int renk[N];

    int i, j;
    int oturum = 0;
    int uygun;

    dereceHesapla(matris, derece);

    sirala(derece, sira);

    printf("\nDereceye gore siralama:\n");

    for (i = 0; i < N; i++)
    {
        printf("%s (%d) ", dersler[sira[i]], derece[sira[i]]);
    }

    printf("\n");

    for (i = 0; i < N; i++)
    {
        renk[i] = 0;
    }

    while (1)
    {
        uygun = 0;
        oturum++;

        for (i = 0; i < N; i++)
        {
            if (renk[sira[i]] == 0)
            {
                uygun = 1;
                break;
            }
        }

        if (uygun == 0)
        {
            oturum--;
            break;
        }

        for (i = 0; i < N; i++)
        {
            int dugum = sira[i];
            int cakisma = 0;

            if (renk[dugum] == 0)
            {
                for (j = 0; j < N; j++)
                {
                    if (matris[dugum][j] == 1 &&
                        renk[j] == oturum)
                    {
                        cakisma = 1;
                        break;
                    }
                }

                if (cakisma == 0)
                {
                    renk[dugum] = oturum;
                }
            }
        }
    }

    printf("\nSinav Oturumlari:\n");

    for (i = 1; i <= oturum; i++)
    {
        printf("Oturum %d: ", i);

        for (j = 0; j < N; j++)
        {
            if (renk[j] == i)
            {
                printf("%s ", dersler[j]);
            }
        }

        printf("\n");
    }

    printf("\nMinimum sinav oturumu sayisi (Kromatik Sayi): %d\n",
           oturum);

    return oturum;
}

int main()
{
    int ogrenciler[OGRENCI][3] = {
        {0, 1, 4},
        {0, 2, 4},
        {2, 3, 5},
        {3, 4, 5}
    };

    int dersSayisi[OGRENCI] = {3, 3, 3, 3};

    int matris[N][N];
    int ilkKromatik;
    int yeniKromatik;

    printf("*****	WELCH-POWELL SINAV TAKVIMI	*****\n");

    printf("\n--- GOREV 1: CAKISMA GRAFI OLUSTURMA ---\n");

    grafikOlustur(ogrenciler, dersSayisi, matris);

    matrisiYazdir(matris);

    printf("\n--- GOREV 2: WELCH-POWELL RENKLENDIRMESI ---\n");

    ilkKromatik = welchPowell(matris);

    printf("\n--- GOREV 3: SINAV TAKVIMI RAPORU ---\n");

    printf("Gerekli minimum sinav oturumu: %d\n",
           ilkKromatik);

    printf("\n--- GOREV 4: DINAMIK GUNCELLEME ---\n");

    printf("Ogrenci-4 d4 dersini birakti.\n");

    ogrenciler[3][0] = 3;
    ogrenciler[3][1] = 5;
    dersSayisi[3] = 2;

    grafikOlustur(ogrenciler, dersSayisi, matris);

    printf("\nGuncellenmis komsuluk matrisi:\n");

    matrisiYazdir(matris);

    printf("\nGuncellenmis Welch-Powell analizi:\n");

    yeniKromatik = welchPowell(matris);

    printf("\n--- SONUC VE ACIKLAMA ---\n");

    printf("Ilk kromatik sayi: %d\n", ilkKromatik);
    printf("Yeni kromatik sayi: %d\n", yeniKromatik);

    if (yeniKromatik < ilkKromatik)
    {
        printf("Ders cakismalari azaldigi icin oturum sayisi azalmistir.\n");
    }
    else if (yeniKromatik == ilkKromatik)
    {
        printf("d4 dersinin birakilmasina ragmen kromatik sayi degismemistir.\n");
        printf("Cunku d0, d1 ve d4 dersleri arasinda ucgen cakisma vardir.\n");
        printf("Bu nedenle en az 3 farkli oturum gereklidir.\n");
    }
    else
    {
        printf("Guncelleme sonrasi oturum sayisi artmistir.\n");
    }

    return 0;
}

