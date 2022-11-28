// C++ code
//
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

int curr_col; //current col
int curr_row; //current row
int point = 0;
int speed_time;
int game_mode = 48763; //0: easy_mode 1: hard_mode

int CheckTarget(int tmp){
    int target;
    if(tmp > 6) target = 12;
    else if(tmp > 3) target = 11;
    else target = 10;
    return target;
}

void reset(){
    if(game_mode == 0){
      speed_time = random(4, 8) * 100;
    }
    else{
      speed_time = random(1, 5) * 100;
    }
    curr_col = random(0, 3);
    curr_row = 1;
}

void Buzz(int val){
    tone(A0, val);
    delay(100);
    noTone(A0);
}

void setup(){
    reset();         
    Serial.begin(9600);

    pinMode(A1, OUTPUT);
    for(int i = 2; i <= 9; i++){ //let led pinmode = output
        pinMode(i, OUTPUT);
    }
    for(int i = 10; i <= 12; i++){ //let butten pinmode = INPUT
        pinMode(i, INPUT_PULLUP);
    }
    
    pinMode(13, OUTPUT);         //let white led pinmode = output
    pinMode(A0, OUTPUT); //buzzer

    lcd.init();
    lcd.backlight();
    
    lcd.setCursor(0, 0); 
    lcd.print("Easy_mode Left");
    lcd.setCursor(0, 1);
    lcd.print("Hard_mode Right"); 
    while(true){
        if(digitalRead(10) == LOW){
          lcd.clear();
          game_mode = 0;
          lcd.setCursor(0, 0);
          lcd.print("Easy_mode");
          lcd.setCursor(0, 1);
          lcd.print("Start!!");
          delay(2000);
          break;
        }
        else if(digitalRead(12) == LOW){
          lcd.clear();
          game_mode = 1;
          lcd.setCursor(0, 0);
          lcd.print("Hard_mode");
          lcd.setCursor(0, 1);
          lcd.print("Start!!");
          delay(2000);
          break;
        }
    }

    
}

void loop(){
    lcd.clear();
    char s1[20];
    Serial.println(point);
    lcd.setCursor(0, 0); 
    sprintf(s1, "point: %d", point);
    lcd.print(s1);
    lcd.setCursor(0, 1); 
    if(point == 20){
        Serial.println(game_mode);
        digitalWrite(13, HIGH);
        lcd.print("!!Finish!!");
        exit(0);
    } 
    else{
        lcd.print("target: 20");
    }
    
    int tmp = curr_col * 3 + curr_row;
    
    if(tmp != 1) digitalWrite(tmp, HIGH);
    else digitalWrite(A1, HIGH);
    

    int target;
    target = CheckTarget(tmp); 

    int flag = 0;
    for(int i = 0; i < speed_time; i++){
        if(digitalRead(target) == LOW && curr_row == 3){
            reset();
            Buzz(1000);
            flag = 1;
            delay(500);
            point++;
            break;
        }
        else if(digitalRead(target) == LOW && curr_row != 3){
            reset();
            Buzz(0);
            delay(2000);
            break;
        }
        delay(1);
    }
  
    if(tmp != 1) digitalWrite(tmp, LOW);
    else digitalWrite(A1, LOW);
  
    if(flag == 0){
        curr_row++;
        if(curr_row == 4){
            reset();
            Buzz(0);
            delay(2000);
        }
    }
}