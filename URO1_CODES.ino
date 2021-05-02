
#include <Wire.h>
#include "SparkFunISL29125.h"
#include <GSM.h>

// The following is pin number for sim cards
#define PINNUMBER "" 
GSM gsm;
GSM_SMS sms;
SFE_ISL29125 RGB_sensor;

const int stepPin = 3;
const int dirPin = 4;

unsigned int Red;
unsigned int Blue; 
unsigned int Green;

double delay_time[6]={10000,5000,15000,1000,60000,0};
int steps[6]={32,16,32,16,48,0};


void colour(int &r,int &g,int &b);
void setup() {
  // To check whether GSM module is communicating or not
  boolean x=true;
  while(x)
  {
    if(gsm.begin(PINNUMBER)== GSM_READY)
    {x = false;}
  }
  // Initializing RGB sensors
  RGB_sensor.init();


int Red,Blue,Green;
int countr,countb,countg;

delay(30000);

for(int x = 0; x < 16; x++) 
{
//16-> no. of step required to move b/w each colour
digitalWrite(stepPin,HIGH);
delayMicroseconds(500);
digitalWrite(stepPin,LOW);
delayMicroseconds(500);//we can control the speed by delay b/w each pulse by varying delay time
}


for(int y=0; y<6; y++)
{
for(int i=0;i<10;i++)
{
Red =0;
Blue=0;
Green=0;
colour(Red,Green,Blue);
countr+=Red;
countb+=Blue;
countg+=Green;
}
Red = countr/10;                               //by taking average of 10 values we increase the accuracy
Blue = countb/10;
Green = countg/10;
  if(y==0)
  {
    // Glucose time for 30 seconds

if(16<Red<36 && 212<Green<232 && 173<Blue<193) 
{
  sms.beginSMS("9746751054");                  //send sms to this number
  sms.print("test is negative");               //text to be sent
  sms.endSMS();}                               //stop the connection 
  else if(16<Red<36 && 212<Green<232 && 33<Blue<53) 
  {
  sms.beginSMS("9746751054");
  sms.print("low levels of blood glucose");
  sms.endSMS();} 
    else if(5<Red<25 && 175<Green<195 && 34<Blue<54) 
    {
  sms.beginSMS("9746751054");
  sms.print("Moderate levels of glucose");
  sms.endSMS();}
      else if(143<Red<163 && 143<Green<163 && 0<=Blue<10) 
      {
  sms.beginSMS("9746751054");
  sms.print("good level of glucose");
  sms.endSMS();}
        else if(127<Red<147 && 127<Green<147 && 6<Blue<26) 
        {
  sms.beginSMS("9746751054");
  sms.print("high levels of glucose");
  sms.endSMS();}
          else if(143<Red<163 && 66<Green<86 && 0<=Blue<10) 
          {
  sms.beginSMS("9746751054");
  sms.print("Very high levels of glucose");
  sms.endSMS();}
  }
  else if (y==1)
  {
    // ketones after 40 second
if(0<Red<10 && 70<Green<90 && 33<Blue<53) {
  sms.beginSMS("9746751054");
  sms.print("-ve test for ketones");
  sms.endSMS();
  } 
  else if(250<Red<255 && 150<Green<170 && 112<Blue<132) 
  {
  sms.beginSMS("9746751054");
  sms.print("trace levels of ketones");
  sms.endSMS();} 
    else if(245<Red<255 && 118<Green<138 && 104<Blue<120) 
    {
  sms.beginSMS("9746751054");
  sms.print("Small levels of ketones");
  sms.endSMS();}
      else if(222<Red<242 && 63<Green<83 && 45<Blue<65) 
      {
  sms.beginSMS("9746751054");
  sms.print("Moderate levels of glucose");
  sms.endSMS();}
        else if(181<Red<201 && 41<Green<61 && 26<Blue<46) 
        {
  sms.beginSMS("9746751054");
  sms.print("Large levels of glucose");
  sms.endSMS();}
          else if(105<Red<125 && 4<Green<24 && 0<Blue<10) 
          {
  sms.beginSMS("9746751054");
  sms.print("Very large levels of glucose");
  sms.endSMS();}

  }

else if(y==2)
    {
      // specific gravity after 45 seconds

if(0<Red<10 && 70<Green<90 && 33<Blue<53) 
{
  sms.beginSMS("9746751054");
  sms.print("Normal specific density ,s=1");
  sms.endSMS();}
  else if(20<Red<40 && 140<Green<160 && 80<Blue<100) 
  {/*1.005*/
  sms.beginSMS("9746751054");
  sms.print("Normal specific gravity ,s=1.005");
  sms.endSMS();}
    else if(25<Red<45 && 145<Green<165 && 60<Blue<80) 
    {
  sms.beginSMS("9746751054");
  sms.print("Average value of specific gravity,s=1.010");
  sms.endSMS();}
      else if(197<Red<217 && 132<Green<152 && 25<Blue<45) 
      {
  sms.beginSMS("9746751054");
  sms.print("moderate value of specific gravity ,s=1.015");
  sms.endSMS();}
        else if(145<Red<165 && 195<Green<215 && 40<Blue<60)
        {
  sms.beginSMS("9746751054");
  sms.print("Moderate value of specific gravity ,s=1.020");
  sms.endSMS();}
          else if(210<Red<230 && 155<Green<175 && 20<Blue<40)
          {/*1.030*/
  sms.beginSMS("9746751054");
  sms.print("High value of specific density ,s=1.030");
  sms.endSMS();}
      
    }

else if(y==3)
{
  // pH takes 60 seconds

if(245<Red<=255 && 100<Green<120 && 0<=Blue<10) 
{
  sms.beginSMS("9746751054");
  sms.print("Highly acidic, pH = 5");
  sms.endSMS();}
  else if(245<Red<=255 && 180<Green<200 && 30<Blue<50) 
  {
  sms.beginSMS("9746751054");
  sms.print("slightly acidic, pH = 6.5");
  sms.endSMS();}
    else if(90<Red<110 && 190<Green<210 && 50<Blue<70) 
    {
  sms.beginSMS("9746751054");
  sms.print("slightly basic, pH = 7.5");
  sms.endSMS();}   //check this specially
      else if(0<Red<10 && 165<Green<190 && 165<Blue<190) 
      {
  sms.beginSMS("9746751054");
  sms.print("Basic, pH = 8");
  sms.endSMS();}   
        else if(35<Red<60 && 145<Green<165 && 145<Blue<165)
        {
  sms.beginSMS("9746751054");
  sms.print("Highly Basic, pH=8.5");
  sms.endSMS();}
  
}

else if(y==4)
{
  //protein takes 60 seconds

if(200<Red<225 && 245<Green<265 && 145<Blue<165) 
{
  sms.beginSMS("9746751054");
  sms.print("-VE test");
  sms.endSMS();}
  else if(180<Red<200 && 225<Green<245 && 115<Blue<135) 
  {
  sms.beginSMS("9746751054");
  sms.print("Trace amounts of protein");
  sms.endSMS();}
    else if(135<Red<155 && 190<Green<210 && 45<Blue<65) 
    {
  sms.beginSMS("9746751054");
  sms.print("Moderate amounts of protein, 30+");
  sms.endSMS();}
      else if(5<Red<25 && 215<Green<235 && 185<Blue<205) 
      {
  sms.beginSMS("9746751054");
  sms.print("Good amounts of protein, 100++");
  sms.endSMS();}
        else if(25<Red<45 && 190<Green<210 && 165<Blue<185)
        {
  sms.beginSMS("9746751054");
  sms.print("High levels of proteins, 300+++");
  sms.endSMS();}
          else if(5<Red<25 && 160<Green<180 && 150<Blue<170)
          {
  sms.beginSMS("9746751054");
  sms.print("Very high levels of proteins, 2000+++++");
  sms.endSMS();}
}

else if(y==5)
{
  //leukocytes takes 120 seconds
if(235<Red<260 && 240<Green<265 && 185<Blue<210) 
{
  sms.beginSMS("9746751054");
  sms.print("Negative test");
  sms.endSMS();}

  else if(215<Red<235 && 225<Green<245 && 160<Blue<180) 
  {
  sms.beginSMS("9746751054");
  sms.print("Trace amounts of leukocytes");
  sms.endSMS();}
    else if(195<Red<215 && 150<Green<175 && 175<Blue<200) 
    {
  sms.beginSMS("9746751054");
  sms.print("Moderate amounts of leukocytes");
  sms.endSMS();}
      else if(185<Red<205 && 115<Green<135 && 155<Blue<175) 
      {
  sms.beginSMS("9746751054");
  sms.print("Large amounts of leukocytes");
  sms.endSMS();}
}

delay(delay_time[y]);

for(int x = 0; x < steps[y]; x++) 
{
//16-> no. of step required to move b/w each colour
digitalWrite(stepPin,HIGH);
delayMicroseconds(500);
digitalWrite(stepPin,LOW);
delayMicroseconds(500);//we can control the speed by delay b/w each pulse

}
}
digitalWrite(dirPin,LOW);
for(int x = 0; x < 144; x++) {
//144-> no. of steps required to take out dipstick
digitalWrite(stepPin,HIGH);
delayMicroseconds(500);
digitalWrite(stepPin,LOW);
delayMicroseconds(500);
}
                  
}


void colour(int &r,int &g,int &b)
{

 unsigned int Red = RGB_sensor.readRed();
 unsigned int Blue = RGB_sensor.readBlue();
 unsigned int Green = RGB_sensor.readGreen();

//  lowest and heighest values of Red Green and Blue is calculated by calibrating the sensor with black and white light
r = map(Red, 200, 3800, 0 ,255);
g = map(Blue, 500, 4000, 0, 255);
b = map(Green, 700,5000, 0, 255);

}
void loop()
{}
