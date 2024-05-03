const int trigpin1=13; const int echopin1=12; const int buzzer1=8; const int led1=4;
const int trigpin2=11; const int echopin2=10; const int buzzer2=7; const int led2=2;
float duration1,distance1,duration2,distance2; void setup()
{

Serial.begin(9600); pinMode(trigpin1,OUTPUT); pinMode(echopin1,INPUT); pinMode(buzzer1,OUTPUT); pinMode(led1,OUTPUT); pinMode(trigpin2,OUTPUT); pinMode(echopin2,INPUT); pinMode(buzzer2,OUTPUT); pinMode(led2,OUTPUT);
}

void loop()

{

// serial 1 digitalWrite(trigpin1,LOW); delayMicroseconds(2); digitalWrite(trigpin1,HIGH); delayMicroseconds(10); digitalWrite(trigpin1,LOW); duration1= pulseIn(echopin1,HIGH); distance1=(duration1*0.034)/2;

Serial.print(distance1); Serial.println("cm");
// serial2 digitalWrite(trigpin2,LOW); delayMicroseconds(2); digitalWrite(trigpin2,HIGH); delayMicroseconds(10); digitalWrite(trigpin2,LOW); duration2= pulseIn(echopin2,HIGH); distance2=(duration2*0.034)/2; Serial.print(distance2); Serial.println("cm");
// distance 1 if((distance1>15&& distance1<=20) && (distance2>15 && distance2<=20))
{

digitalWrite(led2,HIGH); delay(100); digitalWrite(led2,LOW); delay(100); digitalWrite(buzzer2,LOW); Serial.println("alert");
digitalWrite(led1,HIGH);

delay(100); digitalWrite(led1,LOW); delay(100); digitalWrite(buzzer1,LOW); Serial.println("alert");
}

else if((distance1>15)&&(distance1<=20))

{

digitalWrite(led2,HIGH); delay(100); digitalWrite(led2,LOW); delay(100); digitalWrite(buzzer2,LOW);
Serial.println("alret!!Maintain distance");

}

else if((distance2>15)&&(distance2<=20))

{

digitalWrite(led1,HIGH); delay(100); digitalWrite(led1,LOW);

delay(100); digitalWrite(buzzer1,LOW);
Serial.println("alret!!Maintain distance");

}

else if((distance1>0&& distance1<=15)&&(distance2>0&&distance2<=15))

{

digitalWrite(buzzer1,HIGH); delay(100); digitalWrite(led1,HIGH); delay(100);
Serial.println("collision alert!!!Slow down the vehicle both 2."); digitalWrite(buzzer2,HIGH);
delay(100); digitalWrite(led2,HIGH); delay(100);
Serial.println("collision alert!!!Slow down the vehicle both 1.");

}

else if(distance1>15 &&(distance2<=15 &&distance2>0))

{

digitalWrite(buzzer1,HIGH);
delay(100); digitalWrite(led1,HIGH);

delay(100);

Serial.println("collision alert!!!Slow down the vehicle distance2."); digitalWrite(buzzer2,LOW);
digitalWrite(led2,LOW);

}

else if(distance2>15 &&(distance1<=15 &&distance1>0))

{

digitalWrite(buzzer2,HIGH); delay(100); digitalWrite(led2,HIGH); delay(100);
Serial.println("collision alert!!!Slow down the vehicle distance1."); digitalWrite(buzzer1,LOW);
digitalWrite(led1,LOW);

}

else if((distance2>=16 && distance2<=20) && (distance1<=15 && distance1>=0 ))
{

digitalWrite(led1,HIGH); delay(100); digitalWrite(led1,LOW);

delay(100); digitalWrite(buzzer1,LOW);
Serial.println("alret!!Maintain distance"); digitalWrite(buzzer2,HIGH);
delay(100); digitalWrite(led2,HIGH); delay(100);
Serial.println("collision alert!!!Slow down the vehicle distance2.");

}

else if((distance1>=16 && distance1<=20) && (distance2<=15 && distance2>=0 ))
{

digitalWrite(led1,HIGH); delay(100); digitalWrite(led1,LOW); delay(100); digitalWrite(buzzer1,LOW);
Serial.println("alret!!Maintain distance"); digitalWrite(buzzer2,HIGH);
delay(100);

digitalWrite(led2,HIGH);

delay(100);

Serial.println("collision alert!!!Slow down the vehicle distance2.");

}

else{ digitalWrite(buzzer1,LOW); digitalWrite(led1,LOW); delay(100); digitalWrite(buzzer2,LOW); digitalWrite(led2,LOW); delay(100);
Serial.println("safe,no vehicle ahead");

}

delay(100);

}
