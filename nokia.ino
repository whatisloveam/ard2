int n = 0;
int st = 0;
int en = 0;

int tempo = 120;
int octave = 0;
int part = 0;
float mult = 1;
int note = 0;

int notes[] = {
    440,//a
    494,//b
    523,//c
    587,//d
    659,//e
    698,//f
    784,//g
    462,//a#
    544,//c#
    622,//d#
    740,//f#
    830,//g#
    0  //pause
};

void setup()
{
    Serial.begin(9600);
    pinMode(11, OUTPUT);
}
void loop()
{
    if(Serial.available())
    {
        String s = Serial.readStringUntil('\n');
        st = 0;
        en = 0;
        for(int i = 0; i < s.length(); i++)
        {
            if(s[i] == ' ') 
            {
                en = i;
                String nota = s.substring(st, en);
                Serial.println(nota);
                // find part
                if(nota[1] == '6') part = 16;
                else if(nota[1] == '2') part = 32;
                else part = nota[0] - 48;

                if(part > 9) nota = nota.substring(2,nota.length());
                else nota = nota.substring(1,nota.length());
                Serial.println(part);
                //note
                if(nota[0] != '-')
                {
                    mult = 1;
                    if(nota[0] == '.') 
                    {
                        nota = nota.substring(1,nota.length());
                        mult = 1.5;
                        Serial.println(".");
                    }

                    if(nota[0] >= 'a' || nota[0] <= 'g') note = nota[0] - 97;
                    else if(nota[0] == '#') note = nota[1] - 90;
                    Serial.println(notes[note]);
                    octave = nota[nota.length() - 1] - 48;
                    Serial.println(octave);
                }
                else
                {
                    note = 12;
                    Serial.println(notes[note]);
                }
                st = i + 1;
            }
        }
    }
}
