// Código de Funcionamento para Sistema de Monitoramento e Irrigação com Arduino
#include "DHT.h"
#include <Wire.h> //INCLUSÃO DE BIBLIOTECA
#include <LiquidCrystal_I2C.h> //INCLUSÃO DE BIBLIOTECA

LiquidCrystal_I2C lcd(0x27,2,1,0,4,5,6,7,3, POSITIVE); //ENDEREÇO DO I2C E DEMAIS INFORMAÇÕES

#define pino5VL 4
#define DHTPIN A1 //  Define o pino que irá fazer a leitura do sensor de temperatura DHT11
#define DHTTYPE DHT11 // DHT 11
#define pinoAnalog A0 // Define o pino A0 como "pinoAnalog" do sensor de umidade
#define pinoRele 8 // Define o pino 8 como "pinoRele" e ativa o modulo rele
#define pino5V 7 // Define o pino 7 como "pino5V"
 
int LED = 13; // Pino no qual o LED está conectado
int LDR = A2; // Pino no qual o LDR está conectado
int entrada; // Variável que terá o valor do LDR
int ValAnalogIn; // Introduz o valor analógico ao código
DHT dht(DHTPIN, DHTTYPE);
 
void setup() {
lcd.begin (16,2); //SETA A QUANTIDADE DE COLUNAS(16) E O NÚMERO DE LINHAS(2) DO DISPLAY
lcd.println("FELAS ENGENHARIA");
delay(3000);
lcd.setBacklight(HIGH); //LIGA O BACKLIGHT (LUZ DE FUNDO)
Serial.begin(9600); // Declara o BaundRate em 9600
Serial.println("FELAS ENGENHARIA"); // Imprime a frase no monitor serial
dht.begin();
pinMode(pinoRele, OUTPUT); // Declara o pinoRele como Saída
pinMode(pino5V, OUTPUT); // Declara o pino5V como Saída
digitalWrite(pino5V, HIGH); // Põem o pino5V em estado Alto = 5V
pinMode(pino5VL, OUTPUT);
pinMode(LED, OUTPUT);
digitalWrite(pino5VL, HIGH);
}
 
void loop() {
 
//Leitura do sensor de umidade do solo
ValAnalogIn = analogRead(pinoAnalog); // Relaciona o valor analógico com o recebido do sensor
int Porcento = map(ValAnalogIn, 1023, 0, 0, 100); // Relaciona o valor analógico à porcentagem

Serial.print(Porcento);
Serial.println("% umd no solo  ");


lcd.setCursor(0,0);
lcd.print(Porcento); // Imprime o valor em Porcento no monitor Serial
lcd.print("% umd no solo  "); // Imprime o símbolo junto ao valor encontrado
 
if (Porcento <= 30) { // Se a porcentagem for menor ou igual à
Serial.println("Irrigando...");
lcd.setCursor(0,1);
lcd.print("Irrigando...    "); // Imprime a frase no monitor serial
digitalWrite(pinoRele, LOW); // Altera o estado do pinoRele para nível Alto
}
 
else { // Se não ...
Serial.println("Planta irrigada.");
lcd.setCursor(0,1);
lcd.print("Planta Irrigada...    "); // Imprime a frase no monitor serial
digitalWrite(pinoRele, HIGH); // Altera o estado do pinoRele para nível Baixo
}
delay (2000); // Estabelece o tempo de 1s para reinicializar a leitura

//Leitura da temperatura e umidade pode levar 250ms!
  // O atraso do sensor pode chegar a 2 segundos.
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  // testa se retorno é valido, caso contrário algo está errado.
  if (isnan(t) || isnan(h)) 
  {
    Serial.println("Failed to read from DHT");
    lcd.println("Failed to read from DHT");
  } 
  else
  {
    Serial.print("Umidade no ambiente: ");
    Serial.print(h);
    Serial.println("%");
    Serial.print("Temperatura no ambiente: ");
    Serial.print(t);
    Serial.println(" *C");

    lcd.setCursor(0,0);
    lcd.print("Umd amb: ");
    lcd.print(h);
    lcd.print("% ");
    lcd.setCursor(0,1);
    lcd.print("                ");
 delay (2000);
    lcd.print("%");
    lcd.setCursor(0,0);
    lcd.print("Temp: ");
    lcd.print(t);
    lcd.print("*C   ");
  }
 delay (2000);

//Leitura do sensor de luminosidade
entrada = analogRead(LDR); // Relaciona o valor analógico com o recebido do sensor
int PorcentoL = map(entrada, 1023, 0, 0, 100); // Relaciona o valor analógico à porcentagem

Serial.print(100 - PorcentoL);
Serial.println("% Lum no amb");
lcd.setCursor(0,0);
lcd.print(100 - PorcentoL); // Imprime o valor em Porcento no monitor Serial
lcd.print("% Lum no amb"); // Imprime o símbolo junto ao valor encontrado
 
if (100 - PorcentoL <= 45) { // Se a porcentagem for menor ou igual à
Serial.println("Baixa Lum");
Serial.println("...");
lcd.setCursor(0,1);
lcd.print("Baixa lum       "); // Imprime a frase no monitor serial
digitalWrite(LED, HIGH); // Altera o estado do pinoRele para nível Alto
}
 
else { // Se não ...
Serial.println("Lum ok");
Serial.println("...");
lcd.setCursor(0,1);
lcd.print("Lum ok          "); // Imprime a frase no monitor serial
digitalWrite(LED, LOW); // Altera o estado do pinoRele para nível Baixo
}
delay (2000); // Estabelece o tempo de 1s para reinicializar a leitura
}
