/*************  1. define statement       *****************/
#define latchPin  2   //  Arduino Pins
#define clockPin  3
#define dataPin   4

/*************  2. Static variable        *****************/
static volatile bool dataBit = 0;

/*************  3. Static funtion declaration *****************/
static void clkPulse(int clk);
static void bitWrt(bool dataBit);
static void shiftOutData(int data);

/*************  4. main, setup, loop from Arduino   *****************/
volatile int dataByte = 0;

void setup()
{
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  
  initSR();
  dataByte = 0b1110110011111111;    //  Sample 16-bit data
}

void loop()
{
  shiftAllData(dataByte);
  while(1);
}

/*************  5. Static function definition  *****************/
void initSR(void)
{
  digitalWrite(latchPin, LOW);
  digitalWrite(clockPin, LOW);
  digitalWrite(dataPin, LOW);
}

static void clkPulse(int clk)
{
  digitalWrite(clk, HIGH);
  delay(10);
  digitalWrite(clk, LOW);
  delay(10);
}

static void shiftOutData(int data)
{
  for (int i=7; i>=0; i--)
  {
    dataBit = data & (1 << i);
    bitWrt(dataBit);
  }
  
  clkPulse(latchPin); 
}

static void bitWrt(bool dataBit)
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
