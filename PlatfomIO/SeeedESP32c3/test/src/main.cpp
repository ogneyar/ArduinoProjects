
// void main(void) { while(1) {} }

void setup(void) {
    pinMode(2, OUTPUT);
}

void loop(void) {
    digitalWrite(2, HIGH);
    delay(100);
    digitalWrite(2, LOW);
    delay(100);
}

