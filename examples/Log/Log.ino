#include <ArduinoLog.h>

/*!
* This example sketch shows most of the features of the ArduinoLog library
*
*/


int          intValue1  , intValue2;
long         longValue1, longValue2;
bool         boolValue1, boolValue2;
const char * charArray    = "this is a string";
String       stringValue1 = "this is a string";

void setup() {
    // Set up serial port and wait until connected
    Serial.begin(9600);
    while(!Serial && !Serial.available()){}
    randomSeed(analogRead(0));
    // Pass log level, whether to show log level, and print interface. 
    // Available levels are: 
    // LOG_LEVEL_SILENT, LOG_LEVEL_FATAL, LOG_LEVEL_ERROR, LOG_LEVEL_WARNING, LOG_LEVEL_NOTICE, LOG_LEVEL_VERBOSE
    // Note: if you want to fully remove all logging code, uncomment #define DISABLE_LOGGING in Logging.h
    //       this will significantly reduce your project size
    
    Log.begin(LOG_LEVEL_VERBOSE, &Serial);
    
    //Start logging

    Log.notice(F(CR "******************************************" CR));                     // Info string with Newline
    Log.notice(  "***          Logging example                " CR);                       // Info string in flash memory
    Log.notice(F("******************* ")); Log.notice("*********************** " CR);      // two info strings without newline
}

void loop() {

    // set up some random variables
    intValue1  = random(100);
    intValue2  = random(10000);
    longValue1 = random(1000000);
    longValue2 = random(100000000);
    boolValue1 = random(2)==0;
    boolValue2 = random(2)==1;
    
    Log.notice   (  "Log as Info with integer values : %d, %d" CR                  , intValue1,  intValue2);
    Log.notice   (F("Log as Info with hex values     : %x, %X" CR                 ), intValue1,  intValue1);
    Log.notice   (  "Log as Info with hex values     : %x, %X" CR                  , intValue2,  intValue2);
    Log.notice   (F("Log as Info with binary values  : %b, %B" CR                 ), intValue1,  intValue1);
    Log.notice   (  "Log as Info with binary values  : %b, %B" CR                  , intValue2,  intValue2);
    Log.notice   (F("Log as Info with long values    : %l, %l" CR                 ), longValue1, longValue2);
    Log.notice   (  "Log as Info with bool values    : %t, %T" CR                  , boolValue1, boolValue2);
    Log.notice   (F("Log as Info with string value   : %s" CR                     ), charArray);
    Log.notice   (  "Log as Info with string value   : %s" CR                      , stringValue1.c_str());
    Log.notice   (F("Log as Debug with mixed values  : %d, %d, %l, %l, %t, %T" CR ), intValue1 , intValue2,
                longValue1, longValue2, boolValue1, boolValue2);
    Log.trace    (  "Log as Trace with bool value    : %T" CR                      , boolValue1);
    Log.warning  (  "Log as Warning with bool value  : %T" CR                      , boolValue1);
    Log.error    (  "Log as Error with bool value    : %T" CR                      , boolValue1);
    Log.fatal    (  "Log as Fatal with bool value    : %T" CR                      , boolValue1);
    Log.verbose  (F("Log as Vebose with bool value   : %T" CR CR CR               ), boolValue2);
    delay(5000);
}