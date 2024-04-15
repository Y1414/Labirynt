Program uruchamia się w następujący sposób: ./labirynt <lokalizacja_pliku> (po skompilowaniu poleceniem 'make')

Akceptowane rozszerzenia to .bin i .txt

Jeżeli wprowadzony zostanie labirnynt w pliku txt program stworzy plik txt z instrukcjami oraz plik bin z labiryntem i jego rozwiązaniem

Jeżeli wprowadzony zostanie plik z rozszerzeniem bin program znajdzie w nim rozwiązanie i wpisze je do pliku z instrukcjami. W przypadku braku rozwiązania w pliku, program sam dopisze rozwiązanie.

Format w jakim labirynt musi być przedstawiony w pliku txt to:
* P –﻿ wejście do labiryntu,
* K ﻿–﻿ wyjście z labiryntu,﻿
* X ﻿– ściana,
* spacja ﻿– miejsce, po którym można się poruszać.  


Przykładowy labirynt:

<pre>
XXXXXXXXXXX
P         X
XXXXXXXXX X
X         X
X XXXXXXX X
X   X     X
XXX X XXXXX
X   X     X
X XXXXXXX X
X       X K
XXXXXXXXXXX
</pre>

Program zawsze znajdzie najkrótszą ścieżkę  
Czas działania programu dla labiryntu o wymiarach 2050x2050 to około 8 sekund  
Pamięć używania przez program w czasie całego swojego działania wynosi mniej niż 15 KB (dla każdego labiryntu) czyli ponad 34 razy mniej niż limit wyznaczony przez twórcę zadania  
Do wykonania projektu zostały użyte:
* Visual Studio Code 1.88.1
* WSL z UBUNTU 22.04.2
* gcc 11.4.0
* valgrind 3.18.1 (do pomiarów pamięci oraz wykrywania wycieków pamięci)
* ChatGPT 3.5 (do wyjaśnienia niektórych zagadnień związanych z projektem np. pliku binarnego oraz do implementacji prostych funkcji)
* hex-editor (do odczytu plików binarnych)

Twórcy: Piotr Gawroński

