#ifndef Dice_h
#define Dice_h

class Dice {

    public:
        Dice();
        void roll();
        int getFace() const;

    private:
        int face;
};

#endif