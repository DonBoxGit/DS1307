<h2 align='center'>This is a light library for work with RTC 1307</h2>

##### First of all need to create an object:
```c
DS1307 clock;
```
##### The device address is 0x68 by default, but you can set it explicity as parameter.
```c
DS1307 clock(0x68);
```
##### For initialize and start the clock use:
```c
clock.begin();
clock.start();
```
##### Stop the clock:
```c
clock.stop();
```
##### Methods to get data from RTC:
```c
clock.getDayOfWeek();
clock.getHours();
clock.getMinutes();
clock.getSeconds();
clock.getDay();
clock.getMonth();
clock.getYear();
```
##### To get time and date data into the structur (for example):
```c
DateTime dateTime = clock.get();
char strTime[8];
sprintf(strTime, "%d:%d:%d", dateTime.hour, dateTime.minute, dateTime.second);
Serial.println(strTime);
```
##### To set time and date of compilation:
```c
clock.setCompTime();
```
##### To set custom time and date use this methods:
```c
clock.set(sec, min, hour, day, month, year);
clock.setSeconds(seconds);
clock.setMinutes(minutes);
clock.setHours(hours);
clock.setDay(dayOfMonth);
clock.setMonth(month);
clock.setYear(year);
```
##### There are also methods for controlling the generation of square waves:
```c
clock.startSQW(mode);
```
###### Where mode is:<br>`SQW_MODE_1_GH` - 1Gh (by default)<br>`SQW_MODE_4_096_KGH` - 4.096kGh<br>`SQW_MODE_8_192_KGH` - 8.192kGh<br>`SQW_MODE_32_768_KGH` - 32.768kGh<br>accordingly.
##### To stop generation of meandr:
```c
clock.stopSQW();
```
To set level of SQWE/OUT when the generation is off:
```c
clock.setSQW_OUT(level);
```
##### Where `true` is HIGH and `false` is LOW level.
