#include <TimerOne.h>
int ge= 0; // grados electricos correspondientes a la onda senoidal
int intensidad=0; //intensidad
int intensidad2=0; //intensidad
int intensidad3=0; //intensidad
int intensidad4=0; //intensidad
int intensidad5=0; //intensidad
int intensidad6=0; //intensidad
int disparo = 5; // pin donde se debe conectar el ch1
int ledB = 9; // otro canal
int ledC = 10; // otro canal
int ledD = 11; // otro canal
int ledE = 12; // otro canal
int ledF = 6; // otro canal
const byte interruptPin = 2; // pin donde se debe conectar el sync
volatile byte state = LOW; // me toca buscar que hace
float lectura; //lee el numero analogico de 0 a 1023
float volt; //convierte numero leido a tensión
String inputString = ""; // a String para mantener información entrante
bool stringComplete = false; // si el String esta completo para revisar si ya hemos complteado un comando


void setup()
{
  Serial.begin(9600);
  pinMode(interruptPin, INPUT_PULLUP); //me toca buscar que hace
  attachInterrupt(digitalPinToInterrupt(interruptPin),cruce_cero,FALLING); //entra cada que lee un RISING no importa que este haciendo en ese momento
  Timer1.initialize(46); // cada vez que pasen 46 us se ejecuta la funcion grado electrico que es lo que dura un grado electrico en cambiar
  Timer1.attachInterrupt(grado_electrico);
  pinMode(disparo,OUTPUT);
  pinMode(ledB,OUTPUT);
  pinMode(ledC,OUTPUT);
  pinMode(ledD,OUTPUT);
  pinMode(ledE,OUTPUT);
  pinMode(ledF,OUTPUT);
  //pinMode(A0,INPUT);
}

void loop() {
 // digitalWrite(disparo, LOW); // Asegura que el disparo esté en bajo cuando no se reciban nuevos comandos
 if (stringComplete)
{
  inputString.trim(); // Para cortar o eliminar cualquier caracter especial
  Serial.println(inputString); //imprimir para el control en el monitpr serial

//procesar comando
funcionProcesar();
    // luego se vacio el comando 
inputString = "";
stringComplete = false;
}
}

void funcionProcesar(){
  if (inputString.indexOf("$SA") != -1){
  String holi = inputString.substring(3); // Convierte la cadena a un entero
  intensidad = holi.toInt();
  Serial.println(intensidad);
}
else if (inputString.indexOf("$SB") != -1) {
  String holi2 = inputString.substring(3); // Convierte la cadena a un entero
  intensidad2 = holi2.toInt();
  Serial.println(intensidad2);
}
else if (inputString.indexOf("$SC") != -1) {
  String holi3 = inputString.substring(3); // Convierte la cadena a un entero
  intensidad3 = holi3.toInt();
  Serial.println(intensidad3);
}
else if (inputString.indexOf("$SD") != -1) {
  String holi4 = inputString.substring(3); // Convierte la cadena a un entero
  intensidad4 = holi4.toInt();
  Serial.println(intensidad4);
}
else if (inputString.indexOf("$SE") != -1) {
  String holi5 = inputString.substring(3); // Convierte la cadena a un entero
  intensidad5 = holi5.toInt();
  Serial.println(intensidad5);
}
else if (inputString.indexOf("$SF") != -1) {
  String holi6 = inputString.substring(3); // Convierte la cadena a un entero
  intensidad6 = holi6.toInt();
  Serial.println(intensidad6);
}
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
  if(intensidad2==ge) // cuando la intensidad es igual al grado electrico se dispara el triac
  {
   digitalWrite(ledB,HIGH); //62.5 ns
   digitalWrite(ledB,LOW);
  }
  if(intensidad3==ge) // cuando la intensidad es igual al grado electrico se dispara el triac
  {
   digitalWrite(ledC,HIGH); //62.5 ns
   digitalWrite(ledC,LOW);
  }
    if(intensidad4==ge) // cuando la intensidad es igual al grado electrico se dispara el triac
  {
   digitalWrite(ledD,HIGH); //62.5 ns
   digitalWrite(ledD,LOW);
  }
    if(intensidad5==ge) // cuando la intensidad es igual al grado electrico se dispara el triac
  {
   digitalWrite(ledE,HIGH); //62.5 ns
   digitalWrite(ledE,LOW);
  }
    if(intensidad6==ge) // cuando la intensidad es igual al grado electrico se dispara el triac
  {
   digitalWrite(ledF,HIGH); //62.5 ns
   digitalWrite(ledF,LOW);
  }
}

//Parte de samuel
void serialEvent()
{
	while (Serial.available()) 
	{
		// conseguir el nuevo byte:
		char inChar = (char)Serial.read(); //leer y pasar a tipo char
		if (inChar == '\n') //si llega al final del comando
		{
			stringComplete = true; //se marca true para finalizar
		}
		else
		{
			//Se sigue añadiendo carácteres a la cadena
			inputString += inChar;
			// El operador += suma el valor de su derecha a la variable o propiedad de su izquierda y asigna el resultado a la variable o propiedad de su izquierda
		}
	}
}