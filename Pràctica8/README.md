# Pràctica 8 : Busos de comunicació IV (uart)

## **Objectiu** 
L'objectiu principal de la pràctica és entendre el funcionament de la comunicació sèrie asincrona usart. 
Per aconseguir-ho farem que es mostri pel terminal les dades que enviem al microprocessador.

## **Material**

### Tecnologies Utilitzades
- ESP32-WROOM-32
- Cables femella-famella
### Software
- Visual studio
- PlatformIO

## **Codi**
~~~cpp
#include <Arduino.h>
#define RXD2 16
#define TXD2 17

void setup()
{
  Serial.begin(115200);
  Serial2.begin(115200, SERIAL_8N1, RXD2, TXD2);
  Serial.println("Serial Txd is on pin: "+String(TX));
  Serial.println("Serial Rxd is on pin: "+String(RX));
}

void loop()
{
  while (Serial2.available()) 
  {
    Serial.print(char(Serial2.read()));
  }
  while (Serial.available())
  {
    Serial2.print(char(Serial.read()));
  }
}
~~~

## **Explicació i Funcionament del Codi**
Primerament es defineixen les senyals de comunicació RXD2 i TXD2, assignades, respectivament, als pins 16 i 17.

A continuació, dins del "void setup()" s'inicialitzen dos serials. I seguidament amb la funció "println()" es mostra pel terminal el pin dels serials TxD i RxD.

![](Terminal_p8.png)


Finalment s'obra un "loop()", que mostrarà pel termina el que s'envia a la placa. Primer provarem amb un sol microprossessador i el terminal. Es connectarà el pin 16 i 17 del microprocessador mitjançant un cable famella-famella. El terminal mostrarà les dades que li arriben al microprocessador, aquestes dades s'escriuen per teclat al mateix terminal. És a dir al terminal apareixaran les dades que escrivim per teclat.

![](Terminal_p8(mateix).png)

Per acabar, connectarem dos microprocessadors mitjançant tres cables famella-famella: un que connecti els GND de les plaques i dos cables des del pin 17 d'una placa fins al pin 16 de l'altra, i a l'inversa. Com a resultat, obtindrem una comunicació entre els dos ordinadors, és a dir, el que s'escrigui en un apareixerà en el terminal de l'altra.
