// Ex1

int ms=0, poz=0, value=0;
char adc_low=0, adc_high=0;

void display(char p, char c)
{
 PORTA &= 0b11110000;
 PORTC &= 0b00000000;

  switch(c){
     case 0: PORTC|=0b00111111; break;
     case 1: PORTC|=0b00000110; break;
     case 2: PORTC|=~0b10100100; break;
     case 3: PORTC|=~0b10110000; break;
     case 4: PORTC|=~0b10011001; break;
     case 5: PORTC|=~0b10010010; break;
     case 6: PORTC|=~0b10000010; break;
     case 7: PORTC|=~0b11111000; break;
     case 8: PORTC|=~0b10000000; break;
     case 9: PORTC|=~0b10010000; break;
  }
  switch(p){
      case 1: PORTA|=0b00001000; break;
      case 2: PORTA|=0b00000100; break;
      case 3: PORTA|=0b00000010; break;
      case 4: PORTA|=0b00000001; break;
  }
}

void init_timer()
{
      SREG |= 1<<7;
      TCCR0 = 0b00001011; //CTC-3,6, Prescaler-0,1,2
      TCNT0 = 0;
      OCR0 = 125;
      TIMSK |= 0b00000010;//set interrupt OCM
}

void Init_adc(){
      ADMUX  = 0b01000000; //Referin.a - AVCC
      ADCSRA = 0b10000111; //Activare ADC; Prescaler = 128;
}

int readADC(char ch){
      ADMUX &= 0b11100000;
      ADMUX |= ch;
      ADCSRA |= 1<<6;
      while(ADCSRA & (1<<6));
      adc_low = ADCL;
      adc_high = ADCH;
      return  ((adc_high <<8) | adc_low);   //Returneaza rezultatul conversiei
}

void Timer0_ISR() iv IVT_ADDR_TIMER0_COMP{
     poz++;
        switch(poz)
        {
                case 1: display(1,value%10);break;
                case 2: display(2,(value/10)%10);break;
                case 3: display(3,(value/100)%10);break;
                case 4: display(4,(value/1000)%10); poz=0;break;
        }
        if (ms==999)
        {
            value=readADC(6);
            ms=0;
        }
        else
            ms++;
}

void main()
{
  DDRA = 0b00001111;  //seteaza pinii de iesire
  DDRC = 0b11111111;

  init_timer();
  Init_adc();
  ms=0;
}



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Ex2

int ms=0, poz=0, value=0;
char adc_low=0, adc_high=0;

int adc, T=0;
float Vin, tmp;

void display(char p, char c)
{
 PORTA &= 0b11110000;
 PORTC &= 0b00000000;

  switch(c){
     case 0: PORTC|=0b00111111; break;
     case 1: PORTC|=0b00000110; break;
     case 2: PORTC|=~0b10100100; break;
     case 3: PORTC|=~0b10110000; break;
     case 4: PORTC|=~0b10011001; break;
     case 5: PORTC|=~0b10010010; break;
     case 6: PORTC|=~0b10000010; break;
     case 7: PORTC|=~0b11111000; break;
     case 8: PORTC|=~0b10000000; break;
     case 9: PORTC|=~0b10010000; break;
  }
  switch(p){
      case 1: PORTA|=0b00001000; break;
      case 2: PORTA|=0b00000100; break;
      case 3: PORTA|=0b00000010; break;
      case 4: PORTA|=0b00000001; break;
  }
}

// Function to initialize the timer
void init_timer()
{
    // Enable global interrupts
    SREG |= 1 << 7;

    // Configure Timer 0 for Clear Timer on Compare (CTC) mode with a prescaler of 64
    TCCR0 = 0b00001011; // CTC-3,6, Prescaler-0,1,2

    // Initialize Timer/Counter Register to 0
    TCNT0 = 0;

    // Set the value for the compare match (output compare register)
    OCR0 = 125;

    // Enable Timer/Counter 0 Output Compare Match interrupt
    TIMSK |= 0b00000010; // Set interrupt OCM
}

// Function to initialize the analog-to-digital converter (ADC)
void Init_adc()
{
    // Set the voltage reference to AVCC (5V)
    ADMUX = 0b01000000; // Reference voltage - AVCC

    // Enable ADC and set the prescaler to 128
    ADCSRA = 0b10000111; // Enable ADC; Prescaler = 128

    // Enable ADC Auto Triggering and set the interrupt flag
    ADCSRA |= (1 << 3);
}

// Function to read ADC with interrupts based on the specified channel (ch)
void readADC_interrupt(char ch)
{
    // Reset the channel for conversion
    ADMUX &= 0b11100000;

    // Set the specified channel for conversion
    ADMUX |= ch;

    // Start ADC conversion
    ADCSRA |= (1 << 6);
}

void ADC_Completed() iv IVT_ADDR_ADC{
      adc_low = ADCL;
      adc_high = ADCH;
      adc = (adc_high << 8) | adc_low;
      Vin = ((float)adc*5)/1024;
      tmp = Vin*1000/10;
      T = (int)tmp;
}


void Timer0_ISR() iv IVT_ADDR_TIMER0_COMP{
     poz++;
        switch(poz)
        {
                case 1: display(1,value%10);break;
                case 2: display(2,(value/10)%10);break;
                case 3: display(3,(value/100)%10);break;
                case 4: display(4,(value/1000)%10); poz=0;break;
        }
        if (ms==999)
        {
            readADC_interrupt(7);
            value = T;
            // value=readADC(6);
            ms=0;
        }
        else
            ms++;
}

void main()
{
  DDRA = 0b00001111;  //seteaza pinii de iesire
  DDRC = 0b11111111;

  init_timer();
  Init_adc();
  ms=0;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Ex 3 & extra

int ms=0,m=0, s=0, poz=0, adv=0, value=0, test=0;
char adclow=0, adchigh=0;

int adc, T=0;
float Vin, tmp;

int selection = 0;  //potentiometru/temp

void display(char p, char c)
{
 PORTA &= 0b11110000;
 PORTC &= 0b00000000;

  switch(c){
     case 0: PORTC|=0b00111111; break;
     case 1: PORTC|=0b00000110; break;
     case 2: PORTC|=~0b10100100; break;
     case 3: PORTC|=~0b10110000; break;
     case 4: PORTC|=~0b10011001; break;
     case 5: PORTC|=~0b10010010; break;
     case 6: PORTC|=~0b10000010; break;
     case 7: PORTC|=~0b11111000; break;
     case 8: PORTC|=~0b10000000; break;
     case 9: PORTC|=~0b10010000; break;
  }
  switch(p){
      case 1: PORTA|=0b00001000; break;
      case 2: PORTA|=0b00000100; break;
      case 3: PORTA|=0b00000010; break;
      case 4: PORTA|=0b00000001; break;
  }
}

void init_timer()
{
      SREG |= 1<<7;
      TCCR0 = 0b00001011; //CTC-3,6, Prescaler-0,1,2
      TCNT0 = 0;
      OCR0 = 125;
      TIMSK |= 0b00000010;//set interrupt OCM
}

void init_adc(){
      ADMUX = 0b01000000; //Referin.a - AVCC
      ADCSRA = 0b10000111; //Activare ADC; Prescaler = 128;
}

int readADC(char ch){
      ADMUX &= 0b11100000;
      ADMUX |= ch;
      ADCSRA |= 1<<6;
      while(ADCSRA & (1<<6));
      adclow = ADCL;
      adchigh = ADCH;
      return  adchigh<<8 | adclow;   //Returneaza rezultatul conversiei
}

void readADC_interrupt(char ch){
      ADMUX &= 0b11100000; //Reseteaz? canalul de conversie
      ADMUX |= ch; //Seteaz? canalul
      ADCSRA |= (1<<6); //?ncepe conversia
}

void ADC_Completed() iv IVT_ADDR_ADC{
      adclow = ADCL;
      adchigh = ADCH;
      adc = (adchigh << 8) | adclow;
      Vin = ((float)adc*5)/1024;
      tmp = Vin*1000;
      T = (int)tmp;
}


void Timer0_ISR() iv IVT_ADDR_TIMER0_COMP{
     poz++;
        switch(poz)
        {
                case 1: display(1,value%10);break;
                case 2: display(2,(value/10)%10); 
                 if (selection == 0) PORTC |= 0b10000000; break;
                case 3: display(3,(value/100)%10);break;
                case 4: display(4,(value/1000)%10); poz=0;break;
        }
        if (ms==100)
        {
            if (selection)
               value=readADC(6);
            else
            {
               readADC_interrupt(7);
               value = T;
            }
            ms=0;
        }
        else
            ms++;
}

void switch_int() iv IVT_ADDR_INT0{
       init_adc();
       ADCSRA ^= (1<<3); //Activare ?ntrerupere ADIE
       selection ^= 1;
}

void init_external_int(){
  GICR |=  0b01000000;
  MCUCR |= 0b00000010; // precizare c? evenimentul va avea
}

void main()
{
  DDRA = 0b00001111;  //seteaza pinii de iesire
  DDRC = 0b11111111;

  init_timer();
  init_external_int();
  init_adc();
  selection=1;
  m=0;
}
