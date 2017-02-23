/*
    _   ___ ___  _   _ ___ _  _  ___  _    ___   ___ 
   /_\ | _ \   \| | | |_ _| \| |/ _ \| |  / _ \ / __|
  / _ \|   / |) | |_| || || .` | (_) | |_| (_) | (_ |
 /_/ \_\_|_\___/ \___/|___|_|\_|\___/|____\___/ \___|
                                                     
  Log library for Arduino
  version 1.0.0
  https://github.com/thijse/Arduino-Log

Licensed under the MIT License <http://opensource.org/licenses/MIT>.

*/

#ifndef LOGGING_H
#define LOGGING_H
#include <inttypes.h>
#include <stdarg.h>
#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

//#include <stdint.h>
//#include <stddef.h>
// *************************************************************************
//  Uncomment line below to fully disable logging, and reduce project size
// ************************************************************************
//#define DISABLE_LOGGING


#define LOG_LEVEL_SILENT  0 
#define LOG_LEVEL_FATAL   1
#define LOG_LEVEL_ERROR   2
#define LOG_LEVEL_WARNING 3
#define LOG_LEVEL_NOTICE  4
#define LOG_LEVEL_TRACE   5
#define LOG_LEVEL_VERBOSE 6

#define CR "\n"
#define LOGGING_VERSION 1_0_0

/*!
 Logging is a helper class to output informations over
 RS232. If you know log4j or log4net, this logging class
 is more or less similar ;-) <br>
 Different loglevels can be used to extend or reduce output
 All methods are able to handle any number of output parameters.
 All methods print out a formated string (like printf).<br>
 To reduce output and program size, reduce loglevel.
 
 Output format string can contain below wildcards. Every wildcard
 must be start with percent sign (\%)
 
**** Wildcards
 
* %s	replace with an string (char*)
* %c	replace with an character
* %d	replace with an integer value
* %l	replace with an long value
* %x	replace and convert integer value into hex
* %X	like %x but combine with 0x123AB
* %b	replace and convert integer value into binary
* %B	like %x but combine with 0b10100011
* %t	replace and convert boolean value into "t" or "f"
* %T	like %t but convert into "true" or "false"

**** Loglevels

* 0 - LOG_LEVEL_SILENT     no output 
* 1 - LOG_LEVEL_FATAL      fatal errors 
* 2 - LOG_LEVEL_ERROR      all errors  
* 3 - LOG_LEVEL_WARNING    errors, and warnings 
* 4 - LOG_LEVEL_NOTICE     errors, warnings and notices 
* 5 - LOG_LEVEL_TRACE      errors, warnings, notices, traces
* 6 - LOG_LEVEL_VERBOSE    all 
*/

class Logging {
private:
    int _level;
	bool _showLevel;
    Print* _logOutput;
public:
    /*! 
	 * default Constructor
	 */
    Logging()
      : _level(LOG_LEVEL_SILENT),
	    _showLevel(true),
        _logOutput(NULL) {}
	

    /**
    * Initializing, must be called as first. Note that if you use
    * this variant of Init, you need to initialize the baud rate
    * yourself, if printer happens to be a serial port.
    * \param level - logging levels <= this will be logged.
    * \param printer - place that logging output will be sent to.
    * \return void
    *
    */
    void begin(int level, Print *output, bool showLevel = true);

	    /**
	* Output an error message. Output message contains
	* ERROR: followed by original msg
	* Error messages are printed out, at every loglevel
	* except 0 ;-)
	* \param msg format string to output
	* \param ... any number of variables
	* \return void
	*/
  template <class T> void fatal(T msg, ...){
#ifndef DISABLE_LOGGING	  
    if (LOG_LEVEL_FATAL <= _level) {
      if (_showLevel) _logOutput->print("F: ");
      va_list args;
      va_start(args, msg);
      print(msg,args);
    }
#endif	
  }
	
    /**
	* Output an error message. Output message contains
	* ERROR: followed by original msg
	* Error messages are printed out, at every loglevel
	* except 0 ;-)
	* \param msg format string to output
	* \param ... any number of variables
	* \return void
	*/
  template <class T> void error(T msg, ...){
#ifndef DISABLE_LOGGING	  
    if (LOG_LEVEL_ERROR <= _level) {
      if (_showLevel) _logOutput->print("E: ");
      va_list args;
      va_start(args, msg);
      print(msg,args);
    }
#endif	
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

  template <class T> void warning(T msg, ...){
#ifndef DISABLE_LOGGING	  
    if (LOG_LEVEL_WARNING <= _level) {
      if (_showLevel) _logOutput->print("W: ");
      va_list args;
      va_start(args, msg);
      print(msg,args);
    }
#endif		
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

  template <class T> void notice(T msg, ...){
#ifndef DISABLE_LOGGING	  
    if (LOG_LEVEL_NOTICE <= _level) {
	  if (_showLevel) _logOutput->print("N: ");
      va_list args;
      va_start(args, msg);
      print(msg,args);
    }
#endif		
  }
    /**
	* Output a trace message. Output message contains
	* Debug messages are printed out at l
	* loglevels >= LOG_LEVEL_VERBOSE
	*
	* \param msg format string to output
	* \param ... any number of variables
	* \return void
	*/
  template <class T> void trace(T msg, ...){
#ifndef DISABLE_LOGGING	  
    if (LOG_LEVEL_TRACE <= _level) {
	  if (_showLevel) _logOutput->print("T: ");
      va_list args;
      va_start(args, msg);
      print(msg,args);
    }
#endif		
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
  template <class T> void verbose(T msg, ...){
#ifndef DISABLE_LOGGING	  
    if (LOG_LEVEL_VERBOSE <= _level) {
	  if (_showLevel) _logOutput->print("V: ");
      va_list args;
      va_start(args, msg);
      print(msg,args);
    }
#endif		
  }
    
private:
    void print(const char *format, va_list args);
    void print(const __FlashStringHelper *format, va_list args);
    void printFormat(const char format, va_list *args);
};

extern Logging Log;
#endif




