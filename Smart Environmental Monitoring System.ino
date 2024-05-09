#include <ESP8266WiFi.h> // Include the ESP8266 Wi-Fi library
#include <Adafruit_GFX.h> // Include the Adafruit Graphics library
#include <Adafruit_SSD1306.h> // Include the Adafruit OLED display library
#include <DHT.h> // Include the DHT sensor library

// WiFi credentials
const char* ssid = "UUMWiFi_Guest"; // SSID of the Wi-Fi network
const char* password = "";  // Password of the Wi-Fi network

// DHT22 sensor setup
#define DHTPIN D5 // Pin where the DHT22 is connected
#define DHTTYPE DHT22 // DHT22 sensor type
DHT dht(DHTPIN, DHTTYPE); // Create a DHT sensor object

// OLED display setup
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET    -1 // OLED reset pin (not used)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET); // Create an OLED display object

// Sound detector setup
#define SOUND_PIN D6 // Pin where the sound detector is connected

void setup() {
  Serial.begin(115200); // Start the serial communication
  dht.begin(); // Initialize the DHT22 sensor
  
  // Initialize the OLED display
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Infinite loop if the display initialization fails
  }
  display.display(); // Show initial display buffer
  delay(2000); // Delay for 2 seconds
  display.clearDisplay(); // Clear the display buffer

  // Connect to Wi-Fi
  WiFi.begin(ssid, password); // Start Wi-Fi connection
  while (WiFi.status() != WL_CONNECTED) { // Wait for Wi-Fi connection
    delay(500); // Delay half a second
    Serial.print("."); // Print dots while connecting
  }
  Serial.println(""); // New line after connecting
  Serial.println("WiFi connected"); // Print Wi-Fi connected message
  Serial.print("IP address: "); // Print IP address message
  Serial.println(WiFi.localIP()); // Print the IP address
}

void loop() {
  // Read humidity and temperature from DHT22
  float humidity = dht.readHumidity(); // Read humidity
  float temperature = dht.readTemperature(); // Read temperature
  
  // Read sound level from the sound detector
  int soundLevel = analogRead(SOUND_PIN); // Read sound level

  // Display sensor readings on the OLED
  display.clearDisplay(); // Clear the display buffer
  display.setTextSize(1); // Set text size
  display.setTextColor(WHITE); // Set text color
  display.setCursor(0,0); // Set cursor position
  display.print("Temp: "); // Print temperature label
  display.print(temperature); // Print temperature value
  display.println(" C"); // Print temperature unit
  
  display.print("Humidity: "); // Print humidity label
  display.print(humidity); // Print humidity value
  display.println(" %"); // Print humidity unit
  
  display.print("Sound: "); // Print sound level label
  display.print(soundLevel); // Print sound level value
  display.display(); // Update the display with all the above

  delay(5000); // Wait for 5 seconds before the next loop
}
