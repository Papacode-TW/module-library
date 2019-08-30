#ifndef MODULES_H
#define MODULES_H

#include <Arduino.h>

//MOTOR
#define MOTOR_LEFT_FORWARD 5
#define MOTOR_LEFT_BACKWARD 6
#define MOTOR_RIGHT_FORWARD 9
#define MOTOR_RIGHT_BACKWARD 10
#define LOW_SPEED 50
#define HIGH_SPEED 255
//JOYSTICK
#define JOYSTICK_X A0
#define JOYSTICK_Y A1
#define JOYSTICK_SW 2
//ULTRASOUND
#define ULTRASOUND_ECHO 3
#define ULTRASOUND_TRIG 2
//TURNSIGNAL
#define TURNSIGNAL_L 4
#define TURNSIGNAL_R 7
#define TURNSIGNAL_BLINK_HZ 2
//BUZZER
#define BUZZER_PIN 8

class Motor{
    public:
        Motor();
        /**
         * @function
         * @param   -100 to +100 for backward to forward
        */
        void leftRun(int8_t speed);
        void rightRun(int8_t speed);
        void leftStop();
        void rightStop();
        static void cycleplusle();
		static void cycleplusri();
        void active(int move,int pic[]);
        int8_t getLeftSpeed(){return _left_speed;}
        int8_t getRightSpeed(){return _right_speed;}
    private:
        int8_t _left_speed=0;
        int8_t _right_speed=0;
        static volatile int cyclele;
        static volatile int cycleri;
};

        // static int cyclele=0;
        // static int cycleri=0;

class JoyStick{
    public:
        JoyStick(){pinMode(JOYSTICK_SW,INPUT);}
        bool isClicked(){return digitalRead(JOYSTICK_SW);}
        bool up(){return readY()<(int)(0.25*894);}
        bool down(){return readY()>(int)(0.75*894);}
        bool left(){return readX()<(int)(0.25*894);}
        bool right(){return readX()>(int)(0.75*894);}
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