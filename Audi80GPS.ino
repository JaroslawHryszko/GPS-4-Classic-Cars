#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include <SevenSegmentTM1637.h>
#include <stdlib.h>

/*
   This sample code demonstrates just about every built-in operation of TinyGPS++ (TinyGPSPlus).
   It requires the use of SoftwareSerial, and assumes that you have a
   4800-baud serial GPS device hooked up on pins 4(rx) and 3(tx).
*/
static const int RXPin = 4, TXPin = 3;
static const uint32_t GPSBaud = 9600;



boolean zatrzask = false; // czy klawisz wciaz jest wcisniety

int mode = 0;


/*

0 - predkosc
1 - kierunek jazdy
2 - wspolrzedne
3 - wspolrzedne dokladne
4 - wysokosc
5 - kierunek do domu
6 - odleglosc od domu
7 - odleglosc od UJ
8 - odeleglosc od Pucka
9 - odleglosc od wspolrzednych zapamietanych
10 - kierunek do wspolrzednych zapamietanych
11 - predkosc maksymalna od ostatniego uruchomienia


*/

int max_mode = 11; // ostatnia mozliwa opcja

double LONDON_LAT = 50.669977, LONDON_LON = 16.158397;
double LOCAL_LAT = 50.669977, LOCAL_LON = 16.158397;
double predkosc = 0;
double MAX_SPEED = 0;

const int buttonPinUp = 8;     // the number of the pushbutton pin
const int buttonPinDown = 7;     // the number of the pushbutton pin
const int buttonPinReset = 6;     // the number of the pushbutton pin

int buttonStateUp = 0;
int buttonStateDown = 0;
int buttonStateReset = 0;

char buff[10];  // bufor do wyswietlania

boolean czy_fix = false; //czy jest fix sat

const byte PIN_CLK = 11;   // define CLK pin (any digital pin)
const byte PIN_DIO = 12;   // define DIO pin (any digital pin)
SevenSegmentTM1637    display(PIN_CLK, PIN_DIO);


// The TinyGPS++ object
TinyGPSPlus gps;

// The serial connection to the GPS device
SoftwareSerial ss(RXPin, TXPin);

// For stats that happen every 5 seconds
unsigned long last = 0UL;

void setup()
{
  
    pinMode(buttonPinUp, INPUT);
    pinMode(buttonPinDown, INPUT);
    pinMode(buttonPinReset, INPUT);
  
  
  // Serial.begin(115200);   // z kodu GPS
  Serial.begin(9600);         //  z kodu 7-segment initializes the Serial connection @ 9600 baud
  ss.begin(GPSBaud);
  
  
  
  Serial.println(F("KitchenSink.ino"));
  Serial.println(F("Demonstrating nearly every feature of TinyGPS++"));
  Serial.print(F("Testing TinyGPS++ library v. ")); Serial.println(TinyGPSPlus::libraryVersion());
  Serial.println(F("by Mikal Hart"));
  Serial.println();

  display.begin();            // initializes the display
  display.setBacklight(100);  // set the brightness to 100 %
      display.print("DZIEN DOBRY  =]");
 
 /*
             delay(1000);
                         display.print("CZEKAM NA GPS");
             delay(1000);
      display.clear();
 */
}

void loop()
{
  buttonStateUp = digitalRead(buttonPinUp);
  buttonStateDown = digitalRead(buttonPinDown);
  buttonStateReset = digitalRead(buttonPinReset);  
  
  /*
  
  if (zatrzask == false && buttonStateUp == HIGH)
  {
    zatrzask = true;
    if (mode == max_mode) { mode = 0; 
    wyswietltryb(mode);
    }
    else
    { mode++; 
    wyswietltryb(mode);
    }
  }
  else
  {
  zatrzask = false;
  } 
 
 */ 
  
  if (zatrzask == false && buttonStateDown == HIGH)
  {
    zatrzask = true;
    if (mode == 0) { mode = max_mode; 
    wyswietltryb(mode);
    }
    else
    { mode--; 
    wyswietltryb(mode);
    }
  }
  else
  {
  zatrzask = false;
  }  
  
  
  // Dispatch incoming characters
  while (ss.available() > 0)
    gps.encode(ss.read());

  if (gps.location.isUpdated())
  {
    
    czy_fix = true;
    
    Serial.print(F("LOCATION   Fix Age="));
    Serial.print(gps.location.age());
    Serial.print(F("ms Raw Lat="));
    Serial.print(gps.location.rawLat().negative ? "-" : "+");
    Serial.print(gps.location.rawLat().deg);
    Serial.print("[+");
    Serial.print(gps.location.rawLat().billionths);
    Serial.print(F(" billionths],  Raw Long="));
    Serial.print(gps.location.rawLng().negative ? "-" : "+");
    Serial.print(gps.location.rawLng().deg);
    Serial.print("[+");
    Serial.print(gps.location.rawLng().billionths);
    Serial.print(F(" billionths],  Lat="));
    Serial.print(gps.location.lat(), 6);
    Serial.print(F(" Long="));
    Serial.println(gps.location.lng(), 6);


// quick fix

/*
    
   if (zatrzask == false && buttonStateReset == HIGH)
  {
    zatrzask = true;
    LOCAL_LAT = gps.location.lat();
    LOCAL_LON = gps.location.lng();
   display.print("WSPOLRZEDNE ZAPAMIETANE");
   delay(1000);
   display.clear();
  }
  else
  {
  zatrzask = false;
  }  
    
  */ 
    
        if (mode == 2) 
    {
          dtostrf(gps.location.lat(), 4, 1, buff);  //4 is mininum width, 0 is precision
          display.print(buff);
          delay(1000);
          dtostrf(gps.location.lng(), 4, 1, buff);  //4 is mininum width, 0 is precision
          display.print(buff);
          delay(1000);          
          
    }
    
    
            if (mode == 3) 
    {
          dtostrf(gps.location.lat(), 7, 4, buff);  //4 is mininum width, 0 is precision
          display.print(buff);
          delay(1000);
          dtostrf(gps.location.lng(), 7, 4, buff);  //4 is mininum width, 0 is precision
          display.print(buff);
          delay(1000);          
          
    }
    
    
    
  }

  else if (gps.date.isUpdated())
  {
    Serial.print(F("DATE       Fix Age="));
    Serial.print(gps.date.age());
    Serial.print(F("ms Raw="));
    Serial.print(gps.date.value());
    Serial.print(F(" Year="));
    Serial.print(gps.date.year());
    Serial.print(F(" Month="));
    Serial.print(gps.date.month());
    Serial.print(F(" Day="));
    Serial.println(gps.date.day());
  }

  else if (gps.time.isUpdated())
  {
    Serial.print(F("TIME       Fix Age="));
    Serial.print(gps.time.age());
    Serial.print(F("ms Raw="));
    Serial.print(gps.time.value());
    Serial.print(F(" Hour="));
    Serial.print(gps.time.hour());
    Serial.print(F(" Minute="));
    Serial.print(gps.time.minute());
    Serial.print(F(" Second="));
    Serial.print(gps.time.second());
    Serial.print(F(" Hundredths="));
    Serial.println(gps.time.centisecond());
  }

  else if (gps.speed.isUpdated())
  {
    Serial.print(F("SPEED      Fix Age="));
    Serial.print(gps.speed.age());
    Serial.print(F("ms Raw="));
    Serial.print(gps.speed.value());
    Serial.print(F(" Knots="));
    Serial.print(gps.speed.knots());
    Serial.print(F(" MPH="));
    Serial.print(gps.speed.mph());
    Serial.print(F(" m/s="));
    Serial.print(gps.speed.mps());
    Serial.print(F(" km/h="));
    Serial.println(gps.speed.kmph());
    
    predkosc = gps.speed.kmph();
    
    if (predkosc > MAX_SPEED)
    { MAX_SPEED = predkosc; }
    
    
    if (mode == 0) 
    {
          dtostrf(gps.speed.kmph(), 4, 0, buff);  //4 is mininum width, 0 is precision
          display.print(buff);
    }
    
        if (mode == 11) 
    {
          dtostrf(MAX_SPEED, 4, 0, buff);  //4 is mininum width, 0 is precision
          display.print(buff);
    }
    
    
  }

  else if (gps.course.isUpdated())
  {
    Serial.print(F("COURSE     Fix Age="));
    Serial.print(gps.course.age());
    Serial.print(F("ms Raw="));
    Serial.print(gps.course.value());
    Serial.print(F(" Deg="));
    Serial.println(gps.course.deg());
    
 
    
    
  }

  else if (gps.altitude.isUpdated())
  {
    Serial.print(F("ALTITUDE   Fix Age="));
    Serial.print(gps.altitude.age());
    Serial.print(F("ms Raw="));
    Serial.print(gps.altitude.value());
    Serial.print(F(" Meters="));
    Serial.print(gps.altitude.meters());
    Serial.print(F(" Miles="));
    Serial.print(gps.altitude.miles());
    Serial.print(F(" KM="));
    Serial.print(gps.altitude.kilometers());
    Serial.print(F(" Feet="));
    Serial.println(gps.altitude.feet());
    

    
        if (mode == 4) 
    {
          dtostrf(gps.altitude.meters(), 4, 0, buff);  //4 is mininum width, 0 is precision
          display.print(buff);
    }
    
    
  }

  else if (gps.satellites.isUpdated())
  {
    Serial.print(F("SATELLITES Fix Age="));
    Serial.print(gps.satellites.age());
    Serial.print(F("ms Value="));
    Serial.println(gps.satellites.value());
  }

  else if (gps.hdop.isUpdated())
  {
    Serial.print(F("HDOP       Fix Age="));
    Serial.print(gps.hdop.age());
    Serial.print(F("ms raw="));
    Serial.print(gps.hdop.value());
    Serial.print(F(" hdop="));
    Serial.println(gps.hdop.hdop());
  }

  else if (millis() - last > 5000)
  {
    Serial.println();
    if (gps.location.isValid())
    {
  /*
      
      6 - odleglosc od domu
7 - odleglosc od UJ
8 - odeleglosc od Pucka


*/
      
      
      
      
      if (mode == 7) { 
      LONDON_LAT = 50.030937;
      LONDON_LON = 19.905913;  // UJ
      }
       else if (mode == 8) { 
       LONDON_LAT = 54.722512;
       LONDON_LON = 18.417184; // puck
      } 
      else if (mode == 9 || mode == 10)
      {
      LONDON_LAT = LOCAL_LAT;
      LONDON_LON = LOCAL_LON; // temp
      }
      else
      {
      LONDON_LAT = 50.669977;
      LONDON_LON = 16.158397; // rozana
      }
      
      double distanceToLondon =
        TinyGPSPlus::distanceBetween(
          gps.location.lat(),
          gps.location.lng(),
          LONDON_LAT, 
          LONDON_LON);
      double courseToLondon =
        TinyGPSPlus::courseTo(
          gps.location.lat(),
          gps.location.lng(),
          LONDON_LAT, 
          LONDON_LON);

      Serial.print(F("LONDON     Distance="));
      Serial.print(distanceToLondon/1000, 6);
      Serial.print(F(" km Course-to="));
      Serial.print(courseToLondon, 6);
      Serial.print(F(" degrees ["));
      Serial.print(TinyGPSPlus::cardinal(courseToLondon));
      Serial.println(F("]"));
      

    
         if (mode == 5) 
    {
          display.print(TinyGPSPlus::cardinal(courseToLondon));
    }
    
             if (mode == 9) 
    {
          
          dtostrf(courseToLondon, 4, 0, buff);  //4 is mininum width, 0 is precision
          display.print(buff);
    }
      
      
           //if (mode = 6) 
           if (mode == 6 || mode == 7 || mode == 8 || mode == 9) 
    {
          dtostrf(distanceToLondon/1000, 4, 0, buff);  //4 is mininum width, 0 is precision
          display.print(buff);
    }
      
      
    }

    Serial.print(F("DIAGS      Chars="));
    Serial.print(gps.charsProcessed());
    Serial.print(F(" Sentences-with-Fix="));
    Serial.print(gps.sentencesWithFix());
    Serial.print(F(" Failed-checksum="));
    Serial.print(gps.failedChecksum());
    Serial.print(F(" Passed-checksum="));
    Serial.println(gps.passedChecksum());

    if (gps.charsProcessed() < 10)
      Serial.println(F("WARNING: No GPS data.  Check wiring."));
      

     
   //   if (!czy_fix) {display.print(gps.passedChecksum()); }
      

    last = millis();
    Serial.println();
  }
}

/*

0 - predkosc
1 - kierunek jazdy
2 - wspolrzedne
3 - wspolrzedne dokladne
4 - wysokosc
5 - kierunek do domu
6 - odleglosc od domu
7 - odleglosc od UJ
8 - odeleglosc od Pucka
9 - odleglosc od wspolrzednych zapamietanych
10 - kierunek do wspolrzednych zapamietanych
11 - predkosc maksymalna od ostatniego uruchomienia


*/

void wyswietltryb(int mode)
{
  display.clear();
  switch (mode)
  {
    case 0:
      display.print("PREDKOSC");
    break;
    case 1:
      display.print("KIERUNEK JAZDY");
    break;
    case 2:
      display.print("WSPOLRZEDNE ZGRUBNE");
    break;
    case 3:
      display.print("WSPOLRZEDNE DOKLADNE");
    break;
    case 4:
      display.print("WYSOKOSC");
    break;
    case 5:
      display.print("DOM-KIERUNEK");
    break;
    case 6:
      display.print("DOM-ODLEGLOSC");
    break;
        case 7:
      display.print("UJ-ODLEGLOSC");
    break;
        case 8:
      display.print("PUCK-ODLEGLOSC");
    break;
        case 9:
      display.print("X-ODLEGLOSC");
    break;
        case 10:
      display.print("X-KIERUNEK");
    break;
        case 11:
      display.print("PREDKOSC MAKSYMALNA");
    break;
  }
    delay(1000);
    display.clear();
}
