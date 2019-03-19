// What does the morse say - Beeper
// Recebe texto ascii pelo serial e apita e pisca em codigo morse

// Pinos usados
int pino_led = 13;
int pino_buzzer = 11;

// Todos os caracteres ISO 8859-1 com correspondencia em codigo morse (https://en.wikipedia.org/wiki/Morse_code)
// Caracteres sem correspondencia estão marcados como erro '........'
// Letras acentuadas sem correspondencia foram trocadas pelo símbolo mais próximo
// Dividido em uma matriz 16x16 para encontrar mais facil
char *codigo_morse[] = {
  "........", "........", "........", "........", "........", "........", "........", "........", "........", "........", '\n', "........", "........", "........", "........", "........",
  "........", "........", "........", "........", "........", "........", "........", "........", "........", "........", "........", "........", "........", "........", "........", "........",
  " ", "-.-.--", ".-..-.", "........", "...-..-", "........", ".-...", ".----.", "-.--.", "-.--.-", "........", ".-.-.", "--..--", "-....-", ".-.-.-", "-..-.",
  "-----", ".----", "..---", "...--", "....-", ".....", "-....", "--...", "---..", "----.", "---...", "-.-.-.", "........", "-...-", "........", "..--..",
  ".--.-.", ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---", "-.-", ".-..", "--", "-.", "---",
  ".--.", "--.-", ".-.", "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--..", "........", "........", "........", "........", "..--.-",
  " ", ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---", "-.-", ".-..", "--", "-.", "---",
  ".--.", "--.-", ".-.", "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--..", "........", "........", "........", "........", "........",
  "........", "........", "........", "........", "........", "........", "........", "........", "........", "........", "........", "........", "........", "........", "........", "........",
  "........", "........", "........", "........", "........", "........", "........", "........", "........", "........", "........", "........", "........", "........", "........", "........",
  "........", "........", "........", "........", "........", "........", "........", "........", "........", "........", "........", "........", "........", "........", "........", "........",
  "........", "........", "........", "........", "........", "........", "........", "........", "........", "........", "........", "........", "........", "........", "........", "........",
  ".--.-", ".--.-", ".--.-", ".-.-", ".-.-", ".--.-", ".-.-", "-.-..", ".-..-", "..-..", "..-..", "..-..", "..", "..", "..", "..",
  "..-..", "--.--", "---.", "---.", "---.", "---.", "---.", " ", "---.", "..--", "..--", "..--", "..--", "-.--", ".--..", "...-...",
  ".--.-", ".--.-", ".--.-", ".-.-", ".-.-", ".--.-", ".-.-", "-.-..", ".-..-", "..-..", "..-..", "..-..", "..", "..", "..", "..",
  "..-..", "--.--", "---.", "---.", "---.", "---.", "---.", " ", "---.", "..--", "..--", "..--", "..--", "-.--", ".--..", "-.--"
};

// Tempo de cada ação em ms
int tPonto = 60;
int tTraco = 3*tPonto;
int tTP = tPonto;
int tLetra = (3-1)*tPonto; // Dá 3 com o espaço depois da letra
int tPalavra = (7-1)*tPonto;

void setup() {  
  pinMode(pino_led, OUTPUT);
  pinMode(pino_buzzer, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  
  unsigned char ch;  //8 bits
  if(Serial.available()){ //ha algo para ser lido no usb
    ch = Serial.read();
    if(ch == '\n'){
      Serial.write('\n');
    }
    else{
      Serial.print((int)ch);
      Serial.print(' ');
      pisca(codigo_morse[ch]);
    }
  }
}

void pisca(char *seq){  //seq é um ponteiro?
  int i = 0;
  while(seq[i] != '\0'){
    Serial.print(seq[i]);
    pontoTraco(seq[i]);
    i++;  
  }
  delay(tLetra);
}

void pontoTraco(char pt){  
  if(pt == '.'){
    digitalWrite(pino_buzzer, HIGH);
    digitalWrite(pino_led, HIGH);
    delay(tPonto);
    digitalWrite(pino_buzzer, LOW);
    digitalWrite(pino_led, LOW);
    delay(tTP);
  }  
  else if(pt == '-'){
    digitalWrite(pino_buzzer, HIGH);
    digitalWrite(pino_led, HIGH);
    delay(tTraco);
    digitalWrite(pino_buzzer, LOW);
    digitalWrite(pino_led, LOW);
    delay(tTP);
  } 
  else if(pt == ' '){
    delay(tPalavra);
  }
  else{
    // Deu ruim.
    digitalWrite(pino_buzzer, HIGH);
    digitalWrite(pino_led, HIGH);
    delay(40*tPonto);
    digitalWrite(pino_buzzer, LOW);
    digitalWrite(pino_led, LOW);
  }
}
