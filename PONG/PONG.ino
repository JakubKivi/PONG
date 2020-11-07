#include <Servo.h> //Biblioteka odpowiedzialna za serwa
 
Servo serwomechanizm;  //Tworzymy obiekt, dzięki któremu możemy odwołać się do serwa 
int pozycja = 0; //Aktualna pozycja serwa 0-180
int zmiana = 6; //Co ile ma się zmieniać pozycja serwa?
 
void setup() 
{ 
  Serial.begin(9600);
  serwomechanizm.attach(3);  //Serwomechanizm podłączony do pinu 9
} 
 
void loop() 
{  
  
    serwomechanizm.write(map(analogRead(A0), 600, 900, 0, 180)); //Wykonaj ruch
  
  delay(100);                       
}
