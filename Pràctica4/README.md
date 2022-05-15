# Pràctica 4 : Sistemes Operatius en Temps Real

## **Objectiu** 
L'objectiu principal de la pràctica és entendre el funcionament d'un sistema operatiu en temps real. Per aconseguir-ho veurem com s'executen varies tasques dividint el temps d'ús de la CPU.

La pràctica es separarà en dues parts. La primera consistirà en generar una dues tasques senzilles a la ESP32. L'altra part consistirà en tres tasques: encendre i apagar dos leds i mostrar per pantalla el voltatge cada un segon. Aquest voltatge es pot modificar amb un potenciòmetre.

utilitzant FreeRTOS
## **Material**

### Tecnologies Utilitzades
- ESP32-WROOM-32
- Placa Protoboard
- Leds
- Resistències
- Potenciòmetre
- Cables mascle-famella
### Software
- Visual studio
- PlatformIO

## **PART 1: Multitasca (2 tasques)**

## **Codi**
~~~cpp
#include <Arduino.h>
void anotherTask( void * parameter )
{
/* loop forever */
for(;;)
{
Serial.println("this is another Task");
delay(1000);
}

/* delete a task when finish,
this will never happen because this is infinity loop */
vTaskDelete( NULL );
}

void setup()
{
Serial.begin(112500);
/* we create a new task here */
xTaskCreate(
anotherTask, /* Task function. */
"another Task", /* name of task. */
10000, /* Stack size of task */
NULL, /* parameter of the task */
1, /* priority of the task */
NULL); /* Task handle to keep track of created task */
}
/* the forever loop() function is invoked by Arduino ESP32 loopTask */
void loop()
{
Serial.println("this is ESP32 Task");
delay(1000);
}
~~~

## **Explicació i Funcionament del Codi**
Primerament es defineix una funció anomenada anotherTask(), que es cridarà més endavant en el codi. Aquesta consisteix en un bucle que repeteix, cada un segon, el missatge "this is ESP32 Task", al terminal. Aquesta tasca s'acabaria amb la funció "vTaskDelete()" quan finalitzés el bucle, però en aquest cas el bucle és infinit, per tant la tasca no acabarà mai.

A continuació, dins del "void setup()", es crea una nova tasca mitjançant la funció anterior. A aquesta tasca se li assigna el nom "antoher Task", un delay de un segon i un prioritat de nivell 1, és a dir la segona amb menys prioritat.

Finalment s'obra un "loop()", que imprimirà el missatge "This is ESP32 Task" al terminal, amb un delay de un segon.


*Resultat al terminal:*
![foto1](terminal_p4.png)


## **PART 2: Multitasca (3 tasques)**

## **Codi**
~~~cpp
#include <Arduino.h>
TaskHandle_t Task1;
TaskHandle_t Task2;
TaskHandle_t Task3;

const int led_1 = 32;
const int led_2 = 25;
const int potenciometre = 34;


void Task1code( void * parameter ){
  Serial.print("Task1 is running on core ");
  Serial.println(xPortGetCoreID());

  for(;;){
    digitalWrite(led_1, HIGH);
    vTaskDelay(500);
    digitalWrite(led_1, LOW);
    vTaskDelay(500);
  } 
}


void Task2code( void * parameter ){
  Serial.print("Task2 is running on core ");
  Serial.println(xPortGetCoreID());

  for(;;){
    digitalWrite(led_2, HIGH);
    vTaskDelay(1000);
    digitalWrite(led_2, LOW);
    vTaskDelay(1000);
  }
}

void Task3code( void * parameter ){
  Serial.print("Task3 is running on core ");
  Serial.println(xPortGetCoreID());

  for(;;){
    int prova = analogRead(potenciometre);
    Serial.print("Voltatge: ");
    Serial.println(prova);
    
     vTaskDelay(1000);
  }
}

void setup() {
  Serial.begin(115200); 
  pinMode(led_1, OUTPUT);
  pinMode(led_2, OUTPUT);


  xTaskCreatePinnedToCore(Task1code,"Task1",10000,NULL,1,&Task1,0);                         
  vTaskDelay(500); 

  xTaskCreatePinnedToCore(Task2code,"Task2",10000,NULL,1,&Task2,1);          
    vTaskDelay(500); 

  xTaskCreatePinnedToCore(Task3code,"Task3",10000,NULL,1,&Task3,0);          
    vTaskDelay(500); 
}



void loop() {
}
~~~

## **Explicació i Funcionament del Codi**
Primerament es defineixen les tres tasques, que més endavant assignarem al LED1, al LED2 i al potenciòmetre. Seguidament es creen i es defineixen els pins del led_1, led_2 i potenciometre.

A continuació, es crea la funció que farà cada tasca. Les dues primeres, "void Task1code()" i void "Task2code()", encendran i apagaran, infinitament, els seus corresponents leds, amb uns delays de 0.5 i 1 segons respectivament. La tercera funció actuarà com a un multimetre, i mostrarà per pantalla el voltatge cada segon, infinitament.
Les tres funcions, a l'executar-se, mostraran pel terminal a quin nucli de la ESP32 s'està executant la tasca.

Finalment dins del "setup()" es cridarà a les tres funcions anteriors i s'els assignarà un nom, un nivell de prioritat i el nucli de la ESP32 on s'executaran. Al tenir les tres tasques el mateix nivell de prioritat (1), compartiran el temps de processament disponible.


*Resultat al terminal:*
![foto2](terminal_p42.png)
