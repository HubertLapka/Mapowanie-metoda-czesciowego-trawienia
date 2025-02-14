## Treść projektu
Problem mapowania metodą częściowego trawienia bazuje na wynikach eksperymentu z jednym enzymem restrykcyjnym tnącym kopie badanego fragmentu DNA w odpowiadających mu miejscach restrykcyjnych (w różnych przedziałach czasowych).
W rezultacie otrzymujemy multizbiór A długości odcinków uzyskanych we wszystkich takich reakcjach, uzupełniony o długość całego fragmentu.

Przedstawiony algorytm dokładny o złożoności wykładniczej realizuje następujące zagadnienia:
- wczytanie z pliku instancji problemu mapowania metodą częściowego trawienia (multizbioru A)
- skonstruowanie mapy restrykcyjnej zgodnej z podanym multizbiorem
- wypisanie rezultatu na wyjściu lub stosownego komunikatu w razie braku rozwiązania (gdyby instancja zawierała błędy)

Zaimplementowany algorytm opiera się na przeszukiwaniu z nawrotami, zagłębiając się
coraz bardziej w drzewie rekurencyjnym w celu znalezienia poprawnego rozwiązania.
### Format wejściowy
Instancja to multizbiór składający się z długości odcinków uzyskanych we wszystkich
cięciach, uzupełniony o długość całego fragmentu. Dane prezentowane są w pliku
tekstowym jako sekwencja liczb naturalnych, oddzielonych spacjami. Wczytywanie odbywa
się w funkcji getFile.
### Informacje o implementacji
Program w celu ustalenia możliwej liczby cięć iteruje po wartościach całkowitych z
przedziału [1,20), dla każdej z nich uruchamiając funkcję binomialCoefficient. Wspomniana
funkcja oblicza wartość współczynnika dwumianowego dla obecnie przetwarzanej wartości.
Jeśli program znajdzie wartość współczynnika równą ilości elementów w multizbiorze A, to
obecna wartość zostaje uznana za liczbę cięć. W przeciwnym wypadku użytkownik jest
powiadamiany stosownym komunikatem, a program kończy działanie.

O pierwszym elemencie rozwiązania mamy wiedzę iż jest to różnica dwóch największych
elementów multizbioru A. Program przystępuje więc do poszukiwania dwóch największych
wartości w instancji za pomocą funkcji max_element, a następnie ustala ich różnicę.
Odpowiednio z wektora przechowującego dane usuwane są dwa największe elementy oraz
ich różnica, aby uniknąć ich powtórnego dodania do rozwiązania.

Algorytm wywołuje funkcję szukaj(), która rozpoczyna przeszukiwanie drzewa decyzyjnego.
Korzysta ona z funkcji pomocniczej canBeAdded() sprawdzającej, czy rozważana wartość
może być dodana do aktualnego rozwiązania.
Funkcja pomocnicza ocenia, czy dana liczba może być dodana do rozwiązania przez
poszukiwanie odpowiednich wartości w zestawie A, które można by dodać, aby uzyskać
kolejny kawałek dozwolonej długości. Jeśli tak, zwraca true wraz z listą indeksów tych liczb.
### Generator instancji
Dla zadanej przez użytkownika mapy, którą reprezentuje struktura vector<int> MAPA algorytm stworzy plik tekstowy zawierający sekwencję liczb naturalnych odpowiadających długości możliwych fragmentów odczytanych w wyniku eksperymentu częściowego trawienia. 
Program oblicza sumy skumulowane dla wszystkich możliwych podciągów o rosnącej długości. Uzyskane wartości są następnie sortowane w kolejności rosnącej i zapisywane do pliku, gdzie każda liczba jest oddzielona spacją.

