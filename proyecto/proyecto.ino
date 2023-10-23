/*
  Proyecto: Casa Automatizada
  Descripción: 
  Autores: Kevin Lobo y Pablo Sánchez.
*/


// Se incluye la biblioteca DHT para el uso del sensor de temperatura y humedad DHT11.
#include <DHT.h>

// Se define el pin digital al que está conectado el sensor DHT11.
#define DHTPIN 9 

// Se define el tipo de sensor (DHT11).
#define DHTTYPE DHT11  

// Se crea un objeto DHT.
DHT dht(DHTPIN, DHTTYPE); 

// Se define el pin analógico al que está conectado el fotoresistor.
#define FOTO_PIN A0 

// Se define el pin analógico al que está conectado el sensor de humedad del suelo.
#define HYGROMETER_PIN A1

// Variables de retorno (toman los valores del pin digital 9 y los pines analógicos A0 y A1)
int light;
int value;
float humidity; 
float temperature; 

void setup() 
{
  Serial.begin(9600);

  // Se inicializa el sensor DHT.
  dht.begin(); 

  // Se configuran los pines digitales para los LEDs (2, 3, 4, 5, 6, 7, 8).
  for (int i = 2; i <= 8; i++) 
  {
    pinMode(i, OUTPUT);
  }
}

void loop() 
{
  // La variable light toma el valor leído del A0.
  light = analogRead(FOTO_PIN);

  // Se lee la temperatura y la humedad del sensor.
  humidity = dht.readHumidity();
  temperature = dht.readTemperature();

  // La variable value toma el valor leído del A1.
  value = analogRead(HYGROMETER_PIN); 
  // Se limita el rango de valores.
  value = constrain(value, 400, 1023);  
  // Se mapea el valor.
  value = map(value, 400, 1023, 100, 0); 

  // Condición de éxito.
  analizar_fotoresistencia(light);
  imprime_valores();

  // Cada segundo toma valores.
  delay(1000); 
}

/**
 * Analiza el valor de la fotoresistencia obtenido del pin analógico A0.
 * @param humidity Valor obtenido del pin digital 9.
 * @param temperature Valor obtenido del pin digital 9.
 */
 bool analizar_dht11(float humidity, float temperature)
 {
  if (isnan(humidity) || isnan(temperature))
  {
    return true;
  }
  return false;
 }

/**
 * Analiza el valor de la fotoresistencia obtenido del pin analógico A0.
 * @param light Valor obtenido del pin analógico A0.
 */
void analizar_fotoresistencia(int light)
{
  // Se encienden los LEDs si el valor del fotoresistor es mayor a 900 (este valor depende de la oscuridad).
  if (light > 900) 
  {
    encender_LEDs();
  } 
  else 
  {
    apagar_LEDs();
  }
}

/**
 * Imprime todos los valores obtenidos del pin digital y los pines analógicos (Arduino IDE).
 *
*/
void imprime_valores()
{
  // Se imprime la humedad del suelo. 
  Serial.print("Humedad del suelo: ");
  Serial.print(value);
  Serial.print("%\t");

  // Se imprime la temperatura.
  Serial.print("Humedad: ");
  Serial.print(humidity);
  Serial.print("%\t");

  // Se imprime la humedad.
  Serial.print("Temperatura: ");
  Serial.print(temperature);
  Serial.print("°C\t");

  // Se imprime la luz.
  Serial.print("Luz: ");
  Serial.println(light);
  Serial.print("\t");

}

/**
 * Enciende el LED en el pin especificado.
 * @param pin El número del pin donde se encuentra el LED.
 */
void encender_LED(int pin) 
{
  digitalWrite(pin, HIGH); 
}

/**
 * Apaga el LED en el pin especificado.
 * @param pin El número del pin donde se encuentra el LED.
 */
void apagar_LED(int pin) 
{
  digitalWrite(pin, LOW); 
}

/**
 * Enciende todos los LEDs.
 *
 */
void encender_LEDs() 
{
  for (int i = 2; i <= 8; i++) 
  {
  // Se enciende cada LED
  digitalWrite(i, HIGH); 
  }
}

/**
 * Apaga todos los LEDs.
 *
 */
void apagar_LEDs() 
{
  for (int i = 2; i <= 8; i++) 
  {
  digitalWrite(i, LOW); 
  }
}