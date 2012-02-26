#include <Logging.h>

/*!
* This example show some examples to use the logging library
*
* Have fun
* mrRobot@web.de
*/

// we need a logger object

#define LOGLEVEL LOG_LEVEL_DEBUG

Logging logger = Logging(LOGLEVEL, 38400L);

int myInt1, myInt2;
long myLong1, myLong2;
bool myBool1, myBool2;
char* myString = "this is a string";

void setup() {
    logger.Init();
    logger.Info(CR"******************************************"CR);
    logger.Info("My favorite output stuff in future :-)"CR);
    logger.Info("******************************************"CR);
	myInt1 = 232;
	myInt2 = 32199;
	myLong1 = 99403020;
	myLong2 = 45021;
	myBool1 = true;
	myBool2 = !myBool1;
}

void loop() {
	logger.Info("Display my integers myInt1 %d, myInt2 %d"CR,myInt1, myInt2);
	logger.Info("Display as hex myInt1=%x, myInt1=%X"CR,myInt1, myInt1);
	logger.Info("Display as hex myInt2=%x, myInt2=%X"CR,myInt2, myInt2);
	logger.Info("Display as binary myInt1=%b, myInt1=%B"CR,myInt1, myInt1);
	logger.Info("Display as binary myInt2=%b, myInt2=%B"CR,myInt2, myInt2);
	logger.Info("Display my longs myLong1 %l, myLong2=%l"CR,myLong1, myLong2);
	logger.Info("Display my bool myBool1=%t, myBool2=%T"CR,myBool1, myBool2);
	logger.Info("Output: %s"CR, myString);
	logger.Error("is this an real error? %T"CR,myBool2);
	logger.Debug("%d, %d, %l, %l, %t, %T"CR,myInt1,myInt2,
											myLong1,myLong2,
											myBool1,myBool2);
	logger.Info(CR"have fun with this logger"CR);
	delay(5000);
}
