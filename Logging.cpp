#include "Logging.h"

void Logging::Init(int level, long baud){
    _level = constrain(level,LOG_LEVEL_NOOUTPUT,LOG_LEVEL_VERBOSE);
    _baud = baud;
    _printer = &Serial;
    Serial.begin(_baud);
}

void Logging::Init(int level, Print* printer){
    _level = constrain(level,LOG_LEVEL_NOOUTPUT,LOG_LEVEL_VERBOSE);
    _printer = printer;
}

void Logging::Error(const char* msg, ...){
    if (LOG_LEVEL_ERRORS <= _level) {   
        _printer->print("ERROR: ");
        va_list args;
        va_start(args, msg);
        print(msg,args);
    }
}


void Logging::Info(const char* msg, ...){
    if (LOG_LEVEL_INFOS <= _level) {
        va_list args;
        va_start(args, msg);
        print(msg,args);
    }
}

void Logging::Debug(const char* msg, ...){
    if (LOG_LEVEL_DEBUG <= _level) {
        va_list args;
        va_start(args, msg);
        print(msg,args);
    }
}


void Logging::Verbose(const char* msg, ...){
    if (LOG_LEVEL_VERBOSE <= _level) {
        va_list args;
        va_start(args, msg);
        print(msg,args);
    }
}



void Logging::print(const char *format, va_list args) {
    //
    // loop through format string
    for (; *format != 0; ++format) {
        if (*format == '%') {
            ++format;
            if (*format == '\0') break;
            if (*format == '%') {
                _printer->print(*format);
                continue;
            }
            if( *format == 's' ) {
				register char *s = (char *)va_arg( args, int );
				_printer->print(s);
				continue;
			}
            if( *format == 'd' || *format == 'i') {
				_printer->print(va_arg( args, int ),DEC);
				continue;
			}
            if( *format == 'x' ) {
				_printer->print(va_arg( args, int ),HEX);
				continue;
			}
            if( *format == 'X' ) {
				_printer->print("0x");
				_printer->print(va_arg( args, int ),HEX);
				continue;
			}
            if( *format == 'b' ) {
				_printer->print(va_arg( args, int ),BIN);
				continue;
			}
            if( *format == 'B' ) {
				_printer->print("0b");
				_printer->print(va_arg( args, int ),BIN);
				continue;
			}
            if( *format == 'l' ) {
				_printer->print(va_arg( args, long ),DEC);
				continue;
			}

            if( *format == 'c' ) {
				_printer->print(va_arg( args, int ));
				continue;
			}
            if( *format == 't' ) {
				if (va_arg( args, int ) == 1) {
					_printer->print("T");
				}
				else {
					_printer->print("F");
				}
				continue;
			}
            if( *format == 'T' ) {
				if (va_arg( args, int ) == 1) {
					_printer->print("true");
				}
				else {
					_printer->print("false");
				}
				continue;
			}
        }
        else if (*format == '\n') {
            _printer->print('\r');
        }
        _printer->print(*format);
    }
}
 
Logging Log = Logging();

 
 
  




