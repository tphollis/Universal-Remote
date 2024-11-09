// Include Header File
#include "OLED.h"

// Define Global Variables
int OLED_VCC;
int OLED_SDA;
int OLED_SCL;

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setupOLED(int vcc, int scl, int sda) {
    OLED_VCC = vcc;
    OLED_SCL = scl;
    OLED_SDA = sda;

    // Start with OLED Screen Turned on
    pinMode(OLED_VCC, OUTPUT);
    setOLEDPower(true);

    // Initialize I2C with provided pins
    Wire.begin(OLED_SDA, OLED_SCL);
    
    // Add a small delay for stability
    delay(100);
    
    if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
        Serial.println(F("SSD1306 allocation failed"));
        Serial.println("Trying alternate address...");
        
        // Try alternate address if first attempt fails
        if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3D)) {
            Serial.println(F("SSD1306 allocation still failed"));
            for(;;);
        }
    }
    
    display.clearDisplay();
    display.setTextColor(WHITE);
    display.setTextSize(1);
    display.cp437(true);  // Use full 256 char 'Code Page 437' font
    display.display();
}

void setOLEDPower(bool on) {
    digitalWrite(OLED_VCC, on ? HIGH : LOW);
}

// Remove default arguments from implementation
void displayText(const char* text, int x, int y, int size) {
    display.setTextSize(size);
    display.setCursor(x, y);
    display.println(text);
    display.display();
}

void clearDisplay() {
    display.clearDisplay();
    display.display();
}

void bootAnimation() {
    display.clearDisplay();

    const int MAX_TAIL_LENGTH = 10;

    // Structure to store previous positions
    struct Point {
        int x;
        int y;
    };

    Point tail[MAX_TAIL_LENGTH];

    // Initialize tail positions
    for (int i = 0; i < MAX_TAIL_LENGTH; i++) {
        tail[i] = {-10, -10};
    }

    // Set initial parameters for the oval spiral motion
    float angle = 0.0;                            // Start angle in radians
    float radiusX = SCREEN_WIDTH / 2.0;           // Horizontal radius (width of spiral)
    float radiusY = SCREEN_HEIGHT / 2.0;          // Vertical radius (height of spiral)
    float centerX = SCREEN_WIDTH / 2;
    float centerY = SCREEN_HEIGHT / 2;
    float angleIncrement = 0.4;                   // Speed of angle increase (higher value = fewer spirals)
    float radiusDecrementX = 0.8;                 // Rate at which horizontal radius decreases
    float radiusDecrementY = 0.5;                 // Rate at which vertical radius decreases

    int tailIndex = 0; // Index to track current tail position

    // Spiral effect moving toward the center
    while (radiusX > 1 || radiusY > 1) {          // Continue until close to center
        display.clearDisplay();

        // Calculate x and y positions based on angle and oval radii
        int x = centerX + cos(angle) * radiusX;
        int y = centerY + sin(angle) * radiusY;

        // Store current position in the tail array
        tail[tailIndex] = {x, y};
        tailIndex = (tailIndex + 1) % MAX_TAIL_LENGTH;  // Loop back to start if max length is reached

        // Draw the tail with smaller circles for older positions (simulating fading)
        for (int i = 0; i < MAX_TAIL_LENGTH; i++) {
            int index = (tailIndex + i) % MAX_TAIL_LENGTH;
            int size = 3 - i / 5;  // Decrease size of circles as tail ages
            if (size > 0) {
                display.fillCircle(tail[index].x, tail[index].y, size, SSD1306_WHITE);
            }
        }

        // Draw the "light object" (a small circle) at the current position
        display.fillCircle(x, y, 3, WHITE);

        display.display();
        delay(20);  // Controls the speed of the animation

        // Update angle and radii for oval spiral effect
        angle += angleIncrement;
        radiusX -= radiusDecrementX;
        radiusY -= radiusDecrementY;
    }

    // Step 1: Explosion with multiple flying circles
    int numExplosions = 20;  // Number of explosion particles
    struct ExplosionParticle {
        int x, y;
        int speedX, speedY;
        int size;
    };
    
    ExplosionParticle particles[numExplosions];

    // Initialize explosion particles with random directions and speeds
    for (int i = 0; i < numExplosions; i++) {
        float angle = random(0, 360);  // Random direction in degrees
        int speed = random(3, 10);     // Random speed for the explosion particles
        particles[i].x = centerX;
        particles[i].y = centerY;
        particles[i].speedX = cos(angle * DEG_TO_RAD) * speed;
        particles[i].speedY = sin(angle * DEG_TO_RAD) * speed;
        particles[i].size = random(1, 4);  // Random size for the explosion particles
    }

    // Explosion animation: move and draw each particle, while displaying the text
    int explosionTime = 0;
    while (explosionTime < 30) {  // Continue for a fixed number of steps
        display.clearDisplay();

        // Update and draw each explosion particle
        for (int i = 0; i < numExplosions; i++) {
            particles[i].x += particles[i].speedX;
            particles[i].y += particles[i].speedY;
            display.fillCircle(particles[i].x, particles[i].y, particles[i].size, SSD1306_WHITE);
        }

        // Display the "Controlex" text at the center during the explosion
        display.setTextColor(SSD1306_WHITE);
        display.setTextSize(2);
        display.setCursor(10, 25);
        display.print("Controlex");

        display.display();
        delay(50);  // Controls the speed of the explosion animation
        explosionTime++;
    }

    delay(500);  // Hold the explosion for a bit before clearing screen

    // Clear the display after the explosion
    display.clearDisplay();
    display.display();
}



