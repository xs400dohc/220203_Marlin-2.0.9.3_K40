typedef unsigned short uint16_t;        //0 bis 65.535 (16bit/2Byte)
typedef short int16_t;                  //–32.768 bis 32.767 (16bit/2Byte)
typedef float celsius_float_t;          //3.4E +/- 38 (7 Stellen) (32bit/4Byte)
typedef int16_t celsius_t;              //–32.768 bis 32.767 (16bit/2Byte)
typedef unsigned char uint8_t;          //0-255 (8bit/1Byte)
// A temperature sensor
typedef struct TempInfo {               //Struktur TempInfo{unsigned short acc; short raw; float celsius}
  uint16_t acc;                         
  int16_t raw;
  celsius_float_t celsius;
  inline void reset() { acc = 0; }
  inline void sample(const uint16_t s) { acc += s; }
  inline void update() { raw = acc; }
} temp_info_t;
// A PWM heater with temperature sensor
typedef struct HeaterInfo : public TempInfo {
  celsius_t target;
  uint8_t soft_pwm_amount;
} heater_info_t;