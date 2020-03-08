#include<SoftwareSerial.h>

SoftwareSerial mySerial(9, 10);

int sensor=7; //The output of PIR sensor connected to pin 7
//int push_switch=6; // push button switch connected to pin 6
int led=13;
int buzzer=12;// buzzer connected at pin 8
int sensor_value; //variable to hold read sensor value
int sms_count=0;

void setup()
{ 
 // configuring pin 7 as Input
 pinMode(sensor,INPUT);
 // configuring pin 6 as Input
//pinMode(push_switch,INPUT);
// configuring pin 13 as OUTPUT
pinMode(led,OUTPUT);
// configuring pin 12 as OUTPUT
pinMode(buzzer,OUTPUT);
mySerial.begin(9600);
}

void loop()
{
// subroutine to check sensor status and activation of outputs
Check_Burglar();
 // subroutine to check if alarm reset switch pressed or not
Check_Reset();
}

void Check_Burglar()
{
 // Reading sensor value from pin 7
 sensor_value=digitalRead(sensor);
 // Checking if PIR sensor sends a HIGH signal to Arduino
 if(sensor_value==HIGH)
{
  digitalWrite(led,HIGH);// Activating the buzzer 
  tone(buzzer,500);
  
  while(sms_count<2) //Number of SMS Alerts to be sent limited at 3
    {  
      SendTextMessage(); // Function to send AT Commands to GSM module
    }
    delay(500);
    digitalWrite(led,LOW);
    digitalWrite(buzzer,LOW);
    noTone(buzzer);
}
else{
  digitalWrite(led,LOW);
    digitalWrite(buzzer,LOW);
  }
 }

void Check_Reset()
{
//if(digitalRead(push_switch==HIGH)
//Checking if pushbutton was pressed 
{
//digitalWrite(buzzer,LOW); 
// turning OFF the buzzer 
sms_count=0; 
// Reactivating the SMS Alert Facility
}

}

void SendTextMessage()
{
  //To send SMS in Text Mode
  mySerial.println("AT+CMGF=1");
  delay(500);
  mySerial.println("AT+CMGS=\"+919228801110\"\r"); // changing to the phone number  
  delay(500);
  //the content of the message
  mySerial.println(" Intruder alert! Intruder alert! Intruder alert!");
  delay(200);
 //the stopping character
  mySerial.println((char)26);
  delay(500);
  sms_count++;
}
