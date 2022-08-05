#define IR 4
#define pump 6
int timer=0;
int offtime = 10000;
int x = 0;
bool ir_val =0;

void setup()
{
  Serial.begin(9600);
  pinMode(IR, INPUT);
  pinMode(pump, OUTPUT);
}

void loop()
{
  ir_val = digitalRead(IR);
  if(ir_val == LOW && timer<=offtime){
    timer++;
    delay(500);
  }else{
    timer = 0;
  }

  if(timer == 0 || timer>1){
    digitalWrite(pump, HIGH);
  }else{
    digitalWrite(pump, LOW);
  }
  }
