/*
  This is a light library to work with RTC 1307.
  ver. 1.0.0
  Roman Yakubovskiy
*/

#ifndef _DS_1307_H_
#define _DS_1307_H_

#include <Wire.h>

#define RTC_I2_ADDR 0x68

#define CH_BIT            7    // Clock Halt: 1 - clock stop, 0 - clock works
#define AM_PM_SET_BIT     6    // 1 - 12 hours mode(5 bit - AM=0/PM=1), 0(default) - 24 hours mode(5 bit = 2 tenth hours)
#define CONTROL_REGISTER  0x7
#define OUT_BIT           7
#define SQWE_BIT          4    // Squawe Wawe Enable, 1 - On
#define RS0_BIT           0    // Rate Select 00 - 1kHz, 01 - 4.096kHz
#define RS1_BIT           1    // 10 - 8.192kHz, 11 - 32.768kHz

struct DateTime {
    uint8_t second; 
    uint8_t minute;
    uint8_t hour;
    uint8_t dayOfWeek;
    uint8_t day;
    uint8_t month;
    uint16_t year;
};

extern const char* monthList[];

class DS1307 {
  public:
    /// @brief Constructor
    /// @param addr address of RTC device 0x68(by default).
    DS1307(uint8_t addr = RTC_I2_ADDR);

    /// @brief Initialization RTC.
    /// @return true - RTC is found.
    /// @return false - RTC is not found.
    bool begin(void);

    /// @brief Starting the RTC.
    /// @details  Sets the Clock Halt Bit to 0. 
    void start(void);

    /// @brief Stopping the RTC.
    /// @details Sets the Clock Halt Bit to 1.
    void stop(void);

    /// @brief Getting time and date in to the structure.
    /// @return DateTime structure.
    DateTime get(void);

    /* Get seconds */
    uint8_t getSeconds(void);

    /* Get minutes */
    uint8_t getMinutes(void);

    /* Get hours */
    uint8_t getHours(void);

    /* Get day of the week */
    uint8_t getDayOfWeek(void);

    /* Get day of month */   
    uint8_t getDay(void);

    /* Get month */
    uint8_t getMonth(void);

    /* Get year in 4-digit format */
    uint16_t getYear(void);

    /// @brief Settting current time and date where day is the day of the month.
    void set(uint8_t sec, uint8_t min, uint8_t hour, 
             uint8_t day, uint8_t month, uint16_t year);

    /* Set time and data from structure DateTime */
    void set(DateTime dateTime);

    /* Set the compilation time */
    void setCompTime(void);

    /* Set seconds */
    void setSeconds(uint8_t sec);

    /* Set minutes */
    void setMinutes(uint8_t min);

    /* Set hours */
    void setHours(uint8_t hour);

    /* Set day of month */
    void setDay(uint8_t day);

    /* Set month */
    void setMonth(uint8_t month);

    /* Set year in 2-digit formant or 4-digit */
    void setYear(uint16_t year);

    /* Checking for time reset */
    bool lostPower(void);

  private:
    uint8_t compDayWeek(uint8_t day, uint8_t month, uint16_t year);
    uint8_t readRegister(uint8_t addr, uint8_t reg);
    void writeRegister(uint8_t addr, uint8_t reg, uint8_t val);
    uint8_t charToInt(char* str, uint8_t index);
    uint8_t bin2bcd(uint8_t data);
    uint8_t bcd2bin(uint8_t data);
    const uint8_t _addr;
};

#endif /* _DS_1307_H_ */
