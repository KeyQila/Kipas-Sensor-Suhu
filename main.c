// UAS OAK
// KIPAS ANGIN OTOMATIS BERBASIS SENSOR SUHU
#include <Adafruit_Sensor.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

LiquidCrystal_I2C lcd(0x27, 20, 4); // Alamat I2C dari LCD dan ukuran (20x4)
DHT dht(2, DHT11); // Pin data sensor DHT dan jenis sensor (DHT11)
int powerPin = 3;  // Pin untuk mengontrol daya (pengganti VCC/5V)
int kipas = 4; // Pin untuk mengontrol kipas
boolean kipasStatus = false; // Status awal kipas mati (OFF)

void setup() {
  lcd.init(); // Inisialisasi LCD
  lcd.backlight(); // Mengaktifkan lampu latar LCD
  
  pinMode(powerPin, OUTPUT); // Menjadikan powerPin sebagai output
  digitalWrite(powerPin, HIGH); // Set powerPin ke HIGH (nyalakan)
  
  pinMode(kipas, OUTPUT); // Menjadikan pin kipas sebagai output
  digitalWrite(kipas, LOW); // Matikan kipas saat awal
  
  Serial.begin(9600); // Mulai komunikasi serial dengan baud rate 9600
  dht.begin(); // Inisialisasi sensor DHT
}

void loop() {
  digitalWrite(powerPin, HIGH); // Nyalakan sensor DHT
  
  float suhu = dht.readTemperature(); // Baca suhu dari sensor DHT
  
  Serial.print("suhu: ");
  Serial.println(suhu); // Tampilkan suhu di serial monitor
  
  lcd.clear(); // Bersihkan layar LCD
  lcd.setCursor(0, 0); // Atur posisi kursor di baris pertama
  lcd.print("UAS OAK"); // Tampilkan pesan di baris pertama
  lcd.setCursor(0, 1); // Atur posisi kursor di baris kedua
  lcd.print("KIPAS SENSOR SUHU"); // Tampilkan pesan di baris kedua
  lcd.setCursor(0, 2); // Atur posisi kursor di baris ketiga
  lcd.print("Suhu: ");
  lcd.setCursor(6, 2); // Geser kursor ke posisi keenam di baris ketiga
  lcd.print(suhu); // Tampilkan suhu di LCD

  lcd.setCursor(0, 3); // Atur posisi kursor di baris keempat
  lcd.print("Kipas: ");
  lcd.print(kipasStatus ? "ON" : "OFF"); // Tampilkan "ON" jika kipas hidup, dan "OFF" jika mati
  
  delay(1000); // Tunggu 1 detik
  
  if (suhu < 28.00) { // Jika suhu di bawah 28°C
    digitalWrite(kipas, LOW); // Matikan kipas
    kipasStatus = false; // Kipas dimatikan (OFF)
  } else { // Jika suhu 28°C atau lebih
    digitalWrite(kipas, HIGH); // Nyalakan kipas
    kipasStatus = true; // Kipas dinyalakan (ON)
  }
}
// -B24