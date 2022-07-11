
// Script to run a nixie clock. I/O will be used to run K155ID1 nixie driver ICs and time will be gotten from #include<time.h>

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>

#include <pigpio.h> // used for controlling gpio lines on rpi
#include <unistd.h>

struct nixie_time
{
    int hours;
    int mins;
    int secs;
};

struct nixie_time Get_Time()
{
    const int TIME_MODE = 0; // 0 = 12 hour mode  // 1 is 24 hour mode
    int hours = 0;
    int minutes = 0;
    int seconds = 0;
    time_t now; // creates an arithmetic time type

    struct tm *current_time; // converts time_t value to pointer to a tm structure that contains hour, min, and second members
    //const int original_hours = 0;	// used to track AM/PM hours value

    time(&now);                     // gives value to now
    current_time = localtime(&now); // fills current_time structs members with values

    hours = current_time->tm_hour; // gives value from current time struct to hours integer
    minutes = current_time->tm_min;
    ; // gives value from current time struct to hours integer
    seconds = current_time->tm_sec;
    ; // gives value from current time struct to hours integer
        //    printf("Time is %02d:%02d:%02d\n", hours, minutes, seconds);
    if (hours > 12 && TIME_MODE == 0)
        hours = hours - 12; // converts pm hours when in 12 hour mode
    struct nixie_time time; // used for an easy way to return the current time
    time.hours = hours;
    time.mins = minutes;
    time.secs = seconds;
    return time;
}

void Set_Hours_Pins(int hours)
{
    gpioInitialise();
    int tens = 0, ones = 0;
    if (hours >= 20)
    {
        tens = 2;
        ones = hours - 20;
    }
    else if (hours >= 10)
    {
        tens = 1;
        ones = hours - 10;
    }
    else if (hours < 10)
    {
        tens = 0;
        ones = hours;
    }
    else
    {
        tens = 9; // Used for error detection
        ones = 9;
    }
    // sets pin locations (in their gpio titles)
    int tens_pin_1_gpio = 8;  // PIN 3 MSB
    int tens_pin_2_gpio = 9;  // PIN 5
    int tens_pin_3_gpio = 7;  // PIN 7
    int tens_pin_4_gpio = 0; // PIN 11 LSB

    int ones_pin_1 = 2; // PIN 13 MSB
    int ones_pin_2 = 3; // PIN 15
    int ones_pin_3 = 12; // PIN 19
    int ones_pin_4 = 13; // PIN 21 LSB

    gpioSetMode(tens_pin_1_gpio, PI_OUTPUT);
    gpioSetMode(tens_pin_2_gpio, PI_OUTPUT);
    gpioSetMode(tens_pin_3_gpio, PI_OUTPUT);
    gpioSetMode(tens_pin_4_gpio, PI_OUTPUT);

    gpioSetMode(ones_pin_1, PI_OUTPUT);
    gpioSetMode(ones_pin_2, PI_OUTPUT);
    gpioSetMode(ones_pin_3, PI_OUTPUT);
    gpioSetMode(ones_pin_4, PI_OUTPUT);

    // Sets pin values based off value
    bool tens_pin_1_value = tens & 0b1000; // GPIO 2 MSB
    bool tens_pin_2_value = tens & 0b0100; // GPIO 5
    bool tens_pin_3_value = tens & 0b0010; // GPIO 7
    bool tens_pin_4_value = tens & 0b0001; // GPIO 11 LSB

    bool ones_pin_1_value = ones & 0b1000; // GPIO 13 MSB
    bool ones_pin_2_value = ones & 0b0100; // GPIO 15
    bool ones_pin_3_value = ones & 0b0010; // GPIO 19
    bool ones_pin_4_value = ones & 0b0001; // GPIO 21 LSB

    gpioWrite(tens_pin_1_gpio, tens_pin_1_value);
    gpioWrite(tens_pin_2_gpio, tens_pin_2_value);
    gpioWrite(tens_pin_3_gpio, tens_pin_3_value);
    gpioWrite(tens_pin_4_gpio, tens_pin_4_value);

    gpioWrite(ones_pin_1, ones_pin_1_value);
    gpioWrite(ones_pin_2, ones_pin_2_value);
    gpioWrite(ones_pin_3, ones_pin_3_value);
    gpioWrite(ones_pin_4, ones_pin_4_value);
}

void Set_Minutes_Pins(int minutes)
{
    gpioInitialise();
    int tens = 0, ones = 0;
    if (minutes == 60)
    {
        tens = 6;
        ones = 6;
    }
    else if (minutes >= 50)
    {
        tens = 5;
        ones = minutes - 50;
    }
    else if (minutes >= 40)
    {
        tens = 4;
        ones = minutes - 40;
    }
    else if (minutes >= 30)
    {
        tens = 3;
        ones = minutes - 30;
    }
    else if (minutes >= 20)
    {
        tens = 2;
        ones = minutes - 20;
    }
    else if (minutes >= 10)
    {
        tens = 1;
        ones = minutes - 10;
    }
    else if (minutes < 10)
    {
        tens = 0;
        ones = minutes;
    }
    else
    {
        tens = 9; // Used for error detection
        ones = 9;
    }

    // sets pin locations (in their gpio titles)
    int tens_pin_1_gpio = 11;    // PIN 23 MSB
    int tens_pin_2_gpio = 21;    // PIN 29
    int tens_pin_3_gpio = 22;    // PIN 31
    int tens_pin_4_gpio = 23;    // PIN 33 LSB

    int ones_pin_1 = 24;    // PIN 35 MSB
    int ones_pin_2 = 25;    // PIN 37
    int ones_pin_3 = 28;    // PIN 38
    int ones_pin_4 = 27;    // PIN 36 LSB

    gpioSetMode(tens_pin_1_gpio, PI_OUTPUT);
    gpioSetMode(tens_pin_2_gpio, PI_OUTPUT);
    gpioSetMode(tens_pin_3_gpio, PI_OUTPUT);
    gpioSetMode(tens_pin_4_gpio, PI_OUTPUT);

    gpioSetMode(ones_pin_1, PI_OUTPUT);
    gpioSetMode(ones_pin_2, PI_OUTPUT);
    gpioSetMode(ones_pin_3, PI_OUTPUT);
    gpioSetMode(ones_pin_4, PI_OUTPUT);

    // Sets pin values based off value
    bool tens_pin_1_value = tens & 0b1000; // GPIO 2 MSB
    bool tens_pin_2_value = tens & 0b0100; // GPIO 5
    bool tens_pin_3_value = tens & 0b0010; // GPIO 7
    bool tens_pin_4_value = tens & 0b0001; // GPIO 11 LSB

    bool ones_pin_1_value = ones & 0b1000; // GPIO 13 MSB
    bool ones_pin_2_value = ones & 0b0100; // GPIO 15
    bool ones_pin_3_value = ones & 0b0010; // GPIO 19
    bool ones_pin_4_value = ones & 0b0001; // GPIO 21 LSB

    gpioWrite(tens_pin_1_gpio, tens_pin_1_value);
    gpioWrite(tens_pin_2_gpio, tens_pin_2_value);
    gpioWrite(tens_pin_3_gpio, tens_pin_3_value);
    gpioWrite(tens_pin_4_gpio, tens_pin_4_value);

    gpioWrite(ones_pin_1, ones_pin_1_value);
    gpioWrite(ones_pin_2, ones_pin_2_value);
    gpioWrite(ones_pin_3, ones_pin_3_value);
    gpioWrite(ones_pin_4, ones_pin_4_value);
}

void Set_Seconds_Pins(int seconds)
{
    gpioInitialise();
    int tens = 0, ones = 0;
    if (seconds == 60)
    {
        tens = 6;
        ones = 6;
    }
    else if (seconds >= 50)
    {
        tens = 5;
        ones = seconds - 50;
    }
    else if (seconds >= 40)
    {
        tens = 4;
        ones = seconds - 40;
    }
    else if (seconds >= 30)
    {
        tens = 3;
        ones = seconds - 30;
    }
    else if (seconds >= 20)
    {
        tens = 2;
        ones = seconds - 20;
    }
    else if (seconds >= 10)
    {
        tens = 1;
        ones = seconds - 10;
    }
    else if (seconds < 10)
    {
        tens = 0;
        ones = seconds;
    }
    else
    {
        tens = 9; // Used for error detection
        ones = 9;
    }

    // sets pin locations (in their gpio titles)
    int tens_pin_1_gpio = 26;    // PIN 32 MSB
    int tens_pin_2_gpio = 11;    // PIN 26
    int tens_pin_3_gpio = 10;    // PIN 24
    int tens_pin_4_gpio = 6;     // PIN 22 LSB

    int ones_pin_1 = 16;    // PIN 10 MSB
    int ones_pin_2 = 1;     // PIN 12
    int ones_pin_3 = 4;     // PIN 16
    int ones_pin_4 = 5;     // PIN 18 LSB

    gpioSetMode(tens_pin_1_gpio, PI_OUTPUT);
    gpioSetMode(tens_pin_2_gpio, PI_OUTPUT);
    gpioSetMode(tens_pin_3_gpio, PI_OUTPUT);
    gpioSetMode(tens_pin_4_gpio, PI_OUTPUT);

    gpioSetMode(ones_pin_1, PI_OUTPUT);
    gpioSetMode(ones_pin_2, PI_OUTPUT);
    gpioSetMode(ones_pin_3, PI_OUTPUT);
    gpioSetMode(ones_pin_4, PI_OUTPUT);

    // Sets pin values based off value
    bool tens_pin_1_value = tens & 0b1000; // GPIO 2 MSB
    bool tens_pin_2_value = tens & 0b0100; // GPIO 5
    bool tens_pin_3_value = tens & 0b0010; // GPIO 7
    bool tens_pin_4_value = tens & 0b0001; // GPIO 11 LSB

    bool ones_pin_1_value = ones & 0b1000; // GPIO 13 MSB
    bool ones_pin_2_value = ones & 0b0100; // GPIO 15
    bool ones_pin_3_value = ones & 0b0010; // GPIO 19
    bool ones_pin_4_value = ones & 0b0001; // GPIO 21 LSB

    gpioWrite(tens_pin_1_gpio, tens_pin_1_value);
    gpioWrite(tens_pin_2_gpio, tens_pin_2_value);
    gpioWrite(tens_pin_3_gpio, tens_pin_3_value);
    gpioWrite(tens_pin_4_gpio, tens_pin_4_value);

    gpioWrite(ones_pin_1, ones_pin_1_value);
    gpioWrite(ones_pin_2, ones_pin_2_value);
    gpioWrite(ones_pin_3, ones_pin_3_value);
    gpioWrite(ones_pin_4, ones_pin_4_value);
}

int main()
{
    for (int hours = 0; hours <= 11; hours++)
    {

        bool tens_pin_1_gpio = hours & 0b1000; // GPIO 2 MSB
        bool tens_pin_2_gpio = hours & 0b0100; // GPIO 5
        bool tens_pin_3_gpio = hours & 0b0010; // GPIO 7
        bool tens_pin_4_gpio = hours & 0b0001;
        printf("Number: %d bin value: %d%d%d%d\n", hours, tens_pin_1_gpio, tens_pin_2_gpio, tens_pin_3_gpio, tens_pin_4_gpio);
    }

    return 0;
}
