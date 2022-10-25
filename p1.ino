// C++ code
//
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

int curr_col; //current col
int curr_row; //current row
int point = 0;


int CheckTarget(int tmp){
    int target;
    if(tmp > 6) target = 12;
    else if(tmp > 3) target = 11;
    else target = 10;
    return target;
}

void reset(){
    curr_col = random(0, 3);
    curr_row = 1;
}

void Buzz(int val){
    tone(0, val);
    delay(100);
    noTone(0);
}

void setup(){
    reset();         
  
    for(int i = 1; i <= 9; i++){ //let led pinmode = output
        pinMode(i, OUTPUT);
    }
    for(int i = 10; i <= 12; i++){ //let butten pinmode = INPUT
        pinMode(i, INPUT_PULLUP);
    }
    pinMode(13, OUTPUT);         //let white led pinmode = output
    pinMode(0, OUTPUT); //buzzer

    lcd.init();
    lcd.blacklight();
}

void loop(){
    char s1[20];

    lcd.setCursor(2, 0); 
    sprintf(s1, "point: %d", point);
    lcd.print(s1);
    lcd.setCursor(0, 1); 
    if(point == 20){
        digitalWrite(13, HIGH);
        lcd.print("!!YOU WIN !!");
        exit(0);
    }	
    else{
        lcd.print("target: 20");
    }
    
    int tmp = curr_col * 3 + curr_row;
    digitalWrite(tmp, HIGH);

    int target;
    target = CheckTarget(tmp); 

    int flag = 0;
    for(int i = 0; i < 700; i++){
        if(digitalRead(target) == LOW && curr_row == 3){
            reset();
            Buzz(1000);
            flag = 1;
            delay(500);
          	point++;
            break;
        }
        delay(1);
    }
  
    digitalWrite(tmp, LOW);
  
    if(flag == 0){
        curr_row++;
        if(curr_row == 4){
            reset();
            Buzz(0);
            delay(2000);
        }
    }
}