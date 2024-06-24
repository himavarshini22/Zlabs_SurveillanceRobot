#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN         9          // Configurable, see typical pin layout above
#define SS_PIN          10         // Configurable, see typical pin layout above
int count = 0;
MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance

// byte accessUID1[4] = {0xD3, 0x7A, 0xC0, 0x2E};
// byte accessUID2[4] = {0x30, 0x5B, 0x64, 0x20};
// byte accessUID3[4] = {0x1E, 0xE3, 0x66, 0xB9};
// byte accessUID4[4] = {0x6E, 0xCB, 0x5F, 0xB9};

byte L1S[4] = {0x41, 0xC5, 0x37, 0x2D};
byte L1E[4] = {0x71, 0xC4, 0x2F, 0x2D};
byte L2S[4] = {0x71, 0xD4, 0x2C, 0x2D};
byte L2E[4] = {0x11, 0x65, 0x3E, 0x2D};

void setup() {
    Serial.begin(9600);         // Initialize serial communications with the PC
    while (!Serial);            // Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)
    SPI.begin();                // Init SPI bus
    mfrc522.PCD_Init();         // Init MFRC522
    delay(4);                   // Optional delay. Some boards do need more time after init to be ready, see Readme
    // mfrc522.PCD_DumpVersionToSerial(); // Show details of PCD - MFRC522 Card Reader details
}

void loop() {
    // Reset the loop if no new card present on the sensor/reader. This saves the entire process when idle.
    if ( ! mfrc522.PICC_IsNewCardPresent()) {
        return;
    }

    // Select one of the cards
    if ( ! mfrc522.PICC_ReadCardSerial()) {
        return;
    }

    if (equal(mfrc522.uid.uidByte, L1S) || 
        equal(mfrc522.uid.uidByte, L1E) || 
        equal(mfrc522.uid.uidByte, L2S) || 
        equal(mfrc522.uid.uidByte, L2E)) {
        count++;    
        if (count % 2 == 0 && count != 0) {
            Serial.println("Lane " + String(count / 2) + " ended");
        } else {
            Serial.println("Lane " + String((count + 1) / 2) + " started");
        }
    } else {
        Serial.println("Unknown Card");
    }
    delay(2000);
}

bool equal(byte arr1[4], byte arr2[4]) {
    for (int i = 0; i < 4; i++) {
        if (arr1[i] != arr2[i]) {
            return false;
        }
    }
    return true;
}
