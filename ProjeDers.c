// Standart kütüphaneler
#include <stdio.h>   // giriş/çıkış işlemleri
#include <stdlib.h>  // bellek yönetimi, exit
#include <string.h>  // string işlemleri (strlen, fgets, vb.)
#include <ctype.h>   // karakter sınıflandırma (tolower, isspace)
#include <math.h>    // matematik fonksiyonları (floor, fmod)
#include <time.h>	// zaman işlemleri (time, localtime, strftime)

#define NAME_LEN 50

/*
Furkan Erdoğmuş
*/
// Proje Ödevi: Ders çalışma programı hesaplama
// Amaç: Kullanıcıdan ders adları ve zorluklarını alıp
//       günlük çalışma süresine orantılı olarak ders başına süre dağıtmak.

// Veri yapıları
// Ders: 2 sütunlu matris
//   - Ders[i][0] : ders adı (string)
//   - Ders[i][1] : ders zorluğu (string; sayısala çevrilerek kullanılır)

char ***Ders;

// sure[i]: i. ders için dakika cinsinden çalışma süresi
float *sure;

// CAPACITY: Şu an ayrılmış ders satırı kapasitesi (gerekirse büyütülür)
int CAPACITY = 30;

// Başlangıç bellek tahsisi: CAPACITY kadar satır ve 2 sütun ayrılır
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

void kaydet(int dersSayi,int program) {
	// program olup olmadığını kontrol eder
	if (program == 0) {
		system("cls");
		printf("Plan olusturulmadi\n");
		return 0;
	}
	else {

		time_t currentTime;
		struct tm *tm_info;
		char dosyaAdi[100];

		// Şu anki zamanı al
		time(&currentTime);
		tm_info = localtime(&currentTime);

		// Dosya adı formatla
		strftime(
			dosyaAdi,
			sizeof(dosyaAdi),
			"%d.%m.%Y_%H.%M.%S_Ders_Programi.txt",
			tm_info
		);

		FILE *dosya = fopen(dosyaAdi, "w");
		if (dosya == NULL) {
			printf("Dosya acma hatasi!\n");
			return;
		}

		fprintf(dosya, "------------------------------------------\n");
		fprintf(dosya, "| Ders Adi     | Zorluk |  Saat | dakika |\n");
		fprintf(dosya, "------------------------------------------\n");

		for (int i = 0; i < dersSayi; i++) {
			if (strlen(Ders[i][0]) == 0) break; // Boş ders adı ise dur
			fprintf(dosya, "%-15s | %-10s | %.f | %.f |\n", Ders[i][0], Ders[i][1], floor(sure[i]/60), fmod(sure[i],60));
		}

		fclose(dosya);
		printf("Ders plani '%s' dosyasina kaydedildi.\n\n", dosyaAdi);

	}
}


// scanf ile sayısal okumalardan sonra tamponda kalan '\n' karakterini temizler
void buffer_temizleme() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Kullanıcıdan ders adları ve zorluklarını alır
// EkliDersSayi: daha önce eklenmiş ders sayısı (üzerine ekleme yapılır)
// Dönüş: toplam ders sayısı
int DersEkleme(int EkliDersSayi)
{
		
		printf("Ders Ekleme sistemi\n");
		printf("-----------------------\n");
		printf("Ders Sayisi girin: ");
		// Ders sayısını alır
		int dersSayi;
		if (scanf("%d", &dersSayi) != 1 || dersSayi <= 0) {
			buffer_temizleme();
			system("cls");
			printf("Gecersiz sayi girdiniz.\n");
			// Menuye ders eklenmedi olarak veri gönderir
			return EkliDersSayi;
		}
		buffer_temizleme();

		// Gerekirse kapasiteyi büyüt (minimal: doğrudan gereken kadar büyütülür)
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

// Günlük toplam süreyi alır, zorluklara orantılı süre dağıtır
// program = 1 (başarılı) / 0 (başarısız)
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
	// Toplam zorluk değerini hesaplar (string -> float çevirerek)
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
	// Çalışma süresi faktörünü hesaplar ve derslere süre (dakika) atar
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

// Hesaplanan planı ekrana yazdırır
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
	// Başlangıçta gerekli bellekleri ayır
	dizi_boyutlama();
	int DersSayi = 0;
	// Açıldığında ders ekleme ekranına yönlendirir
	printf("Program ilk defa calistirildigi icin ders ekleme ekranina yonlendiriliyorsunuz.\n");
	printf("-----------------------------------------------\n");
	// Ders sayısını alır
	DersSayi = DersEkleme(DersSayi);
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
		printf("D) Plani Kaydet\n");
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
			case 'd':
				system("cls");
				kaydet(DersSayi,program);
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
