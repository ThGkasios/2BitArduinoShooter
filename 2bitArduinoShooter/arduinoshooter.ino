/*
	Hello, this is the Arduino 2-bit shooter.
	The goal is literally to press a button that fires a bullet. You win by shooting the enemy.
	This project is more of a simple application of Arduino in gaming.
	Of cource, feel free to use this project for your purposes, but a shoutout never hurts. :)
	Enjoy!  ~Tzouraguy

*/
  int LED1 = 2; //1st bullet spot
  int LED2 = 3; //2nd bullet spot
  int LED3 = 4; //3rd bullet spot
  int LED4 = 5; //4th bullet spot
  int LED5 = 6; // Enemy spot
  int LED6 = 7; // Success icon
  int INP = 8;  //"Fire" button

  int gauge;//Manage LED 1-4
  int my_in_switch;//Manage event Button Pressed

  //Game mechanics variables
  long last_enemy_point;
  long next_enemy_point;
  long enemy_wither;
  long shot;
  
  /**
  * Method that activates the enemy position as vulnerable after a period of downtime
  * by manipulating the global game variables. Bad OOC programming, but hey, it works.
  */
void set_enemy()
{
  if(millis()>next_enemy_point){
    last_enemy_point=millis();
    enemy_wither=last_enemy_point+random(1300,2500);
    next_enemy_point=last_enemy_point+random(3000,6000);
  }
}
  
  //Setup all pins and turn off all LEDs
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


//Apply display and game logic
void loop() {

	//Bullet display control block
  if(shot!=-1) gauge=(millis()-shot)/200; else gauge=0;
  if(gauge>=1) digitalWrite(LED1, HIGH); else digitalWrite(LED1, LOW);
  if(gauge>=2) digitalWrite(LED2, HIGH); else digitalWrite(LED2, LOW);
  if(gauge>=3) digitalWrite(LED3, HIGH); else digitalWrite(LED3, LOW);
  if(gauge>=4) digitalWrite(LED4, HIGH); else digitalWrite(LED4, LOW);
  
	//Enemy switching block
  set_enemy();
  if(enemy_wither>=millis()) digitalWrite(LED5, HIGH); else digitalWrite(LED5, LOW);

	//Button control block, which searches for a "button_is_pressed" event and creates the shot variable
  if(digitalRead(INP)== HIGH && my_in_switch == 0 && shot==-1)
  {
    shot=millis();
    my_in_switch = 1;
  }
  if(digitalRead(INP)==LOW && my_in_switch==1) my_in_switch=0;

  
	//"Bullet_reaches_enemy_position" event handling block
  if(millis()-shot>=1000 && shot!=-1){
      digitalWrite(LED1, LOW);
      digitalWrite(LED2, LOW);
      digitalWrite(LED3, LOW);
      digitalWrite(LED4, LOW);
  if(enemy_wither>=millis())//Victory
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
  else//Defeat
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
