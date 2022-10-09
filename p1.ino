// C++ code
//
int curr_col; //current col
int curr_row; //current row

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
        pinMode(i, INPUT);
    }
  
    pinMode(0, OUTPUT); //buzzer
}

void loop(){
    int tmp = curr_col * 3 + curr_row;
    digitalWrite(tmp, HIGH);

    int target;
    target = CheckTarget(tmp); 

    int flag = 0;
    for(int i = 0; i < 700; i++){
        if(digitalRead(target) == HIGH && curr_row == 3){
            reset();
            Buzz(1000);
            flag = 1;
            delay(500);
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