#ifndef __PARAMETERS_H
#define __PARAMETERS_H

#include <Arduino.h>

#define CANFORMAT // Comment this define to disable format parameters feature

#ifdef CANFORMAT
const uint8_t PIN_FORMAT = 7; // Connect this pin to ground on startup to format parameters
const uint32_t FORMAT_DETECT_TIME = 1000; // 1 sec.
#endif

class BaseParameters {
public:
  BaseParameters(uint8_t chunks = 1) : _chunks(chunks), _crc(0xFF) {}
  virtual bool begin();
  virtual void format();
  virtual bool read();
  virtual bool write();
  virtual bool setParameter(const char* name, const char* value);

protected:
  virtual int16_t readData(uint16_t offset, uint8_t chunk = 0) = 0;
  virtual int16_t writeData(uint16_t offset, uint8_t chunk = 0) = 0;
  virtual void defaults(uint8_t chunk = 0);

  void initCRC() {
    _crc = 0xFF;
  }
  void updateCRC(uint8_t data) {
    _crc = _crc8update(_crc, data);
  }
  uint8_t getCRC() const {
    return _crc;
  }

  virtual uint16_t _read(uint16_t offset, void* buf, uint16_t size, bool calcCRC = true) = 0;
  virtual uint16_t _write(uint16_t offset, const void* buf, uint16_t size, bool calcCRC = true) = 0;
  virtual int16_t checkSignature();
  virtual int16_t writeSignature();
  virtual int16_t checkCRC(uint16_t offset);
  virtual int16_t writeCRC(uint16_t offset);

  static uint8_t _crc8update(uint8_t crc, uint8_t data);
  static uint8_t _crc8(uint8_t crc, const uint8_t* buf, uint16_t size);

  uint8_t _chunks;
  uint8_t _crc;
};

class EEPROMParameters : public BaseParameters {
public:
  EEPROMParameters(uint8_t chunks = 1) : BaseParameters(chunks) {}

protected:
  uint16_t _read(uint16_t offset, void* buf, uint16_t size, bool calcCRC = true);
  uint16_t _write(uint16_t offset, const void* buf, uint16_t size, bool calcCRC = true);
};

#endif
