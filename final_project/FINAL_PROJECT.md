# doKTOr1

## Wersja 1.00 - Mat.POiC++.2023/24

### Wstęp
Być może pod choinką czekały na nas stosy gier planszowych, ale na wszelki wypadek, gdyby jednak w
tym roku ich nie było, zróbmy sobie jedną sami. W postaci programu w obiektowym C++. Czyli przyjemne z
pożytecznym.

### Opis gry
W tym zadaniu należy zaprojektować i zaimplementować grę planszową DoKTOr. Gra toczy się na liniowej
planszy, podzielonej na pola. Gracze stoją na polach (jeden gracz stoi na jednym polu, na jednym polu
może stać wielu graczy). Należy przejść z pola startowego do pola końcowego, rzucając kostką i
przesuwając się (zwykle) o liczbę oczek wyrzuconą na kostce.

### Plansza
Plansza jest typową dla wielu planszówek listą kolejnych pól. Liczba pól jest określona w opisie gry, można
założyć, że ta liczba jest nie mniejsza niż trzy. Zakładamy, że plansza jest zapętlona, to znaczy, po
ostatnim polu jest znów pierwsze.

### Pola
- Pole startowe (S): Jest obowiązkowe.
- Pole docelowe (D): Jest obowiązkowe.
- Pole puste (.): Nic specjalnego nie dzieje się ani przy stanięciu na tym polu ani przy przejściu przez to pole.
- Pole regeneracji (R): Jest obowiązkowe.
- Pole przeskoku (P): Po stanięciu gracza na nim wyświetlany jest komunikat o sytuacji na polu i
  gracz jest przesuwany o zadaną liczbę pól do przodu lub do tyłu.
- Pole oczekiwania (O): Gracz, który zatrzyma się na tym polu, musi czekać zadaną parametrem pola
  liczbę kolejek.

### Regeneracje doKTOra
Grę rozpoczynamy jako 9. doKTOr. doKTOr - po stanięciu na odpowiednim polu - przechodzi regenerację.

### Kostki
W grze dostępny jest zestaw trzech kostek. Każda po wyrzuceniu pokazuje liczbę naturalną z zakresu 1..6.

### Gracze
Gracze komputerowi mogą być bardzo różni. Oto klika ich rodzajów:
- Gracz losowy (L)
- Gracz tradycyjny (T)
- Gracz eksperymentujący (E)
- Gracz rozważny (R)

### Kończenie gry
Grę wygrywa ten z graczy, który dojdzie do pola docelowego jako 13. doKTOr.

### Program
Należy napisać program implementujący grę kilku komputerowych graczy. Program ma wczytać opis gry z
pliku tekstowego i przeprowadzić symulację jednej gry zgodnie z podanym w tym zadaniu opisem.

### Format danych
Plik z danymi ma format tekstowy. Pierwszy wiersz zawiera liczbę graczy, kolejne wiersze opisują rodzaj
i nazwę każdego gracza. Następny wiersz to liczba pól, a kolejne wiersze opisują rodzaj i ewentualne
parametry każdego pola.

### Możliwe rozszerzenia
- Bardzo zachęcamy do dodania gracza białkowego (B), komunikującego się z grą za pomocą
  klawiatury.
- Grę można rozbudowywać, dodając nowe rodzaje pól i graczy komputerowych.

### Uwagi
- Zwróć uwagę na obiektowość w C++ Twojego rozwiązania.
- Koniecznie pisz program przyrostowo.
- Postaraj się możliwie wcześnie dodać do swojego programu wypisywanie zgodne z treścią zadania.
- Programy powinny same zamykać otwierane pliki i zwalniać całą przydzieloną pamięć.
- Warto sprawdzać poprawność wczytywanych danych.
- W każdej klasie należy jawnie ustosunkować się do czterech kłopotliwych operacji omawianych na
  wykładzie.
- Można korzystać ze wszystkich klas z biblioteki standardowej C++.
- Pamiętaj o komentowaniu swojego kodu.

Życzymy powodzenia i przyjemności z oglądania rozgrywek lub brania w nich udziału!

