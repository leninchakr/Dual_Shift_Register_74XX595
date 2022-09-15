/*************  1. External header files    *****************/


/*************  2. define statement       *****************/
#define latchPin  2
#define clockPin  3
#define dataPin   4

/*************  3. Global variable        *****************/


/*************  4. Static variable        *****************/
volatile int dataByte = 0;
volatile bool dataBit = 0;

/*************  5.  User defined variables    *****************/


/*************  6. Global funtion declaration   *****************/


/*************  7. Static funtion declaration *****************/
void initSR(void);
void clkPulse(int clk);
void bitWrt(bool dataBit);
void shiftOutData(int data);
void shiftAllData(int dataByte);

/*************  8. main, setup, loop      *****************/
void setup()
{
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  
  initSR();
  dataByte = 0b1110110011111111;
}

void loop()
{
  shiftAllData(dataByte);
  while(1);
}

/*************  9. Global function definition *****************/


/*************  10. Static function definition  *****************/
void  initSR(void)
{
  digitalWrite(latchPin, LOW);
  digitalWrite(clockPin, LOW);
  digitalWrite(dataPin, LOW);
}

void clkPulse(int clk)
{
  digitalWrite(clk, HIGH);
  delay(10);
  digitalWrite(clk, LOW);
  delay(10);
}

void shiftOutData(int data)
{
  for (int i=7; i>=0; i--)
  {
    dataBit = data & (1 << i);
    bitWrt(dataBit);
  }
  
  clkPulse(latchPin); 
}

void bitWrt(bool dataBit)
{
  digitalWrite(dataPin, dataBit);
  clkPulse(clockPin);
}

void shiftAllData(int dataByte)
{
  int dummyLsb = dataByte & 0b11111111;
  shiftOutData(dummyLsb);
  int dummyUsb = (dataByte >> 8);
  shiftOutData(dummyUsb);
}

/*************  11. ISR definition        *****************/
