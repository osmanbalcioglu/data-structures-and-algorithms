#include <stdio.h>

int main() {
    int sayi, orijinalSayi;
    int ters = 0, kalan;

    printf("Bir tam sayi giriniz: ");
    scanf("%d", &sayi);

    orijinalSayi = sayi;

    while (sayi > 0) {
        kalan = sayi % 10;
        ters = (ters * 10) + kalan;
        sayi = sayi / 10;
    }

    if (orijinalSayi == ters) {
        printf("%d bir Palindrom sayidir.\n", orijinalSayi);
    } else {
        printf("%d bir Palindrom sayi degildir.\n", orijinalSayi);
    }

    return 0;
}