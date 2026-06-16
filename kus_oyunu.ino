#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Ekran boyutlari
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

// Pin Tanimlamalari
#define OLED_RESET     -1
#define BUTTON_PIN     4   // Yesil kablo D4'e bagli (Dahili INPUT_PULLUP ile GND'ye tetiklenir)
#define BUZZER_PIN     23  // Kirmizi kablo D23'e bagli

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// --- HIZ VE FIZIK AYARLARI ---
float birdY = 32;
float velocity = 0;
float gravity = 0.25;    // Kusun dusus hizi (Yavaslatildi)
float jump = -2.5;       // Yercekimiyle dengeli ziplama gucu

int pipeX = 128;
int pipeGap = 26;        // Borularin arasindaki dikey gecis boslugu
int pipeGapY = 20;
int pipeWidth = 12;
float pipeSpeed = 1.2;   // Borularin baslangic gelis hizi (Yavaslatildi)

int score = 0;
bool gameOver = false;
bool gameStarted = false;

// Kusun Sekli (Bitmap - 8x6 piksel)
static const unsigned char PROGMEM bird_bmp[] = {
  0b00111100,
  0b01111110,
  0b11111111,
  0b11110011,
  0b11111111,
  0b01111110,
};

void setup() {
  Serial.begin(115200);

  // I2C pinlerini baslatiyoruz (SDA: 21, SCL: 22)
  Wire.begin(21, 22);

  // Ekrani baslat
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println(F("SSD1306 ekran bulunamadi!"));
    for(;;);
  }
  
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(BUZZER_PIN, OUTPUT);

  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  
  resetGame();
}

void loop() {
  display.clearDisplay();

  if (!gameStarted) {
    // Acilis Ekrani (Telif riski barindirmayan temiz isim)
    display.setTextSize(2);
    display.setCursor(40, 10);
    display.print("KUS");
    display.setCursor(28, 32);
    display.print("OYUNU");
    
    display.setTextSize(1);
    display.setCursor(15, 54);
    display.print("Ziplamak icin bas");
    display.display();

    if (digitalRead(BUTTON_PIN) == LOW) {
      gameStarted = true;
      playSound(1000, 100);
      delay(200);
    }
  } 
  else if (gameOver) {
    // Oyun Bitti Ekrani
    display.setTextSize(2);
    display.setCursor(10, 10);
    display.print("GAME OVER");
    
    display.setTextSize(1);
    display.setCursor(35, 35);
    display.print("Skor: ");
    display.print(score);
    
    display.setCursor(15, 52);
    display.print("Tekrar baslat...");
    display.display();

    if (digitalRead(BUTTON_PIN) == LOW) {
      resetGame();
      delay(200);
    }
  } 
  else {
    // Ana Oyun Dongusu
    
    // Ziplama kontrolu
    if (digitalRead(BUTTON_PIN) == LOW) {
      velocity = jump;
      playSound(800, 40);
    }

    // Fizik kurallari
    velocity += gravity;
    birdY += velocity;

    // Boru hareketi
    pipeX -= pipeSpeed;

    // Boru ekrandan cikinca sifirla ve skoru arttir
    if (pipeX < -pipeWidth) {
      pipeX = 128;
      pipeGapY = random(10, 38);
      score++;
      playSound(1200, 60);
      
      // Hizlanma siniri kontrolu (Maksimum 2.5 hiza ulasabilir)
      if(score % 5 == 0 && pipeSpeed < 2.5) {
        pipeSpeed += 0.15;
      }
    }

    // Carpisma Testleri
    // Tavan veya tabana carpma kontrolu
    if (birdY > SCREEN_HEIGHT - 6 || birdY < 0) {
      endGame();
    }
    
    // Boruya carpma kontrolu
    if (pipeX < 24 + 8 && pipeX + pipeWidth > 24) {
      if (birdY < pipeGapY || birdY > pipeGapY + pipeGap - 6) {
        endGame();
      }
    }

    // Grafiklerin Ekrana Cizilmesi
    // Ust Boru
    display.fillRect(pipeX, 0, pipeWidth, pipeGapY, SSD1306_WHITE);
    // Alt Boru
    display.fillRect(pipeX, pipeGapY + pipeGap, pipeWidth, SCREEN_HEIGHT - (pipeGapY + pipeGap), SSD1306_WHITE);
    // Kus Bitmap'i (X ekseninde sabit 24. pikselde durur)
    display.drawBitmap(24, (int)birdY, bird_bmp, 8, 6, SSD1306_WHITE);

    // Canli Skor Gösterimi
    display.setTextSize(1);
    display.setCursor(0, 0);
    display.print("Skor: ");
    display.print(score);

    display.display();
  }

  delay(30); // Ekran yenilenme suresi gecikmesi
}

void resetGame() {
  birdY = 32;
  velocity = 0;
  pipeX = 128;
  pipeGapY = random(10, 38);
  score = 0;
  pipeSpeed = 1.2; 
  gameOver = false;
}

void endGame() {
  gameOver = true;
  playSound(300, 300);
  delay(100);
  playSound(150, 400);
}

void playSound(int frequency, int duration) {
  tone(BUZZER_PIN, frequency, duration);
}
