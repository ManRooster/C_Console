# C_Console

Bu depo, **C programlama dili ile geliştirilmiş çeşitli konsol (console)
uygulamalarını** içerir.\
Amaç; algoritma pratiği, temel--orta seviye C projeleri, kullanıcı
etkileşimli programlar ve akademik amaçlı uygulamaları tek bir çatı
altında toplamaktır.

Projeler; dizi kullanımı, fonksiyonlar, kullanıcı girdisi kontrolü,
matematiksel işlemler, menü sistemleri ve hata yönetimi gibi temel C
konularını kapsamaktadır.

------------------------------------------------------------------------

## İçerik

Bu repo içerisinde şunlar bulunmaktadır:

-   Ders çalışma planı hesaplama uygulaması\

Her uygulama **bağımsız olarak çalıştırılabilir** yapıdadır.

------------------------------------------------------------------------

## Örnek Proje: Ders Çalışma Programı

Bu uygulama:

-   Kullanıcıdan ders sayısını alır\
-   Her ders için:
    -   Ders adı
    -   Zorluk seviyesi (1--10)
-   Günlük çalışma süresine göre her derse:
    -   Dakika bazlı süre ataması yapar\
-   Menü sistemi içerir:
    -   Ders ekleme
    -   Plan oluşturma
    -   Plan görüntüleme

### Kullanılan Konular:

-   Diziler (`char`, `float`)
-   Fonksiyonlar
-   `scanf`, `printf`
-   `ctype.h`, `math.h`
-   Girdi doğrulama
-   Menü sistemi
-   `floor()` ve `fmod()` kullanımı

------------------------------------------------------------------------

## Derleme ve Çalıştırma

### GCC ile Derleme:

``` bash
gcc main.c -o program -lm
```

### Çalıştırma:

``` bash
./program
```

Windows için:

``` bash
program.exe
```

> Not: `math.h` kullanıldığı için `-lm` parametresi gereklidir.

------------------------------------------------------------------------

## Sistem Gereksinimleri

-   GCC / MinGW / Clang
-   Windows, Linux veya macOS
-   Temel C derleyici ortamı

------------------------------------------------------------------------

## Kod Standartları

-   Global diziler kontrollü kullanılmıştır
-   Girdi taşmalarına karşı sınırlandırmalar eklenmiştir
-   Menü sistemi `switch-case` ile kurulmuştur
-   Hatalı girişler için doğrulama yapılır
-   Modüler fonksiyon yapısı tercih edilmiştir

------------------------------------------------------------------------

## Amaç

Bu repo:

-   C öğrenenler için örnek kaynak\
-   Üniversite proje ve ödevleri için referans\
-   Konsol tabanlı uygulama geliştirme pratiği\
-   Algoritma ve mantık gelişimi

amaçlarıyla oluşturulmuştur.

------------------------------------------------------------------------

## Katkı

Katkı sağlamak istersen:

1.  Fork al
2.  Yeni bir proje ekle
3.  Açıklayıcı isimle commit at
4.  Pull request gönder

------------------------------------------------------------------------

## Lisans

Bu depo eğitim ve kişisel kullanım amaçlıdır.\
Ticari kullanım için kaynak gösterilmesi tavsiye edilir.

------------------------------------------------------------------------

## Geliştirici

**Furkan Erdoğmuş**\
C Programlama \| Algoritma \| Konsol Uygulamaları
