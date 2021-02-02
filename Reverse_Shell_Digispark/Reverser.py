reversed = "################################ !`#$%&`()*+,-.é0123456789:;'=.É\"ABCDEFGHIJKLMNOPQRSTUVWXYZ^<¸?_#abcdefghijklmnopqrstuvwxyz^>¨|" #CAFR
# reversed = "##########\n##################### !`/$%&`()*+,-.#0123456789:;'=.#\"ABCDEFGHIJKLMNOPQRSTUVWXYZ^<#?_#abcdefghijklmnopqrstuvwxyz^>¨|"  #CMS
# reversed = "##########\n###################### !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~"  #US
keyboard = [None] * len(reversed)
for i, char in enumerate(reversed):
    keyboard[ord(char) if ord(char) <= 128 else 0] = chr(i)

str = ""
for char in keyboard:
    if char is not None: str += char
    else: str += "#"

str = '"' + str.replace('\\', '\\\\').replace('\n', '\\n').replace('"', '\\"') + '"'
open('Reverser output.txt', 'w').write(str)
