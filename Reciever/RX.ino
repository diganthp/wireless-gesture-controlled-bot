##########################################################################################################################
###                                   Project: Wireless gesture controlled bot                                         ###   
###                                   Copyrights 2017 Wireless gesture controlled bot                                  ###
###                                   Date: April 2017                                                                 ###
###                                   Location: BMSCE, Bangalore                                                       ###
###                                   Creators: Anjana Niranjan, Diganth Prakash, Ramya MA                             ###
###                                   For more details, visit github                                                   ###
###                                   License : MIT open source license                                                ###
##########################################################################################################################

/*
Arduino Due + HC-06 (Bluetooth) -echo bluetooth data

Serial (Tx/Rx) communicate to PC via USB
Serial3 (Tx3/Rx3) connect to HC-06
HC-06 Rx - Due Tx3
HC-06 Tx - Due Rx3
HC-06 GND - Due GND
HC-06 VCC - Due 3.3V

*/
int LmotorUp = 22; //initialising Arduino port 10 be be called as LmotorUp
int LmotorDn = 24; //initialising Arduino port 11 be be called as LmotorDn
int RmotorUp = 26;  //initialising Arduino port 8 be be called as RmotorUp
int RmotorDn = 28;  //initialising Arduino port 9 be be called as RmotorDn

#define HC06 Serial3

void setup()
{
  delay(1000);
  Serial.begin(9600);
  HC06.begin(9600);
  pinMode(LmotorUp,OUTPUT);//Setting ports as OUTPUTS as they 
  pinMode(LmotorDn,OUTPUT);//supply signal values to motor driver
  pinMode(RmotorUp,OUTPUT);
  pinMode(RmotorDn,OUTPUT);
  Serial.println("<Robot name> Welcomes you"); //begining statement because i can :P
  
}

void loop()
{
  while(HC06.available())
  {
    int data = HC06.read();
    Serial.write(data);
    HC06.write(data);
    switch(data)
    {
     case 'F' : MoveF(); //Calling respective functions if mathced with case label 
     break;
     case 'B' : MoveB(); // here is it important to use '' as that stores the ASCII value is the letter in the variable
     break;
     case 'L' : MoveL(); // and hence we can use the int keyword
     break;
     case 'R' : MoveR();
     break;
     case 'S' : Stop();
     break;
     default : break;
    }
  } 
}

void MoveF()
{
  Serial.println("<Robot Name> Forward");
  digitalWrite(LmotorUp,LOW); //As said in video we are writing a Digital HIGH to the upper left pin of the motor driver
  digitalWrite(LmotorDn,HIGH); //As said in video we are writing a Digital LOW to the lower left pin of the motor driver
  digitalWrite(RmotorUp,HIGH); //As said in video we are writing a Digital HIGH to the upper right pin of the motor driver
  digitalWrite(RmotorDn,LOW); //As said in video we are writing a Digital LOW to the lower right pin of the motor driver
   // As a result the robot will move forward
}

void MoveB()
{
  Serial.println("<Robot Name> Backward");
  digitalWrite(LmotorUp,HIGH); //Reverse logic of above
  digitalWrite(LmotorDn,LOW);
  digitalWrite(RmotorUp,LOW);
  digitalWrite(RmotorDn,HIGH);
}

void MoveL()
{
  Serial.println("<Robot Name> Left");
  digitalWrite(LmotorUp,LOW); //we are completely stopping the left motor and allowing the right motor to move forward
  digitalWrite(LmotorDn,HIGH); //this will cause the robot to move left
  digitalWrite(RmotorUp,LOW);
  digitalWrite(RmotorDn,LOW);
}

void MoveR()
{
  Serial.println("<Robot Name> Right");
  digitalWrite(LmotorUp,LOW);//we are completely stopping the right motor and allowing the left motor to move forward
  digitalWrite(LmotorDn,LOW);//this will cause the robot to move right
  digitalWrite(RmotorUp,HIGH);
  digitalWrite(RmotorDn,LOW);
}

void Stop()
{
  Serial.println("<Robot Name> Stop");
  digitalWrite(LmotorUp,LOW);//Writing a digital LOW to all pins associated with movement of motor driver causes all motors to stop
  digitalWrite(LmotorDn,LOW);
  digitalWrite(RmotorUp,LOW);
  digitalWrite(RmotorDn,LOW);
}
