// C++ code
//
#include <Servo.h>

#include <Adafruit_LiquidCrystal.h>

int sensordistancia = 0;

int tempodeespera = 0;

int luminosidade = 0;

int potenciometro = 0;

int botao = 0;

int leds[] = {9,10,12,13};

Servo servo_6;

Adafruit_LiquidCrystal lcd_1(0);

long readUltrasonicDistance(int triggerPin, int echoPin)
{
  pinMode(triggerPin, OUTPUT);  // Clear the trigger
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  // Sets the trigger pin to HIGH state for 10 microseconds
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  pinMode(echoPin, INPUT);
  // Reads the echo pin, and returns the sound wave travel time in microseconds
  return pulseIn(echoPin, HIGH);
}

void setup()
{
  servo_6.attach(6, 500, 2500);
  lcd_1.begin(16, 2);
  pinMode(6, INPUT);
  pinMode(A1, INPUT);
  pinMode(A0, INPUT);
  Serial.begin(9600);
  pinMode(5, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(A2, INPUT);

  servo_6.write(0);
}
void leituraDados(){
  botao = digitalRead(6);
  potenciometro = analogRead(A1);
  sensordistancia = 0.01723 * readUltrasonicDistance(8, 8);
  luminosidade = analogRead(A0);
  tempodeespera = map(potenciometro, 0, 1023, 5, 20);
  }
void loop()
{
  lcd_1.setCursor(0, 0);
  lcd_1.print("TEMPO ");
  leituraDados();
  lcd_1.print((4 * tempodeespera));
  Serial.println(tempodeespera);
  delay(1000); // Wait for 1000 millisecond(s)
  if (sensordistancia <= 15) {
   

    for(int contador = 3;contador >=0;contador--){
      servo_6.write(90);
    
 tone(5,700,1000);
    
      digitalWrite(leds[contador],HIGH);
      lcd_1.setCursor(0, 0);
  lcd_1.print("TEMPO ");
  leituraDados();
  lcd_1.print(contador * tempodeespera);

      delay(1000 * tempodeespera);

    }
  }else{
    digitalWrite(9, LOW);
      digitalWrite(10, LOW);
      digitalWrite(12, LOW);
      digitalWrite(13, LOW);
    }
  
  


    
    
  
  if (luminosidade < 500) {
    digitalWrite(7, HIGH);
  } else {
    digitalWrite(7, LOW);
  }
  lcd_1.setCursor(0, 1);
  lcd_1.print("TEMPERATURA ");
  lcd_1.print((-40 + 0.488155 * (analogRead(A2) - 20)));
}
