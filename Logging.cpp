#include "Logging.h"

void Logging::init(int level, long baud){
    _level = constrain(level,LOG_LEVEL_NOOUTPUT,LOG_LEVEL_VERBOSE);
    _baud = baud;
    Serial.begin(_baud);
	info("Start logging");
}

void Logging::error(char* msg, ...){
    if (LOG_LEVEL_ERRORS <= _level) {
		Serial.print("E: ");
        va_list args;
        va_start(args, msg);
        print(msg, args);
    }
}


void Logging::info(char* msg, ...){
    if (LOG_LEVEL_INFOS <= _level) {
		Serial.print("I:  ");
        va_list args;
        va_start(args, msg);
        print(msg,args);
    }
}

void Logging::debug(char* msg, ...){
    if (LOG_LEVEL_DEBUG <= _level) {
		Serial.print("D:   ");
        va_list args;
        va_start(args, msg);
        print(msg,args);
    }
}


void Logging::verbose(char* msg, ...){
    if (LOG_LEVEL_VERBOSE <= _level) {
		Serial.print("V:    ");
        va_list args;
        va_start(args, msg);
        print(msg,args);
    }
}

 void Logging::print(const char *format, va_list args) {
    // loop through format string
    for (; *format != 0; ++format) {
        if (*format == '%') {
            ++format;
            if (*format == '\0') break;
            if (*format == '%') {
                Serial.print(*format);
                continue;
            }
            if( *format == 's' ) {
				register char *s = (char *)va_arg( args, int );
				Serial.print(s);
				continue;
			}
            if( *format == 'd' || *format == 'i') {
				Serial.print(va_arg( args, int ),DEC);
				continue;
			}
            if( *format == 'x' ) {
				Serial.print(va_arg( args, int ),HEX);
				continue;
			}
            if( *format == 'X' ) {
				Serial.print("0x");
				Serial.print(va_arg( args, int ),HEX);
				continue;
			}
            if( *format == 'b' ) {
				Serial.print(va_arg( args, int ),BIN);
				continue;
			}
            if( *format == 'B' ) {
				Serial.print("0b");
				Serial.print(va_arg( args, int ),BIN);
				continue;
			}
            if( *format == 'l' ) {
				Serial.print(va_arg( args, long ),DEC);
				continue;
			}

            if( *format == 'c' ) {
				Serial.print(va_arg( args, int ));
				continue;
			}
            if( *format == 't' ) {
				if (va_arg( args, int ) == 1) {
					Serial.print("T");
				}
				else {
					Serial.print("F");				
				}
				continue;
			}
            if( *format == 'T' ) {
				if (va_arg( args, int ) == 1) {
					Serial.print("true");
				}
				else {
					Serial.print("false");				
				}
				continue;
			}

        }
        Serial.print(*format);
    }
    Serial.println();
 }
 
 Logging Log = Logging();

 
 
  




