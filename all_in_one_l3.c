// Ex 1
int s=0,ms=0,m=0;
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
//Delay_ms(4);     // important - fara delay!
}

void init_timer()
{
        TCCR0 = 0b00000011;     //prescaler 64, mod normal de operare
        TCNT0 = 0;              //se initializeaza numaratorul cu 0
}

void lcd_display(){
        display(4,s%10);
        display(3,(s/10)%10);
        display(2,(m%10));
        PORTC |= 0b10000000;
        display(1,(m/10)%10);
}

void timer_one()
{
   if(TCNT0>=125) //implinirea unei milisecunde
     {
          TCNT0=0;       //resetarea timerului
          ms++;
          if(ms==1000)  //implinirea unei secunde
          {
              ms=0;
              s++;
          }
          if(s==60)  //implinirea unui minut
          {
              s=0;
              m++;
          }
     }
}
void main() {
    DDRA |= 0b00001111; //PA0-PA3 ? Ie.iri
    DDRC |= 0b11111111; //PC0-PC7 ? Ie.iri

    init_timer();
    do{
        timer_one();
        lcd_display();
    }while(1);
}



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


// Ex 2
// Only the TCCR register is changed:
    TCCR2 = 0b00000100; 
    //and the name of the other register: from 0 to 2 -> TCNT2

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Ex 3

bit starePB2, starePB3, freeze_time, reset;
int n, s=0,ms=0,m=0;

void buttons(){
    if(PINB & (1<<2))
    {
        if(starePB2 == 0)
        {
            starePB2 = 1;
            freeze_time ^= 1;
        }
    }
    else
        starePB2 = 0;

    if(PINB & (1<<3))
    {
        if(starePB3 == 0)
        {
            starePB3 = 1;
            TCNT0 = 0;
            s=0;
            ms=0;
            m=0;
        }
    }
    else
        starePB3 = 0;
}

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
//Delay_ms(4);     // important - fara delay!
}

void init_timer()
{
        TCCR2 = 0b00000100;     //prescaler 64, mod normal de operare
        TCNT2 = 0;              //se initializeaza numaratorul cu 0
}

void lcd_display(){
        display(4, (ms/10)%10);
        display(3, (ms/100)%10);
        display(2, s%10);
        PORTC |= 0b10000000;
        display(1, (s/10)%10);
}

void timer_one()
{
   if(TCNT2>=125) //implinirea unei milisecunde
     {
          TCNT2=0;       //resetarea timerului
          ms++;
          if(ms==1000)  //implinirea unei secunde
          {
              ms=0;
              s++;
          }
          if(s==60)  //implinirea unui minut
          {
              s=0;
              m++;
          }
     }
}
void main() {
    DDRA |= 0b00001111; //PA0-PA3 ? Ie.iri
    DDRC |= 0b11111111; //PC0-PC7 ? Ie.iri

    init_timer();
    do{
      buttons();
      if (freeze_time == 0)
      {
           timer_one();
      }
      lcd_display();
      }while(1);
}