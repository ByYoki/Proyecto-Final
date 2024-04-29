#include <TimerOne.h>
int ge= 0; // grados electricos correspondientes a la onda senoidal
int intensidad=0; //intensidad
int disparo = 5; // pin donde se debe conectar el ch1
int ledB = 3; // otro canal
const byte interruptPin = 2; // pin donde se debe conectar el sync
volatile byte state = LOW; // me toca buscar que hace
float lectura; //lee el numero analogico de 0 a 1023
float volt; //convierte numero leido a tensión
void setup()
{
  Serial.begin(9600);
  pinMode(interruptPin, INPUT_PULLUP); //me toca buscar que hace
  attachInterrupt(digitalPinToInterrupt(interruptPin),cruce_cero,FALLING); //entra cada que lee un RISING no importa que este haciendo en ese momento
  Timer1.initialize(46); // cada vez que pasen 46 us se ejecuta la funcion grado electrico que es lo que dura un grado electrico en cambiar
  Timer1.attachInterrupt(grado_electrico);
  pinMode(disparo,OUTPUT);
  pinMode(ledB,OUTPUT);
  //pinMode(A0,INPUT);
}

void loop() {
if (Serial.available() > 0) {
    String input = Serial.readStringUntil('\n'); // Lee la entrada serial hasta que encuentre un salto de línea
    intensidad = input.toInt(); // Convierte la cadena a un entero
    Serial.println(intensidad);
  }
    // lectura = analogRead(A0);
    // volt = (lectura)*0.05; //vuelve el valor de la lecutura 1 o menos y se multiplica por el factor de escalamiento
    // Serial.print("El valor de tensión es:");
    // Serial.println(volt);
  digitalWrite(disparo, LOW); // Asegura que el disparo esté en bajo cuando no se reciban nuevos comandos
}

void cruce_cero()
{
  ge=0; //cada vez que entra el ge es cero
}

void grado_electrico()
{
  ge++;

  if(intensidad==ge) // cuando la intensidad es igual al grado electrico se dispara el triac
  {
   digitalWrite(disparo,HIGH); //62.5 ns
   digitalWrite(disparo,LOW);
  }
}
