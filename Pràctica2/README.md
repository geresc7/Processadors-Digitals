# Pràctica 2 : Interrupcions

## **Objectiu** 
L'objectiu principal de la pràctica és entendre el funcionament de les interrupcions.

## **Material**

### Tecnologies Utilitzades
- ESP32-WROOM-32
- Cable femella-mascle
### Software
- Visual studio
- PlatformIO

## **Codi**
~~~cpp
#include <Arduino.h>

struct Button {
    const uint8_t PIN;
    uint32_t numberKeyPresses;
    bool pressed;
};
Button button1 = {18, 0, false};
void IRAM_ATTR isr() {
    button1.numberKeyPresses += 1;
    button1.pressed = true;
}
void setup() {
    Serial.begin(115200);
    pinMode(button1.PIN, INPUT_PULLUP);
    attachInterrupt(button1.PIN, isr, FALLING);
}
void loop() {
    if (button1.pressed) {
    Serial.printf("Button 1 has been        pressed %u times\n", button1.numberKeyPresses);
    button1.pressed = false;
    }
    //Detach Interrupt after 1 Minute
    static uint32_t lastMillis = 0;
    if (millis() - lastMillis > 60000) {
    lastMillis = millis();
    detachInterrupt(button1.PIN);
    Serial.println("Interrupt Detached!");
    }
}
~~~

## **Explicació i Funcionament del Codi**
Primerament es defineix el pulsador, que conté el número de pin (PIN), un comptador de cops que s'ha polsat (numberKeyPresses) i una variable booleana que indica si el pulsador està premut o no (pressed). Aquestes variables s'inicien per defecte de la següent manera: PIN=18, numberKeyPresses=0 i pressed=false.

Un cop definit el pulsador, es crea una funció (isr) que donarà valors a les variables numberKeyPresses i pressed, esmentades anteriorment.

A continuació es defineix al pin com a entrada (INPUT_PULLUP) i es fa la interrupció utilitzant la funció "attachInterrupt", que conté els tres paràmetres següents: **button1.PIN** com a Pin GPIO, **isr** que serà la funció que es cridi cada cop que es dispari la interrupció, i **Falling** que defineix la manera en que es dispararà la interrupció, en aquest cas es dispararà quan el pin vagi de HIGH a LOW.

Finalment, un bucle (loop) fa que, si es prem el polsador, es mostri pel "terminal"  el nombre de vegades que s'ha polsat. Per últim, es desconnecta la interrupció quan transcorren 60000ms amb la funció **detachInterrupt()**.

Per simular el polsador s'ha fet servir un cable famella-macle connectat al Pin 18. Al fer tocar l'extrem del cable amb GND, es produïa la funció del polsador.


## **Resultat al "Terminal"**
![](P2_terminal.png)


