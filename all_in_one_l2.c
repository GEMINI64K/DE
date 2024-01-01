// Ex 1

void main() {
 DDRA |= 0b00001111;
 DDRC |= 0b11111111;

    do {
        PORTA = 0b00001000;
        PORTC = 0b00111111;
        Delay_ms(4);
        PORTA = 0b00000100;
        PORTC = 0b00000110;
        Delay_ms(4);
        PORTA = 0b00000010;
        PORTC = ~0b10100100;
        Delay_ms(4);
        PORTA = 0b00000001;
        PORTC = ~0b10110000;
        Delay_ms(4);
    } while(1);
}

// Ex 2

int value=0;

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
 Delay_ms(4);
}

void ex2(int value){
    display(1,value%10);
    display(2,(value/10)%10);
    display(3,(value/100)%10);
    display(4,(value/1000)%10);
}

void main() {
    DDRA |= 0b00001111;
    DDRC |= 0b11111111;

    value = 2023;

    while(1) {
        ex2(value);
    }
}

// Ex 3

bit starePB2;
int value=0;

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
 Delay_ms(4);
}

void ex2(int value){
    display(1,value%10);
    display(2,(value/10)%10);
    display(3,(value/100)%10);
    display(4,(value/1000)%10);
}

int button_2_logic(int value){
    if(PINB & (1<<2)) //testare pin PB2
    { 
        if(starePB2 == 0) //variabila va .ine minte starea
        { 
            starePB2 = 1; //anterioara a pin-ului PB2
            value++;
        }
    }
    else
        starePB2 = 0;
    
    return value;
}

void main() {
    DDRA |= 0b00001111;
    DDRC |= 0b11111111;
    DDRB &= ~(1<<2);

    value = 2023;

    while(1) {
        value = button_2_logic(value);
        ex2(value);
    }
}
