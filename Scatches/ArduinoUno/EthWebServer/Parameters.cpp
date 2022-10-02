#include <avr/pgmspace.h>
#include <EEPROM.h>
#include "Parameters.h"

const uint8_t SIGNATURE_SIZE = 4;
const char _signature[SIGNATURE_SIZE] PROGMEM = { '#', 'A', 'V', 'R' };

bool BaseParameters::begin() {
#ifdef CANFORMAT
  pinMode(PIN_FORMAT, INPUT_PULLUP);
  if (! digitalRead(PIN_FORMAT)) {
    uint32_t detectTime = millis() + FORMAT_DETECT_TIME;
    bool detected = true;
    while (millis() < detectTime) {
      if (digitalRead(PIN_FORMAT)) {
        detected = false;
        break;
      }
    }
    if (detected) {
      format();
      Serial.println(F("EEPROM cleared"));
    }
  }
#endif

  return true;
}

void BaseParameters::format() {
  char sign[SIGNATURE_SIZE];

  memset(sign, 0xFF, SIGNATURE_SIZE);
  _write(0, sign, SIGNATURE_SIZE, false);
}

bool BaseParameters::read() {
  int16_t result;

  result = checkSignature();
  if (result < 0) {
    defaults(0);
    return false;
  }
  for (uint8_t chunk = 0; chunk < _chunks; ++chunk) {
    initCRC();
    result = readData(result, chunk);
    if (result > 0)
      result = checkCRC(result);
    if (result < 0) {
      defaults(chunk);
      return false;
    }
  }

  return true;
}

bool BaseParameters::write() {
  int16_t result;

  result = writeSignature();
  if (result < 0)
    return false;
  for (uint8_t chunk = 0; chunk < _chunks; ++chunk) {
    initCRC();
    result = writeData(result, chunk);
    if (result > 0)
      result = writeCRC(result);
    if (result < 0)
      return false;
  }

  return true;
}

bool BaseParameters::setParameter(const char* name, const char* value) {
  return false;
}

void BaseParameters::defaults(uint8_t chunk) {
// Stub
}

int16_t BaseParameters::checkSignature() {
  char sign[SIGNATURE_SIZE];

  if (_read(0, sign, SIGNATURE_SIZE, false) != SIGNATURE_SIZE)
    return -1;
  for (uint8_t i = 0; i < SIGNATURE_SIZE; ++i) {
    if (sign[i] != pgm_read_byte(_signature + i))
      return -1;
  }

  return SIGNATURE_SIZE;
}

int16_t BaseParameters::writeSignature() {
  char sign[SIGNATURE_SIZE];

  memcpy_P(sign, _signature, SIGNATURE_SIZE);
  if (_write(0, sign, SIGNATURE_SIZE, false) != SIGNATURE_SIZE)
    return -1;

  return SIGNATURE_SIZE;  
}

int16_t BaseParameters::checkCRC(uint16_t offset) {
  uint8_t crc;

  if ((_read(offset, &crc, sizeof(crc), false) != sizeof(crc)) || (crc != _crc))
    return -1;

  return (offset + sizeof(crc));
}

int16_t BaseParameters::writeCRC(uint16_t offset) {
  if (_write(offset, &_crc, sizeof(_crc), false) != sizeof(_crc))
    return -1;

  return (offset + sizeof(_crc));
}

uint8_t BaseParameters::_crc8update(uint8_t crc, uint8_t data) {
  crc ^= data;

  for (uint8_t i = 0; i < 8; ++i)
    crc = crc & 0x80 ? (crc << 1) ^ 0x31 : crc << 1;

  return crc;
}

uint8_t BaseParameters::_crc8(uint8_t crc, const uint8_t* buf, uint16_t size) {
  while (size--) {
    crc = _crc8update(crc, *buf++);
  }

  return crc;
}

uint16_t EEPROMParameters::_read(uint16_t offset, void* buf, uint16_t size, bool calcCRC) {
  uint8_t* bufptr = (uint8_t*)buf;
  uint16_t result = 0;

  while (size--) {
    uint8_t data = EEPROM.read(offset++);
    if (calcCRC)
      updateCRC(data);
    *bufptr++ = data;
    ++result;
  }

  return result;
}

uint16_t EEPROMParameters::_write(uint16_t offset, const void* buf, uint16_t size, bool calcCRC) {
  uint8_t* bufptr = (uint8_t*)buf;
  uint16_t result = 0;

  while (size--) {
    uint8_t data = *bufptr++;
    if (calcCRC)
      updateCRC(data);
    EEPROM.update(offset++, data);
    ++result;
  }

  return result;
}
