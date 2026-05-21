char t;
int ena = 10;
int enb = 11;
int in1 = 7;
int in2 = 8;
int in3 = 9;
int in4 = 12;
 
void setup() {
pinMode(ena,OUTPUT);
pinMode(enb,OUTPUT);

pinMode(in1,OUTPUT);   //left motors
pinMode(in2,OUTPUT);   //left motors

pinMode(in3,OUTPUT);   //right motors
pinMode(in4,OUTPUT);   //right motors

pinMode(9,OUTPUT);   //Led
Serial.begin(9600);

digitalWrite(ena,HIGH);
digitalWrite(enb,HIGH);
 
}
 
void loop() {
if(Serial.available()){
  t = Serial.read();
  Serial.println(t);
}


if(t == 'F'){            //move forward(all motors rotate in forward direction)
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);
  
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);
}
 
else if(t == 'B'){      //move reverse (all motors rotate in reverse direction)
  digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH);
  
  digitalWrite(in3,LOW);
  digitalWrite(in4,HIGH);
  
  
  
}
 
else if(t == 'L'){      //turn right (left side motors rotate in forward direction, right side motors doesn't rotate)
  digitalWrite(in1,LOW);
  digitalWrite(in2,LOW);
  
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);
  
}
 
else if(t == 'R'){      //turn left (right side motors rotate in forward direction, left side motors doesn't rotate)
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);
  
  digitalWrite(in4,LOW);
  digitalWrite(in3,LOW);
}
 
else if(t == 'S'){      //STOP (all motors stop)
  digitalWrite(in1,LOW);
  digitalWrite(in2,LOW);
  
  digitalWrite(in3,LOW);
  digitalWrite(in4,LOW);
 }
else if(t == 'RP') {   //To rotate car at a point(in right direction). For this left motors will rotate in forward direction
                      // and right motors will rotate in backward direction.
  
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);
  
  digitalWrite(in3,LOW);
  digitalWrite(in4,HIGH);
}
else if(t == 'LP') {   //To rotate car at a point(in left direction). For this right motors will rotate in forward direction
                      // and left motors will rotate in backward direction.
  
  digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH);
  
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);
}
delay(100);
}
