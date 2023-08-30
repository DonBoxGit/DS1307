<h2 align='center'>This is a light library for work with RTC 1307</h2>

##### First of all need to create an object:
```c
DS1307 clock;
```
##### The device address is 0x68 by default, but you can set it explicity in parentheses.
##### For initialize and start the clock use:
```c
clock.begin();
clock.start();
```
##### To get data from RTC:
```c
Serial.print(clock.getDayOfWeek());
Serial.print(" ");
Serial.print(clock.getHours());
Serial.print(":");
Serial.print(clock.getMinutes());
Serial.print(":");
Serial.print(clock.getSeconds());
Serial.print("   ");
Serial.print(clock.getDay());
Serial.print(".");
Serial.print(clock.getMonth());
Serial.print(".");
Serial.println(clock.getYear());
```
##### To get time and date data into the structur:
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
##### To set custom time and data use:
```c
clock.setSeconds(seconds);
clock.setMinutes(minutes);
clock.setHours(hours);
```
##### and etc.
