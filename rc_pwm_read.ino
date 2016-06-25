#define INTERRUPT 0
#define INTERRUPT_PIN 2
//interrupt index is 0, which refers to physical pin 2 on the arduino
#define PULSE_WIDTH_NEUTRAL 1500
//pulse width, in microseconds, which describes neutral, or 90/180 degrees rotation to the servo

volatile int dutyCycle = PULSE_WIDTH_NEUTRAL;
volatile unsigned long pulseStartTime = 0;


void setup() 
{
  // put your setup code here, to run once:
  attachInterrupt(INTERRUPT, readPWM, CHANGE);
  Serial.begin(9600); 

}

void loop() 
{
  //the interrupt code will run independently of this code, so just loop reading the PWM signal.
  Serial.print("Current Duty Cycle");
  Serial.println(dutyCycle);
}

void readPWM()
{
  if(digitalRead(INTERRUPT_PIN) == HIGH)
  { 
    //set start time of the leading edge of the PWM pulse using the slightly innacurate microseconds function provided by the arduino
    //under load this can become innaccurate.
    pulseStartTime = micros();
  }
  else
  {
    //falling edge of the pulse, so subtract current time from start time to get the length of the duty cycle pulse.
          dutyCycle = (int)(micros() - pulseStartTime);
  }
}

