#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define MAX_DERS 30
#define NAME_LEN 50

/*
Furkan Erdoğmuş
*/
// Proje Ödevi: ders çalişma programi hesaplama

// taşma riskini kontrol et
// buffer temizleme ekle
// ders adı boşluklu girilebilsin

char Ders[MAX_DERS][NAME_LEN];
float Zorluk[MAX_DERS];
float sure[MAX_DERS];

int DersEkleme(int EkliDersSayi)
{
		
		printf("Ders Ekleme sistemi\n");
		printf("-----------------------\n");
		printf("Ders Sayisi girin: ");
		// Ders sayısını alır
		int dersSayi = 0;
		if (scanf("%d", &dersSayi) != 1 || dersSayi <= 0 || dersSayi + EkliDersSayi > MAX_DERS) {
			system("cls");
			printf("Gecersiz sayi girdiniz.\n");
			// Menuye ders eklenmedi olarak veri gönderir
			return EkliDersSayi;
		}
	
		// Ders bilgilerini alır eğer eklenen ders varsa üzerine ekleme yapar

		int i;
		for (i = EkliDersSayi; i <= dersSayi+EkliDersSayi-1; i++) {
			printf("%d. Ders Adini Girin: ", i+1);
			if (scanf(" %49s", Ders[i]) != 1) {
				printf("Girdi hatasi yanlis veya cok uzun bir isim girdiniz.\n");
				i--; continue;
			}
			printf("%d. Ders Zorlugunu Girin (1-10): ", i+1);
			if (scanf("%f", &Zorluk[i]) != 1 || Zorluk[i] < 1 || Zorluk[i] > 10) {
				system("cls");
				printf("Gecersiz zorluk.\n\n");
				i--; continue;
			}
			system("cls");
			printf("Ders: %s %.1f zorlugu ile eklendi.\n\n", Ders[i], Zorluk[i] );
		}
		// Eklenen ders sayısını döner 
		system("cls");
		return EkliDersSayi + dersSayi;

}

int olustur(int dersSayi) {
	// Calisma plani değişkenlerini tanımlar
	printf("Gunluk calisma suresini girin (saat): ");
	// günlük çalışma süresini alır
	float GSure = 0;
	// Zorlukların toplam değerini tutar
	float TopZorluk = 0;
	// Zorluğun çalışma süresine dönüştürülmesi için oranı tutar
	float faktor = 0;

	// Günlük çalışma süresini kontrol eder

	if (scanf("%f", &GSure) != 1 || GSure <= 0 || GSure > 24) {
		printf("Gecersiz sure.\n\n");
		system("cls");
		return 0;
	}
	else {
	// Toplam zorluk değerini hesaplar
	for (int i = 0; i < dersSayi; i++) {
		TopZorluk += Zorluk[i];
	}
	// Ders eklendiğinden emin olur
	if (TopZorluk == 0) {
		system("cls");
		printf("Once Ders Eklemelisiniz\n\n");
		return 0;
	}
	else{
	// Çalışma süresi faktörünü hesaplar ve derslere süre atar
	faktor = (GSure*60)/TopZorluk;
	for (int i = 0; i < dersSayi; i++) {
		sure[i] = faktor * Zorluk[i];
	}
	system("cls");
	printf("Calisma plani olusturuldu\n\n");
	// Programın var olduğunu belirtir
	int program = 1;
	return program;
	}
}
}

int goruntule(int dersSayi,int program) {
	// program olup olmadığını kontrol eder
	if (program == 0) {
		system("cls");
		printf("Plan olusturulmadi\n");
		return 0;
	}
	else {
	//  programı yazdırır
	system("cls");
	printf("Ders planiniz asagidaki gibidir:\n");
	printf("-------------------------------\n\n");
	for (int i = 0; i < dersSayi; i++) {
		printf("%s = %.f saat %.f dakika\n", Ders[i], floor(sure[i]/60), fmod(sure[i],60));
	}
}
return 0;
}



int main(void) {
	// Açıldığında ders ekleme ekranına yönlendirir
	printf("Program ilk defa calistirildigi icin ders ekleme ekranina yonlendiriliyorsunuz.\n");
	printf("-----------------------------------------------\n");
	// Ders sayısını alır
	int DersSayi = DersEkleme(0);
	// programın olmadığını belirtir
	int program = 0;

	// Menu sistemi
	while (1) {
		printf("----------------------------------\n");
		printf("|             Menu:              |\n");
		printf("----------------------------------\n");
		printf("A) Yeni ders ekle\n");
		printf("B) Calisma plani olustur\n");
		printf("C) Plani goruntule\n");
		printf("Q) Cikis\n");
		printf("----------------------------------\n");
		char secim;
		printf("Seciminiz: ");	
		scanf(" %c", &secim);
		switch (tolower(secim)) {
			case 'a':	
				system("cls");
				DersSayi = DersEkleme(DersSayi);
				program = 0;
				break;
			case 'b':
				system("cls");
				program = olustur(DersSayi);
				break;
			case 'c':
				system("cls");
				goruntule(DersSayi,program);
				break;
			case 'q':
				printf("Cikis yapiliyor...\n");
				exit(0);
			default:
				system("cls");
				printf("Gecersiz secim yaptiniz!\n");
				break;
		}
	}

	
	return 0;
}