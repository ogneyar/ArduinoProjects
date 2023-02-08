
// LGT8F328P

// 5641AS_4x7seg
/*
12,9,8,6 - GND
11,7,4,2,1,10,5,3 - VCC
*/
#define _1 13
#define _2 2
#define _3 3
#define _4 4
#define _5 5
#define _6 6
#define _7 7
#define _8 8
#define _9 9
#define _10 10
#define _11 11
#define _12 12

#define _1_seg _12
#define _2_seg _9
#define _3_seg _8
#define _4_seg _6

#define _1_cif _11
#define _2_cif _7
#define _3_cif _4
#define _4_cif _2
#define _5_cif _1
#define _6_cif _10
#define _7_cif _5

#define _point _3

static uint8_t flag = 0;


void send(uint8_t segment, uint8_t data, bool point = false);
void all_ON(void);


void setup() {
  pinMode(_1_cif, OUTPUT);
  pinMode(_2_cif, OUTPUT);
  pinMode(_3_cif, OUTPUT);
  pinMode(_4_cif, OUTPUT);
  pinMode(_5_cif, OUTPUT);
  pinMode(_6_cif, OUTPUT);
  pinMode(_7_cif, OUTPUT);

  pinMode(_point, OUTPUT);
}

void loop() {
  // all_ON();
  send(1, 1);
  send(2, 8, true);
  send(3, 2);
  send(4, 7);
}

// вывод числа
void send(uint8_t segment, uint8_t data, bool point) 
{
  switch(segment) {
  case 4:
    pinMode(_1_seg, INPUT);
    pinMode(_2_seg, INPUT);
    pinMode(_3_seg, INPUT);
    pinMode(_4_seg, OUTPUT);
  break;
  case 3:
    pinMode(_1_seg, INPUT);
    pinMode(_2_seg, INPUT);
    pinMode(_3_seg, OUTPUT);
    pinMode(_4_seg, INPUT);
  break;
  case 2:
    pinMode(_1_seg, INPUT);
    pinMode(_2_seg, OUTPUT);
    pinMode(_3_seg, INPUT);
    pinMode(_4_seg, INPUT);
  break;
  default:
    pinMode(_1_seg, OUTPUT);
    pinMode(_2_seg, INPUT);
    pinMode(_3_seg, INPUT);
    pinMode(_4_seg, INPUT);
  break;
  }
  
  switch(data) {
  case 9:
    digitalWrite(_1_cif, HIGH);
    digitalWrite(_2_cif, HIGH);
    digitalWrite(_3_cif, HIGH);
    digitalWrite(_4_cif, HIGH);
    digitalWrite(_5_cif, LOW);
    digitalWrite(_6_cif, HIGH);
    digitalWrite(_7_cif, HIGH);
  break;
  case 8:
    digitalWrite(_1_cif, HIGH);
    digitalWrite(_2_cif, HIGH);
    digitalWrite(_3_cif, HIGH);
    digitalWrite(_4_cif, HIGH);
    digitalWrite(_5_cif, HIGH);
    digitalWrite(_6_cif, HIGH);
    digitalWrite(_7_cif, HIGH);
  break;
  case 7:
    digitalWrite(_1_cif, HIGH);
    digitalWrite(_2_cif, HIGH);
    digitalWrite(_3_cif, HIGH);
    digitalWrite(_4_cif, LOW);
    digitalWrite(_5_cif, LOW);
    digitalWrite(_6_cif, LOW);
    digitalWrite(_7_cif, LOW);
  break;
  case 6:
    digitalWrite(_1_cif, HIGH);
    digitalWrite(_2_cif, LOW);
    digitalWrite(_3_cif, HIGH);
    digitalWrite(_4_cif, HIGH);
    digitalWrite(_5_cif, HIGH);
    digitalWrite(_6_cif, HIGH);
    digitalWrite(_7_cif, HIGH);
  break;
  case 5:
    digitalWrite(_1_cif, HIGH);
    digitalWrite(_2_cif, LOW);
    digitalWrite(_3_cif, HIGH);
    digitalWrite(_4_cif, HIGH);
    digitalWrite(_5_cif, LOW);
    digitalWrite(_6_cif, HIGH);
    digitalWrite(_7_cif, HIGH);
  break;
  case 4:
    digitalWrite(_1_cif, LOW);
    digitalWrite(_2_cif, HIGH);
    digitalWrite(_3_cif, HIGH);
    digitalWrite(_4_cif, LOW);
    digitalWrite(_5_cif, LOW);
    digitalWrite(_6_cif, HIGH);
    digitalWrite(_7_cif, HIGH);
  break;
  case 3:
    digitalWrite(_1_cif, HIGH);
    digitalWrite(_2_cif, HIGH);
    digitalWrite(_3_cif, HIGH);
    digitalWrite(_4_cif, HIGH);
    digitalWrite(_5_cif, LOW);
    digitalWrite(_6_cif, LOW);
    digitalWrite(_7_cif, HIGH);
  break;
  case 2:
    digitalWrite(_1_cif, HIGH);
    digitalWrite(_2_cif, HIGH);
    digitalWrite(_3_cif, LOW);
    digitalWrite(_4_cif, HIGH);
    digitalWrite(_5_cif, HIGH);
    digitalWrite(_6_cif, LOW);
    digitalWrite(_7_cif, HIGH);
  break;  
  case 1:
    digitalWrite(_1_cif, LOW);
    digitalWrite(_2_cif, HIGH);
    digitalWrite(_3_cif, HIGH);
    digitalWrite(_4_cif, LOW);
    digitalWrite(_5_cif, LOW);
    digitalWrite(_6_cif, LOW);
    digitalWrite(_7_cif, LOW);
  break;
  default:
    digitalWrite(_1_cif, HIGH);
    digitalWrite(_2_cif, HIGH);
    digitalWrite(_3_cif, HIGH);
    digitalWrite(_4_cif, HIGH);
    digitalWrite(_5_cif, HIGH);
    digitalWrite(_6_cif, HIGH);
    digitalWrite(_7_cif, LOW);
  break;
  }

  if (point) {    
    digitalWrite(_point, HIGH);
  }else { 
    digitalWrite(_point, LOW);
  }
  delay(3);
}

// 4 восьмёрки с точками
void all_ON(void) {
  if ( ! flag || flag > 4) {
    flag = 1;
  }
  switch(flag) {
  case 4:
    pinMode(_1_seg, INPUT);
    pinMode(_2_seg, INPUT);
    pinMode(_3_seg, INPUT);
    pinMode(_4_seg, OUTPUT);
  break;
  case 3:
    pinMode(_1_seg, INPUT);
    pinMode(_2_seg, INPUT);
    pinMode(_3_seg, OUTPUT);
    pinMode(_4_seg, INPUT);
  break;
  case 2:
    pinMode(_1_seg, INPUT);
    pinMode(_2_seg, OUTPUT);
    pinMode(_3_seg, INPUT);
    pinMode(_4_seg, INPUT);
  break;
  default:
    pinMode(_1_seg, OUTPUT);
    pinMode(_2_seg, INPUT);
    pinMode(_3_seg, INPUT);
    pinMode(_4_seg, INPUT);
  break;
  }
  digitalWrite(_1_cif, HIGH);
  digitalWrite(_2_cif, HIGH);
  digitalWrite(_3_cif, HIGH);
  digitalWrite(_4_cif, HIGH);
  digitalWrite(_5_cif, HIGH);
  digitalWrite(_6_cif, HIGH);
  digitalWrite(_7_cif, HIGH);
  digitalWrite(_point, HIGH);
  flag++;
}
