#ifndef LOGGING_H
#define LOGGING_H
#include <inttypes.h>
#include <stdarg.h>
#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif
//#include "pins_arduino.h"
extern "C" {
  #include <avr/io.h>
}


#define LOG_LEVEL_NOOUTPUT 0 
#define LOG_LEVEL_ERRORS 1
#define LOG_LEVEL_INFOS 2
#define LOG_LEVEL_DEBUG 3
#define LOG_LEVEL_VERBOSE 4

// default loglevel if nothing is set from user
#define LOGLEVEL LOG_LEVEL_DEBUG 


#define CR "\r\n"
#define LOGGING_VERSION 1

/*!
* Logging is a helper class to output informations over
* RS232. If you know log4j or log4net, this logging class
* is more or less similar ;-) <br>
* Different loglevels can be used to extend or reduce output
* All methods are able to handle any number of output parameters.
* All methods print out a formated string (like printf).<br>
* To reduce output and program size, reduce loglevel.
* <br>
* Output format string can contain below wildcards. Every wildcard
* must be start with percent sign (\%)
*
* <b>Depending on loglevel, source code is excluded from compile !</b><br>
* <br>
* <b>Wildcards</b><br>
* <ul>
* <li><b>\%s</b>	replace with an string (char*)</li>
* <li><b>\%c</b>	replace with an character</li>
* <li><b>\%d</b>	replace with an integer value</li>
* <li><b>\%l</b>	replace with an long value</li>
* <li><b>\%x</b>	replace and convert integer value into hex</li>
* <li><b>\%X</b>	like %x but combine with <b>0x</b>123AB</li>
* <li><b>\%b</b>	replace and convert integer value into binary</li>
* <li><b>\%B</b>	like %x but combine with <b>0b</b>10100011</li>
* <li><b>\%t</b>	replace and convert boolean value into <b>"t"</b> or <b>"f"</b></li>
* <li><b>\%T</b>	like %t but convert into <b>"true"</b> or <b>"false"</b></li>
* </ul><br>
* <b>Loglevels</b><br>
* <table border="0">
* <tr><td>0</td><td>LOG_LEVEL_NOOUTPUT</td><td>no output </td></tr>
* <tr><td>1</td><td>LOG_LEVEL_ERRORS</td><td>only errors </td></tr>
* <tr><td>2</td><td>LOG_LEVEL_INFOS</td><td>errors and info </td></tr>
* <tr><td>3</td><td>LOG_LEVEL_DEBUG</td><td>errors, info and debug </td></tr>
* <tr><td>4</td><td>LOG_LEVEL_VERBOSE</td><td>all </td></tr>
* </table>
* <br>
* <h1>History</h1><br>
* <table border="0">
* <tr><td>01 FEB 2012</td><td>initial release</td></tr>
* <tr><td>06 MAR 2012</td><td>implement a preinstanciate object (like in Wire, ...)</td></tr>
* <tr><td></td><td>methode init get now loglevel and baud parameter</td></tr>
*/
class Logging {
private:
    int _level;
    long _baud;
public:
    /*! 
	 * default Constructor
	 */
    Logging(){} ;
	
    /** 
	* Initializing, must be called as first.
	* \param void
	* \return void
	*
	*/
	void Init(int level, long baud);
	
    /**
	* Output an error message. Output message contains
	* ERROR: followed by original msg
	* Error messages are printed out, at every loglevel
	* except 0 ;-)
	* \param msg format string to output
	* \param ... any number of variables
	* \return void
	*/

  template <class T> void Error(T msg, ...){
    if (LOG_LEVEL_ERRORS <= _level) {
      print (F("ERROR: "),0);
      va_list args;
      va_start(args, msg);
      print(msg,args);
    }
  }


    /**
	* Output an info message. Output message contains
	* Info messages are printed out at l
	* loglevels >= LOG_LEVEL_INFOS
	*
	* \param msg format string to output
	* \param ... any number of variables
	* \return void
	*/

  template <class T> void Info(T msg, ...){
    if (LOG_LEVEL_INFOS <= _level) {
      va_list args;
      va_start(args, msg);
      print(msg,args);
    }
  }

    /**
	* Output an debug message. Output message contains
	* Debug messages are printed out at l
	* loglevels >= LOG_LEVEL_DEBUG
	*
	* \param msg format string to output
	* \param ... any number of variables
	* \return void
	*/


  template <class T> void Debug(T msg, ...){
    if (LOG_LEVEL_DEBUG <= _level) {
      va_list args;
      va_start(args, msg);
      print(msg,args);
    }
  }


    /**
	* Output an verbose message. Output message contains
	* Debug messages are printed out at l
	* loglevels >= LOG_LEVEL_VERBOSE
	*
	* \param msg format string to output
	* \param ... any number of variables
	* \return void
	*/

  template <class T> void Verbose(T msg, ...){
    if (LOG_LEVEL_VERBOSE <= _level) {
      va_list args;
      va_start(args, msg);
      print(msg,args);
    }
  }


private:
    void print(const char *format, va_list args);
    void print(const __FlashStringHelper *format, va_list args);
    void printFormat(const char format, va_list *args);
};

extern Logging Log;
#endif




