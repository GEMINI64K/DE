int digit=0;
int s=0, ms=0, m=0;

void display(char p, char c)
{
    PORTA &= 0b11110000; //liniile de sel. digit - oprite
    PORTC &= 0b00000000; //liniile de sel. Seg. - oprite
     switch(c){
      case 0:PORTC |= 0b00111111;break;//codificare cifra 0
      case 1:PORTC |= 0b00000110;break;
      case 2:PORTC |= 0b01011011;break;
      case 3:PORTC |= 0b01001111;break;
      case 4:PORTC |= 0b01100110;break;
      case 5:PORTC |= 0b01101101;break;
      case 6:PORTC |= 0b01111101;break;
      case 7:PORTC |= 0b00000111;break;
      case 8:PORTC |= 0b01111111;break;
      case 9:PORTC |= 0b01100111;break;
     }
     switch(p){
      case 1:PORTA |= 0b00000001;break;
      case 2:PORTA |= 0b00000010;break;
      case 3:PORTA |= 0b00000100;break;
      case 4:PORTA |= 0b00001000;break;
     }
}

void init_timer(){
     SREG = 1<<7; // Global Interrupt Enable
     TCCR0 = 0b00001011; //CTC-3,6; Prescaler-0,1,2
     TCNT0 = 0;
     OCR0 = 125;
     TIMSK |= 0b00000010; //set interrupt OCM
}

void Timer0_OC_ISR() iv IVT_ADDR_TIMER0_COMP { //ISR
       digit++;
       switch(digit){
                        case 1: display(1,s%10); break;
                        case 2: display(2,(s/10)%10); break;
                        case 3: display(3,m%10);
                                PORTC |= 0b10000000;break;
                        case 4: display(4,(m/10)%10); digit=0; break;
       }
       if (ms == 999){
              s++;
              ms = 0;
              if(s == 60){
                      s = 0;
                      m++;
              }
       }else ms++;
}

void main(){
     DDRA = 0b00001111; //seteaz� pinii de ie.ire
     DDRC = 0b11111111;
     init_timer();
     s=0;
     ms=0;
     m=0;
}



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Ex2

int digit=0;
int s=0, ms=0, m=0;

void display(char p, char c)
{
    PORTA &= 0b11110000; //liniile de sel. digit - oprite
    PORTC &= 0b00000000; //liniile de sel. Seg. - oprite
     switch(c){
      case 0:PORTC |= 0b00111111;break;//codificare cifra 0
      case 1:PORTC |= 0b00000110;break;
      case 2:PORTC |= 0b01011011;break;
      case 3:PORTC |= 0b01001111;break;
      case 4:PORTC |= 0b01100110;break;
      case 5:PORTC |= 0b01101101;break;
      case 6:PORTC |= 0b01111101;break;
      case 7:PORTC |= 0b00000111;break;
      case 8:PORTC |= 0b01111111;break;
      case 9:PORTC |= 0b01100111;break;
     }
     switch(p){
      case 1:PORTA |= 0b00000001;break;
      case 2:PORTA |= 0b00000010;break;
      case 3:PORTA |= 0b00000100;break;
      case 4:PORTA |= 0b00001000;break;
     }
}

void init_timer(){
     SREG = 1<<7; // Global Interrupt Enable
     TCCR2 = 0b00001011; //CTC-3,6; Prescaler-0,1,2
     TCNT2 = 0;
     OCR2 = 250;
     TIMSK |= 0b10000000; //set interrupt OCM
}

void Timer2_OC_ISR() iv IVT_ADDR_TIMER2_COMP { //ISR
       digit++;
       switch(digit){
                        case 1: display(1,s%10); break;
                        case 2: display(2,(s/10)%10); break;
                        case 3: display(3,m%10);
                                PORTC |= 0b10000000;break;
                        case 4: display(4,(m/10)%10); digit=0; break;
       }
       if (ms == 999){
              s++;
              ms = 0;
              if(s == 60){
                      s = 0;
                      m++;
              }
       }else ms++;
}

void main(){
     DDRA = 0b00001111; //seteaz� pinii de ie.ire
     DDRC = 0b11111111;
     init_timer();
     s=0;
     ms=0;
     m=0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Ex3/4
int digit=0;
int s=0, ms=0, m=0;

void display(char p, char c)
{
    PORTA &= 0b11110000; //liniile de sel. digit - oprite
    PORTC &= 0b00000000; //liniile de sel. Seg. - oprite
     switch(c){
      case 0:PORTC |= 0b00111111;break;//codificare cifra 0
      case 1:PORTC |= 0b00000110;break;
      case 2:PORTC |= 0b01011011;break;
      case 3:PORTC |= 0b01001111;break;
      case 4:PORTC |= 0b01100110;break;
      case 5:PORTC |= 0b01101101;break;
      case 6:PORTC |= 0b01111101;break;
      case 7:PORTC |= 0b00000111;break;
      case 8:PORTC |= 0b01111111;break;
      case 9:PORTC |= 0b01100111;break;
     }
     switch(p){
      case 1:PORTA |= 0b00000001;break;
      case 2:PORTA |= 0b00000010;break;
      case 3:PORTA |= 0b00000100;break;
      case 4:PORTA |= 0b00001000;break;
     }
}

void init_timer(){
     SREG = 1<<7; // Global Interrupt Enable
     TCCR2 = 0b00001011; //CTC-3,6; Prescaler-0,1,2
     TCNT2 = 0;
     OCR2 = 250;
     TIMSK |= 0b10000000; //set interrupt OCM
}

void init_INT0_INT1(){
     GICR |= (1<<7);    
     GICR |= (1<<6);
     
     //activarea intreruperii externe INT0/INT1
     MCUCR |= 0b00001111; // precizare c� evenimentul va avea loc pe frontul crescator
}

void nume_functie1() iv IVT_ADDR_INT0 { // Interrupt rutine
     s++;
}
void INTRERUPERE() iv IVT_ADDR_INT1 ics ICS_AUTO {
     m++;
}


void Timer2_OC_ISR() iv IVT_ADDR_TIMER2_COMP { //ISR
       digit++;
       switch(digit){
                        case 1: display(1,s%10); break;
                        case 2: display(2,(s/10)%10); break;
                        case 3: display(3,m%10);
                                PORTC |= 0b10000000;break;
                        case 4: display(4,(m/10)%10); digit=0; break;
       }
       if (ms == 999){
              s++;
              ms = 0;
              if(s == 60){
                      s = 0;
                      m++;
              }
       }else ms++;
}

void main(){
     DDRA = 0b00001111; //seteaz� pinii de ie.ire
     DDRC = 0b11111111;
     init_timer();
     init_INT0_INT1();
     s=0;
     ms=0;
     m=0;
}