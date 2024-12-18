// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// released under the GPLv3 license to match the rest of the AdaFruit NeoPixel library

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1
#define PIN            6

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      24


// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

#define BAUD_RATE 9600    // (bits/second)          serial buffer baud rate
#define BUFF_SIZE 64      // (bytes)                maximum message size
#define MSG_TIMEOUT 5000  // (milliseconds)         timeout from last character received
#define NUM_CMDS 2

uint8_t buff[BUFF_SIZE];         // message read buffer
unsigned long lastCharTime;      // used to timeout a message that is cut off or too slow

// custom data type that is a pointer to a command function
typedef void (*CmdFunc)(int argc, char* argv[]);

// command structure
typedef struct {
  int commandArgs;          // number of command line arguments including the command string
  char* commandString;      // command string (e.g. "LED_ON", "LED_OFF"; use caps for alpha characters)
  CmdFunc commandFunction;  // pointer to the function that will execute if this command matches
} CmdStruct;

void Command_Clear(int argc = 0, char* argv[] = { NULL });
void Command_SetColor(int argc = 0, char* argv[] = { NULL });

// command table
CmdStruct cmdTable[NUM_CMDS] = {

  {
    .commandArgs = 1,                   // CLEAR
    .commandString = "CLEAR",          // capitalized command for getting environment datum
    .commandFunction = &Command_Clear  // run Command_Clear
  },

  {
    .commandArgs = 4,                    // SET_COLOR <R> <G> <B>
    .commandString = "SET_COLOR",          // capitalized command for adjusting LED color
    .commandFunction = &Command_SetColor  // run Command_SetColor
  }

};
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(BAUD_RATE);
  while (Serial.available() > 0) { Serial.read(); }
  Serial.flush();

  pixels.begin(); // This initializes the NeoPixel library.
  pixels.clear();
  pixels.show();
}

void loop() {
  // receive the serial input and process the message
  receive_message();
}

/******************************************************************************************
 **********************************   Helper Functions   **********************************
 ******************************************************************************************/

// reads in serial byte-by-byte and executes command
void receive_message(void) {

  // control variables
  uint8_t rc;              // stores byte from serial
  static uint8_t idx = 0;  // keeps track of which byte we are on

  // check for a timeout if we've received at least one character
  if (idx > 0) {
    // ignore message and reset index if we exceed timeout
    if ((millis() - lastCharTime) > MSG_TIMEOUT) {
      idx = 0;
    }
  }

  // if there's a character waiting
  if (Serial.available() > 0) {
    // update the last character timer
    lastCharTime = millis();
    // read the character
    rc = Serial.read();
    // if character is newline (serial monitor delimeter)
    if (rc == '\n') {
      // null-terminate the message
      buff[idx] = '\0';
      // and go process it
      process_message();
      // reset the buffer index to get ready for the next message
      idx = 0;
    } else {
      // store capitalized character and bump buffer pointer
      buff[idx++] = toupper(rc);
      // but not beyond the limits of the buffer
      if (idx == BUFF_SIZE) {
        --idx;
      }
    }
  }
}

// matches the message buffer to supported commands
void process_message(void) {

  // split the input message by a space delimeter (first token is the command name)
  char* token = strtok(buff, " ");

  // if we at least have a command name (first token)
  if (token != NULL) {
    // walk through command table to search for message match
    for (int i = 0; i < NUM_CMDS; ++i) {
      // start handling the arguments if the requested command is supported
      if (strcmp(token, cmdTable[i].commandString) == 0) {
        // get the number of required arguments
        int argc = cmdTable[i].commandArgs;
        // create an array to store arguments
        char* argv[argc];
        // store the command name in argv
        argv[0] = token;
        // parse the arguments required for the command
        for (int j = 1; j < argc; ++j) {
          // get the next argument
          token = strtok(NULL, " ");
          // check if there is too few arguments
          if (token == NULL) {
            return;
          }
          // store if it's provided
          argv[j] = token;
        }
        // try to get another argument (should be done already)
        token = strtok(NULL, " ");
        // check if there is too many arguments
        if (token != NULL) {
          return;
        }

        // send acknowledgement
        Serial.write("OK\n");

        // execute the command and pass any arguments
        cmdTable[i].commandFunction(argc, argv);
        
        // ok get out of here now
        return;
      }
    }
  }
}

/******************************************************************************************
 *********************************   Command Functions   **********************************
 ******************************************************************************************/



// clear pixel strip
void Command_Clear(int argc, char* argv[]) {
  pixels.clear();
  pixels.show();
}

// change RGB values of LED
void Command_SetColor(int argc, char* argv[]) {

  // ensure RGB arguments are byte sized
  uint8_t R = constrain(atoi(argv[1]), 0, 255);
  uint8_t G = constrain(atoi(argv[2]), 0, 255);
  uint8_t B = constrain(atoi(argv[3]), 0, 255);

  for(int i=0;i<NUMPIXELS;i++){
    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(i, pixels.Color(R, G, B));
  }
  pixels.show(); // This sends the updated pixel color to the hardware.

}
