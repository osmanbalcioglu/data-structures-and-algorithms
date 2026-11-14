#include <stdio.h>
#include <stdlib.h>

struct Dugum {
    int veri;
    struct Dugum *sol;
    struct Dugum *sag;
};

struct Dugum *dugumOlustur(int veri) {
    struct Dugum *yeni = (struct Dugum *)malloc(sizeof(struct Dugum));

    yeni->veri = veri;
    yeni->sol = NULL;
    yeni->sag = NULL;

    return yeni;
}

struct Dugum *ekle(struct Dugum *kok, int veri) {
    if (kok == NULL) {
        return dugumOlustur(veri);
    }

    if (veri < kok->veri) {
        kok->sol = ekle(kok->sol, veri);
    } else if (veri > kok->veri) {
        kok->sag = ekle(kok->sag, veri);
    }

    return kok;
}

int hazineAra(struct Dugum *kok, int aranan, int *adim) {
    if (kok == NULL) {
        return 0;
    }

    (*adim)++;
    printf("Ziyaret edilen dugum: %d\n", kok->veri);

    if (kok->veri == aranan) {
        return 1;
    }

    if (aranan < kok->veri) {
        return hazineAra(kok->sol, aranan, adim);
    }

    return hazineAra(kok->sag, aranan, adim);
}

int yukseklik(struct Dugum *kok) {
    if (kok == NULL) {
        return 0;
    }

    int solYukseklik = yukseklik(kok->sol);
    int sagYukseklik = yukseklik(kok->sag);

    if (solYukseklik > sagYukseklik) {
        return solYukseklik + 1;
    }

    return sagYukseklik + 1;
}

void bellegiTemizle(struct Dugum *kok) {
    if (kok == NULL) {
        return;
    }

    bellegiTemizle(kok->sol);
    bellegiTemizle(kok->sag);
    free(kok);
}

int main() {
    struct Dugum *kok = NULL;
    int sayi, aranan, adim = 0;

    kok = ekle(kok, 50);
    kok = ekle(kok, 30);
    kok = ekle(kok, 70);
    kok = ekle(kok, 20);
    kok = ekle(kok, 40);
    kok = ekle(kok, 60);
    kok = ekle(kok, 80);

    printf("Hazine Agaci Oyunu\n");
    printf("Agactaki sayilar: 50, 30, 70, 20, 40, 60, 80\n");
    printf("Hazineyi bulmak icin bir sayi girin: ");
    scanf("%d", &aranan);

    if (hazineAra(kok, aranan, &adim)) {
        printf("Hazine bulundu!\n");
    } else {
        printf("Bosuna kazdin!\n");
    }

    printf("Ziyaret edilen dugum sayisi: %d\n", adim);
    printf("Agacin yuksekligi: %d\n", yukseklik(kok));
    printf("En kotu durumda gereken adim sayisi: %d\n", yukseklik(kok));

    bellegiTemizle(kok);

    return 0;
}
