#ifndef MODULES_H
#define MODULES_H

#include <Arduino.h>

//MOTOR
#define MOTOR_LEFT_FORWARD 6
#define MOTOR_LEFT_BACKWARD 5
#define MOTOR_RIGHT_FORWARD 9
#define MOTOR_RIGHT_BACKWARD 10
#define LOW_SPEED 50
#define HIGH_SPEED 255
//JOYSTICK
#define JOYSTICK_X A0
#define JOYSTICK_Y A1
#define JOYSTICK_SW 4
//ULTRASOUND
#define ULTRASOUND_ECHO A3
#define ULTRASOUND_TRIG A2
//TURNSIGNAL
#define TURNSIGNAL_L 11
#define TURNSIGNAL_R 12
#define TURNSIGNAL_BLINK_HZ 2
//BUZZER
#define BUZZER_PIN 8

#define COUNT_PER_ROT 200
#define DIAMETER 4.5
#define WHEEL_WIDTH 14.5

class Motor{
    public:
        Motor();
        /**
         * @function
         * @param   -100 to +100 for backward to forward
        */

        void leftSpeed(int8_t speed);
        void rightSpeed(int8_t speed);
        void runDist(int8_t distance);
        void turnDeg(int16_t degree);
        void leftStop();
        void rightStop();
        static void cycleplusle();
		static void cycleplusri();
        int8_t getLeftSpeed(){return _left_speed;}
        int8_t getRightSpeed(){return _right_speed;}
    private:
        int8_t _left_speed=0;
        int8_t _right_speed=0;
        static volatile uint16_t cyclele;
        static volatile uint16_t cycleri;
};



class JoyStick{
    public:
        JoyStick(){pinMode(JOYSTICK_SW,INPUT);}
        bool isClicked(){return !digitalRead(JOYSTICK_SW);}
        bool up(){return readY()<(int)(10);}
        bool down(){return readY()>(int)(800);}
        bool left(){return readX()<(int)(10);}
        bool right(){return readX()>(int)(800);}
        //range: 0-894 left-right up-down
        int readX(){return analogRead(JOYSTICK_X);}
        int readY(){return analogRead(JOYSTICK_Y);}
};

class Ultrasound{
    public:
        Ultrasound();
        double getDistanceCM();
        double getDistanceINCH(){return this->getDistanceCM()*0.393700787;}
};

class TurnSignal{
    public:
        TurnSignal();
        void initBlink();
        void setRight(bool state);
        void setLeft(bool state);
        void setBlinkRight(bool state);
        void setBlinkLeft(bool state);
        static void timer1ISR();
    private:
        static volatile bool _blink_right;      //use volatile for variables used in ISR
        static volatile bool _blink_left;
};

class Buzzer{
    public:
        Buzzer();
        void setFrequency(unsigned int frequency);
        void start();
        void stop();
        unsigned int getFrequency(){return _frequency;}
    private:
        unsigned int _frequency=440;
};

#endif