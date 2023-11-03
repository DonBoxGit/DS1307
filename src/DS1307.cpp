/*
  This is a light library for work with RTC 1307.
                 ver. 1.0.0
                            by Roman Yakubovskiy.
*/

#include "DS1307.h"

const char* monthList[] = {
  "Jan", "Feb", "Mar", "Apr", "May", "Jun",
  "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"   
};

DS1307::DS1307(uint8_t addr) : _addr(addr) {}

bool DS1307::begin() {
	Wire.begin();
	Wire.beginTransmission(_addr);
	return (!Wire.endTransmission());
}

void DS1307::start() {
	uint8_t val = readRegister(_addr, 0x00);
  val &= ~(1 << CH_BIT);
  writeRegister(_addr, 0x00, val);
}

void DS1307::stop() {
  uint8_t val = readRegister(_addr, 0x00);
  val |= (1 << CH_BIT);
  writeRegister(_addr, 0x00, val);
}

uint8_t DS1307::readRegister(uint8_t addr, uint8_t reg) {
  Wire.beginTransmission(addr);
  Wire.write(reg);
  if (Wire.endTransmission() != 0) return 0;
  Wire.requestFrom(addr, 1U);
	while (!Wire.available()) {}
  return Wire.read();
  Wire.endTransmission();
}

void DS1307::writeRegister(uint8_t addr, uint8_t reg, uint8_t val) {
  Wire.beginTransmission(addr);
  Wire.write(reg);
  Wire.write(val);
  Wire.endTransmission();
}

DateTime DS1307::get() {
  DateTime dateTime;
  Wire.beginTransmission(_addr);
  Wire.write(0x00);
  if (Wire.endTransmission() != 0) return dateTime;

  Wire.requestFrom(_addr, 7U);
  dateTime.second = bcd2bin(Wire.read() & 0x7F);
  dateTime.minute = bcd2bin(Wire.read());
  dateTime.hour = bcd2bin(Wire.read());
  dateTime.dayOfWeek = bcd2bin(Wire.read());
  dateTime.day = bcd2bin(Wire.read());
  dateTime.month = bcd2bin(Wire.read());
  dateTime.year = bcd2bin(Wire.read()) + 2000;
  return dateTime;
}

uint8_t DS1307::getSeconds() {
  return bcd2bin(readRegister(_addr, 0x00) & 0x7F);
}

uint8_t DS1307::getMinutes() {
  return bcd2bin(readRegister(_addr, 0x01) & 0x7F);
}

uint8_t DS1307::getHours() {
  return bcd2bin(readRegister(_addr, 0x02) & 0x3F);
}

uint8_t DS1307::getDayOfWeek() {
  return bcd2bin(readRegister(_addr, 0x03) & 0x07);
}

uint8_t DS1307::getDay() {
  return bcd2bin(readRegister(_addr, 0x04) & 0x3F);
}

uint8_t DS1307::getMonth() {
  return bcd2bin(readRegister(_addr, 0x05) & 0x1F);
}

uint16_t DS1307::getYear() {
  return bcd2bin(readRegister(_addr, 0x06)) + 2000U;
}

void DS1307::set(uint8_t sec, uint8_t min, uint8_t hour,
                 uint8_t day, uint8_t month, uint16_t year) {
  uint8_t dayOfWeek = compDayWeek(day, month, year);
  if (year >= 2000) year -= 2000;

  /* Get CH_BIT */
  Wire.beginTransmission(_addr);
  Wire.write(0x00);
  Wire.endTransmission();
  Wire.requestFrom(_addr, 1U);
  /* Check CH_BIT */
  uint8_t ch = (Wire.read() & 0x80) ? 0x80 : 0x00;

  Wire.beginTransmission(_addr);
  Wire.write(0x00);
  Wire.write(bin2bcd(sec) | ch);
  Wire.write(bin2bcd(min));
  Wire.write(bin2bcd(hour));
  Wire.write(bin2bcd(dayOfWeek));
  Wire.write(bin2bcd(day));
  Wire.write(bin2bcd(month));
  Wire.write(bin2bcd(year));
  Wire.endTransmission();
}

void DS1307::set(DateTime dateTime) {
  if (dateTime.year >= 2000) dateTime.year -= 2000;

  Wire.beginTransmission(_addr);
  Wire.write(0x00);
  Wire.write(bin2bcd(dateTime.second) | 0x00);
  Wire.write(bin2bcd(dateTime.minute));
  Wire.write(bin2bcd(dateTime.hour));
  Wire.write(bin2bcd(dateTime.dayOfWeek));
  Wire.write(bin2bcd(dateTime.day));
  Wire.write(bin2bcd(dateTime.month));
  Wire.write(bin2bcd(dateTime.year));
  Wire.endTransmission();
}

void DS1307::setCompTime() {
  char compileTime[] = __TIME__;
  char compileDate[] = __DATE__;
  uint8_t sec = charToInt(compileTime, 6);
  uint8_t min = charToInt(compileTime, 3);
  uint8_t hour = charToInt(compileTime, 0);
  uint8_t day = charToInt(compileDate, 4);
  uint8_t month = 0;
  char nameMonth[3] = { compileDate[0], compileDate[1], compileDate[2] };
  for (uint8_t i = 0; i < 12; i++)
    if (!strcmp(nameMonth, monthList[i]))
      month = i + 1;
  uint8_t year = charToInt(compileDate, 9);
  uint8_t dayOfWeek = compDayWeek(day, month, year);

  Wire.beginTransmission(_addr);
  Wire.write(0x00);
  Wire.write(bin2bcd(sec) | 0x00);
  Wire.write(bin2bcd(min));
  Wire.write(bin2bcd(hour));
  Wire.write(bin2bcd(dayOfWeek));
  Wire.write(bin2bcd(day));
  Wire.write(bin2bcd(month));
  Wire.write(bin2bcd(year));
  Wire.endTransmission();
}

void DS1307::setSeconds(uint8_t sec) {
  writeRegister(_addr, 0x00, (bin2bcd(sec) | 0x00));  
}

void DS1307::setMinutes(uint8_t min) {
  writeRegister(_addr, 0x01, (bin2bcd(min) & 0x7F));
}

void DS1307::setHours(uint8_t hour) {
  writeRegister(_addr, 0x02, (bin2bcd(hour) & 0x3F));  
}

void DS1307::setDay(uint8_t day) {
  writeRegister(_addr, 0x04, (bin2bcd(day) & 0x3F));  
}

void DS1307::setMonth(uint8_t month) {
  writeRegister(_addr, 0x05, (bin2bcd(month) & 0x1F));
}

void DS1307::setYear(uint16_t year) {
  writeRegister(_addr, 0x06, (bin2bcd(year)));
}

bool DS1307::lostPower(void) {
  return (getYear() == 2000 && getMonth() == 1 && getDay() == 1);      
}

uint8_t DS1307::charToInt(char* str, uint8_t index) {
  return((uint8_t)(str[index] - '0') * 10 + (uint8_t)(str[index+1] - '0'));
}

uint8_t DS1307::compDayWeek(uint8_t day, uint8_t month, uint16_t year) {
  uint8_t c;  // Century
  uint16_t y; // The year in a century
  uint8_t m;  // Month according to the ancient Roman calendar

  if (month == 1 || month == 2) year--; // January and February refer to the previous year.
  m = month - 2;                        // Because the ancient Roman calendar starts to March.
  if (m <= 0) m += 12;
  c = year / 100;
  y = year - c * 100;
  uint8_t dayOfWeek = (day + ((13 * m - 1) / 5) + y + (y / 4) + (c / 4) - (2 * c) + 777) % 7;
  return dayOfWeek;
} 

void DS1307::startSQW(const uint8_t mode) {
  uint8_t val = readRegister(_addr, CONTROL_REGISTER);
  val |= (1 << SQWE_BIT);

  switch (mode) {
    case 1:  /* 1 Hz mode */
      val &= ~((1 << RS0_BIT) | (1 << RS1_BIT));
      break;

    case 2:  /* 4.096 kHz mode */
      val |= (1 << RS0_BIT);
      val &= ~(1 << RS1_BIT);
      break;
  
    case 3:  /* 8.192 kHz mode */
      val &= ~(1 << RS0_BIT);
      val |= (1 << RS1_BIT);
      break;
  
    case 4:  /* 32.768 kHz mode */
      val |= (1 << RS0_BIT) | (1 << RS1_BIT);
      break;
  }

  writeRegister(_addr, CONTROL_REGISTER, val);
}

void DS1307::stopSQW() {
  writeRegister(_addr, CONTROL_REGISTER, 0x00);
}

void DS1307::setSQW_OUT(bool state) {
  uint8_t val = 0x00;
  if (state) val |= (1 << OUT_BIT);
  writeRegister(_addr, CONTROL_REGISTER, val);
}

uint8_t DS1307::bin2bcd(uint8_t data) { return (((data / 10) << 4) | (data % 10)); }
uint8_t DS1307::bcd2bin(uint8_t data) { return ((data >> 4) * 10 + (data & 0xF)); }
