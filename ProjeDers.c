#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define NAME_LEN 50

/*
Furkan Erdoğmuş
*/
// Proje Ödevi: ders çalişma programi hesaplama
// String sorunları mevcut

char ***Ders;  // 2D matris: Ders[i][0] = ad, Ders[i][1] = zorluk (string olarak)
float *sure;
int CAPACITY = 30;

void dizi_boyutlama() {
	// Ders için 2D matris: [satır][sütun] - her satır bir ders, 2 sütun (ad, zorluk)
	Ders = (char***)malloc(CAPACITY * sizeof(char**));
	for (int i = 0; i < CAPACITY; i++) {
        Ders[i] = (char**)malloc(2 * sizeof(char*));  // 2 sütun
        Ders[i][0] = (char*)malloc(NAME_LEN * sizeof(char));  // Ders adı
        Ders[i][1] = (char*)malloc(20 * sizeof(char));        // Zorluk (string olarak)
    }
    
	// sure için float dizisi ayır
	sure = (float*)malloc(CAPACITY * sizeof(float));
}


void dizi_temizle() {
    // Ders matrisini temizle
	for (int i = 0; i < CAPACITY; i++) {
        free(Ders[i][0]);  // Ders adı
        free(Ders[i][1]);  // Zorluk
        free(Ders[i]);     // Satır
    }
    free(Ders);  // Tüm matris
    
    // sure temizleme
    free(sure);
}

void buffer_temizleme() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int DersEkleme(int EkliDersSayi)
{
		
		printf("Ders Ekleme sistemi\n");
		printf("-----------------------\n");
		printf("Ders Sayisi girin: ");
		// Ders sayısını alır
		int dersSayi = 0;
		if (scanf("%d", &dersSayi) != 1 || dersSayi <= 0) {
			buffer_temizleme();
			system("cls");
			printf("Gecersiz sayi girdiniz.\n");
			// Menuye ders eklenmedi olarak veri gönderir
			return EkliDersSayi;
		}
		buffer_temizleme();

		// Gerekirse kapasiteyi büyüt (minimal: doğrudan gereken kadar)
		int needed = dersSayi + EkliDersSayi;
		if (needed > CAPACITY) {
			int oldCap = CAPACITY;
			CAPACITY = needed;
			char ***yeniDers = (char***)realloc(Ders, CAPACITY * sizeof(char**));
			if (!yeniDers) {
				 fprintf(stderr, "Bellek yetersiz (Ders).\n"); exit(1); 
			}

			Ders = yeniDers;
			// yeni satırlar için sütun belleklerini ayır
			for (int i = oldCap; i < CAPACITY; i++) {
				Ders[i] = (char**)malloc(2 * sizeof(char*));
				Ders[i][0] = (char*)malloc(NAME_LEN * sizeof(char));
				Ders[i][1] = (char*)malloc(20 * sizeof(char));
			}
			float *yeniSure = (float*)realloc(sure, CAPACITY * sizeof(float));
			
			if (!yeniSure) {
				 fprintf(stderr, "Bellek yetersiz (sure).\n"); exit(1);
			}
			sure = yeniSure;
		}
	
		// Ders bilgilerini alır eğer eklenen ders varsa üzerine ekleme yapar

		int i;
		for (i = EkliDersSayi; i <= dersSayi+EkliDersSayi-1; i++) {
			printf("%d. Ders Adini Girin: ", i+1);
			if (!fgets(Ders[i][0], NAME_LEN, stdin)) {
				printf("Girdi hatasi.\n");
				i--; continue;
			}
			// Satır sonu karakterini temizle
			size_t len = strlen(Ders[i][0]);
			if (len > 0 && Ders[i][0][len-1] == '\n') Ders[i][0][len-1] = '\0';
			if (strlen(Ders[i][0]) == 0) { printf("Bos isim kabul edilmez.\n"); i--; continue; }
			
			printf("%d. Ders Zorlugunu Girin (1-10): ", i+1);
			if (!fgets(Ders[i][1], 20, stdin)) {
				printf("Girdi hatasi.\n");
				i--; continue;
			}
			// Satır sonu karakterini temizle
			len = strlen(Ders[i][1]);
			if (len > 0 && Ders[i][1][len-1] == '\n') Ders[i][1][len-1] = '\0';
			
			float zorluk = atof(Ders[i][1]);
			if (zorluk < 1 || zorluk > 10) {
				system("cls");
				printf("Gecersiz zorluk.\n\n");
				i--; continue;
			}
			system("cls");
			printf("Ders: %s %s zorlugu ile eklendi.\n\n", Ders[i][0], Ders[i][1]);
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
		buffer_temizleme();
		printf("Gecersiz sure.\n\n");
		system("cls");
		return 0;
	}
	buffer_temizleme();
	// Toplam zorluk değerini hesaplar
	for (int i = 0; i < dersSayi; i++) {
		TopZorluk += atof(Ders[i][1]);
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
		sure[i] = faktor * atof(Ders[i][1]);
	}
	system("cls");
	printf("Calisma plani olusturuldu\n\n");
	// Programın var olduğunu belirtir
	int program = 1;
	return program;
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
		printf("%s = %.f saat %.f dakika\n", Ders[i][0], floor(sure[i]/60), fmod(sure[i],60));
	}
}
return 0;
}



int main(void) {
	dizi_boyutlama();
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
				dizi_temizle();
				exit(0);
			default:
				system("cls");
				printf("Gecersiz secim yaptiniz!\n");
				break;
		}
	}

	
	return 0;
}
