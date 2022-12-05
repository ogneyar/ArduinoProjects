
// STM32F103C8T6

#include <Wire.h>
 
 
void setup() {
    // I2C-1 standard pins: PB7(sda) PB6(scl)    
    Wire.begin();
    // I2C-1 alternative pins: PB9(sda) PB8(scl)
    //Wire.setSDA(PB11);
    //Wire.setSCL(PB10);
    //Wire.begin();
    // If you want to use the two I2Cs simultaneously, create a new instance for the second I2C
    // I2C-2: PB11(sda) PB10(scl)
    // TwoWire Wire2(PB9,PB8); 
    // Wire2.begin();
    
    Serial.begin(115200);
    while (!Serial); 
    
    Serial.println("\nI2C Scanner");
}
 
 
void loop() {
    byte error, address;
    int nDevices;
    
    Serial.println("Scanning...");
    
    nDevices = 0;
    for(address = 1; address < 127; address++ ) {
        // The i2c_scanner uses the return value of
        // the Write.endTransmisstion to see if
        // a device did acknowledge to the address.
        Wire.beginTransmission(address);
        error = Wire.endTransmission();
    
        if (error == 0) {
            Serial.print("I2C device found at address 0x");
            if (address<16)
                Serial.print("0");
            Serial.print(address,HEX);
            Serial.println("  !");
        
            nDevices++;
        }else if (error==4) {
            Serial.print("Unknown error at address 0x");
            if (address<16) Serial.print("0");
            Serial.println(address,HEX);
        }    
    }

    if (nDevices == 0) Serial.println("No I2C devices found\n");
    else Serial.println("done\n");
    
    delay(5000);           // wait 5 seconds for next scan
}
