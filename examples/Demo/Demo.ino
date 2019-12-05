#include <SPI.h>
#include <Wire.h>
#include <Modules.h>
#include <pitches.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

#define LOGO16_GLCD_HEIGHT 16
#define LOGO16_GLCD_WIDTH 16
#define imageWidth 96
#define imageHeight 64
int8_t count = 0, up = 0;//count為下排游標位置  up是上排第幾個指令
bool inverse = 0;//游標是上排還是下排
int8_t pic[10];//總共最多十個圖案
Motor motor;
const unsigned char PROGMEM picarray[4][96] =
{
  {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x01, 0x00, 0x00, 0x01, 0x80, 0x00, 0x01, 0xC0, 0x00, 0x01, 0xE0, 0x00, 0x07, 0xF0, 0x00, 0x1F,
    0xF8, 0x00, 0x7F, 0xFC, 0x00, 0xFF, 0xFE, 0x01, 0xFF, 0xFE, 0x03, 0xFF, 0xFC, 0x07, 0xFF, 0xF8,
    0x0F, 0xFF, 0xF0, 0x1F, 0xC1, 0xE0, 0x1E, 0x01, 0xC0, 0x3C, 0x01, 0x80, 0x38, 0x01, 0x00, 0x30,
    0x00, 0x00, 0x60, 0x00, 0x00, 0x40, 0x00, 0x00, 0x40, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
  },
  {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xC0, 0x00, 0x01, 0xC0, 0x00, 0x03, 0xC0, 0x00, 0x07, 0x80, 0x00, 0x0F, 0xE0, 0x00, 0x1F, 0xF8,
    0x00, 0x3F, 0xFE, 0x00, 0x7F, 0xFF, 0x00, 0x7F, 0xFF, 0xC0, 0x3F, 0xFF, 0xC0, 0x1F, 0xFF, 0xE0,
    0x0F, 0xFF, 0xF0, 0x07, 0xC3, 0xF8, 0x03, 0xC0, 0x78, 0x01, 0xC0, 0x3C, 0x00, 0xC0, 0x1C, 0x00,
    0x00, 0x0C, 0x00, 0x00, 0x06, 0x00, 0x00, 0x02, 0x00, 0x00, 0x02, 0x00, 0x00, 0x02, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
  },
  {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x3C, 0x00, 0x00, 0x7E, 0x00, 0x00, 0x7E, 0x00, 0x00, 0xFF,
    0x00, 0x01, 0xFF, 0x80, 0x03, 0xFF, 0xC0, 0x03, 0xFF, 0xC0, 0x07, 0xFF, 0xE0, 0x0F, 0xFF, 0xF0,
    0x0F, 0xBD, 0xF0, 0x0F, 0x3C, 0xF0, 0x0E, 0x3C, 0x70, 0x06, 0x3C, 0x60, 0x00, 0x3C, 0x00, 0x00,
    0x3C, 0x00, 0x00, 0x3C, 0x00, 0x00, 0x3C, 0x00, 0x00, 0x3C, 0x00, 0x00, 0x3C, 0x00, 0x00, 0x3C,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
  },
  {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x3C, 0x00, 0x00, 0x3C, 0x00, 0x00, 0x3C, 0x00, 0x00, 0x3C, 0x00, 0x00, 0x3C, 0x00, 0x00, 0x3C,
    0x00, 0x00, 0x3C, 0x00, 0x06, 0x3C, 0x60, 0x0E, 0x3C, 0x70, 0x0F, 0x3C, 0xF0, 0x0F, 0xBD, 0xF0,
    0x0F, 0xFF, 0xF0, 0x07, 0xFF, 0xE0, 0x03, 0xFF, 0xC0, 0x03, 0xFF, 0xC0, 0x01, 0xFF, 0x80, 0x00,
    0xFF, 0x00, 0x00, 0x7E, 0x00, 0x00, 0x7E, 0x00, 0x00, 0x3C, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
  }
};

const unsigned char PROGMEM start[] =
{
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
  0xFF, 0x80, 0x07, 0xFF, 0xE0, 0x07, 0xFF, 0xE0, 0x0F, 0xFF, 0xF0, 0x0F, 0xFF, 0xF0, 0x0F, 0xFF,
  0xF0, 0x0F, 0xCF, 0xF0, 0x0F, 0x87, 0xF0, 0x0F, 0x83, 0xF0, 0x0F, 0x81, 0xF0, 0x0F, 0x80, 0xF0,
  0x0F, 0x80, 0xF0, 0x0F, 0x81, 0xF0, 0x0F, 0x83, 0xF0, 0x0F, 0x87, 0xF0, 0x0F, 0x8F, 0xF0, 0x0F,
  0xDF, 0xF0, 0x0F, 0xFF, 0xF0, 0x0F, 0xFF, 0xF0, 0x07, 0xFF, 0xE0, 0x07, 0xFF, 0xE0, 0x01, 0xFF,
  0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

const unsigned char PROGMEM del[] =
{
  0x01, 0xF0, 0x00, 0x01, 0xF0, 0x00, 0x03, 0x18, 0x00, 0x3F, 0xFF, 0x80, 0x3F, 0xFF, 0x80, 0x20,
  0x00, 0x80, 0x20, 0x00, 0x80, 0x3F, 0xFF, 0x80, 0x3F, 0xFF, 0x80, 0x11, 0x11, 0x00, 0x11, 0x11,
  0x00, 0x11, 0x11, 0x00, 0x11, 0x11, 0x00, 0x11, 0x11, 0x00, 0x11, 0x11, 0x80, 0x11, 0x1F, 0xE0,
  0x11, 0x1E, 0xF0, 0x11, 0x18, 0x38, 0x11, 0x30, 0x18, 0x11, 0x20, 0x0C, 0x11, 0x66, 0x4C, 0x11,
  0x66, 0xC4, 0x11, 0x63, 0x84, 0x11, 0x63, 0x84, 0x11, 0x63, 0xC4, 0x11, 0x66, 0xCC, 0x11, 0x20,
  0x4C, 0x1F, 0xF0, 0x08, 0x1F, 0xF8, 0x18, 0x00, 0x1C, 0x30, 0x00, 0x0F, 0xE0, 0x00, 0x00, 0x00
};
#define SSD1306_LCDHEIGHT 64
#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

void setup()//初始設定
{
  // put your setup code here, to run once:
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  for (int i = 0; i < 10; i++)
    pic[i] = -1;
  delay(2000);
  // Clear the buffer.
  display.clearDisplay();
  for (int i = 0; i < 4; i++)
    display.drawBitmap(1 + i * 25, 32, picarray[i], 24, 32, 1);
  display.drawBitmap(102, 32, del, 24, 32, 1);
  display.drawRect(1, 33, 24, 29, WHITE);
  display.drawRect(1, 1, 24, 29, 1);
  display.drawTriangle(109, 11, 119, 15, 109, 21, WHITE);
  display.display();
  Serial.begin(9600);
  pinMode(3, INPUT_PULLUP);
  pinMode(2, INPUT_PULLUP);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(4, INPUT);
}

void curright(int8_t * cur, bool in)//下排游標右移
{
  display.drawRect(1 + (* cur) * 25, 1 + 32 * in, 24, 29, BLACK);
  (* cur) ++;
  if (* cur >= 5)
    * cur = 0;
  display.drawRect(1 + (* cur) * 25, 1 + 32 * in, 24, 29, WHITE);
  display.display();
}

void curleft(int8_t * cur, bool in)//下排游標左移
{
  display.drawRect(1 + (* cur) * 25, 1 + 32 * in, 24, 29, BLACK);
  (* cur) --;
  if ((* cur) < 0)
    (* cur) = 4;
  display.drawRect(1 + (* cur) * 25, 1 + 32 * in, 24, 29, WHITE);
  display.display();
}

void nextuprec(int8_t * up, int page, int move)//上排游標移動
{
  display.drawRect(page * 25 + 1, 1, 24, 29, 0);
  (* up) += move;
  display.drawRect((page + move) * 25 + 1, 1, 24, 29, 1);
}

void draw(int up)//畫指令的圖案
{
  if (pic[up] != -1)
  {
    if (up % 3 != 0)
      display.drawBitmap((up % 3) * 25 + 1, 1, picarray[pic[up]], 24, 32, 1);
    else
      display.drawBitmap(76, 1, picarray[pic[up]], 24, 32, 1);
  }
}

void loop()
{
  delay(5);
  int a0 = analogRead(A0), a1 = analogRead(A1), a2 = digitalRead(4);
  Serial.print(a0);
  Serial.print(a1);
  Serial.print(a2);
  Serial.println();
  // put your main code here, to run repeatedly:
  if (a0 > 1000)
  {
    if (!inverse)// 下半部
      curright(& count, !inverse); 
    else//上半部
    {
      if (up <= 3)  //上排第一頁
      {
        if (up == 3) //第一頁最後一個圖案
        {
          display.fillRect(1, 1, 100, 32, 0);
          display.drawTriangle(9, 15, 19, 11, 19, 21, WHITE);
          display.drawRect(26, 1, 24, 29, 1);
          up++;
          for (int i = 4; i < 7; i++)
          {
            draw(i);
          }
        }
        else
          nextuprec(& up, up, 1);  //其他
      }
      else
        if (up <= 6)  //上排第二頁
        {
          if (up == 6)//第二頁最後一個圖案
          {
            display.fillRect(26, 1, 75, 32, 0);
            display.drawRect(76, 1, 24, 29, 0);
            up++;
            display.drawRect(26, 1, 24, 29, 1);
            for (int i = 7; i < 10; i++)
            {
              draw(i);
            }
            display.drawBitmap(101, 1, start, 24, 32, 1);
          }
          else
            nextuprec(& up, up - 3, 1);//其他
        }
      else
        if (up <= 10)//上排第三頁
        {
          if (up == 10)//第一頁最後一個圖案
          {
            up = 0;
            display.fillRect(0, 0, 127, 32, 0);
            display.drawTriangle(109, 11, 119, 15, 109, 21, WHITE);
            display.drawRect(1, 1, 24, 29, 1);
            for (int i = 0; i < 4; i++)
              if (pic[0] == i)
              {
                display.drawBitmap(1, 1, picarray[i], 24, 32, 1);
                break;
              }
            for (int i = 1; i < 4; i++)
            {
              draw(i);
            }
          }
          else
            nextuprec(& up, up - 6, 1);
        }
      display.display();
    }
  }
  else
    if (a0 < 10)//往左
    {
      //同往右
      if (!inverse)
        curleft(& count, !inverse);
      else
      {
        if (up <= 3)
        {
          if (up == 0)
          {
            up = 10;
            display.fillRect(1, 1, 127, 32, 0);
            display.drawTriangle(9, 15, 19, 11, 19, 21, WHITE);
            display.drawBitmap(101, 1, start, 24, 32, 1);
            display.drawRect(101, 1, 24, 29, 1);
            for (int i = 7; i < 10; i++)
            {
              draw(i);
            }
          }
          else
          {
            nextuprec(& up, up, -1);
          }
        }
        else
          if (up <= 6)
          {
            if (up == 4)
            {
              up--;
              display.fillRect(1, 1, 100, 32, 0);
              display.drawRect(76, 1, 24, 29, 1);
              for (int i = 0; i < 4; i++)
                if (pic[0] == i)
                {
                  display.drawBitmap(1, 1, picarray[i], 24, 32, 1);
                  break;
                }
              for (int i = 1; i < 4; i++)
              {
                draw(i);
              }
            }
            else
            {
              nextuprec(& up, up - 3, -1);
            }
          }
        else
        {
          if (up == 7)
          {
            up--;
            display.fillRect(26, 1, 100, 32, 0);
            display.drawTriangle(109, 11, 119, 15, 109, 21, WHITE);
            display.drawRect(76, 1, 24, 29, 1);
            for (int i = 4; i < 7; i++)
            {
              draw(i);
            }
          }
          else
          {
            nextuprec(& up, up - 6, -1);
          }
        }
        display.display();
      }
    }
  else 
    if ((!a2) && (!inverse) && up != 10) //新增指令圖案
    {
      int pos;//畫在哪個位置
      if (up <= 3)
        pos = 1 + up * 25;
      else
        if (up <= 6)
          pos = 1 + (up - 3) * 25;
      else
        if (up <= 9)
          pos = 1 + (up - 6) * 25;
      if (count != 4)//不是刪除
      {
        pic[up] = count;
        up++;
        if (up == 4)//輸入圖案後換頁
        {
          display.fillRect(1, 1, 100, 32, 0);
          display.drawRect(26, 1, 24, 29, 1);
          display.drawTriangle(9, 15, 19, 11, 19, 21, WHITE);
          for (int i = 4; i < 7; i++)
          {
            draw(i);
          }
        }
        else
          if (up == 7)//輸入圖案後換頁
          {
            display.fillRect(26, 1, 100, 32, 0);
            display.drawRect(26, 1, 24, 29, 1);
            display.drawBitmap(101, 1, start, 24, 32, 1);
            for (int i = 7; i < 10; i++)
            {
              draw(i);
            }
          }
        else//一般輸入圖案
        {
          display.fillRect(pos, 1, 24, 29, 0);
          for (int i = 0; i < 4; i++)
            if (i == count)
            {
              display.drawBitmap(pos, 0, picarray[i], 24, 32, 1);
              break;
            }
          display.drawRect(pos + 25, 1, 24, 29, 1);
        }
      }
      else  //刪除
      {
        pic[up] = -1;
        display.fillRect(pos, 1, 24, 29, 0);
        up--;
        if (up == -1 || up == 6 || up == 3)
        {
          up++;
          display.drawRect(pos, 1, 24, 29, 1);
        }
        else
          display.drawRect(pos - 25, 1, 24, 29, 1);
      }
      display.display();
    }
  else
    if ((!a2) && inverse && up == 10)  //馬達開跑！！
    {
      //請使用者輸入loop數量
      display.fillRect(1, 1, 127, 32, 0);
      display.setTextColor(WHITE);
      display.setCursor(1, 0);
      display.setTextSize(4);
      display.println("LOOP");
      display.setCursor(100, 1);
      display.write(49);
      display.display();
      int loop = 1;
      while (1)
      {
        a2 = digitalRead(4);
        a1 = analogRead(A1);
        if (a1 <10&&loop<9)//loop++最大到9
        {
          loop++;
          display.fillRect(100, 1, 24, 29, 0);
          display.setCursor(100, 1);
          display.write(loop + 48);
          display.display();
        }
        else
          if (a1 >1000 && loop > 1)//loop--最小到1
          {
            loop--;
            display.fillRect(100, 1, 24, 29, 0);
            display.setCursor(100, 1);
            display.write(loop + 48);
            display.display();
          }
        else
          if (a2 == 0)//按確認鍵，開跑
            break;
      }
      //從第一個指令開始跑
      display.fillRect(1, 1, 127, 32, 0);
      display.drawRect(1, 1, 24, 29, 1);
      display.drawTriangle(109, 11, 119, 15, 109, 21, WHITE);
      int picnum=0;//數有幾個指令
      
      for(int i=0;i<10;i++)
        if(pic[i]!=-1)
          picnum++;
      for(int j=0;j<loop;j++)
      {
        int num=picnum;
        for (int i = 0; i < 10&&num>=0; i++)
        {
          activepic(i);//跑圖片
          active(i,pic);//跑馬達
          if(pic[i]!=-1)
            num--;
        }
      
      }
      //初始化回來
      for(int i=0;i<10;i++)
        pic[i]=-1;
      count = 0;
      up = 0;
      display.drawRect(1, 1, 24, 29, 1);
      display.display();
    }
  else //上排還是下排
    if (a1 < 10 || a1 > 1000)
    {
      inverse = !inverse;
      display.invertDisplay(inverse);
      display.drawRect(1 + count * 25, 33, 24, 29, !inverse);
      display.display();
    }
}

void activepic(int initial)
{
  display.fillRect(1, 1, 100, 32, 0);
  for (int i = initial;(i < initial + 4) && (i <= 9); i++)
  {
    if (pic[i] == -1)
      continue;
    display.drawBitmap((i - initial) * 25 + 1, 0, picarray[pic[i]], 24, 32, 1);
  }
  display.drawRect(1, 1, 24, 29, 1);
  display.display();
}
void active(int move,int8_t pic[]){
  if (pic[move] == 0)
      motor.turnDeg(90);  //turnleft
  else if (pic[move] == 1)
      motor.turnDeg(-90);   //turnright
  else if (pic[move] == 2)
      motor.runDist(40);  //forward
  else if (pic[move] == 3)
      motor.runDist(-40);//back
  delay(100);
}