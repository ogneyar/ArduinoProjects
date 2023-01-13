#pragma once

#include <string.h>
#include <driver/rmt.h>

struct __attribute__((__packed__)) sound_t {
  uint16_t freq; // Hz
  uint16_t duration; // ms.
};

template<const rmt_channel_t BUZZER_RMT_CHANNEL = RMT_CHANNEL_0>
class Buzzer {
public:
  Buzzer(uint8_t pin);

  bool playing() const;
  void play(uint16_t freq, uint16_t duration);
  void play(const sound_t *sound) {
    play(sound->freq, sound->duration);
  }
  void play(const sound_t *sounds, uint16_t length);
  void stop();
  bool playNote(char note, bool sharp = false, uint8_t duration = 4, bool dot = false, uint8_t octave = 5, uint16_t tempo = 63);
  bool playRTTTL(const char *notes);

protected:
  static void rmt_tx_loop_end(rmt_channel_t channel, void *args);
  static void rmt_sound(uint16_t freq, uint16_t duration);

  bool noteToSound(char note, bool sharp, uint8_t duration, bool dot, uint8_t octave, uint16_t tempo, sound_t *sound);
  uint16_t numFromString(char **str);
  bool checkNoteDuration(uint16_t duration);
  int16_t checkRTTTL(const char *notes);

  sound_t *_sounds;
  uint16_t _length;
  volatile uint16_t _position;
};

template<const rmt_channel_t BUZZER_RMT_CHANNEL>
Buzzer<BUZZER_RMT_CHANNEL>::Buzzer(uint8_t pin) : _sounds(nullptr) {
  rmt_config_t config = RMT_DEFAULT_CONFIG_TX((gpio_num_t)pin, BUZZER_RMT_CHANNEL);

  config.tx_config.loop_en = true; // Enable loop mode
  rmt_config(&config);
  rmt_driver_install(BUZZER_RMT_CHANNEL, 0, 0);
  rmt_register_tx_end_callback(rmt_tx_loop_end, this);
}

template<const rmt_channel_t BUZZER_RMT_CHANNEL>
bool Buzzer<BUZZER_RMT_CHANNEL>::playing() const {
  if (_sounds && (_position < _length))
    return true;

  rmt_channel_status_result_t status;

  rmt_get_channel_status(&status);
  return status.status[BUZZER_RMT_CHANNEL - RMT_CHANNEL_0] == RMT_CHANNEL_BUSY;
}

template<const rmt_channel_t BUZZER_RMT_CHANNEL>
void Buzzer<BUZZER_RMT_CHANNEL>::play(uint16_t freq, uint16_t duration) {
  stop();
  rmt_sound(freq, duration);
}

template<const rmt_channel_t BUZZER_RMT_CHANNEL>
void Buzzer<BUZZER_RMT_CHANNEL>::play(const sound_t *sounds, uint16_t length) {
  stop();
  _sounds = new sound_t[length];
  if (! _sounds)
    return;
  memcpy(_sounds, sounds, sizeof(sound_t) * length);
  _length = length;
  rmt_sound(_sounds[0].freq, _sounds[0].duration);
  _position = 1;
}

template<const rmt_channel_t BUZZER_RMT_CHANNEL>
void Buzzer<BUZZER_RMT_CHANNEL>::stop() {
  rmt_tx_stop(BUZZER_RMT_CHANNEL);
  if (_sounds) {
    delete[] _sounds;
    _sounds = nullptr;
  }
}

template<const rmt_channel_t BUZZER_RMT_CHANNEL>
void Buzzer<BUZZER_RMT_CHANNEL>::rmt_tx_loop_end(rmt_channel_t channel, void *args) {
  if (channel == BUZZER_RMT_CHANNEL) {
    Buzzer *self = (Buzzer*)args;

    rmt_tx_stop(BUZZER_RMT_CHANNEL);
    if (self->_sounds && (self->_position < self->_length)) {
      rmt_sound(self->_sounds[self->_position].freq, self->_sounds[self->_position].duration);
      ++self->_position;
    }
  }
}

template<const rmt_channel_t BUZZER_RMT_CHANNEL>
void Buzzer<BUZZER_RMT_CHANNEL>::rmt_sound(uint16_t freq, uint16_t duration) {
  rmt_item32_t items[32];
  uint32_t rmt_freq;
  uint16_t count;

  rmt_get_counter_clock(BUZZER_RMT_CHANNEL, &rmt_freq);
  if (freq) {
    items[0].level0 = 1;
    items[0].duration0 = rmt_freq / freq / 2;
    items[0].level1 = 0;
    items[0].duration1 = items[0].duration0;
    duration = (uint32_t)duration * freq / 1000;
  } else {
    items[0].level0 = 0;
    items[0].duration0 = rmt_freq / 1000 / 2;
    items[0].level1 = 0;
    items[0].duration1 = items[0].duration0;
  }
  count = (duration + 1022) / 1023;
  if (count <= sizeof(items) / sizeof(items[0])) {
    for (uint8_t i = 1; i < count; ++i) {
      memcpy(&items[i], &items[0], sizeof(rmt_item32_t));
    }
    duration /= count;
    rmt_set_tx_loop_count(BUZZER_RMT_CHANNEL, duration);
    rmt_write_items(BUZZER_RMT_CHANNEL, items, count, false);
  }
}

template<const rmt_channel_t BUZZER_RMT_CHANNEL>
bool Buzzer<BUZZER_RMT_CHANNEL>::playNote(char note, bool sharp, uint8_t duration, bool dot, uint8_t octave, uint16_t tempo) {
  sound_t sound;

  if (noteToSound(note, sharp, duration, dot, octave, tempo, &sound)) {
    play(&sound);
    return true;
  }
  return false;
}

template<const rmt_channel_t BUZZER_RMT_CHANNEL>
bool Buzzer<BUZZER_RMT_CHANNEL>::playRTTTL(const char *notes) {
  uint16_t defaultTempo = 63;
  uint8_t defaultDuration = 4;
  uint8_t defaultOctave = 5;

  stop();
  {
    int16_t length = checkRTTTL(notes);

    if (length <= 0)
      return false;
    _sounds = new sound_t[length];
    if (! _sounds)
      return false;
    _length = length;
    _position = 0;
  }

  while (*notes++ != ':'); // Skip name part
  if (*notes == 'd') {
    ++notes;
    ++notes; // Skip '='
    defaultDuration = numFromString((char**)&notes);
    if (*notes == ',')
      ++notes; // Skip ','
  }
  if (*notes == 'o') {
    ++notes;
    ++notes; // Skip '='
    defaultOctave = numFromString((char**)&notes);
    if (*notes == ',')
      ++notes; // Skip ','
  }
  if (*notes == 'b') {
    ++notes;
    ++notes; // Skip '='
    defaultTempo = numFromString((char**)&notes);
  }
  ++notes; // Skip ':'
  while (*notes) {
    uint8_t duration, octave;
    char note;
    bool sharp = false, dot = false;

    duration = defaultDuration;
    if (isdigit(*notes)) {
      duration = numFromString((char**)&notes);
    }
    note = *notes++;
    if (*notes == '#') {
      sharp = true;
      ++notes;
    }
    if (*notes == '.') {
      dot = true;
      ++notes;
    }
    octave = defaultOctave;
    if (isdigit(*notes)) {
      octave = numFromString((char**)&notes);
    }
    if (*notes == ',') { // Skip ','
      ++notes;
    }
    noteToSound(note, sharp, duration, dot, octave, defaultTempo, &_sounds[_position++]);
  }
  rmt_sound(_sounds[0].freq, _sounds[0].duration);
  _position = 1;
  return true;
}

template<const rmt_channel_t BUZZER_RMT_CHANNEL>
bool Buzzer<BUZZER_RMT_CHANNEL>::noteToSound(char note, bool sharp, uint8_t duration, bool dot, uint8_t octave, uint16_t tempo, sound_t *sound) {
  static const uint16_t NOTES[] = {
    262, 277, 294, 311, 330, 349, 370, 392, 415, 440, 466, 494,
    523, 554, 587, 622, 659, 698, 740, 784, 831, 880, 932, 988,
    1047, 1109, 1175, 1245, 1319, 1397, 1480, 1568, 1661, 1760, 1865, 1976,
    2093, 2217, 2349, 2489, 2637, 2794, 2960, 3136, 3322, 3520, 3729, 3951
  };

  uint32_t toneDuration = (60000 * 4 / tempo) / duration;

  if (dot)
    toneDuration += toneDuration / 2;
  if (note == 'p') { // Pause
    sound->freq = 0;
    sound->duration = toneDuration;
  } else {
    switch (note) {
      case 'c':
        note = 0;
        break;
      case 'd':
        note = 2;
        break;
      case 'e':
        note = 4;
        break;
      case 'f':
        note = 5;
        break;
      case 'g':
        note = 7;
        break;
      case 'a':
        note = 9;
        break;
      case 'b':
        note = 11;
        break;
      default:
        return false;
    }
    if (sharp) {
      if ((note == 4) || (note == 11)) // e# and b# doesn't exist
        return false;
      ++note;
    }
    sound->freq = NOTES[(octave - 4) * 12 + note];
    sound->duration = toneDuration;
  }
  return true;
}

template<const rmt_channel_t BUZZER_RMT_CHANNEL>
uint16_t Buzzer<BUZZER_RMT_CHANNEL>::numFromString(char **str) {
  uint16_t result = 0;

  while (isdigit(**str)) {
    result = result * 10 + (*((*str)++) - '0');
  }
  return result;
}

template<const rmt_channel_t BUZZER_RMT_CHANNEL>
bool Buzzer<BUZZER_RMT_CHANNEL>::checkNoteDuration(uint16_t duration) {
  for (uint8_t i = 0; i <= 5; ++i) {
    if (duration == (1 << i))
      return true;
  }
  return false;
}

template<const rmt_channel_t BUZZER_RMT_CHANNEL>
int16_t Buzzer<BUZZER_RMT_CHANNEL>::checkRTTTL(const char *notes) {
  const char *_notes = notes;
  int16_t result = 0;
  uint16_t t;

  while (*_notes && (*_notes != ':'))
    ++_notes;
  if (*_notes++ != ':') // No name part!
    return (int16_t)(notes - _notes);
  if (*_notes == 'd') {
    if (*++_notes != '=')
      return (int16_t)(notes - _notes);
    ++_notes;
    t = numFromString((char**)&_notes);
    if (! checkNoteDuration(t))
      return (int16_t)(notes - _notes);
    if (*_notes == ',')
      ++_notes;
  }
  if (*_notes == 'o') {
    if (*++_notes != '=')
      return (int16_t)(notes - _notes);
    ++_notes;
    t = numFromString((char**)&_notes);
    if ((t < 4) || (t > 7))
      return (int16_t)(notes - _notes);
    if (*_notes == ',')
      ++_notes;
  }
  if (*_notes == 'b') {
    if (*++_notes != '=')
      return (int16_t)(notes - _notes);
    ++_notes;
    t = numFromString((char**)&_notes);
    if (! t)
      return (int16_t)(notes - _notes);
  }
  if (*_notes++ != ':')
    return (int16_t)(notes - _notes);
  while (*_notes) {
    char note;

    if (isdigit(*_notes)) {
      t = numFromString((char**)&_notes);
      if (! checkNoteDuration(t))
        return (int16_t)(notes - _notes);
    }
    note = *_notes++;
    if ((note != 'p') && ((note < 'a') || (note > 'g')))
      return (int16_t)(notes - _notes);
    if (*_notes == '#') {
      if ((note == 'b') || (note == 'e'))
        return (int16_t)(notes - _notes);
      ++_notes;
    }
    if (*_notes == '.') {
      ++_notes;
    }
    if (isdigit(*_notes)) {
      t = numFromString((char**)&_notes);
      if ((t < 4) || (t > 7))
        return (int16_t)(notes - _notes);
    }
    if (*_notes == ',') { // Skip ','
      ++_notes;
    }
    ++result;
  }
  return result;
}
