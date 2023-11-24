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
##### To get time and date data into the structure(dataTime) for example:
```c
DateTime dateTime = clock.getTime();
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
clock.setTime(sec, min, hour, day, month, year);
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
###### Where mode is:<br>`SQW_MODE_1_GH` - 1 Gh (by default)<br>`SQW_MODE_4096_GH` - 4.096 kGh<br>`SQW_MODE_8192_GH` - 8.192 kGh<br>`SQW_MODE_32768_GH` - 32.768 kGh<br>accordingly.
##### To stop generation of meandr:
```c
clock.stopSQW();
```
##### To set level of SQWE/OUT when the generation is off:
```c
clock.setSQW_OUT(level);
```
###### Where `true` is HIGH and `false` is LOW level.
