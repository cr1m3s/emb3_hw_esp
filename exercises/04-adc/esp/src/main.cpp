#include <Arduino.h>

// Конфігурація
#define LDR_PIN 6           // GPIO6 - ADC1_CH5
#define SAMPLE_INTERVAL 100 // мс
#define VREF 3300.0         // Опорна напруга ESP32-S3: 3.3V = 3300 мВ
#define ADC_MAX 4095.0      // 12-біт АЦП: 0-4095

// Змінні для зберігання даних
uint32_t lastSampleTime = 0;
uint32_t sampleCount = 0;

// Статистика для порівняння
float totalError = 0;
float maxError = 0;
uint32_t errorSamples = 0;

// Функція для друку заголовка таблиці
void printTableHeader() {
  Serial.println("┌─────┬──────────┬───────────────┬───────────────┬─────────┐");
  Serial.println("│  #  │ RAW ADC  │  Calc V (mV)  │  Read V (mV)  │ Error % │");
  Serial.println("├─────┼──────────┼───────────────┼───────────────┼─────────┤");
}

void setup() {
  Serial.begin(115200);
  delay(1000);
  
  // Налаштування АЦП
  analogReadResolution(12);  // 12-біт (0-4095)
  analogSetAttenuation(ADC_11db);  // 0-3.3V діапазон
  
  Serial.println("\n╔════════════════════════════════════════════════════════╗");
  Serial.println("║          ESP32-S3 LDR ADC Measurement Lab             ║");
  Serial.println("╚════════════════════════════════════════════════════════╝");
  Serial.println();
  Serial.println("📋 Configuration:");
  Serial.println("   Pin: GPIO" + String(LDR_PIN));
  Serial.println("   Sample rate: " + String(SAMPLE_INTERVAL) + " ms");
  Serial.println("   ADC resolution: 12-bit (0-4095)");
  Serial.println("   Voltage range: 0-3.3V");
  Serial.println();
  
  // Друкуємо перший заголовок
  printTableHeader();
}

void loop() {
  uint32_t now = millis();

  if (now - lastSampleTime >= SAMPLE_INTERVAL) {
    lastSampleTime = now;
    sampleCount++;
    
    // Зчитати RAW значення АЦП
    uint16_t rawADC = analogRead(LDR_PIN);
    
    // Обчислити напругу за формулою: V = (RAW / ADC_MAX) * VREF
    float calculatedVoltage = (rawADC / ADC_MAX) * VREF;  // мВ
    
    // Зчитати напругу за допомогою analogReadMillivolts()
    uint32_t measuredVoltage = analogReadMilliVolts(LDR_PIN);  // мВ
    
    // Порівняти та обчислити похибку
    float error = 0;
    if (measuredVoltage > 0) {
      error = abs(calculatedVoltage - measuredVoltage) / measuredVoltage * 100.0;

      // Оновлюємо статистику
      totalError += error;
      errorSamples++;
      if (error > maxError) {
        maxError = error;
      }
    }

    // Вивести всі дані
    char buffer[100];
    sprintf(buffer, "│ %3lu │  %4d    │   %7.2f     │   %7lu     │  %5.2f  │",
            sampleCount,
            rawADC,
            calculatedVoltage,
            measuredVoltage,
            error);
    Serial.println(buffer);
    
    // Виводимо статистику і новий заголовок кожні 10 вимірів
    if (sampleCount % 10 == 0) {
      Serial.println("├─────┼──────────┼───────────────┼───────────────┼─────────┤");

      float avgError = errorSamples > 0 ? totalError / errorSamples : 0;

      Serial.print("│ STATS: Avg Error: ");
      Serial.print(avgError, 2);
      Serial.print("% | Max Error: ");
      Serial.print(maxError, 2);
      Serial.println("% |");
      Serial.println("└─────┴──────────┴───────────────┴───────────────┴─────────┘");
      Serial.println();  // Порожній рядок
      
      // Друкуємо новий заголовок для наступної таблиці
      printTableHeader();
    }
  }
}