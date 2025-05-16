int PinoSensor1 = 2;  // PINO DIGITAL UTILIZADO PELO SENSOR
int PinoSensor2 = 3;  // PINO DIGITAL UTILIZADO PELO SENSOR
int PinoSensor3 = 4;  // PINO DIGITAL UTILIZADO PELO SENSOR
int PinoSensor4 = 7;  // PINO DIGITAL UTILIZADO PELO SENSOR
int PinoSensor5 = 8;  // PINO DIGITAL UTILIZADO PELO SENSOR

int Motor1F = 6;   // Motor 1 para frente
int Motor1T = 5;   // Motor 1 para trás
int Motor2F = 10;  // Motor 2 para frente
int Motor2T = 9;   // Motor 2 para trás

void setup() {
  Serial.begin(9600);
  pinMode(PinoSensor1, INPUT);
  pinMode(PinoSensor2, INPUT);
  pinMode(PinoSensor3, INPUT);
  pinMode(PinoSensor4, INPUT);
  pinMode(PinoSensor5, INPUT);

  pinMode(Motor1F, OUTPUT);
  pinMode(Motor1T, OUTPUT);
  pinMode(Motor2F, OUTPUT);
  pinMode(Motor2T, OUTPUT);
}

void loop() {
  int Sensor1 = digitalRead(PinoSensor1);
  int Sensor2 = digitalRead(PinoSensor2);
  int Sensor3 = digitalRead(PinoSensor3);
  int Sensor4 = digitalRead(PinoSensor4);
  int Sensor5 = digitalRead(PinoSensor5);

  Serial.print("S1: ");
  Serial.print(Sensor1);
  Serial.print(" S2: ");
  Serial.print(Sensor2);
  Serial.print(" S3: ");
  Serial.print(Sensor3);
  Serial.print(" S4: ");
  Serial.print(Sensor4);
  Serial.print(" S5: ");
  Serial.println(Sensor5);

  // **PARAR NO PRETO**
  // Se todos os sensores estiverem LOW (preto), para o robô
  if (Sensor1 == LOW && Sensor2 == LOW && Sensor3 == LOW && Sensor4 == LOW && Sensor5 == LOW) {
    stopMotors();
    return; // Sai do loop para não executar mais nada
  }

  // **IDENTIFICAR CURVAS E MOVER**
  if (Sensor3 == HIGH) {
    moveForward(100); // Segue reto quando o sensor central detecta branco
  } 
  else if (Sensor1 == LOW && Sensor2 == LOW) {
    turnRight(100);  // Curva rápida à direita
  } 
  else if (Sensor4 == LOW && Sensor5 == LOW) {
    turnLeft(100);  // Curva rápida à esquerda
  } 
  else if (Sensor1 == LOW && Sensor2 == HIGH) {
    turnRight(70);  // Curva suave à direita
  } 
  else if (Sensor4 == HIGH && Sensor5 == LOW) {
    turnLeft(70);  // Curva suave à esquerda
  } 
  else if (Sensor2 == LOW && Sensor3 == LOW) {
    turnRight(70);  // Curva moderada à direita
  } 
  else if (Sensor4 == LOW && Sensor3 == LOW) {
    turnLeft(100);  // Curva moderada à esquerda
  } 
  else if (Sensor1 == LOW && Sensor5 == HIGH) {
    turnRight(100);  // Curva rápida à direita
  } 
  else if (Sensor1 == HIGH && Sensor5 == LOW) {
    turnLeft(100);  // Curva rápida à esquerda
  } 
  else if (Sensor1 == LOW && Sensor2 == LOW && Sensor3 == LOW && Sensor4 == LOW && Sensor5 == LOW) {
    moveForward(100);
  }
  else {
    stopMotors();  // Para caso não detecte linha (todos HIGH ou outros casos)
  }
}

void moveForward(int speed) {
  analogWrite(Motor1F, speed);
  analogWrite(Motor1T, 0);
  analogWrite(Motor2F, speed);
  analogWrite(Motor2T, 0);
}

void turnRight(int speed) {
  analogWrite(Motor1F, speed);
  analogWrite(Motor1T, 0);
  analogWrite(Motor2F, 0);
  analogWrite(Motor2T, speed);
}

void turnLeft(int speed) {
  analogWrite(Motor1F, 0);
  analogWrite(Motor1T, speed);
  analogWrite(Motor2F, speed);
  analogWrite(Motor2T, 0);
}

void stopMotors() {
  analogWrite(Motor1F, 0);
  analogWrite(Motor1T, 0);
  analogWrite(Motor2F, 0);
  analogWrite(Motor2T, 0);
}
