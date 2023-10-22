#include <DHT.h>

#define DHTPIN 9  // Define el pin al que está conectado el sensor DHT11
#define DHTTYPE DHT11  // Define el tipo de sensor (DHT11 en este caso)
#define FOTO_PIN A0  // Pin del fotoresistor

DHT dht(DHTPIN, DHTTYPE);  // Crea un objeto DHT

int light;

void setup() {
  Serial.begin(9600);
  dht.begin();  // Inicializa el sensor DHT
  // Configura los pines del LED como salidas
  for (int i = 2; i <= 8; i++) {
    pinMode(i, OUTPUT);
  }
}

void loop() {
  light = analogRead(FOTO_PIN);
  // Lee la temperatura y la humedad del sensor
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  // Verifica si la lectura del sensor fue exitosa
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Error al leer el sensor DHT11");
  } else {
    // Imprime la temperatura, la humedad y luego la luz en una sola línea, seguido de un salto de línea
    Serial.print("Humedad: ");
    Serial.print(humidity);
    Serial.print("%\t");
    Serial.print("Temperatura: ");
    Serial.print(temperature);
    Serial.print("°C\t");
    Serial.print("Luz: ");
    Serial.println(light);

    // Enciende los LEDs si el valor del fotoresistor es mayor a 600
    if (light > 600) {
      for (int i = 2; i <= 8; i++) {
        digitalWrite(i, HIGH); // Enciende el LED
      }
    } else {
      for (int i = 2; i <= 8; i++) {
        digitalWrite(i, LOW); // Apaga el LED
      }
    }
  }

  delay(100);  // Espera 10 segundos antes de realizar otra lectura
}
