/*

ACESSAR BIBLIOTECA ARDUINO APDS 9960 NO SITE DO ARDUINO PARA MAIS INFORMACOES

https://www.arduino.cc/reference/en/libraries/arduino_apds9960/

*/

//CODIGO ADAPTADO AO SENSOR DE GESTOS E CORES APDS9960, USADO COMO BASE 
//PARA A LÓGICA DE RBF, USANDO A IDEIA DE TRES CARTOES RBG
//UTILIZADO PARA SUPORTE À EQUIPE DE FOGUETEMODELISMO DA UFSC APEX ROCKETRY

#import <Arduino_APDS9960.h>

const int pinoPIR = 10; //PINO DIGITAL UTILIZADO PELO SENSOR DE PRESENÇA
const int pinoLED_A = 7; //(7,8,9...)PINO DIGITAL UTILIZADO PELA TRILHA A
const int pinoLED_B = 8; //(8,9,10...)PINO DIGITAL UTILIZADO PELA TRILHA B
const int pinoLED_C = 9; //(9,10,11...)PINO DIGITAL UTILIZADO PELA TRILHA C

//RESERVAR PORTAS CORRESPONDENTES AO NUMERO DE ASOCIACOES POR TRILHA


void setup(){
  pinMode(pinoLED_A, OUTPUT); //DEFINE O PINO COMO SAÍDA
  pinMode(pinoLED_B, OUTPUT); //DEFINE O PINO COMO SAÍDA
  pinMode(pinoLED_C, OUTPUT); //DEFINE O PINO COMO SAÍDA

  pinMode(pinoPIR, INPUT); //DEFINE O PINO COMO ENTRADA

  Serial.begin(9600);

  while(!Serial);

  if (!APDS.begin()){
    Serial.println('Modulo nao inicializado');
  // For setGestureSensitivity(...), a value between 1 and 100 is required.
  // Higher values make the gesture recognition more sensitive but less accurate
  // (a wrong gesture may be detected by the sensor). Lower values makes the gesture recognition
  // more accurate but less sensitive (some gestures may be missed by the sensor).
  // Default value is 80.

  //APDS.setGestureSensitivity(80);

    Serial.println('Modulo inicializado');
  }
}


void loop(){


//TRECHO IMPLEMENTÁVEL PARA PERÍODOS DE TESTE, EM QUE A VERIFICACAO DE VALIDADE DO LANÇAMENTO PODE SER FEITA MAIS DE UMA VEZ
//POIS APAGA TODOS OS LEDS QUANDO ESTAO ACESSOS SIMULTANEAMENTE 
//PARA USO DEFINITIVO, RETIRAR O IF 
  if ((digitalRead(pinoLED_A), HIGH) and (digitalRead(pinoLED_A), HIGH) and (digitalRead(pinoLED_A), HIGH)){ //se todos os leds estiverem acessos, eles serao apagados e o loop, interrompido
    digitalWrite(pinoLED_A, LOW); //APAGA O LED
    digitalWrite(pinoLED_B, LOW); //APAGA O LED
    digitalWrite(pinoLED_C, LOW); //APAGA O LED

  }
  

  if (APDS.colorAvailable()){ //LOGICA DO SENSOR EM QUESTAO

    int r, g, b; //inteiros para as cores rgb
    APDS.readColor(r,g,b);

    //LOGICA DO SENSOR EM QUESTAO

    if (r > 220){ //cor vermelha acende o primeiro led, caso esteja apagado
      if (digitalRead(pinoLED_A) == LOW) {
        digitalWrite(pinoLED_A, HIGH); //ACENDE A PRIMEIRA TRHILA DE LEDS, INDICANDO A PRIMEIRA VALIDACAO DE LANCAMENTO      
    }

  }
    else if (g > 220){ //cor verde acende o segundo led, caso esteja apagado
      if (digitalRead (pinoLED_B) == LOW) {
        digitalWrite(pinoLED_B, HIGH); //ACENDE A SEGUNDA TRHILA DE LEDS, INDICANDO A SEGUNDA VALIDACAO DE LANCAMENTO    
      }

}

    else if (b > 220){ //cor azul acende o terceiro led, caso esteja apagado
      if (digitalRead (pinoLED_C) == LOW) {
        digitalWrite(pinoLED_C, HIGH); //ACENDE A TERCEIRA TRHILA DE LEDS, INDICANDO A TERCEIRA VALIDACAO DE LANCAMENTO    
      }

    }
    //OBS: AS CORES DE VALIDACAO (VERMELHA, VERDE E AZUL) SAO ARBITRARIAS E ADAPTADAS AO SENSOR DE TESTE EM QUESTAO USADO
   //A LOGICA IMPLEMENTADA SIMULA QUALQUER OUTRA LOGICA DE VALIDACAO UTILIZAVEL PELA EQUIPE    
  }
  }

