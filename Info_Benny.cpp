typedef unsigned short uint16_t;        //0 bis 65.535 (16bit/2Byte) hoverinfotext
typedef unsigned long uint32_t;         //0 bis 4.294.967.295 (32bit/4Byte)
typedef short int16_t;                  //–32.768 bis 32.767 (16bit/2Byte) hoverinfotext
typedef float celsius_float_t;          //3.4E +/- 38 (7 Stellen) (32bit/4Byte) types.h
typedef int16_t celsius_t;              //–32.768 bis 32.767 (16bit/2Byte) types.h
typedef unsigned char uint8_t;          //0-255 (8bit/1Byte) hoverinfotext
typedef heater_info_t cooler_info_t;    //cooler_info_t hat struktur von heater_info_t (acc, ra, celsius, target, soft_pwm_amount)
typedef uint32_t millis_t;              //millis_t ist 32bit
// temperature.h
  // A temperature sensor
  typedef struct TempInfo {               //Struktur TempInfo{unsigned short acc; short raw; float celsius}
    uint16_t acc;                         
    int16_t raw;
    celsius_float_t celsius;
    inline void reset() { acc = 0; }
    inline void sample(const uint16_t s) { acc += s; }    //Werte einlesen in temperatur.cpp line 3333:
    /*
    #define ACCUMULATE_ADC(obj) do{ \
    if (!HAL_ADC_READY()) next_sensor_state = adc_sensor_state; \
    else obj.sample(HAL_READ_ADC()); \
    }while(0)
    */
    inline void update() { raw = acc; }
  } temp_info_t;                        // Struktur: (acc, ra, celsius)
  // A PWM heater with temperature sensor
  typedef struct HeaterInfo : public TempInfo {
    celsius_t target;
    uint8_t soft_pwm_amount;
  } heater_info_t;                      // Struktur: TempInfo(acc, ra, celsius)+(target, soft_pwm_amount)

  class Temperature {
    //member
    public:
      static cooler_info_t temp_cooler;   //member mit struktur von cooler_info_t (acc, ra, celsius, target, soft_pwm_amount)
    private:
      static cooler_watch_t watch_cooler; //aktualisierungsrate 
      static millis_t next_cooler_check_ms, cooler_fan_flush_ms;
      static int16_t mintemp_raw_COOLER, maxtemp_raw_COOLER;
    //Funktionen
    public:
      void init();
      static void zero_fan_speeds();
      static void isr();
      static void readings_ready();
      static void manage_heater();
      static celsius_float_t degCooler()   { return temp_cooler.celsius; }
      static celsius_t wholeDegCooler()    { return static_cast<celsius_t>(temp_cooler.celsius + 0.5f); }
      static celsius_t degTargetCooler() { return temp_cooler.target; }
      static bool isLaserHeating()       { return temp_cooler.target > temp_cooler.celsius; }
      static bool isLaserCooling()       { return temp_cooler.target < temp_cooler.celsius; }
      static bool wait_for_cooler(const bool no_wait_for_cooling=true);
      static void cooldown() {
       zero_fan_speeds();  
      }
    private:
      static volatile bool raw_temps_ready;
      static void update_raw_temperatures();
      static void updateTemperaturesFromRawValues();
      static bool updateTemperaturesIfReady() {
        if (!raw_temps_ready) return false;
        updateTemperaturesFromRawValues();
        raw_temps_ready = false;
        return true;
      }
  };
  extern Temperature thermalManager;

#if ENABLED(COOLER_FAN)
            #if ENABLED(COOLER2)
              int16_t fan_cooler_pwm;
              if (temp_cooler2.celsius - COOLER_FAN_DIFF > temp_cooler.celsius){
                fan_cooler_pwm = (COOLER_FAN_BASE) + (COOLER_FAN_FACTOR) * ABS((temp_cooler2.celsius - COOLER_FAN_DIFF) - temp_cooler.celsius);
              }
              else{
                fan_cooler_pwm = 0;
              }
              NOMORE(fan_cooler_pwm, 255);
              set_fan_speed(COOLER_FAN_INDEX, fan_cooler_pwm); // Set cooler fan pwm
              cooler_fan_flush_ms = ms + 5000;
            #else
              set_fan_speed(COOLER_FAN_INDEX, temp_cooler.celsius > temp_cooler.target - 2 ? COOLER_FAN_BASE : 0);
            #endif
          #endif