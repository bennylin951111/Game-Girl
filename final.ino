#include <TFT_eSPI.h> 
#include <EEPROM.h>
#include <math.h>
#define GREY  0x5AEB

TFT_eSPI tft = TFT_eSPI();
TFT_eSprite sprite = TFT_eSprite(&tft);
TFT_eSprite SCsprite = TFT_eSprite(&tft);
TFT_eSprite na1 = TFT_eSprite(&tft);
TFT_eSprite na2 = TFT_eSprite(&tft);
TFT_eSprite na3 = TFT_eSprite(&tft);
TFT_eSprite na4 = TFT_eSprite(&tft);
TFT_eSprite na5 = TFT_eSprite(&tft);
TFT_eSprite AI = TFT_eSprite(&tft);
TFT_eSprite CP = TFT_eSprite(&tft);
TFT_eSprite Pe1 = TFT_eSprite(&tft);
TFT_eSprite Pe2 = TFT_eSprite(&tft);
TFT_eSprite onep1 = TFT_eSprite(&tft);
TFT_eSprite twop1 = TFT_eSprite(&tft);
TFT_eSprite twop2 = TFT_eSprite(&tft);

TFT_eSprite back = TFT_eSprite(&tft);
TFT_eSprite sprite4 = TFT_eSprite(&tft);
TFT_eSprite sprite1 = TFT_eSprite(&tft);
TFT_eSprite back2 = TFT_eSprite(&tft);
TFT_eSprite sprite2 = TFT_eSprite(&tft);
TFT_eSprite sprite3 = TFT_eSprite(&tft);

TFT_eSprite sprite5 = TFT_eSprite(&tft);
TFT_eSprite back5 = TFT_eSprite(&tft);
TFT_eSprite sprite6 = TFT_eSprite(&tft);
TFT_eSprite back6 = TFT_eSprite(&tft);
TFT_eSprite sprite7 = TFT_eSprite(&tft);
TFT_eSprite back7 = TFT_eSprite(&tft);
TFT_eSprite sprite8 = TFT_eSprite(&tft);
TFT_eSprite back8 = TFT_eSprite(&tft);
TFT_eSprite Word = TFT_eSprite(&tft);


#define Button1 25
#define Button2 26
#define StartButton 27
#define EEPROM_SIZE 64
#define VRx 34
#define VRy 35
#define VRx2 32
#define VRy2 33
#define GREY  0x5AEB

unsigned long preTime = 0;
int CCangle = 180;
int CCX = 0;
int CCY = 0;
int CCspeedtheta = 4;
int CCspeedTime = 130;
int CCscore = 0;
int CCbad = 0;
int CCBigtheta = 0;
int CCBigOldtheta = 0;
int CCstate = 0;
int CCwind = 225;
int CCData = 0;

int the1 = -26;
int the2 = -13;
int the3 = 0;
int the4 = 13;
int the5 = 26;
int s1 = 0;
int wantgame = 3;
int wantgame1 = 3;
int CH = 0;
int s0 = 0;

int PPb1 = 105; //板子1y
int PPb2 = 105; //板子2y
int PPtime = 0;
int PPtime1 = 0;
int PPtime2 = 0;
int PPtime3 = 0;
int PPtime4 = 0;
int PPs0 = 0;
int PPbx = 160;  //球x
int PPby1 = 0;  //球y
int PPby3 = 0;
int PPbi = 1;  //球x方向向量
int PPbj = 1; //球y方向向量
int HIT = 0;
int Ty = 105;
int highhit = 0;
int oldhighhit = 0;
int PPby = 120;  //球y
int P1score = 0;
int P2score = 0;
int TScore = 6;
bool startFlag = 1;
bool serve = false; // 用來判斷是否在發球階段
bool initialServe = true; // 用於區分初始發球和得分後發球
bool miss = false;
bool score = false; 
bool p1score = false;
bool p2score = false;
bool ballsetting = false;
bool win = false;

float compressedX = 0;
float compressedY = 0;
int VA = 0;
float VA1 = 0;
double result = 0;
double result2 = 0;
double resultnow = 0;
float GOX1 = 0;
float GOY1 = 0;
float co1 = 30;
float co2 = 180;
float compressedX2 = 0;
float compressedY2 = 0;
float VA2 = 0;
float VA3 = 0;
double result3 = 0;
double result4 = 0;
double resultnow2 = 0;
float GOX2 = 0;
float GOY2 = 0;
float co3 = 200;
float co4 = 180;
int GGT = 4;
int GGT1 = 0;
int GGnoet = 0;
int GGnoet1 = 0;
int GGs0 = 0;
int countColor1 = 0; 
int countColor2 = 0;
int countColor3 = 0;
int PPT = 0;
int YY1 = 0;
int YY2 = 265;
int BLS = 0;
int RES = 0;

  
float logCompress(int value, int minInput, int maxInput, float c);


//初始-------------------------------------------------------------------------------------------

void setup() {

  pinMode(Button1, INPUT); 
  pinMode(Button2, INPUT); 
  pinMode(StartButton, INPUT);
  pinMode(VRx, INPUT);
  pinMode(VRy, INPUT);
  pinMode(VRx2, INPUT);
  pinMode(VRy2, INPUT);
  
  Serial.begin(9600); 
  randomSeed(analogRead(A0));
  tft.init();
  tft.setRotation(3); 
  tft.fillScreen(TFT_BLACK);
  sprite.createSprite(35, 35);
  sprite.setSwapBytes(true);
  SCsprite.createSprite(35, 40);
  SCsprite.setSwapBytes(true);
  choseBackground();
  GGSETUP();
  EEPROM.begin(EEPROM_SIZE);
  highhit = EEPROM.read(0) | (EEPROM.read(1) << 8);
  if (highhit > 9999 || highhit < 0) {
    highhit = 0;
  }
  oldhighhit = highhit;
}

//主程式--------------------------------------------------------------

void loop() {
  switch(s0){
    case 0:
      gamecercle();
      if (analogRead(VRy) > 500) {
        if(wantgame == 1 and s1 == 0){
          if(digitalRead(Button1) == HIGH){
            s0 = 50;
          }
        }
      }
      if (analogRead(VRy) > 500) {
        if(wantgame == 2 and s1 == 0){
          if(digitalRead(Button1) == HIGH){
            s0 = 40;
          }
        }
      }
      
      if (analogRead(VRy) > 500) {
        if(wantgame == 3 and s1 == 0){
          if(digitalRead(Button1) == HIGH){
            s0 = 10;
          }
        }
      }

      if (analogRead(VRy) > 500) {
        if(wantgame == 4 and s1 == 0){
          if(digitalRead(Button1) == HIGH){
            s0 = 20;
          }
        }
      }

      if (analogRead(VRy) > 500) {
        if(wantgame == 5 and s1 == 0){
          if(digitalRead(Button1) == HIGH){
            s0 = 30;
          }
        }
      }
      
      break;
      
      //------------------------------------111
    case 10:
      tft.fillScreen(TFT_BLACK);
      delay(1000);
      PPby1 = random(10, 230);
      //highhit = 0;
      //oldhighhit = 0;
      s0++;
      break;
    case 11:
      if(miss == false){
        PPbroad1();
        PPmid1();
        PPtin1();
        showScore1();
        showHighhit1();
        com1(); 
      }
      if(miss == true){
        ENDSCREEN1();
        if(digitalRead(Button1) == HIGH){
          s0++;
        }
      }
      break;
    case 12:
      the1 = -26;
      the2 = -13;
      the3 = 0;
      the4 = 13;
      the5 = 26;
      s1 = 1;
      onereset();
      if(digitalRead(Button1) == LOW){
        backOK();
        tft.setTextColor(TFT_WHITE);
        s0 = 0;
      }
      break;

      //---------------------------------------------222

    case 20:
      tft.fillScreen(TFT_BLACK);
      delay(1000);
      s0++;
      break;
    case 21:
        if(win == false){
          if(score == true){
            initgame2();
          }
          PPbroad2();
          PPmid2();
          PPtin2();
          showScore2();
          checkScore2();
        }
        if(win == true){
          //ENDSCREEN2();
          delay(1500);
          s0++;
        }
      
      break;
      case 22:
      tft.fillScreen(TFT_BLACK);
      s0++;
      break;
    case 23:
      ENDSCREEN2();
      if(digitalRead(Button1) == HIGH){
        s0++;
      }
      break;
    case 24:
      the1 = 26;
      the2 = -26;
      the3 = -13;
      the4 = 0;
      the5 = 13;
      s1 = 1;
      tworeset();
      if(digitalRead(Button1) == LOW){
        backOK();
        tft.setTextColor(TFT_WHITE);
        s0 = 0;
      }
      break;

      //----------------------------------------------------333

    case 30:
      tft.fillScreen(TFT_BLACK);
      delay(1000);
      PPby3 = random(10, 230);
      s0++;
      break;
    case 31:
      if(win == false){
        if(score == true){
          initgame3();
        }
        PPbroad3();
        PPmid3();
        PPtin3();
        showScore3();
        checkScore3();
        com3();
      }
      if(win == true){
        ENDSCREEN3();
        s0++;
      }
      break;
    case 32:
      the1 = 13;
      the2 = 26;
      the3 = -26;
      the4 = -13;
      the5 = 0;
      s1 = 1;
      threereset();
      if(digitalRead(Button1) == HIGH){
        s0++;
      }
      break;
    case 33:
      if(digitalRead(Button1) == LOW){
        backOK();
        tft.setTextColor(TFT_WHITE);
        s0 = 0;
      }
      break;
      
      //---------------------------------------------------圈圈
    case 40:
      tft.fillScreen(TFT_BLACK);
      CCdrawBackground();
      delay(1000);
      
      s0++;
      break;
    case 41:
      if (CCbad < 5){
        CCmain();
        CCgetcircle();     
      } else {
        tft.fillScreen(TFT_BLACK);
        delay(500);
        s0++;
      }
      break;
    case 42:
      tft.setTextSize(3);
      tft.setCursor(50, 50);
      tft.print("YOUR SCORE:");
      tft.print(CCscore);
      if(digitalRead(Button1) == HIGH){
        s0++;
      }
      
      break;
    case 43:
      
      the1 = -13;
      the2 = 0;
      the3 = 13;
      the4 = 26;
      the5 = -26;
      s1 = 1;
      CCreset();
      if(digitalRead(Button1) == LOW){
        backOK();
        s0 = 0;
      }
      
      break;
      
      //-------------------占地
      
    case 50:
      tft.fillScreen(TFT_BLACK);
      s0++;
      break;
    case 51:
      GGmath2();
      result2 = 0;
      result4 = 0;
      GGP1();
      GGP2();
      delay(1500);
      s0++;
      break;
    case 52:
      GGmath1();
      GGP1();
      GGmath2();
      GGP2();
      GGend();
      if(GGT == 0 and GGT1 == 0){
        s0++;
      }
      break;
    case 53:
      GGWIN();
      Serial.println(countColor1);
      Serial.println(countColor2);
      s0++;
      break;
    case 54:
      Word.pushSprite(50,92,TFT_BLACK);
      delay(4000);
      s0++;
      break;
    case 55:
      GGMOVE();
      break;
    case 56:
      tft.fillScreen(TFT_BLACK);
      tft.setCursor(10, 40);
      tft.setTextColor(TFT_WHITE);
      tft.setTextSize(2);
      tft.print("Blue:");
      tft.print(BLS);
      tft.print("%");
      tft.setCursor(10, 70);
      tft.print("Red:");
      tft.print(RES);
      tft.print("%");
          
      tft.setCursor(10, 100);
      if (countColor1 > countColor2) {
        tft.setTextColor(TFT_BLUE);
        tft.println("Blue Win !");
      } else if (countColor2 > countColor1) {
        tft.setTextColor(TFT_RED);
        tft.println("Red Win !");
      } else if(countColor2 == countColor1){
        tft.println("It's a Draw!");
      }
      s0++; 
      break;
    case 57:
      the1 = 0;
      the2 = 13;
      the3 = 26;
      the4 = -26;
      the5 = -13;
      s1 = 1;
      if(digitalRead(Button1) == HIGH){
        backOK();
        GGgg();
        s0++;
      }
      break;
    case 58:
      if(digitalRead(Button1) == LOW){
        tft.setTextColor(TFT_WHITE);
        s0 = 0;
      }
      break;
  }
}

//選題--------------------------------------------------------------

void choseBackground() {
  tft.fillEllipse(0, 120,320, 320, TFT_WHITE);
  tft.fillEllipse(0, 120,315, 315, TFT_BLACK);
  tft.fillEllipse(0, 120,170, 200, TFT_WHITE);
  tft.fillEllipse(0, 120,165, 194, TFT_BLACK);
  tft.fillRect(0,40,144,108,GREY);
  tft.fillTriangle(167, 112, 155,102,155, 122, TFT_RED);

  na1.createSprite(135,40);
  na1.setSwapBytes(true);
  na2.createSprite(135,40);
  na2.setSwapBytes(true);
  na3.createSprite(135,40);
  na3.setSwapBytes(true);
  na4.createSprite(135,40);
  na4.setSwapBytes(true);
  na5.createSprite(135,40);
  na5.setSwapBytes(true);

  na1.fillScreen(TFT_BLACK);
  na1.setTextColor(TFT_WHITE);
  na1.setTextSize(3);
  na1.print(" color ");
  
  na2.fillScreen(TFT_BLACK);
  na2.setTextColor(TFT_WHITE);
  na2.setTextSize(3);
  na2.print(" circle");
  
  na3.fillScreen(TFT_BLACK);
  na3.setTextColor(TFT_WHITE);
  na3.setTextSize(2);
  na3.print(" Ping Pong ");
  na3.println(" How How 1");
  
  na4.fillScreen(TFT_BLACK);
  na4.setTextColor(TFT_WHITE);
  na4.setTextSize(2);
  na4.print(" Ping Pong ");
  na4.println(" How How 2");
  
  na5.fillScreen(TFT_BLACK);
  na5.setTextColor(TFT_WHITE);
  na5.setTextSize(2);
  na5.print(" Ping Pong ");
  na5.println("  how One");

  AI.createSprite(25,30);
  AI.setSwapBytes(true);
  AI.fillScreen(GREY);
  AI.setTextColor(TFT_RED);
  AI.setTextSize(2);
  AI.print("AI");
  
  CP.createSprite(25,30);
  CP.setSwapBytes(true); 
  CP.fillScreen(GREY);
  CP.setTextColor(TFT_RED);
  CP.setTextSize(2);
  CP.print("CP");
  
  Pe1.createSprite(25,30);
  Pe1.setSwapBytes(true);
  Pe1.fillScreen(GREY);
  Pe1.setTextColor(TFT_BLUE);
  Pe1.setTextSize(2);
  Pe1.print("1P");
  
  Pe2.createSprite(25,30);
  Pe2.setSwapBytes(true);
  Pe2.fillScreen(GREY);
  Pe2.setTextColor(TFT_RED);
  Pe2.setTextSize(2);
  Pe2.print("2P ");

  onep1.createSprite(300,23);
  onep1.setSwapBytes(true);
  onep1.setTextColor(TFT_RED);
  onep1.setTextSize(3);

  twop1.createSprite(240,23);
  twop1.setSwapBytes(true);
  twop1.setTextColor(TFT_BLUE);
  twop1.setTextSize(3);

  twop2.createSprite(240,23);
  twop2.setSwapBytes(true);
  twop2.setTextColor(TFT_RED);
  twop2.setTextSize(3);
}

void gamecercle(){
  switch(s1){
    case 0:
      gamechose();
      if (analogRead(VRy) <= 500) {
        wantgame = wantgame+1;
        s1 = 1;
           
      }
      if(wantgame == 6){
        wantgame = 1;
      }
      if(the3 == 0){
        tft.fillRect(0,60,3,20,TFT_WHITE);
        tft.fillRect(141,107,3,20,TFT_WHITE);
        tft.fillRect(60,50,4,4,TFT_YELLOW);
        for(int i = 40; i <= 145; i=i+9){    //中線
          tft.fillRect(71,i,2, 6,TFT_WHITE);
          tft.fillRect(71,i+6,2, 3,GREY);  
        } 
        Pe1.pushSprite(20,87);
        AI.pushSprite(94,87); 
      }
      break;
    case 1:
      if(wantgame == 1){
        if(the1 == 0){
          s1 = 2;
        }else{
          gamechose();
        }
      }
      if(wantgame == 2){
        if(the2 == 0){
          s1 = 2;
        }else{
          gamechose();
        }
      }
      if(wantgame == 3){
        if(the3 == 0){
          s1 = 2;
        }else{
          gamechose();
        }
      }
      if(wantgame == 4){
        if(the4 == 0){
          s1 = 2;
        }else{
          gamechose();
        }
      }
      if(wantgame == 5){
        if(the5 == 0){
          s1 = 2;
        }else{
          gamechose();
        }
      }
      if(the1<-31){
        the1 = 33;
        tft.fillRect(155, 0,130, 12, TFT_BLACK);
      }
      if(the2<-31){
        the2 = 33;
        tft.fillRect(155, 0,130, 12, TFT_BLACK);
      }
      if(the3<-31){
        the3 = 33;
        tft.fillRect(155, 0,130, 12, TFT_BLACK);
      }
      if(the4<-31){
        the4 = 33;
        tft.fillRect(155, 0,130, 12, TFT_BLACK);
      }
      if(the5<-31){
        the5 = 33;
        tft.fillRect(155, 0,130, 12, TFT_BLACK);
      }
      the1 = the1-1;
      the2 = the2-1;
      the3 = the3-1;
      the4 = the4-1;
      the5 = the5-1;
    break;
    case 2:
      tft.fillRect(0,40,144,108,GREY);
      if(the1 == -1){
         tft.fillRect(18,66,12,60,TFT_BLUE);
         tft.fillRect(18,92,40,12,TFT_BLUE);
         tft.fillRect(48,66,12,60,TFT_BLUE);
         tft.fillRect(83,66,30,12,TFT_RED);
         tft.fillRect(83,112,30,12,TFT_RED);
         tft.fillRect(91,66,12,57,TFT_RED);
         s1 = 0;
      }
      if(the2 == -1){
         tft.fillCircle(72, 94 ,30 ,TFT_WHITE);
         tft.fillCircle(72, 94 ,25 ,GREY);
         tft.fillCircle(85, 70 ,5 ,TFT_YELLOW);
         tft.drawCircle(45, 94,7, TFT_BLUE);
         tft.drawCircle(45, 94,6, TFT_BLUE);
         s1 = 0;
      }
      if(the3 == -1){
        tft.fillRect(0,60,3,20,TFT_WHITE);
        tft.fillRect(141,107,3,20,TFT_WHITE);
        tft.fillRect(60,50,4,4,TFT_YELLOW);
        for(int i = 40; i <= 145; i=i+9){    //中線
          tft.fillRect(71,i,2, 6,TFT_WHITE);
          tft.fillRect(71,i+6,2, 3,GREY);
        }
        Pe1.pushSprite(20,87);
        AI.pushSprite(94,87);
        s1 = 0;
      }
      if(the4 == -1){
        tft.fillRect(0,60,3,20,TFT_WHITE);
        tft.fillRect(141,107,3,20,TFT_WHITE);
        tft.fillRect(60,50,4,4,TFT_YELLOW);
        for(int i = 40; i <= 145; i=i+9){    //中線
          tft.fillRect(71,i,2, 6,TFT_WHITE);
          tft.fillRect(71,i+6,2, 3,GREY);
        }
        Pe1.pushSprite(20,87);
        Pe2.pushSprite(94,87);
        s1 = 0;
      }
      if(the5 == -1){
        tft.fillRect(0,60,3,20,TFT_WHITE);
        tft.fillRect(141,107,3,20,TFT_WHITE);
        tft.fillRect(60,50,4,4,TFT_YELLOW);
        for(int i = 40; i <= 145; i=i+9){    //中線
          tft.fillRect(71,i,2, 6,TFT_WHITE);
          tft.fillRect(71,i+6,2, 3,GREY);
        }
        Pe1.pushSprite(20,87);
        CP.pushSprite(94,87);
        s1 = 0;
      } 
      break;  
  }
}

void gamechose(){
  na1.pushSprite(175*cos((the1) * PI / 180),105+234*sin((the1) * PI / 180));
  na2.pushSprite(175*cos((the2) * PI / 180),105+234*sin((the2) * PI / 180));
  na3.pushSprite(175*cos((the3) * PI / 180),105+234*sin((the3) * PI / 180));
  na4.pushSprite(175*cos((the4) * PI / 180),105+234*sin((the4) * PI / 180));
  na5.pushSprite(175*cos((the5) * PI / 180),105+234*sin((the5) * PI / 180));

  delay(10);
}

void backOK(){
  tft.fillEllipse(0, 120,320, 320, TFT_WHITE);
  tft.fillEllipse(0, 120,315, 315, TFT_BLACK);
  tft.fillEllipse(0, 120,170, 200, TFT_WHITE);
  tft.fillEllipse(0, 120,165, 194, TFT_BLACK);
  tft.fillRect(0,40,144,108,GREY);
  tft.fillTriangle(167, 112, 155,102,155, 122, TFT_RED);
}


//圈圈--------------------------------------------------------------

void CCmain() {
  unsigned long currentTime = millis();
  if (currentTime - preTime >= CCspeedTime) { 
    CCrestoreBackgroundCircle(160 + 65 * cos(CCangle * PI / 180), 120 + 65 * sin(CCangle * PI / 180), 11);
    CCangle += CCspeedtheta;
    tft.fillCircle(160 + 65 * cos(CCangle * PI / 180), 120 + 65 * sin(CCangle * PI / 180), 10, TFT_YELLOW);
    preTime = currentTime; 
  }
  
  int des3 = 160 + 65 * cos(CCangle * PI / 180);
  int des4 = 120 + 65 * sin(CCangle * PI / 180);
  if (digitalRead(StartButton) == HIGH) {
    CCData = 0;
  }
  if (CCData == 0){
    if((des3 - CCX) * (des3 - CCX) + (des4 - CCY) * (des4 - CCY) <= 16){
        CCData = 1;
      }
  }
  if (CCData == 1){
      if((des3 - CCX) * (des3 - CCX) + (des4 - CCY) * (des4 - CCY) >= 625){
        tft.fillRect(0, 0,131,50, TFT_BLACK);
        CCbad++;
        CCData = 0;
      }
  }
  
  
  switch (CCstate) {
    
    case 0: {
      if (digitalRead(StartButton) == HIGH) {
        int des1 = 160 + 65 * cos(CCangle * PI / 180);
        int des2 = 120 + 65 * sin(CCangle * PI / 180);
        if ((des1 - CCX) * (des1 - CCX) + (des2 - CCY) * (des2 - CCY) <= CCwind) {
          tft.fillRect(0, 0,131,50, TFT_BLACK);
          CCscore++;
          CCstate = 1;
        }
        else {
          tft.fillRect(0, 0,120,60, TFT_BLACK);
          CCbad++;
          CCstate = 1;
        }
      }
      break;
    }
    case 1: {
      CCcircleBackgroundCircle();
      if(CCscore < 5){
          CCBigtheta = 60 * random(6);
      } else if(CCscore >= 5 and CCscore < 13) {
          CCBigtheta = 30 * random(12);
          CCwind = 196;
      } else if(CCscore >= 13 and CCscore < 20) {
          CCBigtheta = 30 * random(12);
          CCwind = 144;
      }else{
        CCBigtheta = 20 * random(18);
        CCwind = 121;
      }
      if(CCBigtheta != CCBigOldtheta){
        CCBigOldtheta = CCBigtheta;
        if(CCscore >= 2 and CCscore < 5){
          CCspeedTime = 110;
        }
        if(CCscore >= 5 and CCscore < 8){
          CCspeedTime = 90;
          CCspeedtheta = 5;
        }
        if(CCscore >= 8 and CCscore < 20){
          if(CCscore >= 8 and CCscore < 13){
            CCspeedTime = 70;
          }else{
            CCspeedTime = 50;
          }
          
          if(CCspeedtheta != 6){
            CCspeedtheta = 6;
          }else{
            CCspeedtheta = CCspeedtheta*(-1);
          }
        } 
        if(CCscore >= 20 ){
          if(CCspeedtheta != 7){
            CCspeedtheta = 7;
          }else{
            CCspeedtheta = CCspeedtheta*(-1);
          }
        }
      CCstate = 2;
      }
    break;
    }
    case 2: {
      if(digitalRead(StartButton) == LOW){
        CCstate = 0;
      }
    break;
    }
  }
  
  tft.setCursor(30, 20);
  tft.setTextSize(1.5);//1~7 
  tft.print("Scores: ");
  tft.print(CCscore);
  tft.setCursor(30, 30);
  tft.print("NoNo: ");
  tft.print(CCbad);
}

void CCdrawBackground() {
  tft.fillCircle(160, 120, 70, TFT_WHITE);
  tft.fillCircle(160, 120, 60, TFT_BLACK);
}

void CCgetcircle() {
  CCX = 160 + 65 * sin(CCBigtheta * PI / 180);
  CCY = 120 - 65 * cos(CCBigtheta * PI / 180);
  sprite.fillCircle(17, 17, 17, TFT_BLUE);
  sprite.fillCircle(17, 17, 12, TFT_BLACK);
  sprite.pushSprite(CCX - 17, CCY - 17, TFT_BLACK);
}

void CCrestoreBackgroundCircle(int x, int y, int r) {
  for (int i = -r; i <= r; i++) {
    for (int j = -r; j <= r; j++) {
      if (i * i + j * j <= r * r) {
        int dist = (x + i - 160) * (x + i - 160) + (y + j - 120) * (y + j - 120);
        if (dist >= 60 * 60 && dist <= 70 * 70) {
          tft.drawPixel(x + i, y + j, TFT_WHITE);
        } 
        else {
          tft.drawPixel(x + i, y + j, TFT_BLACK);
        }
      }
    }
  }
}

void CCcircleBackgroundCircle() {
  for (int i = -18; i <= 18; i++) {
    for (int j = -18; j <= 18; j++) {
      if (i * i + j * j <= 18 * 18) {
        int dist = (CCX + i - 160) * (CCX + i - 160) + (CCY + j - 120) * (CCY + j - 120);
        if (dist >= 60 * 60 && dist <= 70 * 70) {
          tft.drawPixel(CCX + i, CCY + j, TFT_WHITE);
        } 
        else {
          tft.drawPixel(CCX + i, CCY + j, TFT_BLACK);
        }
      }
    }
  }
}

void CCreset(){
  preTime = 0;
  CCangle = 180;
  CCX = 0;
  CCY = 0;
  CCspeedtheta = 4;
  CCspeedTime = 130;
  CCscore = 0;
  CCbad = 0;
  CCBigtheta = 0;
  CCBigOldtheta = 0;
  CCstate = 0;
  CCwind = 225;
  CCData = 0;
}

//one--------------------------------------------------------------

  void showScore1() {
  if(miss == false){
    tft.setTextSize(2);
    tft.setCursor(200, 10);
    tft.print("Hits: ");
    tft.print(HIT);
  }
}

  void showHighhit1() { // 顯示歷史最高
    if(miss == false){
      tft.setTextSize(1);
      tft.setCursor(200, 30);
      tft.print("High hit: ");
      tft.print(highhit);
      }
  }

  void PPbroad1(){
    unsigned long currentTime = millis();
    tft.fillRect(0,PPb1,4, 30,TFT_WHITE);  //左板子
    tft.fillRect(0,PPb1-5,4, 5,TFT_BLACK);
    tft.fillRect(0,PPb1+30,4, 5,TFT_BLACK);
    if(serve == false){
    if(currentTime - PPtime >= 19){ 
      if(analogRead(VRy) < 1000){    //左搖桿上下
        PPb1 = PPb1 - 2;
      }
      if(analogRead(VRy) > 4000){
        PPb1 = PPb1 + 2;
      }
      if(PPb1<0){
        PPb1 = 0;
      }
      if(PPb1>210){
        PPb1 = 210;
      }
      PPtime = currentTime;
    } 
  }
}

  void PPtin1(){
  unsigned long currentTime = millis();
  if (initialServe) {
    int randomDirection = random(2);
    switch (randomDirection) {
      case 0: // 左上
        PPbi = -1;
        PPbj = -1;
        initialServe = false;
        break;
      case 1: // 左下
        PPbi = -1;
        PPbj = 1;
        initialServe = false;
        break;
    }
  }
  if (serve==false){
    if(currentTime - PPtime1 >= 8 ){     //球移動+碰到板子會反彈
      tft.fillRect(PPbx,PPby1,7,7,TFT_BLACK);
      PPbx = PPbx + PPbi;
      PPby1 = PPby1 + PPbj;
  
      if(PPbx == 309){   
        if (PPby1 >= PPb2-5 and PPby1 <= PPb2+28){
          PPbi = PPbi * (-1);
        }
      }
      if(PPbx == 4 ){
        if (PPby1 >= PPb1-5 and PPby1 <= PPb1+28){
          PPbi = PPbi * (-1);
          tft.fillRect(200, 0,85,50, TFT_BLACK);
          tft.fillRect(170,0,130, 50,TFT_BLACK);
          HIT ++;
          if(HIT > highhit){
            highhit = HIT;
            EEPROM.write(0, highhit & 0xFF); // 保存低 8 位元
            EEPROM.write(1, (highhit >> 8) & 0xFF); // 保存高 8 位元
            EEPROM.commit(); // 提交變更
          }
          if(PPbj ==1){
            Ty = 161-PPby1;
            if(Ty<0){
              Ty = Ty * (-1);
            }
          }
          if(PPbj == -1){
            if(PPby1>=72){
              Ty = 305-PPby1;
            }
            if(PPby1<72){
              Ty = 161+PPby1;
            }
          }
        }
      } 
      if (PPby1 == 0 || PPby1 == 233){
        PPbj = PPbj * (-1);
      }
      tft.fillRect(PPbx,PPby1,7,7,TFT_YELLOW);
      PPtime1 = currentTime;
    }
  }
  if (PPbi == -1 && PPbx + 7 < 0) {
    tft.fillScreen(TFT_BLACK);
    miss = true;
  }
}

  void PPmid1(){
  for(int i = 2; i <= 240; i=i+17){    //中線
    tft.fillRect(159,i,3, 10,TFT_WHITE);
    tft.fillRect(159,i+10,3, 7,TFT_BLACK);
  }
}
  
  void com1(){
  unsigned long currentTime = millis();
  if(miss == false){
    tft.fillRect(316,PPb2,4, 30,TFT_WHITE);   //右板子
    tft.fillRect(316,PPb2-5,4, 5,TFT_BLACK);
    tft.fillRect(316,PPb2+30,4, 5,TFT_BLACK);
    if(currentTime - PPtime2 >= 25){ 
      if(Ty-13-PPb2 >-1 && Ty-13-PPb2 <1){
        PPb2 = PPb2+0;
       }
       if(Ty-13-PPb2 >1 ){
        PPb2 = PPb2+2;
       } 
      if(Ty-13-PPb2 <-1){
        PPb2 = PPb2-2;
      }
      if(PPb2<0){
        PPb2 = 0;
      }
      if(PPb2>210){
        PPb2 = 210;
      }
      PPtime2 = currentTime;
    }
  }
}

  void ENDSCREEN1(){
    tft.setTextSize(3);
    tft.setCursor(50, 50);
    tft.print("YOUR SCORE:");
    tft.print(HIT);
  if(HIT>oldhighhit){
    onep1.pushSprite(30, 100);
    onep1.print("NEW HIGH SCORE!!");
  }
}

  void onereset(){
  PPb1 = 105; //板子1y
  PPb2 = 105; //板子2y
  PPtime = 0;
  PPtime1 = 0;
  PPtime2 = 0;
  PPs0 = 0;
  PPbx = 160;  //球x
  PPby1 = 0;  //球y
  PPbi = 1;  //球x方向向量
  PPbj = 1; //球y方向向量
  HIT = 0;
  Ty = 105;
  startFlag = 1;
  serve = false; // 用來判斷是否在發球階段
  initialServe = true; // 用於區分初始發球和得分後發球
  miss = false;
  }

//two--------------------------------------------------------------

void initgame2() {
  PPbx = 160; // 将球设置在中间线上
  PPby = 120; // 将球设置在屏幕中间垂直位置

  tft.fillScreen(TFT_BLACK);
  tft.fillRect(PPbx, PPby, 7, 7, TFT_YELLOW); // 使用黄色显示球
  
  tft.fillRect(0,PPb1,4, 30,TFT_WHITE);  //左板子
  tft.fillRect(0,PPb1-5,4, 5,TFT_BLACK);
  tft.fillRect(0,PPb1+30,4, 5,TFT_BLACK);
  tft.fillRect(316,PPb2,4, 30,TFT_WHITE);   //右板子
  tft.fillRect(316,PPb2-5,4, 5,TFT_BLACK);
  tft.fillRect(316,PPb2+30,4, 5,TFT_BLACK);
  PPmid2();
  showScore2();

  startFlag = 1; // 自動開始遊戲
}

void showScore2() {
  if (startFlag) {
    tft.setTextSize(2);
    tft.setCursor(200, 10);
    tft.print(P2score);
    tft.setCursor(120, 10);
    tft.print(P1score);
  }
}

void checkScore2(){
  if(P1score == TScore || P2score == TScore){
    
    win = true;
  }
}

void PPbroad2(){
  unsigned long currentTime = millis();
  tft.fillRect(0,PPb1,4, 30,TFT_WHITE);  //左板子
  tft.fillRect(0,PPb1-5,4, 5,TFT_BLACK);
  tft.fillRect(0,PPb1+30,4, 5,TFT_BLACK);
  tft.fillRect(316,PPb2,4, 30,TFT_WHITE);   //右板子
  tft.fillRect(316,PPb2-5,4, 5,TFT_BLACK);
  tft.fillRect(316,PPb2+30,4, 5,TFT_BLACK);
  if(serve == false){
    if(currentTime - PPtime >= 17){ 
      if(analogRead(VRy) < 1000){    //左搖桿上下
        PPb1 = PPb1 - 2;
      }
      if(analogRead(VRy) > 4000){
       PPb1 = PPb1 + 2;
      }
      if(PPb1<0){
        PPb1 = 0;
      }
      if(PPb1>210){
        PPb1 = 210;
      }
      if(analogRead(VRy2) < 1000){   //右搖桿上下
        PPb2 = PPb2 - 2;
      }
      if(analogRead(VRy2) > 4000){
        PPb2 = PPb2 + 2;
      }
      if(PPb2<0){
        PPb2 = 0;
      }
      if(PPb2>210){
       PPb2 = 210;
      }
      PPtime = currentTime;
    } 
  }
}

void PPtin2(){
  unsigned long currentTime = millis();
  if (initialServe) {
    int randomDirection = random(4);
    switch (randomDirection) {
      case 0: // 左上
        PPbi = -1;
        PPbj = -1;
        initialServe = false;
        break;
      case 1: // 左下
        PPbi = -1;
        PPbj = 1;
        initialServe = false;
        break;
      case 2: // 右上
        PPbi = 1;
        PPbj = -1;
        initialServe = false;
        break;
      case 3: // 右下
        PPbi = 1;
        PPbj = 1;
        initialServe = false;
        break;
    }
  }
  if (serve==false &&  ballsetting==false){
    if(currentTime - PPtime1 >= 8){     //球移動+碰到板子會反彈
      tft.fillRect(PPbx,PPby,7,7,TFT_BLACK);
      PPbx = PPbx + PPbi;
      PPby = PPby + PPbj;
  
      if(PPbx == 309){   
        if (PPby >= PPb2-5 and PPby <= PPb2+28){
          PPbi = PPbi * (-1);
        }
      }
      if(PPbx == 4 ){
        if (PPby >= PPb1-5 and PPby <= PPb1+28){
          PPbi = PPbi * (-1);
        }
      } 
      if (PPby == 0 || PPby == 233){
        PPbj = PPbj * (-1);
      }
      tft.fillRect(PPbx,PPby,7,7,TFT_YELLOW);
      PPtime1 = currentTime;
    }
  }
  if ((PPbi == 1 && PPbx >= 320) || (PPbi == -1 && PPbx + 7 < 0)) {
    if (PPbi == 1) {
      P1score++;
      score = true;
      p1score = true;
      p2score = false;
      ballsetting = true;
    } else {
      P2score++;
      score = true;
      p2score = true;
      p1score = false;
      ballsetting = true;
    }
    startFlag = 0;
    initgame2();
  }
  if(score){
    initialServe = false;
    serve = true;
    score = false;
    PPbx = 160;
    PPby = 120;
  }
  if (serve==true && initialServe==false) {
    // 在发球阶段，允许失分者控制球的y位置
      // 设置发球方向（朝得分者）
      if(digitalRead(Button1) == HIGH){
        if (p2score == true) {
          PPbi = 1; // 朝右
          PPbj = (random(2) == 0) ? 1 : -1; // 随机决定ball_dy为1或-1
          serve = false; // 按下按钮后，结束发球阶段
          ballsetting = false;
          p2score = false ;
        }  
      }
      if(digitalRead(Button2) == HIGH){
        if(p1score == true){
          PPbi = -1; // 朝左
          PPbj = (random(2) == 0) ? 1 : -1; // 随机决定ball_dy为1或-1
          serve = false; // 按下按钮后，结束发球阶段
          ballsetting = false;
          p1score = false ;
          }  
      } 
  }
  if (serve==true && ballsetting ==true){
      // 控制球在中线上的移动
    if(p2score == true){
      if(currentTime - PPtime3 >= 50){ 
        tft.fillRect(PPbx,PPby,7,7,TFT_BLACK);
        PPby = PPby + PPbj;
        if(analogRead(VRy) < 1000){    //左搖桿上下
          PPbj = PPbj - 2;
        }
        if(analogRead(VRy) > 4000){
          PPbj = PPbj + 2;
        }
        if(analogRead(VRy) < 3500 &&analogRead(VRy) > 1500){
          PPbj = 0;
        }
        if(PPby<2){
          PPby = 2;
        }
        if(PPby>231){
          PPby = 231;
        }
        
        tft.fillRect(PPbx,PPby,7,7,TFT_YELLOW);
        PPtime3 = currentTime;
      } 
      return;
    }
    if(p1score == true){
      if(currentTime - PPtime4 >= 50){ 
        tft.fillRect(PPbx,PPby,7,7,TFT_BLACK);
        PPby = PPby + PPbj;        
        if(analogRead(VRy2) < 1000){    //左搖桿上下
          PPbj = PPbj - 2;
        }
        if(analogRead(VRy2) > 4000){
          PPbj = PPbj + 2;
        }
        if(analogRead(VRy2) < 3500 &&analogRead(VRy2) > 1500){
          PPbj = 0;
        }
        if(PPby<2){
          PPby = 2;
        }
        if(PPby>231){
          PPby = 231;
        }
        tft.fillRect(PPbx,PPby,7,7,TFT_YELLOW);
        PPtime4 = currentTime;
      } 
      return;
    }
  }
}

void PPmid2(){
  for(int i = 2; i <= 240; i=i+17){    //中線
    tft.fillRect(159,i,3, 10,TFT_WHITE);
    tft.fillRect(159,i+10,3, 7,TFT_BLACK);
  }
}

void ENDSCREEN2(){
  tft.setTextSize(3);
  
  if(P1score == TScore){
    twop1.pushSprite(50, 50);
    twop1.print("Player 1 win  ");
  }
  if(P2score == TScore){   
    twop2.pushSprite(50, 50);
    twop2.print("Player 2 win  ");
  }
}  

void tworeset(){
  PPb1 = 105; //板子1y
  PPb2 = 105; //板子2y
  PPtime = 0;
  PPtime1 = 0;
  PPtime2 = 0;
  PPtime3 = 0;
  PPtime4 = 0;
  PPs0 = 0;
  PPbx = 160;  //球x
  PPby = 120;  //球y
  PPbi = 1;  //球x方向向量
  PPbj = 1; //球y方向向量
  P1score = 0;
  P2score = 0;
  TScore = 6;
  startFlag = 1;
  serve = false; // 用來判斷是否在發球階段
  initialServe = true; // 用於區分初始發球和得分後發球
  score = false; 
  p1score = false;
  p2score = false;
  ballsetting = false;
  win = false;
}

//three--------------------------------------------------------------

void initgame3() {
  PPbx = 160; // 将球设置在中间线上
  PPby3 = random(10, 230); // 将球设置在屏幕中间垂直位置
  PPb1 = 105;

  tft.fillScreen(TFT_BLACK);
  tft.fillRect(PPbx, PPby3, 7, 7, TFT_YELLOW); // 使用黄色显示球
  
  tft.fillRect(0,PPb1,4, 30,TFT_WHITE);  //左板子
  tft.fillRect(0,PPb1-5,4, 5,TFT_BLACK);
  tft.fillRect(0,PPb1+30,4, 5,TFT_BLACK);
  PPmid3();
  showScore3();

  startFlag = 1; // 自動開始遊戲
}

void showScore3() {
  if (startFlag) {
    tft.setTextSize(2);
    tft.setCursor(200, 10);
    tft.print(P2score);
    tft.setCursor(120, 10);
    tft.print(P1score);
  }
}

void checkScore3(){
  if(P1score == 3 || P2score == 3){
    win = true;
    tft.fillScreen(TFT_BLACK);
  }
}

void PPbroad3(){
  unsigned long currentTime = millis();
  tft.fillRect(0,PPb1,4, 30,TFT_WHITE);  //左板子
  tft.fillRect(0,PPb1-5,4, 5,TFT_BLACK);
  tft.fillRect(0,PPb1+30,4, 5,TFT_BLACK);
  if(serve == false){
    if(currentTime - PPtime >= 18){ 
      if(analogRead(VRy) < 1000){    //左搖桿上下
        PPb1 = PPb1 - 2;
      }
      if(analogRead(VRy) > 4000){
        PPb1 = PPb1 + 2;
      }
      if(PPb1<0){
        PPb1 = 0;
      }
      if(PPb1>210){
        PPb1 = 210;
      }
      PPtime = currentTime;
    } 
  }
}

void PPtin3(){
  unsigned long currentTime = millis();
  if (initialServe==true || serve==true) {
    int randomDirection = random(2);
    switch (randomDirection) {
      case 0: // 左上
        PPbi = -1;
        PPbj = -1;
        initialServe = false;
        serve = false;
        break;
      case 1: // 左下
        PPbi = -1;
        PPbj = 1;
        initialServe = false;
        serve = false;
        break;
    }
  }
  if (serve==false){
    if(currentTime - PPtime1 >= 8){     //球移動+碰到板子會反彈
      tft.fillRect(PPbx,PPby3,7,7,TFT_BLACK);
      PPbx = PPbx + PPbi;
      PPby3 = PPby3 + PPbj;
  
      if(PPbx == 309){   
        if (PPby3 >= PPb2-5 and PPby3 <= PPb2+28){
          PPbi = PPbi * (-1);
        }
      }
      if(PPbx == 4 ){
        if (PPby3 >= PPb1-5 and PPby3 <= PPb1+28){
          PPbi = PPbi * (-1);
          HIT ++;
          if(PPbj == 1){
            Ty = 161-PPby3;
            if(Ty<0){
              Ty = Ty * (-1);
            }
          }
          if(PPbj == -1){
            if(PPby3>=72){
              Ty = 305-PPby3;
            }
            if(PPby3<72){
              Ty = 161+PPby3;
            }
          }
        }
        int R = random(-35, 35);
        Ty = Ty + R;
      } 
      if (PPby3 == 0 || PPby3 == 233){
        PPbj = PPbj * (-1);
      }
      tft.fillRect(PPbx,PPby3,7,7,TFT_YELLOW);
      PPtime1 = currentTime;
    }
  }
  if ((PPbi == 1 && PPbx >= 320) || (PPbi == -1 && PPbx + 7 < 0)) {
    if (PPbi == 1) {
      P1score++;
      score = true;
      p1score = true;
      p2score = false;
    } else {
      P2score++;
      score = true;
      p2score = true;
      p1score = false;
    }
    startFlag = 0;
    initgame3();
  }
  if(score){
    initialServe = false;
    serve = true;
    score = false;
  }
}

void PPmid3(){
  for(int i = 2; i <= 240; i=i+17){    //中線
    tft.fillRect(159,i,3, 10,TFT_WHITE);
    tft.fillRect(159,i+10,3, 7,TFT_BLACK);
  }
}

void com3(){
  unsigned long currentTime = millis();
  if(win == false){
    tft.fillRect(316,PPb2,4, 30,TFT_WHITE);   //右板子
    tft.fillRect(316,PPb2-5,4, 5,TFT_BLACK);
    tft.fillRect(316,PPb2+30,4, 5,TFT_BLACK);
    if(currentTime - PPtime2 >= 22){ 
      
      if(Ty-13-PPb2 >-1 && Ty-13-PPb2 <1){
          PPb2 = PPb2+0;
        }
        if(Ty-13-PPb2 >1 ){
        PPb2 = PPb2+2;
        }
        if(Ty-13-PPb2 <-1){
          PPb2 = PPb2-2;
        }
      
      if(PPb2<0){
        PPb2 = 0;
      }else if(PPb2>210){
        PPb2 = 210;
      }
      
      PPtime2 = currentTime;
    }
  }
}

void ENDSCREEN3(){
  tft.setTextSize(3);
  if(P1score == 3){
    tft.setTextColor(TFT_BLUE);
    tft.setCursor(50, 50);
    tft.print("Player win");
  }
  if(P2score == 3){
    tft.setTextColor(TFT_RED);
    tft.setCursor(50, 50);
    tft.print("YOU LOSE");
  }
}

void threereset(){
  
  PPb1 = 105; //板子1y
  PPb2 = 105; //板子2y
  PPtime = 0;
  PPtime1 = 0;
  PPtime2 = 0;
  PPs0 = 0;
  PPbx = 160;  //球x
  PPby3 = 0;  //球y
  PPbi = 1;  //球x方向向量
  PPbj = 1; //球y方向向量
  P1score = 0;
  P2score = 0;
  TScore = 6;
  HIT = 0;
  Ty = 105;
  startFlag = 1;
  serve = false; // 用來判斷是否在發球階段
  initialServe = true; // 用於區分初始發球和得分後發球
  score = false; 
  p1score = false;
  p2score = false;
  ballsetting = false;
  win = false;
}

//占地--------------------------------------------------------------

float logCompress(int value, int minInput, int maxInput, float c) {
  // 将输入值标准化到 0 到 1 之间
  float normalizedValue = (float)(value - minInput) / (maxInput - minInput);
  // 应用 y = sign(x) * (log(|x|) + c) 压缩
  float compressedValue = (log(normalizedValue + 1) + c);
  // 将值映射回原始范围
  return compressedValue / (log(2) + c) * (maxInput - minInput) + minInput;
}

void GGmath1(){
  int xValue = analogRead(VRx);
  int yValue = analogRead(VRy);

  compressedX = logCompress(xValue-200, 0, 4095, 1)-3300;
  compressedY = logCompress(yValue-200, 0, 4095, 1)-3300;
  VA = sqrt((compressedX*compressedX)+(compressedY*compressedY));
  VA1 = compressedY / VA;
  if (VA1 < -1.0) VA1 = -1.0;
  if (VA1 > 1.0) VA1 = 1.0;

  if (compressedX < 0){
    result = acos(VA1)*(-57.29);
  }else{
    result = acos(VA1)*(57.29);
  }
  
  GOX1 = compressedX / VA;
  GOY1 = compressedY / VA;
  result2 = (-1)*(result-180);
  if(xValue > 1700 and xValue < 2700 and yValue > 1700 and yValue < 2700){
    result2 = resultnow;
    GOX1 = 0;
    GOY1 = 0;
  }
  
  co1 = co1+ GOX1;
  co2 = co2+ GOY1;

  if(co2 > 185){
    co2 = 185;
  }
  if(co2 < 0){
    co2 = 0;
  }
  if(co1 > 265){
    co1 = 265;
  }
  if(co1 < 0){
    co1 = 0;
  }
}

void GGP1(){
    if(result2 > resultnow+5 || result2 < resultnow-5){
      sprite1.fillCircle(22, 17, 21, TFT_BLUE);
      sprite1.fillRoundRect(1,1,40, 16, 1, TFT_BLUE);
      sprite1.pushRotated(&back,resultnow,TFT_BLACK);
      back.pushSprite(co1,co2,TFT_BLACK);
      resultnow = result2;
    }else{
      resultnow = result2;
    }
  
  sprite4.fillCircle(22, 17, 21, TFT_BLUE);
  sprite4.fillRoundRect(1,1,40, 16, 1, TFT_BLUE);
  sprite4.drawLine(0, 0, 44, 0, TFT_BLACK); 
  sprite4.fillRoundRect(3,3,36, 14, 1, GREY);
  sprite4.fillRoundRect(5,5,32, 10, 1, TFT_YELLOW);
  sprite4.fillRoundRect(37,8,4,14, 1, GREY);
  sprite4.fillRoundRect(22,20,18,4, 1, GREY);
  sprite4.fillRoundRect(17,20,8,17, 1, GREY);
  sprite4.drawLine(13, 4, 8,16, GREY);
  sprite4.drawLine(24, 4, 19,16, GREY);
  sprite4.drawLine(35, 4, 30,16, GREY);

  sprite4.pushRotated(&back,result2,TFT_BLACK);
  back.pushSprite(co1,co2,TFT_BLACK);
}

//-----------------------第二把

void GGSETUP(){
  back.createSprite(55,55);
  back.setSwapBytes(true);
  back.fillScreen(TFT_BLACK);
  sprite4.createSprite(44,44);
  sprite4.setSwapBytes(true);
  sprite1.createSprite(44,44);
  sprite1.setSwapBytes(true);
  back2.createSprite(55,55);
  back2.setSwapBytes(true);
  back2.fillScreen(TFT_BLACK);
  sprite2.createSprite(44,44);
  sprite2.setSwapBytes(true);
  sprite3.createSprite(44,44);
  sprite3.setSwapBytes(true);
  back5.createSprite(60,60);
  back5.setSwapBytes(true);
  back5.fillScreen(TFT_WHITE);
  sprite5.createSprite(44,44);
  sprite5.setSwapBytes(true);
  back6.createSprite(60,60);
  back6.setSwapBytes(true);
  back6.fillScreen(TFT_WHITE);
  sprite6.createSprite(44,44);
  sprite6.setSwapBytes(true);
  back7.createSprite(60,60);
  back7.setSwapBytes(true);
  back7.fillScreen(TFT_WHITE);
  sprite7.createSprite(44,44);
  sprite7.setSwapBytes(true);
  back8.createSprite(60,60);
  back8.setSwapBytes(true);
  back8.fillScreen(TFT_WHITE);
  sprite8.createSprite(44,44);
  sprite8.setSwapBytes(true);
  Word.createSprite(230,50);
  Word.setSwapBytes(true);
  Word.fillScreen(TFT_BLACK);
  Word.setTextColor(TFT_WHITE);
  Word.setTextSize(4);
  Word.print("Time's up ");
  
  GGset();
}

void GGmath2(){
  int xValue = analogRead(VRx2);
  int yValue = analogRead(VRy2);

  compressedX2 = logCompress(xValue-200, 0, 4095, 1)-3300;
  compressedY2 = logCompress(yValue-200, 0, 4095, 1)-3300;
  VA2 = sqrt((compressedX2*compressedX2)+(compressedY2*compressedY2));
  VA3 = compressedY2 / VA2;
  if (VA3 < -1.0) VA3 = -1.0;
  if (VA3 > 1.0) VA3 = 1.0;

  if (compressedX2 < 0){
    result3 = acos(VA3)*(-57.29);
  }else{
    result3 = acos(VA3)*(57.29);
  }
  
  GOX2 = compressedX2 / VA2;
  GOY2 = compressedY2 / VA2;
  result4 = (-1)*(result3 -180);
  if(xValue > 1700 and xValue < 2700 and yValue > 1700 and yValue < 2700){
    result4 = resultnow2;
    GOX2 = 0;
    GOY2 = 0;
  }
  
  co3 = co3+ GOX2;
  co4 = co4+ GOY2;

  if(co4 > 185){
    co4 = 185;
  }
  if(co4 < 0){
    co4 = 0;
  }
  if(co3 > 265){
    co3 = 265;
  }
  if(co3 < 0){
    co3 = 0;
  }
}

void GGP2(){
    if(result4 > resultnow2+5 || result4 < resultnow2-5){
      sprite3.fillCircle(22, 17, 21, TFT_RED);
      sprite3.fillRoundRect(1,1,40, 16, 1, TFT_RED);
      sprite3.pushRotated(&back2,resultnow2,TFT_BLACK);
      back2.pushSprite(co3,co4,TFT_BLACK);
      resultnow2 = result4;
    }else{
      resultnow2 = result4;
    }
  
  sprite2.fillCircle(22, 17, 21, TFT_RED);
  sprite2.fillRoundRect(1,1,40, 16, 1, TFT_RED);
  sprite2.drawLine(0, 0, 44, 0, TFT_BLACK); 
  sprite2.fillRoundRect(3,3,36, 14, 1, GREY);
  sprite2.fillRoundRect(5,5,32, 10, 1, TFT_PINK);
  sprite2.fillRoundRect(37,8,4,14, 1, GREY);
  sprite2.fillRoundRect(22,20,18,4, 1, GREY);
  sprite2.fillRoundRect(17,20,8,17, 1, GREY);
  sprite2.drawLine(13, 4, 8,16, GREY);
  sprite2.drawLine(24, 4, 19,16, GREY);
  sprite2.drawLine(35, 4, 30,16, GREY);

  sprite2.pushRotated(&back2,result4,TFT_BLACK);
  back2.pushSprite(co3,co4,TFT_BLACK);
  
}

void GGend(){
  unsigned long currentTime = millis();
  if(GGT > 0 || GGT1 > 0){
    if(currentTime -GGnoet1 >= 1000){
      GGT1 = GGT1 - 1.0;
      GGnoet1 = currentTime;
      
    }
    if(GGT1 == -1){
      GGT1 = 9;
      GGT = GGT - 1.0;  
    }
  }else{
    GGT = 0;
    GGT1 = 0;
  }
  tft.setCursor(0,0);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.setTextSize(2);
  tft.print(GGT);
  tft.print(GGT1);
  tft.print("s");
  
  
}

void GGWIN(){
  for (int x = 0; x < tft.width(); x++) {
    for (int y = 0; y < tft.height(); y++) {
      uint16_t pixelColor = tft.readPixel(x, y);  // 獲取像素顏色

      // 比較像素顏色並增加相應的計數器
      if (pixelColor == TFT_BLUE) {
        countColor1++;
      } else if (pixelColor == TFT_RED) {
        countColor2++;
      }
      countColor3++;
    }
  }
  BLS = countColor1*100/countColor3;
  RES = countColor2*100/countColor3;
  

  
  // 打印兩種顏色的像素數量


}

void GGset(){
  sprite5.fillCircle(22, 17, 21, TFT_WHITE);
  sprite5.fillRoundRect(1,1,40, 16, 1, TFT_WHITE);
  sprite5.drawLine(0, 0, 44, 0, TFT_WHITE); 
  sprite5.fillRoundRect(3,3,36, 14, 1, GREY);
  sprite5.fillRoundRect(5,5,32, 10, 1, TFT_PINK);
  sprite5.fillRoundRect(37,8,4,14, 1, GREY);
  sprite5.fillRoundRect(22,20,18,4, 1, GREY);
  sprite5.fillRoundRect(17,20,8,17, 1, GREY);
  sprite5.drawLine(13, 4, 8,16, GREY);
  sprite5.drawLine(24, 4, 19,16, GREY);
  sprite5.drawLine(35, 4, 30,16, GREY);

  sprite5.pushRotated(&back5,90,TFT_BLACK);

  sprite6.fillCircle(22, 17, 21, TFT_WHITE);
  sprite6.fillRoundRect(1,1,40, 16, 1, TFT_WHITE);
  sprite6.drawLine(0, 0, 44, 0, TFT_WHITE); 
  sprite6.fillRoundRect(3,3,36, 14, 1, GREY);
  sprite6.fillRoundRect(5,5,32, 10, 1, TFT_GREEN);
  sprite6.fillRoundRect(37,8,4,14, 1, GREY);
  sprite6.fillRoundRect(22,20,18,4, 1, GREY);
  sprite6.fillRoundRect(17,20,8,17, 1, GREY);
  sprite6.drawLine(13, 4, 8,16, GREY);
  sprite6.drawLine(24, 4, 19,16, GREY);
  sprite6.drawLine(35, 4, 30,16, GREY);

  sprite6.pushRotated(&back6,-90,TFT_BLACK);

  sprite7.fillCircle(22, 17, 21, TFT_WHITE);
  sprite7.fillRoundRect(1,1,40, 16, 1, TFT_WHITE);
  sprite7.drawLine(0, 0, 44, 0, TFT_WHITE); 
  sprite7.fillRoundRect(3,3,36, 14, 1, GREY);
  sprite7.fillRoundRect(5,5,32, 10, 1, TFT_WHITE);
  sprite7.fillRoundRect(37,8,4,14, 1, GREY);
  sprite7.fillRoundRect(22,20,18,4, 1, GREY);
  sprite7.fillRoundRect(17,20,8,17, 1, GREY);
  sprite7.drawLine(13, 4, 8,16, GREY);
  sprite7.drawLine(24, 4, 19,16, GREY);
  sprite7.drawLine(35, 4, 30,16, GREY);

  sprite7.pushRotated(&back7,90,TFT_BLACK);

  sprite8.fillCircle(22, 17, 21, TFT_WHITE);
  sprite8.fillRoundRect(1,1,40, 16, 1, TFT_WHITE);
  sprite8.drawLine(0, 0, 44, 0, TFT_WHITE); 
  sprite8.fillRoundRect(3,3,36, 14, 1, GREY);
  sprite8.fillRoundRect(5,5,32, 10, 1, TFT_ORANGE);
  sprite8.fillRoundRect(37,8,4,14, 1, GREY);
  sprite8.fillRoundRect(22,20,18,4, 1, GREY);
  sprite8.fillRoundRect(17,20,8,17, 1, GREY);
  sprite8.drawLine(13, 4, 8,16, GREY);
  sprite8.drawLine(24, 4, 19,16, GREY);
  sprite5.drawLine(35, 4, 30,16, GREY);

  sprite8.pushRotated(&back8,-90,TFT_BLACK);

}

void GGMOVE(){
  unsigned long currentTime = millis();
  
  GGset();
  
  back5.pushSprite(YY1,0);
  back6.pushSprite(YY2,60);
  back7.pushSprite(YY1,120);
  back8.pushSprite(YY2,180);
  if(YY1 == 380){
    s0++;
  }
  YY1 = YY1+2;
  YY2 = YY2-2;
  delay(3);
}

void GGgg(){
  back.fillScreen(TFT_BLACK);
  back2.fillScreen(TFT_BLACK);
  compressedX = 0;
  compressedY = 0;
  VA = 0;
  VA1 = 0;
  result = 0;
  result2 = 0;
  resultnow = 0;
  GOX1 = 0;
  GOY1 = 0;
  co1 = 30;
  co2 = 180;
  compressedX2 = 0;
  compressedY2 = 0;
  VA2 = 0;
  VA3 = 0;
  result3 = 0;
  result4 = 0;
  resultnow2 = 0;
  GOX2 = 0;
  GOY2 = 0;
  co3 = 200;
  co4 = 180;
  GGT = 4;
  GGT1 = 0;
  GGnoet = 0;
  GGnoet1 = 0;
  GGs0 = 0;
  countColor1 = 0; 
  countColor2 = 0;
  countColor3 = 0;
  PPT = 0;
  YY1 = 0;
  YY2 = 265;
  BLS = 0;
  RES = 0;
}

//-----------------------------------------------------------END
