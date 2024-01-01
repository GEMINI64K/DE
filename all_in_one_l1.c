// Ex1

void main() {
     DDRB |= (1<<7); //PB7 � output
     DDRB &= ~(1<<3);
     while(1){
           if(PINB & (1<<3)) //testare pin PB3
              PORTB |= (1<<7); //PB7 � HIGH (LED ON)
           else
              PORTB &= ~(1<<7);
      }
}


// Ex 2

bit starePB2;

void main() {
     DDRB |= (1<<6); //PB7 iesire
     DDRB &= ~(1<<3);         // intrare

        do {
            if(PINB & (1<<3)) //testare pin PB2
              {
                if(starePB2 == 0) //variabila va tine minte starea
                {
                   starePB2 = 1; //anterioara a pin-ului PB2
                   PORTB ^= (1<<6);//se schimba starea LED-ului
                }
              }else
                   starePB2 = 0;
        }while(1);
}


// Ex 3

bit starePB2;
int n;

void main() {

        DDRD |= 0b11111111; //Pini de ie.ire
        DDRB &= ~(1<<2); //PB2 � Intrare

        do {
            if(PINB & (1<<2)) //testare pin PB2
            { 
              if(starePB2 == 0) //variabila va .ine minte starea
                { 
                  starePB2 = 1; //anterioara a pin-ului PB2
                  n++; //se incrementeaza variabila n
                }
            }
            else
                 starePB2 = 0;

            PORTD = n;
        }while(1);

}