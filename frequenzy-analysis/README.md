# Frequenzanalyse (Frequency Analysis)

Lösungen zu den Übungen **LB-FA 00 bis LB-FA 02** aus
`Exercises_Frequency_analysis-1.pdf`.

Ziel der Übungsserie ist es, eine mit dem Vigenère-Verfahren verschlüsselte
englische Nachricht zu analysieren und anschließend wieder zu entschlüsseln.

| Ordner | Aufgabe | Inhalt |
| ------ | ------- | ------ |
| –      | LB-FA 00 | Theoretische Vorüberlegungen (kein Programm) |
| `01`   | LB-FA 01 | Frequenzanalyse pro Schlüsselposition |
| `02`   | LB-FA 02 | Entschlüsselung mit dem Vigenère-Verfahren |

## LB-FA 00 – Analyse der Verschlüsselung (theoretisch)

Die mitgelieferte Geheimtextnachricht ist in englischer Sprache verfasst. In
dieser Aufgabe geht es ohne Programm darum,

- zu begründen, welches einfache Verschlüsselungsverfahren verwendet wurde
  (Hinweis: Vigenère, da die Buchstabenhäufigkeiten über den Text verteilt
  werden, die Wortstruktur aber erhalten bleibt), und
- welche Analyseverfahren geeignet sind, um den wahrscheinlichsten Schlüssel
  zu bestimmen (Frequenzanalyse, Bestimmung der Schlüssellänge, z. B. über
  den Kasiski-Test oder den Friedman-Test, und anschließender Vergleich der
  Häufigkeitsverteilungen pro Schlüsselposition).

## LB-FA 01 – Frequenzanalyse pro Schlüsselposition

**Programm:** `01/01.cpp`

Das Programm liest eine Textdatei ein und verteilt alle Großbuchstaben
`'A'`–`'Z'` abhängig von ihrer Position im Text auf drei Gruppen
(Schlüsselpositionen). Für jede Position wird gezählt, wie oft jeder Buchstabe
vorkommt, und daraus die relative Häufigkeit in Prozent berechnet. Die
Ergebnisse werden spaltenweise – eine Spalte pro Schlüsselposition – nach
absteigender Häufigkeit sortiert ausgegeben. Bei gleicher Häufigkeit wird
alphabetisch sortiert.

Da die Schlüssellänge in der Aufgabenstellung drei beträgt, ist sie im
Programm fest als `3` hinterlegt (`count[3][26]`).

**Aufruf:**

```text
./01 <eingabedatei>
```

**Beispielausgabe:**

```text
E: 13% ; F: 14% ; D: 13%
T: 9% ; U: 9% ; S: 10%
A: 8% ; B: 8% ; Z: 7%
...
```

Die erste Spalte entspricht der Häufigkeitsverteilung der englischen Sprache
und dient als Referenz für die Schlüsselbestimmung in LB-FA 02.

## LB-FA 02 – Vigenère-Entschlüsselung

**Programm:** `02/02.cpp`

Das Programm entschlüsselt eine Datei mit dem Vigenère-Verfahren. Dazu wird
jeder Buchstabe `'A'`–`'Z'` um den passenden Schlüsselbuchstaben rückwärts
verschoben:

```text
m = (c - k) mod 26
```

Der Schlüssel wird zyklisch über den Text angewendet. Zeichen außerhalb von
`'A'`–`'Z'` (Leerzeichen, Satzzeichen, Zeilenumbrüche usw.) werden unverändert
in die Ausgabedatei übernommen.

Der Schlüssel wird aus der Frequenzanalyse von LB-FA 01 bestimmt: Die
Verschiebung zwischen der englischen Referenzverteilung und der beobachteten
Verteilung jeder Spalte ergibt den jeweiligen Schlüsselbuchstaben.

**Aufruf:**

```text
./02 <eingabedatei> <ausgabedatei> <schlüssel>
```

Beispiel:

```text
./02 cipher.txt plain.txt XYZ
```

## Kompilieren

Die Programme benötigen nur die C++-Standardbibliothek:

```bash
g++ -std=c++17 -O2 -o 01/01 01/01.cpp
g++ -std=c++17 -O2 -o 02/02 02/02.cpp
```

## Hinweise

- Der Ordnername `frequenzy-analysis` ist bewusst so belassen (Schreibweise
  aus dem Repository).
- Die Kommentare im Quellcode enthalten teilweise Quellenangaben und
  Lösungsalternativen, die während der Bearbeitung recherchiert wurden.
