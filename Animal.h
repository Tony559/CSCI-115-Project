#ifndef ANIMAL_H
#define ANIMAL_H

class Animal {
    public:
        bool canCrossMountain;
        bool canCrossPlain;
        bool canCrossForest;
        bool canCrossDesert;
        bool canCrossOcean;
};
class Monkey : public Animal {
    public:
        Monkey() { // "the monkey who can just walk and not go in the water or cross the high mountains"
            canCrossMountain = false;
            canCrossPlain = true;
            canCrossForest = true;
            canCrossDesert = true;
            canCrossOcean = false;
        }
};
class Bird : public Animal {
    public:
        Bird() { // "the bird that can fly over mountains but that cannot go in the desert"
            canCrossMountain = true;
            canCrossPlain = true;
            canCrossForest = true;
            canCrossDesert = false;
            canCrossOcean = true;
        }
};
class Fish : public Animal {
    public:
        Fish() { // "the fish that must stay in the water"
            canCrossMountain = false;
            canCrossPlain = false;
            canCrossForest = false;
            canCrossDesert = false;
            canCrossOcean = true;
        }
};
class Frog : public Animal {
    public:
        Frog() { // "the frog that can go everywhere except in the mountains and the desert."
            canCrossMountain = false;
            canCrossPlain = true;
            canCrossForest = true;
            canCrossDesert = false;
            canCrossOcean = true;
        }

};






#endif