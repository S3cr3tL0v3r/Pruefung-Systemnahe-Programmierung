## Prüfung Systemnahe Programmierung
Repository für die Aufgaben der Prüfung in Systemnahe Programmierung.

# Aufgaben
## 1. Ampel
Steuern Sie drei LEDs wie eine Verkehrsampel an.

LEDs 1 und zwei leuchten 200 ms
LED 3 1000 ms
LED 2 200ms
LED 1 1000ms

Dann wiederholt sich der Zyklus

## 2. LED mit zwei Tastern an- und ausschalten (polling)
LED leuchet initial
Drücken des Tasters 2 bringt die LED zum Erlöschen
Drücken des Tasters 1 bringt die LED zum brennen.
Lösung ohne Interrupt.

## 3. LED mit zwei Tastern an- und ausschalten (interrupts)
LED leuchet initial
Drücken des Tasters 2 bringt die LED zum Erlöschen
Drücken des Tasters 1 bringt die LED zum brennen.
Lösung mit Interrupt.

## 4. Summer Ton mit zwei Tastern umschalten
Summer schwingt initial mit 440 Hertz
Drücken des Tasters 2 ändert die Frequenz auf 264 Hertz
Drücken des Tasters 1 ändert die Frequenz auf 440 Hertz
Lösung mit Interrupt.

## 5. LED dimmen via Trimpotenziometer
Potenziometer liest analogen Wert mit 8-Bit Auflösung ein
Dieser Wert steuert entsprechend per PWM die Helligkeit einer LED

## 6. Zwei analoge Kanäle simultan lesen
Lesen Sie zwei analoge Kanäle mit einer 10-Bit Auflösung aus und schreiben Sie die Werte der Kanäle auf die serielle Schnittstelle.
Wandeln Sie die Werte in Zeichenketten.

## 7. Acht Bit Lauflicht
Steuern Sie mindestens 8 LED derart an, das sie nacheinander leuchten.
Beginnen Sie mit LED Nr.1 ,dann Nr. 2 und so fort bis Nr. 8. Die Leuchtdauer soll jeweils konstant sein.
Danach dreht sich das Leuchten um.
zunächst Nr.8 (leuchetet schon), dann 7 etc. bis Nr.1
Dann wiederholt sich der Zyklus.
Beachten Sie dass je Port max. 6 programmierbare Beinchen zur Verfügung stehen.
Hier gibt es vielfältige Möglichkeiten die Aufgabe elegant zu lösen.