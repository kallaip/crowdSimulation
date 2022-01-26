#ifndef PLAYER_H
#define PLAYER_H


class player
{
    public:
        player(int xPos = 0, int yPos = 0);
        virtual ~player();

        int getXPos() { return xPos; }
        void setXPos(int val) { xPos = val; }
        int getYPos() { return yPos; }
        void setYPos(int val) { yPos = val; }
        Vector3 getDirection() { return direction; }
        void setDirection(Vector3 val) { direction = val; }

    protected:
        int xPos;
        int yPos;
        Vector3 direction;

    private:

};

#endif // PLAYER_H
