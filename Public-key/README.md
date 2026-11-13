# Public-Key-Kryptographie (RSA)

Lösungen zu den Übungen **LB-PKC 00 bis LB-PKC 03** aus
`Exercises_Public_key_cryptography-3.pdf`.

Die Programme verwenden die **GMP**-Bibliothek (`gmpxx.h`) für beliebig große
Ganzzahlen. `dbghelp.h` ist ein kleiner Hilfsheader des Übungstemplates, der
sicherstellt, dass `mpz_class::get_str` für Debug-Ausdrücke gelinkt wird.

| Ordner | Aufgabe | Inhalt |
| ------ | ------- | ------ |
| –      | LB-PKC 00 | Multiplikation zweier Zahlen mit GMP (nicht abgegeben, nicht enthalten) |
| `01`   | LB-PKC 01 | RSA-Ver-/Entschlüsselung eines Zahlenwerts |
| `02`   | LB-PKC 02 | Erzeugung eines RSA-Schlüsselpaars (2048 Bit) |
| `03`   | LB-PKC 03 | RSA-Ver-/Entschlüsselung von Zeichenketten aus/in Dateien |

## LB-PKC 01 – RSA mit Zahlenwerten

**Programm:** `01/01.cpp`

Berechnet die RSA-Operation

```text
c ≡ m^e (mod N)   bzw.   m ≡ c^d (mod N)
```

mit `mpz_powm`. Das Programm ver- und entschlüsselt also denselben Zahlenwert –
je nachdem, ob als Exponent `e` (öffentlich) oder `d` (geheim) übergeben wird.
Die Ausgabe erfolgt ausschließlich als Zahl auf `std::cout`.

**Aufruf:**

```text
./01 <m> <e> <N>
```

**Beispiel (aus der Angabe):**

```text
./01 7 29 391     # ergibt den Geheimtext
./01 <c> 85 391   # ergibt wieder 7
```

## LB-PKC 02 – RSA-Schlüsselerzeugung

**Programm:** `02/02.cpp`

Erzeugt ein RSA-Schlüsselpaar nach folgendem Ablauf:

1. Zwei verschiedene Primzahlen `p` und `q` mit je 1024 Bit zufällig erzeugen
   (`mpz_urandomb` + `mpz_nextprime`).
2. `N = p * q` berechnen. Der Vorgang wird wiederholt, bis `N` exakt
   **2048 Bit** lang ist (`mpz_sizeinbase`).
3. `φ(N) = (p - 1) * (q - 1)` berechnen.
4. Ein `e` mit `1 < e < φ(N)` und `gcd(e, φ(N)) = 1` suchen.
5. `d = e^(-1) mod φ(N)` mit `mpz_invert` berechnen.

Anschließend werden öffentlicher und privater Schlüssel im geforderten Format
ausgegeben:

```text
Public key: (e, N)
Private key: (d, N)
```

**Aufruf:** keine Argumente

```text
./02
```

**Hinweis:** Der Zufallsgenerator wird im Code mit dem festen Seed `42`
initialisiert. Dadurch entstehen bei jedem Lauf dieselben Schlüssel. Für echte
Anwendungen müsste stattdessen ein zufälliger Seed verwendet werden.

## LB-PKC 03 – RSA mit Zeichenketten

**Programm:** `03/03.cpp`

Erweitert LB-PKC 01 auf beliebige Dateiinhalte. Die Zeichen werden als
Bytewerte (0–255) interpretiert und als eine große Zahl zur Basis 256
zusammengefasst:

```text
ABC  ->  65 * 256^2 + 66 * 256^1 + 67 * 256^0
```

Diese Zahl wird mit `mpz_powm` ver- bzw. entschlüsselt und anschließend durch
wiederholte Division durch 256 und Restbildung zurück in Bytes umgewandelt.
Ein- und Ausgabedateien werden im Binärmodus geöffnet, damit auch
nicht-druckbare Zeichen (Geheimtext) korrekt verarbeitet werden.

**Aufruf:**

```text
./03 <eingabedatei> <ausgabedatei> <exponent> <N>
```

Beispiel:

```text
./03 input.txt output.txt <e> <N>   # verschlüsseln
./03 output.txt plain.txt <d> <N>   # entschlüsseln
```

## Kompilieren

GMP muss installiert und beim Linken angegeben werden, z. B. unter Linux:

```bash
g++ -std=c++17 -O2 -o 01/01 01/01.cpp -lgmpxx -lgmp
g++ -std=c++17 -O2 -o 02/02 02/02.cpp -lgmpxx -lgmp
g++ -std=c++17 -O2 -o 03/03 03/03.cpp -lgmpxx -lgmp
```

Unter Windows (z. B. mit MSYS2/MinGW) müssen zusätzlich die GMP-Include- und
Library-Pfade gesetzt werden.
