/*
SOURCE CODE TRAFFIC LIGHT
@Author : Nguyen Van Tu
v0.0.0
*/
// Khai báo các chân kết nối với IC 74hc595 và LED 7 đoạn
#define latchPin 8   // RCLK
#define clockPin 12  //SRCLK
#define dataPin 11   //SER
//Khai báo Digital_Output cho Đèn
//Example:
#define LED_GREEN 13
#define LED_YELLOW 10
#define LED_RED 9

const int digit[10] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F}; // Mã Hex 7-seg cathode 
// Thời gian đếm ngược (giây)
int time_ledGREEN = 27; 
int time_ledYELLOW = 3;
int time_ledRED = time_ledGREEN + time_ledYELLOW;
//--------------------------
int check = 0;
//-------------------Hàm Xử Lý Led 7 Thanh-----------------------------------
void displayNumber(int number) {
  int digitOne = number % 10; // Lấy chữ số đơn vị
  int digitTwo = number / 10; // Lấy chữ số hàng chục
  // Chuyển đổi giá trị của chữ số đơn vị và hiển thị lên LED 7 đoạn thứ hai
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, digit[digitOne]);
  shiftOut(dataPin, clockPin, MSBFIRST, digit[digitTwo]);
  digitalWrite(latchPin, HIGH);
}

void LED_7SEG(int time){
  for (int i = time; i >= 0; i--) {
    displayNumber(i); // Hiển thị số trên LED 7 đoạn
    delay(500); // Đợi 1 giây
  }
}
//------------------Hàm Điều Khiển LED----------------------------------------
void LED_GREEN(){
  digitalWrite(LED_GREEN,HIGH);
  digitalWrite(LED_YELLOW,LOW);
  digitalWrite(LED_RED,LOW);
  LED_7SEG(time_ledGREEN);
}
void LED_YELLOW(){
  digitalWrite(LED_GREEN,LOW);
  digitalWrite(LED_YELLOW,HIGH);
  digitalWrite(LED_RED,LOW);
  LED_7SEG(time_ledYELLOW);
}
void LED_RED(){
  digitalWrite(LED_GREEN,LOW);
  digitalWrite(LED_YELLOW,LOW);
  digitalWrite(LED_RED,HIGH);
  LED_7SEG(time_ledRED);
}

void LED_Traffic(int check){
  switch(check){
    case 0:
      // statements
      LED_GREEN();
      break;
    case 1:
      // statements
      LED_YELLOW();
      break;
    case 2:
      // statements
      LED_RED();
      break;
    case 3:
      check = 0;
      break;
    default:
      // default statements
      break;
  }
}
  

void setup() {
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  //set mode của pin LED ở đây
  //Example:
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
  pinMode(LED_RED, OUTPUT);
}

void loop() {
  do{
    LED_Traffic(check);
    check++
    //reset biến check
    if(check == 3){
      check = 0;
    }
  }
  while(check <=3);
}
