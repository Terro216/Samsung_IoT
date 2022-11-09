#ifndef TROYKA_LED_MATRIX_H
#define TROYKA_LED_MATRIX_H

#include <Arduino.h>
#include <Wire.h>
#include <avr/pgmspace.h>

#define I2C_ADDR_BASE               0b01100000
#define I2C_ADDR_ALT0               0b01100000
#define I2C_ADDR_ALT1               0b01100001
#define I2C_ADDR_ALT2               0b01100010
#define I2C_ADDR_ALT3               0b01100011
#define I2C_ADDR_MASK               0b00000011

#define MATRIX_SIZE_8X8             0b0000
#define MATRIX_SIZE_7X9             0b0001
#define MATRIX_SIZE_6X10            0b0010
#define MATRIX_SIZE_5X11            0b0011
#define MATRIX_SIZE_MASK            0b0011

#define MATRIX_MIN_ROWS             8
#define MATRIX_MAX_ROWS             11
#define MATRIX_MIN_COLS             5
#define MATRIX_MAX_COLS             8

#define AUDIO_GAIN_0DB              0b0000
#define AUDIO_GAIN_3DB              0b0001
#define AUDIO_GAIN_6DB              0b0010
#define AUDIO_GAIN_9DB              0b0011
#define AUDIO_GAIN_12DB             0b0100
#define AUDIO_GAIN_15DB             0b0101
#define AUDIO_GAIN_18DB             0b0110
#define AUDIO_GAIN_M6DB             0b0111
#define AUDIO_GAIN_MASK             0b0111

#define ROW_CURRENT_40MA            0b0000
#define ROW_CURRENT_45MA            0b0001
#define ROW_CURRENT_50MA            0b0010
#define ROW_CURRENT_55MA            0b0011
#define ROW_CURRENT_60MA            0b0100
#define ROW_CURRENT_65MA            0b0101
#define ROW_CURRENT_70MA            0b0110
#define ROW_CURRENT_75MA            0b0111
#define ROW_CURRENT_05MA            0b1000
#define ROW_CURRENT_10MA            0b1001
#define ROW_CURRENT_15MA            0b1010
#define ROW_CURRENT_20MA            0b1011
#define ROW_CURRENT_25MA            0b1100
#define ROW_CURRENT_30MA            0b1101
#define ROW_CURRENT_35MA            0b1110
#define ROW_CURRENT_XXMA            0b1111
#define ROW_CURRENT_MASK            0b1111

#define REG_ADDR_CONFIGURATION      0x00
#define REG_ADDR_COLUMN_DATA        0x01
#define REG_ADDR_UPDATE_COLUMN      0x0C
#define REG_ADDR_LIGHTING_EFFECT    0x0D
#define REG_ADDR_AUDIO_EQUALIZER    0x0F

#define BIT_CONFIG_SSD              7
#define BIT_CONFIG_AUDIO_EN         2
#define BIT_CONFIG_ADM              0

#define BIT_EFFECT_AUDIO_GAIN       4
#define BIT_EFFECT_ROW_CURRENT      0

#define BIT_AUDIO_EQ_EN             6

#define FONT_8X8_BASIC              0
#define FONT_8X8_CONTROL            1
#define FONT_8X8_EXT_LATIN          2
#define FONT_8X8_GREEK              3
#define FONT_8X8_MISC               4
#define FONT_8X8_BOX                5
#define FONT_8X8_BLOCK              6
#define FONT_8X8_HIRAGANA           7
#define FONT_8X8_SGA                8

#define ROTATION_0                  0
#define ROTATION_90                 1
#define ROTATION_180                2
#define ROTATION_270                3

const uint8_t PROGMEM RER_BIT_MAP[256] = {  0x00, 0x80, 0x40, 0xC0, 0x20, 0xA0, 0x60, 0xE0, 0x10, 0x90, 0x50, 0xD0, 0x30, 0xB0, 0x70, 0xF0,
                                            0x08, 0x88, 0x48, 0xC8, 0x28, 0xA8, 0x68, 0xE8, 0x18, 0x98, 0x58, 0xD8, 0x38, 0xB8, 0x78, 0xF8, 
                                            0x04, 0x84, 0x44, 0xC4, 0x24, 0xA4, 0x64, 0xE4, 0x14, 0x94, 0x54, 0xD4, 0x34, 0xB4, 0x74, 0xF4,
                                            0x0C, 0x8C, 0x4C, 0xCC, 0x2C, 0xAC, 0x6C, 0xEC, 0x1C, 0x9C, 0x5C, 0xDC, 0x3C, 0xBC, 0x7C, 0xFC,
                                            0x02, 0x82, 0x42, 0xC2, 0x22, 0xA2, 0x62, 0xE2, 0x12, 0x92, 0x52, 0xD2, 0x32, 0xB2, 0x72, 0xF2,
                                            0x0A, 0x8A, 0x4A, 0xCA, 0x2A, 0xAA, 0x6A, 0xEA, 0x1A, 0x9A, 0x5A, 0xDA, 0x3A, 0xBA, 0x7A, 0xFA,
                                            0x06, 0x86, 0x46, 0xC6, 0x26, 0xA6, 0x66, 0xE6, 0x16, 0x96, 0x56, 0xD6, 0x36, 0xB6, 0x76, 0xF6,
                                            0x0E, 0x8E, 0x4E, 0xCE, 0x2E, 0xAE, 0x6E, 0xEE, 0x1E, 0x9E, 0x5E, 0xDE, 0x3E, 0xBE, 0x7E, 0xFE,
                                            0x01, 0x81, 0x41, 0xC1, 0x21, 0xA1, 0x61, 0xE1, 0x11, 0x91, 0x51, 0xD1, 0x31, 0xB1, 0x71, 0xF1,
                                            0x09, 0x89, 0x49, 0xC9, 0x29, 0xA9, 0x69, 0xE9, 0x19, 0x99, 0x59, 0xD9, 0x39, 0xB9, 0x79, 0xF9,
                                            0x05, 0x85, 0x45, 0xC5, 0x25, 0xA5, 0x65, 0xE5, 0x15, 0x95, 0x55, 0xD5, 0x35, 0xB5, 0x75, 0xF5,
                                            0x0D, 0x8D, 0x4D, 0xCD, 0x2D, 0xAD, 0x6D, 0xED, 0x1D, 0x9D, 0x5D, 0xDD, 0x3D, 0xBD, 0x7D, 0xFD,
                                            0x03, 0x83, 0x43, 0xC3, 0x23, 0xA3, 0x63, 0xE3, 0x13, 0x93, 0x53, 0xD3, 0x33, 0xB3, 0x73, 0xF3,
                                            0x0B, 0x8B, 0x4B, 0xCB, 0x2B, 0xAB, 0x6B, 0xEB, 0x1B, 0x9B, 0x5B, 0xDB, 0x3B, 0xBB, 0x7B, 0xFB,
                                            0x07, 0x87, 0x47, 0xC7, 0x27, 0xA7, 0x67, 0xE7, 0x17, 0x97, 0x57, 0xD7, 0x37, 0xB7, 0x77, 0xF7,
                                            0x0F, 0x8F, 0x4F, 0xCF, 0x2F, 0xAF, 0x6F, 0xEF, 0x1F, 0x9F, 0x5F, 0xDF, 0x3F, 0xBF, 0x7F, 0xFF};

class TroykaLedMatrix
{
public:
    TroykaLedMatrix();
    TroykaLedMatrix(const uint8_t addr);
    void begin();
    void begin(TwoWire& wire);
    void enableDisplay();
    void disableDisplay();
    void enableAudioInput();
    void disableAudioInput();
    void enableEqualizer();
    void disableEqualizer();
    void setAudioGain(const uint8_t value);
    void setCurrentLimit(const uint8_t value);
    void setMatrixSize(const uint8_t value);
    void clear();
    void setFont(const uint8_t* font, const uint8_t countChars = 1, const uint8_t countRaws = 8);
    void clearPixel(const uint8_t x, const uint8_t y);
    void drawPixel(const uint8_t x, const uint8_t y);
    void drawSymbol(const uint8_t c);
    void drawBitmap(const uint8_t* data, const bool reverse = true, const uint8_t countRaws = 8);
    void marquee(const uint8_t data[][8], const int len, const int sh, const bool reverse = true);
    void drawBitmapF(const uint8_t* data, const uint8_t countRaws = 8);
    byte map(long input, long in_min, long in_max);
    void marqueeText(char text[], uint8_t len, uint16_t sh);
    void setRotation(const uint8_t value);

private:
    void _init();
    void _updateDisplay();
    uint8_t _getRow(const uint8_t y);
    uint8_t _readReg(const uint8_t addr);
    void _writeReg(const uint8_t addr, const uint8_t data);
    uint8_t _makeConfigReg();
    uint8_t _makeEffectReg();
    uint8_t _addr;
    bool _shutDown;
    bool _audioInput;
    uint8_t _matrixSize;
    uint8_t _width;
    uint8_t _height;
    uint8_t _audioInputGain;
    uint8_t _currentLimit;
    bool _audioEqualizer;
    const uint8_t* _font;
    uint8_t _fontSize;
    uint8_t _fontHeight;
    uint8_t _data[MATRIX_MAX_ROWS];
    TwoWire* _wire;
    uint8_t _rotation;
};

#endif //TROYKA_LED_MATRIX
