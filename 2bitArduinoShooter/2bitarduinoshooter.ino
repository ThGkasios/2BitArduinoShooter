  int LED1 = 2; //1st bullet spot
  int LED2 = 3; //2nd bullet spot
  int LED3 = 4; //3rd bullet spot
  int LED4 = 5; //4th bullet spot
  int LED5 = 6; // Enemy spot
  int LED6 = 7; // Success icon
  int INP = 8;  //"Fire" button

  int gauge;//Manage LED 1-4
  int my_in_switch;//Manage event Button Pressed

  int last_enemy_point;
  int next_enemy_point;
  int enemy_wither;

  int shot;
  
void set_enemy()
{
  if(millis()>next_enemy_point){
    last_enemy_point=millis();
    enemy_wither=last_enemy_point+random(1300,2500);
    next_enemy_point=last_enemy_point+random(3000,6000);
  }
}
  
void setup() {
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  pinMode(LED5, OUTPUT);
  pinMode(LED6, OUTPUT);
  pinMode(INP, INPUT);
  gauge=0;
  my_in_switch = 0;
  next_enemy_point=millis();
  shot=-1;
  
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, LOW);
    digitalWrite(LED4, LOW);
    digitalWrite(LED5, LOW);
    digitalWrite(LED6, LOW);
}

void loop() {
  if(shot!=-1) gauge=(millis()-shot)/200; else gauge=0;
  if(gauge>=1) digitalWrite(LED1, HIGH); else digitalWrite(LED1, LOW);
  if(gauge>=2) digitalWrite(LED2, HIGH); else digitalWrite(LED2, LOW);
  if(gauge>=3) digitalWrite(LED3, HIGH); else digitalWrite(LED3, LOW);
  if(gauge>=4) digitalWrite(LED4, HIGH); else digitalWrite(LED4, LOW);
  
  set_enemy();
  if(enemy_wither>=millis()) digitalWrite(LED5, HIGH); else digitalWrite(LED5, LOW);

  if(digitalRead(INP)== HIGH && my_in_switch == 0 && shot==-1)
  {
    shot=millis();
    my_in_switch = 1;
  }
  if(digitalRead(INP)==LOW && my_in_switch==1) my_in_switch=0;

  
  
  if(millis()-shot>=1000 && shot!=-1){
    
      digitalWrite(LED1, LOW);
      digitalWrite(LED2, LOW);
      digitalWrite(LED3, LOW);
      digitalWrite(LED4, LOW);
  if(enemy_wither>=millis())
  {
      digitalWrite(LED5, LOW);
      
      for(int i=0;i<5;i++)
      {
        if(i%2==0)
          digitalWrite(LED6, HIGH);
        else
          digitalWrite(LED6, LOW);
        delay(400);
      }
      
      gauge=0;
      shot=-1;
      delay(2000);
      digitalWrite(LED6, LOW);
      enemy_wither=millis();   
  }
  else
  {
      for(int i=0;i<5;i++)
      {
        if(i%2==0)
          digitalWrite(LED5, HIGH);
        else
          digitalWrite(LED5, LOW);
        delay(400);
      }
      gauge=0;
      shot=-1;
  }
  }
}
