#include <Wire.h>
#include <RTClib.h>
#include <LiquidCrystal.h>
int sirene = A0;
int SELECT= 8; 
int INCR = 9 ; 
int SB = 11 ; 
int RSB = 0 ;
int RSE = 1; 

LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

RTC_DS1307 RTC;
byte CLOCHE[]={
  B00000,
  B00100,
  B01110,
  B01110,
  B01110,
  B11111,
  B01110,
  B00100
};
// mettre la phrase " Aguech Ahmed project " en mouvement dans LCD 
String scrollingmessage = "Projet siréne automatique  " ;
int ii = 0;
String toShow;
byte face[]={
  B00000,
  B01001,
  B01001,
  B00000,
  B00000,
  B10001,
  B01110,
  B00000
};

void setup() {
 //debut de transmission arduino <----> module RTC
pinMode(SELECT, INPUT_PULLUP);   // button1 is connected to pin 8 (SELECT)
pinMode(INCR, INPUT_PULLUP);  // button2 is connected to pin 9 (INCR)
pinMode(SE, INPUT_PULLUP);    // button3 is connected to pin 10  (Semaine educative )
pinMode(SB, INPUT_PULLUP);  // button4 is connected to pin 11  ( Semaine bloquer )
pinMode(RSB, INPUT_PULLUP);  //button5 is connected to pin 0 (Ramadhan semaine bloqué)
pinMode(RSE, INPUT_PULLUP); //button5 is connected to pin 1 (Ramadhan semaine educative)
pinMode(sirene, OUTPUT);  //Sound output  (sortie de la siréne 
pinMode(12, OUTPUT);    //led red 
pinMode(13, OUTPUT);   //led green
Serial.begin(9600);
Wire.begin();
RTC.begin ();//debut de transmission arduino <---> afficheur LCD 
lcd.begin(16, 2);
  lcd.setCursor(4,1);// fixe le curseur dans la colonne 4 , premier ligne  
  lcd.print("BONJOUR"); // afficher le mot "Bonjour " dand LCD  
  // création et affichage de l'émoji sur l'afficheur
  lcd.createChar(1, face);
  lcd.setCursor(2 ,1);
  lcd.write(byte(1));

  lcd.setCursor(12 ,1);
  lcd.write(byte(1));                                                                                                       
  delay(200);    // prendre un duré de 200 ms                                                                                      
  //lcd.home();
  
  lcd.setCursor(1, 0);                                                                      
  for (int timeCounter = 0; timeCounter < 26; timeCounter++) 
{                               
  lcd.home();
  lcd.setCursor(1, 0);                                                
  toShow = scrollingmessage.substring(ii,ii+16);                             
  lcd.print(toShow);                                            
  ii = ii + 1;  
  delay(300);                                                    
}   
 delay(1000);
lcd.clear();              

if (! RTC.isrunning()) {
 Serial.println("RTC n est pas en cours de fonctionnement!");
//  La ligne suivante fixe la date et l'heure du RTC avec les date et heur de compilation du sketch
RTC.adjust(DateTime(__DATE__, __TIME__));
 }
}
//////////////////////////////////////////////
void Speaker(){
  digitalWrite(sirene, LOW); //la pine numéro 9 prends 1 Logique ( 5 V )ce qui entrain la fonctionnement du siréne lorsque la condition du temps est vrai 
  delay(5000); // atteinte la diode aprés 5 s 
  digitalWrite(12, HIGH);
  delay(1000);
  digitalWrite(12, LOW);
  delay(1000);
  digitalWrite(13, HIGH);
  }
  ////////////////////////////////////////////
void loop() {
 DateTime now = RTC.now(); //synchronisation de transfert de donneé éntre le module et l'arduino 
lcd.setCursor(0, 0); // la ligne suivante fixe le curseur dans le premier ligne et la premier colonne 
  
    switch(now.dayOfTheWeek())//ce boucle permet d'integrer et ajouter le nom de jour avant la date 
    {
    case 1:  lcd.print("Lun:");  break;
    case 2:  lcd.print("Mar:");  break;
    case 3:  lcd.print("Merc:");  break;
    case 4:  lcd.print("Jeu:");  break;
    case 5:  lcd.print("Ven:"); break;
    case 6:  lcd.print("Sam:");  break;
    case 0:  lcd.print("Dim:");  break;
    default: lcd.print("Error");
    }

lcd.print(now.day(), DEC);//afficher sous format décimale le date synchroniser avec notre fuseaux horaire sous la forme "jour/month/année "
lcd.print('/');
lcd.print(now.month(), DEC);
lcd.print('/');
lcd.print(now.year(), DEC);
lcd.print(' ');
lcd.setCursor(0, 1);  //fixe le curseur dans la deuxiéme ligne , premier colonne
if (now.hour()<10)  // affichage de le temps sous la forme   " heur:minute:seconde  "
lcd.print('0');
lcd.print(now.hour(), DEC);
lcd.print(':');
if (now.minute()<10)
lcd.print('0');
lcd.print(now.minute(), DEC);
lcd.print(':');
if (now.second()<10)
lcd.print('0');
lcd.print(now.second(), DEC);
digitalWrite(13, HIGH);
//calendrier de la fonctionnement du siréne de Lundi jusqu'à Vendredi  
 while(!digitalRead(10)){                       // Wait until button (pin #8) released
  while(true){
    if ((now.month()==1)||(now.month()==2)||(now.month()==3)||(now.month()==4)||(now.month()==5)||(now.month()==6)||(now.month()==10)||(now.month()==11)||(now.month()==12)){
 
    if((now.dayOfTheWeek() == 1) || (now.dayOfTheWeek() == 2) || (now.dayOfTheWeek() == 3) || (now.dayOfTheWeek() == 4)|| (now.dayOfTheWeek() == 5))   
  
    { 
         if ((now.hour() == 7&& now.minute() == 50) || (now.hour() == 8 && now.minute() == 00) || (now.hour() == 8 && now.minute() == 55)|| (now.hour() == 9 && now.minute() == 00)||(now.hour() == 9 && now.minute() == 55 )||(now.hour() == 10 && now.minute() == 05 )||(now.hour() == 11 && now.minute() == 00)||(now.hour() == 11 && now.minute() == 05) ||(now.hour() == 12&& now.minute() == 00) ||(now.hour() == 13 && now.minute() == 25)||(now.hour() == 13 && now.minute() == 30) ||(now.hour() == 14 && now.minute() == 25)||(now.hour() == 14 && now.minute() == 30) ||(now.hour() == 15 && now.minute() == 25)|| (now.hour() == 15 && now.minute() == 35) ||(now.hour() == 16 && now.minute() == 25)|| (now.hour() == 16 && now.minute() == 30) ||(now.hour() == 17 && now.minute() == 30))
      {
        digitalWrite(13, LOW);
        delay(7000);
          digitalWrite(12, HIGH);
          delay(500);
          digitalWrite(12, LOW);
          delay(500);
          
         lcd.createChar(2, CLOCHE);// création de l'émoji siréne dans la deuxiéme ligne 10 éme colonne 
         lcd.setCursor(10 ,1);
         lcd.write(byte(2));
          delay(1000); // fixe une delais pour l'affichage de l'émoji de 10000 ms c-à-d 1 s
         Speaker();
        }
        else{
          digitalWrite(13, HIGH);
          digitalWrite(A0, LOW);
          digitalWrite(12, LOW);
          }
        }
        
       if((now.dayOfTheWeek() == 6))   
    { 
         if ((now.hour() == 7&& now.minute() == 50) || (now.hour() == 8 && now.minute() == 00) || (now.hour() == 8 && now.minute() == 55)|| (now.hour() == 9 && now.minute() == 00)||(now.hour() == 9 && now.minute() == 55 )||(now.hour() == 10 && now.minute() == 05 )||(now.hour() == 11 && now.minute() == 00)||(now.hour() == 11 && now.minute() == 05) ||(now.hour() == 12&& now.minute() == 00))
         {
          digitalWrite(13, LOW);
          delay(7000);
           digitalWrite(12, HIGH);
          delay(500);
          digitalWrite(12, LOW);
          delay(500);
          
         lcd.createChar(2, CLOCHE);
         lcd.setCursor(10 ,1);
         lcd.write(byte(2));
          
          delay(1000); // fixe une delais pour l'affichage de l'émoji de 10000 ms c-à-d 1 s
          Speaker();
        }
       
              else
                   {
      
           digitalWrite(13, HIGH);
          digitalWrite(A0, LOW);
          digitalWrite(12, LOW);
                   }
    }
    }
  
     if (now.month()== 11){
      if ((now.day() == 2 )|| (now.day()==3 ) || (now.day()== 4) ){
        digitalWrite(13, LOW);
        delay(20000);
        digitalWrite(13, HIGH);
        digitalWrite(12, HIGH);
        lcd.home();
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Bonne vacance ");
        lcd.setCursor(5,1);
        lcd.print(" à tous");
        delay(10000);
        
        }
        else {
          digitalWrite(13, HIGH);
          digitalWrite(12, LOW);
          lcd.setCursor(10, 1);
          lcd.print(' ');
         
          }
      }
    if ((now.month()== 12)){
     if ((now.day() == 24 )|| (now.day()==25 ) || (now.day()== 26) || (now.day()== 27) || (now.day()== 28) || (now.day()== 29)|| (now.day()== 30)|| (now.day()== 31) ){
      digitalWrite(13, LOW);
      delay(20000);
      digitalWrite(13, HIGH);
        digitalWrite(12, HIGH);
      lcd.home();
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Bonne vacance ");
        lcd.setCursor(5,1);
        lcd.print(" à tous");
        digitalWrite(12, LOW);
        delay(10000);
        }
        else {
          digitalWrite(13, HIGH);
          digitalWrite(12, LOW);
          lcd.setCursor(10, 1);
          lcd.print(' ');
         
          }
      
      }
    if ((now.month()== 1)){
     if ((now.day() == 01 )|| (now.day()==02 )|| (now.day()== 03)){
        digitalWrite(13, LOW);
        delay(20000);
        digitalWrite(13, HIGH);
        digitalWrite(12, HIGH);
        lcd.home();
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Bonne Vacance ");
        lcd.setCursor(5,1);
        lcd.print(" à tous");
        
        delay(10000);
        }
        else {
          digitalWrite(13, HIGH);
          digitalWrite(12, LOW);
          lcd.setCursor(10, 1);
          lcd.print(' ');
         
          }
      
      }  

    if ((now.month()== 2)){
     if ((now.day() == 4 )|| (now.day()==5 )|| (now.day()== 6)){
        digitalWrite(13, LOW);
        delay(20000);
        digitalWrite(13, HIGH);
        digitalWrite(12, HIGH);
      lcd.home();
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Bonne Vacance ");
        lcd.setCursor(5,1);
        lcd.print(" à tous");
        delay(10000);
        }
        else {
          digitalWrite(13, HIGH);
          digitalWrite(12, LOW);
          lcd.setCursor(10, 1);
          lcd.print(' ');
         
          }
      
      }
   if ((now.month()== 3)){
     if ((now.day() == 15 )||(now.day() == 16 )||(now.day() == 17 )||(now.day() == 18 )|| (now.day() == 19 )|| (now.day() == 20 )|| (now.day() == 21 )||(now.day() == 22 )|| (now.day() == 23 )||(now.day() == 24 ) ){
        digitalWrite(13, LOW);
        delay(20000);
        digitalWrite(13, HIGH);
        digitalWrite(12, HIGH);
      lcd.home();
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Bonne Vacance ");
        lcd.setCursor(5,1);
        lcd.print(" à tous");
        delay(10000);
        }
        else {
          digitalWrite(9, HIGH);
          digitalWrite(12, LOW);
          lcd.setCursor(10, 1);
          lcd.print(' ');
         
          }
      
      } 
    if((now.month()== 10)){
      if ((now.day() == 15 )){
        
        digitalWrite(13, LOW);
        delay(20000);
        digitalWrite(13, HIGH);
        digitalWrite(12, HIGH);
        lcd.home();
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Féte de l'Evacuation");
        delay(10000);
        }
        else {
          digitalWrite(13, HIGH);
          digitalWrite(12, LOW);
          lcd.setCursor(10, 1);
          lcd.print(' ');
         
          }
      
      }
    if((now.month()== 10)){
      if ((now.day() == 29 )){
        digitalWrite(13, LOW);
        delay(20000);
        digitalWrite(13, HIGH);
        digitalWrite(12, HIGH);
        lcd.home();
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Féte du Mouled ");
        delay(10000);
        }
        else {
          digitalWrite(13, HIGH);
          digitalWrite(12, LOW);
          lcd.setCursor(10, 1);
          lcd.print(' ');
         
          }
      
      }
     if((now.month()== 1)){
      if ((now.day() == 1 )){
       
        digitalWrite(13, LOW);
        delay(20000);
        digitalWrite(13, HIGH);
        digitalWrite(12, HIGH);
        lcd.home();
      
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Nouvelle année  ");
        delay(10000);
        }
        else {
          digitalWrite(13, HIGH);
          digitalWrite(12, LOW);
          lcd.setCursor(10, 1);
          lcd.print(' ');
         
          }
      
      }
      if((now.month()== 2))
      {
        
          if ((now.day() == 14 ))
      {
       
        digitalWrite(13, LOW);
        delay(20000);
        digitalWrite(13, HIGH);
        digitalWrite(12, HIGH);
        lcd.home();
      
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Féte de la révolution ");
        lcd.setCursor(5,1);
        lcd.print("Tunisienne  ");
      delay(10000);
        }
        else {
          digitalWrite(13, HIGH);
          digitalWrite(12, LOW);
          lcd.setCursor(10, 1);
          lcd.print(' ');
         
          }
      
      }
 if((now.month()== 3)){
      if ((now.day() == 20 )){
         
        digitalWrite(13, LOW);
        delay(20000);
        digitalWrite(13, HIGH);
        digitalWrite(12, HIGH);
        lcd.home();
      
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Féte de l'indépendance  ");
        delay(10000);
        }
        else {
          digitalWrite(13, HIGH);
          digitalWrite(12, LOW);
          lcd.setCursor(10, 1);
          lcd.print(' ');
         
          }
      
      }
   if((now.month()== 4)){
      if ((now.day() == 9 )){
        digitalWrite(13, LOW);
        delay(20000);
        digitalWrite(13, HIGH);
        digitalWrite(12, HIGH);
        lcd.home();
      
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Féte de Martyrs  ");
        delay(10000);
        }
        else {
          digitalWrite(13, HIGH);
          digitalWrite(12, LOW);
          lcd.setCursor(10, 1);
          lcd.print(' ');
         
          }
      
      }
    if((now.month()== 5)){
      if ((now.day() == 1 )){
       
        digitalWrite(13, LOW);
        delay(20000);
        digitalWrite(13, HIGH);
        digitalWrite(12, HIGH);
        lcd.home();
      
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Féte de Travail  ");
        delay(5000);
        }
        else {
          digitalWrite(13, HIGH);
          digitalWrite(12, LOW);
          lcd.setCursor(10, 1);
          lcd.print(' ');
         
          }
      
      }
    if((now.month()== 7)){
      if ((now.day() == 25 )){
        digitalWrite(13, LOW);
        delay(20000);
        digitalWrite(13, HIGH);
        digitalWrite(12, HIGH);
        lcd.home();
      
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Féte de la République  ");
        lcd.setCursor(0,1);
        lcd.print("Tunisie  ");
        
        delay(10000);
        }
        else {
          digitalWrite(9, HIGH);
          digitalWrite(12, LOW);
          lcd.setCursor(10, 1);
          lcd.print(' ');
         
          }
    
  
 }
}
 }
 ////////////////////////////boucle rammadhan//////////////////////////
 while(!digitalRead(1)){                       // Wait until button (pin #1) released
  while(true){
  digitalWrite(13, LOW);
  delay(20000);
  digitalWrite(13, HIGH);
  digitalWrite(12, HIGH);
  lcd.home();
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(" Ramadhan Karim ");
  delay(2000);
 
  if((now.dayOfTheWeek() == 1) || (now.dayOfTheWeek() == 2) || (now.dayOfTheWeek() == 3) || (now.dayOfTheWeek() == 4)|| (now.dayOfTheWeek() == 5))   
    { 
         if ((now.hour() == 7&& now.minute() == 50) || (now.hour() == 8 && now.minute() == 00) || (now.hour() == 8 && now.minute() == 45)||(now.hour() == 8 && now.minute() == 50)|| (now.hour() == 9 && now.minute() == 30)||(now.hour() == 9 && now.minute() == 40 )||(now.hour() == 10 && now.minute() == 30 )||(now.hour() == 11 && now.minute() == 20)||(now.hour() == 12&& now.minute() == 20) ||(now.hour() == 13 && now.minute() == 05)||(now.hour() == 13 && now.minute() == 10) ||(now.hour() == 13 && now.minute() == 55)||(now.hour() == 14 && now.minute() == 05) ||(now.hour() == 14 && now.minute() == 50)|| (now.hour() == 14 && now.minute() == 55) ||(now.hour() == 15 && now.minute() == 40))
         {
         lcd.createChar(2, CLOCHE);  // création de l'émoji siréne dans la deuxiéme ligne 10 éme colonne 
         lcd.setCursor(10 ,1);
         lcd.write(byte(2));
          
          delay(1000);   // fixe une delais pour l'affichage de l'émoji de 10000 ms c-à-d 10 s 
          Speaker();
           }
                 
       
           else  // si non la condition suivante "if " est faux , le programme reste fonctionne normale 
                   {
                
       digitalWrite(13, HIGH);
          digitalWrite(A0, LOW);
          digitalWrite(12, LOW);
                   }
         
        }
         if ((now.dayOfTheWeek()==6))
   {
    if ((now.hour() == 7&& now.minute() == 50) || (now.hour() == 8 && now.minute() == 00) || (now.hour() == 8 && now.minute() == 45)||(now.hour() == 8 && now.minute() == 50)|| (now.hour() == 9 && now.minute() == 30)||(now.hour() == 9 && now.minute() == 40 )||(now.hour() == 10 && now.minute() == 30 )||(now.hour() == 11 && now.minute() == 20))
         { 
          lcd.createChar(2, CLOCHE);  // création de l'émoji siréne dans la deuxiéme ligne 10 éme colonne 
         lcd.setCursor(10 ,1);
         lcd.write(byte(2));
          
          delay(1000);   // fixe une delais pour l'affichage de l'émoji de 10000 ms c-à-d 10 s 
          Speaker();
           }
                 
       
           else  // si non la condition suivante "if " est faux , le programme reste fonctionne normale 
                   {
                
       digitalWrite(13, HIGH);
          digitalWrite(A0, LOW);
          digitalWrite(12, LOW);
                   }
         }
}
 }

while(!digitalRead(11)){
  
      
         
        }
while(!digitalRead(0)){
  
      
         
        }
  }


  
        
