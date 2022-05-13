# Pràctica 7 : Busos de comunicació III (I2S)

## **Objectiu** 
L'objectiu principal de la pràctica és entendre el funcionament de la comunicació I2S. 
Per aconseguir-ho farem que es reprodueixin arxius d'àudio a un altaveu, des d'una targeta SD i des de la memòria interna del microprocessador. Per això s'haurà de decodificar la senyal digital en una senyal analògica, fent servir el MAX98357 (I2S) que actuarà com a DAC.

## **Material**

### Tecnologies Utilitzades
- ESP32-WROOM-32
- MAX98357 I2S
- Altaveu
- Lector de targeta SD
- Cables femella-famella
- Cable d'àudio JACK
### Software
- Visual studio
- PlatformIO

## **PART 1: Memòria Interna**

## **Codi**
~~~cpp
#include "AudioGeneratorAAC.h"
#include "AudioOutputI2S.h"
#include "AudioFileSourcePROGMEM.h"
#include "sampleaac.h"

AudioFileSourcePROGMEM *in;
AudioGeneratorAAC *aac;
AudioOutputI2S *out;

void setup(){
  Serial.begin(9600);

  in = new AudioFileSourcePROGMEM(sampleaac, sizeof(sampleaac));
  aac = new AudioGeneratorAAC();
  out = new AudioOutputI2S();
  out -> SetGain(0.125);
  out -> SetPinout(26,25,22);
  aac->begin(in, out);
}

void loop(){
  if (aac->isRunning()) {
    aac->loop();
  } else {
    aac -> stop();
    Serial.printf("Sound Generator\n");
    delay(1000);
  }
}
~~~

## **Explicació i Funcionament del Codi**
Primerament s'inclou la biblioteca d'audio "ESP8266" i la capçalera "sampleaac.h", que és l'arxiu d'àudio que reproduirà l'altaveu.

A continuació, es defineixen tres punters,per llegir l'arxiu d'àudio, decodificar-lo i enviar-lo de forma analògica.

Seguidament, dins del setup, s'inicializen els punters i els pins. Al punter "out" s'inicialitza amb un guany de 0,125.

Finalment s'obra un "loop()", que farà s'executi el punter "aac" fins que aquest tingui tot el missatge decodificat. Un cop decodificat es reproduirà el so per l'altaveu i es mostrarà el missatge "Sound Generator" pel terminal, per avisar que s'ha generat el so.

![](terminal_p7.png)

En aspectes de connexions físiques, en aquest cas, es connecta el microprocessador al I2S, i del I2S a l'altaveu, mitjançant cables famella-famella.

## **PART 2: Memòria Externa (SD)**

## **Codi**
~~~cpp
#include "Arduino.h"
#include "Audio.h"
#include "SD.h"
#include "FS.h"

// Digital I/O used
#define SD_CS          5
#define SPI_MOSI      23
#define SPI_MISO      19
#define SPI_SCK       18
#define I2S_DOUT      25
#define I2S_BCLK      27
#define I2S_LRC       26

Audio audio;

void setup(){
    pinMode(SD_CS, OUTPUT);
    digitalWrite(SD_CS, HIGH);
    SPI.begin(SPI_SCK, SPI_MISO, SPI_MOSI);
    Serial.begin(115200);
    SD.begin(SD_CS);
    audio.setPinout(I2S_BCLK, I2S_LRC, I2S_DOUT);
    audio.setVolume(10); // 0...21
    audio.connecttoFS(SD, "Goteo.mp3");
}

void loop(){
    audio.loop();
}

// optional
void audio_info(const char *info){
    Serial.print("info        "); Serial.println(info);
}
void audio_id3data(const char *info){  //id3 metadata
    Serial.print("id3data     ");Serial.println(info);
}
void audio_eof_mp3(const char *info){  //end of file
    Serial.print("eof_mp3     ");Serial.println(info);
}
void audio_showstation(const char *info){
    Serial.print("station     ");Serial.println(info);
}
void audio_showstreaminfo(const char *info){
    Serial.print("streaminfo  ");Serial.println(info);
}
void audio_showstreamtitle(const char *info){
    Serial.print("streamtitle ");Serial.println(info);
}
void audio_bitrate(const char *info){
    Serial.print("bitrate     ");Serial.println(info);
}
void audio_commercial(const char *info){  //duration in sec
    Serial.print("commercial  ");Serial.println(info);
}
void audio_icyurl(const char *info){  //homepage
    Serial.print("icyurl      ");Serial.println(info);
}
void audio_lasthost(const char *info){  //stream URL played
    Serial.print("lasthost    ");Serial.println(info);
}
void audio_eof_speech(const char *info){
    Serial.print("eof_speech  ");Serial.println(info);
}
~~~

## **Explicació i Funcionament del Codi**
Primerament s'inclouen les llibreries i es defineixen els pins. Els 4 primers pins serviràn per connectar el lector de la SD i els 4 sigüents pel MAX98357. A part es crea una variable d'audiò anomenada "audio".

A continuació, dins del setup, sinicilitzen els pins i es defineix el volum i l'àrxiu d'àudio, de la SD, que volem reproduïr.

Finalment s'obra un "loop()" amb les funcions que inclou la llibreria d'àudio previament afegida.


![](terminal_p7_2.png)

En aspectes de connexions físiques, mitjançant cables famella-famella, es connecta el lector de la SD al microprocessador, del microprocessador al I2S, i del I2S a l'altaveu.



