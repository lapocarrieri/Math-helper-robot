/**
  ******************************************************************************
  * @file    vr_sample_multi_cmd.ino
  * @author  JiapengLi
  * @brief   This file provides a demostration on 
              how to implement a multi voice command project (exceed 7 voice command) 
              by using VoiceRecognitionModule
  ******************************************************************************
  * @note:
        voice control led
  ******************************************************************************
  * @section  HISTORY
    
    2013/06/13    Initial version.
  */
  
#include <SoftwareSerial.h>
#include "VoiceRecognitionV3.h"

/**        
  Connection
  Arduino    VoiceRecognitionModule
   2   ------->     TX
   3   ------->     RX
*/
VR myVR(2,3);    // 2:RX 3:TX, you can choose your favourite pins.

uint8_t record[7]; // save record
uint8_t buf[64];
String StringOne, StringTwo, StringThree, a;
int led1 = 9; //BLUE
int ReadyLed = 12; //RED
int AreaLed = 11; //YELLOW
int AnsweringLed = 4; //GREEN
int group = 0;
bool done = false;
bool operation = false;
bool FirstOperator=false;
bool SecondOperator=false;
bool ThirdOperator=false;
bool operations = false;

#define HeyDalton           (25)
#define group0Record1       (26) 
#define group0Record2       (27) 
#define group0Record3       (28) 
#define group0Record4       (29) 
#define group0Record5       (30) 
#define group0Record6       (31) 

#define group1Record1       (17) 
#define group1Record2       (18) 
#define group1Triangle       (19) 
#define group1Rhombus       (20) 
#define group1Rectangle       (21) 
#define group1Circle       (22) 

#define group2Record1      (25) 
int buttonState = 0;
bool buttonStateNumbers = false; 
bool buttonStateOperands = false; 
//const int buttonPinReset = 13; 
const int buttonPinNumbers = 10; 
const int buttonPinOperands = 7; 

bool numbersPage = false; 

bool operandsPage = false;

void setup()
{
  /** initialize */
  myVR.begin(9600);
  //pinMode(buttonPinReset, INPUT);
  pinMode(buttonPinNumbers, INPUT);
  pinMode(buttonPinOperands, INPUT);
  
  Serial.begin(115200);
  Serial.println("Elechouse Voice Recognition V3 Module\r\nMulti Commands sample");
  
  pinMode(led1, OUTPUT);
  pinMode(ReadyLed,OUTPUT);
  pinMode(AreaLed,OUTPUT);
  pinMode(AnsweringLed,OUTPUT);


    
  if(myVR.clear() == 0){
    Serial.println("Recognizer cleared.");
  }else{
    Serial.println("Not find VoiceRecognitionModule.");
    Serial.println("Please check connection and restart Arduino.");
    while(1);
  }
  
  record[0] = HeyDalton;
  group = 0;
  if(myVR.load(record, 7) >= 0){
    printRecord(record, 7);
    Serial.println(F("loaded."));
  }
}

void loop()
{
  int ret;
  ret=myVR.recognize(buf,250);
  if(ret>0){
    if(buf[1] == 25){
      digitalWrite(ReadyLed,HIGH);
      Serial.println("Hi, I am Dalton, lets do some math");
      myVR.clear();
      myVR.load(uint8_t (29));
      myVR.load(uint8_t (30));
    
    }
  }
  if(ret>0){
    if(buf[1] == 30){
      digitalWrite(ReadyLed,LOW);
      delay(1000);
      digitalWrite(ReadyLed,HIGH);

      Serial.println("I am fine, ready to do some math");
      myVR.clear();
      myVR.load(uint8_t (29));
    
    }
  }
  if(ret>0){
    if(buf[1] == 29 || buf[1] == 34){
      digitalWrite(led1,HIGH);
      Serial.println("I am ready, What do you wanna do?");
      myVR.clear();
      myVR.load(uint8_t (26));
      myVR.load(uint8_t (27));
      myVR.load(uint8_t (28));
      myVR.load(uint8_t (31));
      done = false;
    
    }
  }
  if(buf[1] > 16 && buf[1]<23){
      digitalWrite(AreaLed,HIGH);
      delay(1000);
      digitalWrite(AreaLed,LOW);
      delay(1000);
    if(done == false){
        if(buf[1]==17){
          Serial.println("The Area of the Trapezius is the sum of bases times height divided by 2");
        }
        if(buf[1]==18){
          Serial.println("length square");
        } 
        if(buf[1]==19){
          Serial.println("base times height /2");
        } 
        if(buf[1]==20){
          Serial.println("major diagonal times minor diagonal divided by two");
        }
        if(buf[1]==21){
          Serial.println("length times breadth");
        }
        if(buf[1]==22){
          Serial.println("pi times radius square");
        }
    myVR.clear();
    myVR.load(uint8_t (34));        
    done=true;
    } 
  }
  /*if(ret>0){
    if(buf[1] == 32){
      digitalWrite(AreaLed,HIGH);
      Serial.println("Okay, ask me some areas formula");
      myVR.clear();
      myVR.load(uint8_t (17));
      myVR.load(uint8_t (18));
      myVR.load(uint8_t (19));
      myVR.load(uint8_t (20));
      myVR.load(uint8_t (21));
      myVR.load(uint8_t (22));
      myVR.load(uint8_t (31));
    
    }
  }*/

  if(ret>0){
    if(buf[1] == 26){
      digitalWrite(AreaLed,HIGH);
      Serial.println("Okay, ask me some areas formula");
      myVR.clear();
      myVR.load(uint8_t (17));
      myVR.load(uint8_t (18));
      myVR.load(uint8_t (19));
      myVR.load(uint8_t (20));
      myVR.load(uint8_t (21));
      myVR.load(uint8_t (22));
      myVR.load(uint8_t (31));
    
    }
  }
  
  String result; 
  if(ret>0){
    if(buf[1] == 27){
      operations = true;    
      digitalWrite(AreaLed,HIGH);
      Serial.println("Okay,lets do some calculus");
    }
  }

  if (operations){
    if(ret>0){
      digitalWrite(AnsweringLed,LOW);
      delay(1000);
      digitalWrite(AnsweringLed,HIGH);
    }

   
    buttonStateNumbers = digitalRead(buttonPinNumbers);
    if (buttonStateNumbers == HIGH) {
      if (numbersPage) numbersPage = false; 
      else numbersPage = true; 
    }
    buttonStateOperands = digitalRead(buttonPinOperands);
    if (buttonStateOperands == HIGH) {
      if (operandsPage) operandsPage = false;
      else operandsPage = true; 
    }
    


    if (operandsPage){
      delay(100);
      myVR.clear();
      myVR.load(uint8_t (11));
      myVR.load(uint8_t (12));
      myVR.load(uint8_t (13));
      myVR.load(uint8_t (14));
      myVR.load(uint8_t (15));
      myVR.load(uint8_t (42));
      if (ret > 0){
        digitalWrite(AnsweringLed,HIGH);
        if (buf[1] == '='){
            StringOne += '=';
            result = compute_equation(StringOne);
            Serial.println(result);
            operations = false;
        }else{
          StringOne += buf[1];
          operandsPage = false; 
        }
      }
    }else{
      if (!numbersPage){             
        myVR.clear();
        myVR.load(uint8_t (100));
        myVR.load(uint8_t (1));
        myVR.load(uint8_t (2));
        myVR.load(uint8_t (3));
        myVR.load(uint8_t (4));
        myVR.load(uint8_t (42));
        Serial.println(ret);
        if (ret >  0){
          
          Serial.println(buf[1]);          
          StringOne = StringOne +buf[1];
        }
        
      }else{
        delay(100);
        myVR.clear();
        myVR.load(uint8_t (5));
        myVR.load(uint8_t (6));
        myVR.load(uint8_t (7));
        myVR.load(uint8_t (8));
        myVR.load(uint8_t (9));
        myVR.load(uint8_t (42));
        if(ret>0){
          StringOne += buf[1];
        }
      }
    }
  }
  /*if(ret>0){
    if(FirstOperator){
      
      StringOne = StringOne +buf[1];
      
      
      FirstOperator=false;
      SecondOperator=true;
      Serial.println(StringOne);
      ret=0;  
    }
  }

  if(ret>0){
    if(SecondOperator){
      if(buf[1]==11){a="+";}
      if(buf[1]==12){a="-";}
      if(buf[1]==13){a="*";}
      if(buf[1]==14){a="+";}
      StringTwo = StringOne+a;
      myVR.clear();
      myVR.load(uint8_t (1));
      myVR.load(uint8_t (2));
      myVR.load(uint8_t (3));
      myVR.load(uint8_t (4));
      myVR.load(uint8_t (5));
      myVR.load(uint8_t (6));
      myVR.load(uint8_t (7));
      ThirdOperator=true;
      SecondOperator=false;
      Serial.println(StringTwo);  
      ret=0;
    }
  }
  if(ret>0){
    if(ThirdOperator){
      StringThree=StringTwo+buf[1]+'=';
      Serial.println("the result is:");
      Serial.println(StringThree);  
      Serial.println(compute_equation(StringThree));  
      ThirdOperator=false;

    }
  }
  >0){
  if(buf[1] == 35 || operation){
    myVR.clear();
    myVR.load(uint8_t (7));
    myVR.load(uint8_t (8));
    myVR.load(uint8_t (9));
    myVR.load(uint8_t (10));
    myVR.load(uint8_t (6));
    Serial.println("bella");
  operation=true;
  Serial.println(buf[1]);
  }
  }
  if(operation==true){
      myVR.clear();
      myVR.load(uint8_t (7));
      myVR.load(uint8_t (8));
      myVR.load(uint8_t (9));
      myVR.load(uint8_t (10));
      myVR.load(uint8_t (6));  
  }*/
  if(ret>0){
    if(buf[1] == 31){
      digitalWrite(AreaLed,LOW);
      digitalWrite(led1,LOW);
      Serial.println("Okay, reset everything");
      myVR.clear();
      myVR.load(uint8_t (29));
    
    }
  }
  //buttonState = digitalRead(buttonPinNumbers);
  //buttonState = digitalRead(buttonPinOperands);

  /*if (buttonState == HIGH) {

    group = 0;
    done = false;
    operation = false;
    StringOne="";
    // turn LED on:
    digitalWrite(ReadyLed, LOW);
    digitalWrite(AreaLed, LOW);
    digitalWrite(led1, LOW);
    delay(100);
    digitalWrite(ReadyLed, HIGH);
    digitalWrite(AreaLed, HIGH);
    digitalWrite(led1, HIGH);
    delay(100);
    digitalWrite(ReadyLed, LOW);
    digitalWrite(AreaLed, LOW);
    digitalWrite(led1, LOW);
    myVR.clear();
    myVR.load(uint8_t (25));
    Serial.println("Button pressed, Reset everything, restart with Hi Dalton");
  }*/
}

/**
  @brief   Print signature, if the character is invisible, 
           print hexible value instead.
  @param   buf     --> command length
           len     --> number of parameters
*/
void printSignature(uint8_t *buf, int len)
{
  int i;
  for(i=0; i<len; i++){
    if(buf[i]>0x19 && buf[i]<0x7F){
      Serial.write(buf[i]);
    }
    else{
      Serial.print("[");
      Serial.print(buf[i], HEX);
      Serial.print("]");
    }
  }
}

/**
  @brief   Print signature, if the character is invisible, 
           print hexible value instead.
  @param   buf  -->  VR module return value when voice is recognized.
             buf[0]  -->  Group mode(FF: None Group, 0x8n: User, 0x0n:System
             buf[1]  -->  number of record which is recognized. 
             buf[2]  -->  Recognizer index(position) value of the recognized record.
             buf[3]  -->  Signature length
             buf[4]~buf[n] --> Signature
*/
void printVR(uint8_t *buf)
{
  Serial.println("VR Index\tGroup\tRecordNum\tSignature");

  Serial.print(buf[2], DEC);
  Serial.print("\t\t");

  if(buf[0] == 0xFF){
    Serial.print("NONE");
  }
  else if(buf[0]&0x80){
    Serial.print("UG ");
    Serial.print(buf[0]&(~0x80), DEC);
  }
  else{
    Serial.print("SG ");
    Serial.print(buf[0], DEC);
  }
  Serial.print("\t");

  Serial.print(buf[1], DEC);
  Serial.print("\t\t");
  if(buf[3]>0){
    printSignature(buf+4, buf[3]);
  }
  else{
    Serial.print("NONE");
  }
//  Serial.println("\r\n");
  Serial.println();
}

void printRecord(uint8_t *buf, uint8_t len)
{
  Serial.print(F("Record: "));
  for(int i=0; i<len; i++){
    Serial.print(buf[i], DEC);
    Serial.print(", ");
  }
}

String compute_equation(String equation) {
    char operands[50] = {'0'};
    float numbers[50] = {0};
    int operand_index = 1;
    int length = 0;
    for (int i = 0; i < equation.length();) {
        String tmp_number = "";
        while (equation[i] != '+' && equation[i] != '-' && equation[i] != '*' && equation[i] != '/' && equation[i] != '=') {
            tmp_number += equation[i];
            i++;
        }
        operands[operand_index] = equation[i];
        i++;
        numbers[operand_index - 1] = tmp_number.toFloat();
        operand_index += 2;
        length += 2;
    }
    int index = 0;
    while (index < length) {
        if (operands[index] == '*' || operands[index] == '/') {
            float partial;
            switch (operands[index]) {
            case '*':
                partial = numbers[index - 1] * numbers[index + 1];
                break;
            default:
                partial = numbers[index - 1] / numbers[index + 1];
                break;
            }
            numbers[index - 1] = partial;
            for (int j = index; j < 50; j++) {
                if (j % 2 == 0) numbers[j] = numbers[j + 2];
                else operands[j] = operands[j + 2];
                if (operands[j] == '=') length -= 2;
            }
        }
        else index++;
    }
    index = 0;
    while (index < length) {
        if (operands[index] == '+' || operands[index] == '-') {
            float partial;
            switch (operands[index]) {
            case '+':
                partial = numbers[index - 1] + numbers[index + 1];
                break;
            default:
                partial = numbers[index - 1] - numbers[index + 1];
                break;
            }
            numbers[index - 1] = partial;
            for (int j = index; j < 50; j++) {
                if (j % 2 == 0) numbers[j] = numbers[j + 2];
                else operands[j] = operands[j + 2];
                if (operands[j] == '=') length -= 2;
            }
        }
        else index++;
    }
    return String(numbers[0]);
}
