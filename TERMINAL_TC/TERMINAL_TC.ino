/*This example shows how to use the Mux Shield for a combination of 
analog inputs, digital inputs, and digital outputs.
*/
#include <LiquidCrystal_I2C.h>
//Initialize the Mux Shield
LiquidCrystal_I2C lcd(0x27,20,4);
//Entradas analogas**********
int TP6_2_00v = A0;

int TP1_23_46VDC = A1;
int TP2_4_97VDC = A2;
int TP3_4_96VDC = A3;
int TP7_3_3V = A4;
int TP8_3_3V = A5;
int TP9_3_3V = A6;
int P1_Pin1_3_3V = A7;
int P3_Pin7_3_3V = A8;
int P3_Pin8_3_3V = A9;

int P3_Pin1_4_96V = A10;
int P3_Pin2_4_96V = A11;
int P3_Pin3_4_96V = A12;
int P3_Pin4_4_96V = A13;
int P3_Pin5_4_96V = A14;
int P3_Pin6_4_96V = A15;
//***************************
//******LEDS**************
int Good_Part_Led = 38;
int Bad_Part_Led = 39;
//***************************
int InitButton = 43;
//**Voltaje esperado*******
float V_Spctd;
float V_Rd;
//*************************
float Range_5 = .4;
float Range_3_3 = .5;
float Range_0 = 1.8;
float Range_0_TP_6 = .8;
float Range_2_TP_6 = .3;
int actual = 0;
int Res_Sum;
int i = 0;
String MsgOut;
bool stop_it = false;
bool run_it = false;
bool Continue = true;
//********Modelos************
bool M118_3388 = false;
void setup()
{
  //Start_Pin
  //******** Salidas de arduino*******
  pinMode(22, OUTPUT);
  pinMode(25, OUTPUT);
  pinMode(30, OUTPUT);
  pinMode(Good_Part_Led, OUTPUT);
  pinMode(Bad_Part_Led, OUTPUT);  
  pinMode(40, OUTPUT);
  pinMode(41,OUTPUT);
  pinMode(42,OUTPUT);
  pinMode(44, OUTPUT);
 // *********ENTRADAS DIGITALES************
 pinMode(23,INPUT_PULLUP);
 pinMode(24,INPUT_PULLUP);
 pinMode(26,INPUT_PULLUP);
 pinMode(27,INPUT_PULLUP);
 pinMode(28,INPUT_PULLUP);
 pinMode(29,INPUT_PULLUP);
 pinMode(31,INPUT);
 pinMode(32,INPUT);
 pinMode(33,INPUT);
 pinMode(34,INPUT);
 pinMode(35,INPUT);
 pinMode(36,INPUT);
 pinMode(37,INPUT);
 pinMode(InitButton,INPUT_PULLUP);
 pinMode(45,INPUT);
 pinMode(46,INPUT);
 pinMode(47,INPUT);
 pinMode(48,INPUT);
 pinMode(49,INPUT);
 pinMode(50,INPUT);
 pinMode(51,OUTPUT);
 pinMode(52,INPUT_PULLUP);


 
 Serial.begin(9600);
  // set up the LCD's number of columns and rows:
  lcd.init();
  // initialize the lcd 
  // Print a message to the LCD.
  //lcd.print("hello, world!");
}
void loop()
{
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Modelo: 118_3388");
  lcd.setCursor(0, 1);
  lcd.print("");
  run_it = !digitalRead(InitButton);
 Serial.println(run_it);
 if (run_it == true)  
 {
    delay(1000);
    digitalWrite(41, LOW);
    digitalWrite(42, LOW);
    
    digitalWrite(22, LOW);
    digitalWrite(25, LOW);
    digitalWrite(44, LOW);
    digitalWrite(30, LOW);    
    digitalWrite(Good_Part_Led, LOW);
    digitalWrite(Bad_Part_Led, LOW);
     digitalWrite(51, LOW);
     delay(500);
     digitalWrite(40, LOW);
    Continue = false;
    MsgOut = "Start...";
    Refresh_Msg();
     //****** BINDING GROUNDS*******
    digitalWrite(40, HIGH);
    //****** BINDING GROUNDS*******
    delay(500);
     //****** AC TESTING*******
      digitalWrite(41, HIGH);
      MsgOut ="AC TESTING";
      Refresh_Msg();
      Test_AnalogIn(5,TP1_23_46VDC, Range_5, "AC TESTING");
      digitalWrite(41, LOW);
    //*************************
     delay(500);
    //****** DC TESTING*******
    if (Continue == true){
      digitalWrite(42, HIGH);
      MsgOut ="DC TESTING";
      Refresh_Msg();
      //delay(2000);
      Test_AnalogIn(5,TP1_23_46VDC, Range_5, "DC TESTING");
    }
    //************************  
     if (Continue == true){
        Test_AnalogIn(4.97,TP2_4_97VDC, Range_5, "TP2");
     }
      if (Continue == true){
    Test_AnalogIn(4.97,TP3_4_96VDC, Range_5, "TP3");
    }
    //*****************************


    //*********TP4 ***********
    if (Continue == true){
      digitalWrite(22, LOW);
      MsgOut ="TP4 TESTING";
      Refresh_Msg();
      if ((digitalRead(23) == false) && (digitalRead(24) == false)){
        MsgOut ="TP4: OK";
        Serial.println(MsgOut);
        Serial.println(digitalRead(23));
        Serial.println(digitalRead(24));
        Refresh_Msg();
        //digitalWrite(22, LOW);
        Continue = true;    
      }
      else if((digitalRead(23) == true)||(digitalRead(24) == true)){
        MsgOut ="TP4: ERR";
               Serial.println(MsgOut);
        Serial.println(digitalRead(23));
        Serial.println(digitalRead(24));
        Refresh_Msg();
        //digitalWrite(22, LOW);
        Continue = false; 
        Test_Err_Led();
      }
    }
    //*******************************
    //*********TP5********************
          //******PRUEBA EN LOW***************
      if (Continue == true){
      digitalWrite(25, LOW);
      if ((digitalRead(26) == false) && (digitalRead(27) == false)){
        MsgOut ="TP5-LOW OK";
        Refresh_Msg(); 
        Continue = true;
        Serial.print("TP5-LOW: OK");
      }
      else if((digitalRead(26) == true) || (digitalRead(27) == true)){
        MsgOut ="TP5-LOW: ERR";
        Refresh_Msg();
        Test_Err_Led();
        Continue = false; 
        Serial.print("TP5-LOW: NO_OK");
        //break;             
      }
      }
    if (Continue == true){
      digitalWrite(25, HIGH);
     //******PRUEBA EN HIGH***************
    
      if ((digitalRead(26) == true) && (digitalRead(27) == true)){
        MsgOut ="TP5-HIGH: OK";
        Refresh_Msg(); 
        Serial.print("TP5-HIGH: OK");
        Continue = true;
      }
      else if((digitalRead(26) == false) || (digitalRead(27) == false)){
        Serial.println("TP5-HIGH: NO_OK");
        Serial.print(digitalRead(26));
        Serial.print(digitalRead(27));
        MsgOut ="TP5-HIGH: ERR";
        Refresh_Msg();
        

        digitalWrite(25, LOW);
        Continue = false;
        Test_Err_Led();        
      } 
      }
      //******TP6 PRUEBA EN LOW***************
      
      if (Continue == true){  
        digitalWrite(25, LOW);    
        Test_AnalogIn(0,TP6_2_00v, Range_0_TP_6, "TP6-LOW");
  
      }      
      //****** TP6 PRUEBA EN HIGH***************
      if (Continue == true){
        digitalWrite(25, HIGH);
        //Test_AnalogIn_TP6(2,TP6_2_00v, Range_2_TP_6, "TP6-HIGH");
        Test_AnalogIn(5,TP6_2_00v, Range_5, "TP6-HIGH");
    }  
    if (Continue == true){
      digitalWrite(25, LOW);
      Test_AnalogIn(0,TP7_3_3V, Range_0, "TP7-LOW");       
    }
    if (Continue == true){
      digitalWrite(25, HIGH);        
      Test_AnalogIn(3.3,TP7_3_3V, Range_3_3, "TP7-HIGH"); //Se cambió el rango de voltage y voltage deseado temporalmente, ya que el buffer no fnciona (DEBE DE SER a 3.3)
      digitalWrite(25, LOW);
    }


    //******************************
   //*******TP8(HIGH)*************
   if (Continue == true){
    digitalWrite(44, HIGH);
    Test_AnalogIn(0,TP8_3_3V, Range_0, "TP8-LOW");   
   }
       //*************************************
     //*******TP8(LOW)*************
   if (Continue == true){
    digitalWrite(44, LOW);
    Test_AnalogIn(3.3,TP8_3_3V, Range_3_3, "TP8-HIGH");
  } 
  //*************************************
  //*******TP9(HIGH)*************
   if (Continue == true){
    digitalWrite(44, HIGH);
    Test_AnalogIn(0,TP9_3_3V, Range_0, "TP9-LOW");
   }
//*************************************
  //*******TP9(LOW)*************
   if (Continue == true){
    digitalWrite(44, LOW);
    Test_AnalogIn(3.3,TP9_3_3V, Range_3_3, "TP9-HIGH");
   }
//************************************* 
  //*******TP10(HIGH)*************
   if (Continue == true){
    digitalWrite(44, HIGH); 
    if (digitalRead(29) == false){
      MsgOut ="TP10-HIGH: OK";
      Continue = true;      
      Refresh_Msg();     
      Serial.println(MsgOut);   
    }
    else{
      MsgOut ="TP10-HIGH: ERR";
      Continue = false;      
      Refresh_Msg();
      Test_Err_Led();   
      Serial.println(MsgOut);
    }
   }
    //*******************************   
  //*******TP10(LOW)*************
   if (Continue == true){
    digitalWrite(44, LOW); 
    delay(10);
    if (digitalRead(29) == true){
      MsgOut ="TP10-LOW: OK";
      Continue = true;      
      Refresh_Msg();  
      Serial.println(MsgOut);      
    }
    else{
      MsgOut ="TP10-LOW: ERR";
      Serial.println(MsgOut);
      Serial.println(digitalRead(29));
    
      Continue = false;      
      Refresh_Msg();
      Test_Err_Led();   
      Serial.println(MsgOut);
    }
   }
    //*******************************
//*******TP11-HIGH/TP12-HIGH/P1-P5(HIGH)*************
  if (Continue==true){
    digitalWrite(30, HIGH); 
    if (((digitalRead(31) == true) && (digitalRead(32) == true)) && (digitalRead(33) == false) && (digitalRead(34) == false) && (digitalRead(35) == false) && (digitalRead(36) == false) && (digitalRead(37) == false)){
      MsgOut ="TP11-HIGH/TP12-HIGH/P1-P5: OK";
      Continue = true;      
      Refresh_Msg();  
      Serial.println(MsgOut);
    }
    else if((digitalRead(31) == false) || (digitalRead(32) == false)) {
      MsgOut ="TP11-HIGH: ERR";
      Continue = false;      
      Refresh_Msg();
      Test_Err_Led();  
      Serial.println(MsgOut);       
    }
    else if(digitalRead(33) == true) {
      MsgOut ="TP12-HIGH: ERR";
      Continue = false;      
      Refresh_Msg();
      Test_Err_Led();  
      Serial.println(MsgOut);
    }
    else if((digitalRead(34) == true) || (digitalRead(35) == true) || (digitalRead(36) == true) || (digitalRead(37) == true)) {
      MsgOut ="P1-P5: ERR";
      Continue = false;      
      Refresh_Msg(); 
      Test_Err_Led();   
      Serial.println(MsgOut);     
    }       
  }
//*******************************
//*******TP11-LOW*************
  if(Continue == true){
    digitalWrite(30, LOW);
    if(( digitalRead(31) == false)&& (digitalRead(32) == false)){
      MsgOut ="TP11-HIGH: OK";
      Continue = true;      
      Refresh_Msg();   
      Serial.println(MsgOut);    
    }
    else{
      MsgOut ="TP11-HIGH: ERR";
      Continue = false;      
      Refresh_Msg();   
      Test_Err_Led();  
      Serial.println(MsgOut);   
    }
  }
//*******************************
  //*******TP13-1*************
  if (Continue == true){
    Test_AnalogIn(3.3,P1_Pin1_3_3V, Range_3_3, "TP13-1");
  }
//*******************************
//*******TP13-2*************
  if (Continue == true){
    Test_AnalogIn(3.3,P3_Pin7_3_3V, Range_3_3, "TP13-2");  
  }
//*******************************
//*******TP13-3*************
  if (Continue == true){
    Test_AnalogIn(3.3,P3_Pin8_3_3V, Range_3_3, "TP13-3");
  }
//*******************************
//*********P3_Pin1******************
if (Continue == true){
    Test_AnalogIn(4.96,P3_Pin1_4_96V, Range_5, "P3_Pin1");
}
//******************************
//*********P3_Pin2******************
if (Continue == true){
    Test_AnalogIn(4.96,P3_Pin2_4_96V, Range_5, "P3_Pin2");
}
//******************************
//*********P3_Pin3******************
if (Continue == true){
    Test_AnalogIn(4.96,P3_Pin3_4_96V, Range_5, "P3_Pin3");
}
//******************************
//*********P3_Pin4******************
if (Continue == true){
    Test_AnalogIn(4.96,P3_Pin4_4_96V, Range_5, "P3_Pin4");
}
//******************************
//*********P3_Pin5******************
if (Continue == true){
    Test_AnalogIn(4.96,P3_Pin5_4_96V, Range_5, "P3_Pin5");
}
//******************************
//*********P3_Pin6******************
if (Continue == true){
    Test_AnalogIn(4.96,P3_Pin6_4_96V, Range_5, "P3_Pin6");
}
//******************************
if (Continue == true){
  if ((digitalRead(45) == false) && (digitalRead(46) == false) && (digitalRead(47) == false) && (digitalRead(48) == false) && (digitalRead(49) == false) && (digitalRead(50) == false)){
    MsgOut = "P3_Cont_0V: OK";
    Continue = true;
    Refresh_Msg();
  }
  else {
    MsgOut = "P3_Cont_0V: ERR";
    Continue = false;
    Refresh_Msg();
    Test_Err_Led(); 
  }
}
  //*******W1/W2*************
     if (Continue == true){
    digitalWrite(51, LOW);
    if  (digitalRead(52) == false){
       MsgOut ="W1/W2-LOW: OK";
      Refresh_Msg();
        
    }
    else if(digitalRead(52) == true){
      MsgOut ="W1/W2-LOW: ERR";
      Continue = false;      
      Refresh_Msg();
      Test_Err_Led();   
    }
    
   }
   if (Continue == true){
    digitalWrite(51, HIGH);
    if  (digitalRead(52) == true){
      MsgOut ="PIEZA OK";
     // MsgOut ="W1/W2: OK";
      Continue = false;    
      
      digitalWrite(39, LOW);
      digitalWrite(40, LOW);
      digitalWrite(42, LOW);
    //  lcd.clear();  
      Refresh_Msg();
    Test_Ok_Led();       
    }
    else if(digitalRead(52) == false){
      MsgOut ="W1/W2-HIGH: ERR";
      Continue = false;      
      Refresh_Msg();
      Test_Err_Led();   
    }
     digitalWrite(51, LOW);
   }
    //*******************************

} 
}
 void Refresh_Msg (){
   lcd.setCursor(1, 1);
   lcd.print("                ");
   lcd.setCursor(1, 1);
   lcd.print(MsgOut);
 }
 void Test_Err_Led(){
  digitalWrite(41, LOW);
  digitalWrite(42, LOW);
  
  digitalWrite(22, LOW);
  digitalWrite(25, LOW);
  digitalWrite(44, LOW);
  digitalWrite(30, LOW);  
   digitalWrite(51, LOW);
  digitalWrite(Good_Part_Led, LOW);
  digitalWrite(Bad_Part_Led, HIGH);
  delay(500);
  digitalWrite(40, LOW);
  Continue = false;
    while(!digitalRead(InitButton) == true){
    delay(2000);
   }
   Continue = false;
 run_it = false;
 }
 void Test_Ok_Led(){
  digitalWrite(41, LOW);
  digitalWrite(42, LOW);
  
  digitalWrite(22, LOW);
  digitalWrite(25, LOW);
  digitalWrite(44, LOW);
  digitalWrite(30, LOW);  
  digitalWrite(Good_Part_Led, HIGH);
  digitalWrite(Bad_Part_Led, LOW);
   digitalWrite(51, LOW);
  delay(500);
  digitalWrite(40, LOW);
   
   while(!digitalRead(InitButton) == true){
    delay(2000);
   }
   Continue = false;
   run_it = false;
 }
 void Test_AnalogIn(float V_Need, int PIN, float Range, String TP_Msg){
   V_Spctd = V_Need;

   V_Rd= ((analogRead(PIN) * 5.0) /1023.0);
   //V_Rd = map(analogRead(PIN), 0, 1023, 0, 5);
    if( ((V_Spctd - Range) < (V_Rd)) && ((V_Rd)< (V_Spctd + Range ))){
      MsgOut = TP_Msg + (String) (": OK");
      Continue = true;
      //Serial.println(V_Rd);
      Serial.println(MsgOut);
      Serial.println(V_Rd);
      Serial.println();
      Refresh_Msg();

    }
    else {
      MsgOut = TP_Msg + (String) (": ERR");
      Refresh_Msg();
      Continue = false;  
      //Serial.println(PIN);
Serial.println(V_Rd);
Serial.println();
      Test_Err_Led();  
      
    }     
 }
  void Test_AnalogIn_TP6(float V_Need, int PIN, float Range, String TP_Msg){
   V_Spctd = V_Need;

   V_Rd= ((analogRead(PIN) * 5.0) /1023.0);
   //V_Rd = map(analogRead(PIN), 0, 1023, 0, 5);
    if( (V_Spctd - Range) < (V_Rd)){
      MsgOut = TP_Msg + (String) (": OK");
      Continue = true;
      //Serial.println(V_Rd);
      Serial.println(MsgOut);
      Serial.println(V_Rd);
      Serial.println();
      Refresh_Msg();

    }
    else {
      MsgOut = TP_Msg + (String) (": ERR");
      Refresh_Msg();
      Serial.println(MsgOut);
      Continue = false;  
      //Serial.println(PIN);
Serial.println(V_Rd);
Serial.println();
      Test_Err_Led();  
      
    }     
 }
