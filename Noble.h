//
//  Noble.h
//  hw07
//
//  Created by Noah LaPoint on 4/14/22.
//

#ifndef Noble_h
#define Noble_h


#include <string>
#include <vector>

namespace WarriorCraft{
    class Noble {
    public:
        Noble(const string& name);
        const string& getName();
        bool healthStatus();
        void died();
        vector<Protector*>& getArmy();
        virtual void battle(Noble& opponent) = 0;
        virtual double get_Strength() = 0;
        virtual void battleCry() = 0;
    private:
        string noble_name;
        bool Alive;
        vector<Protector*> Army;
    };

    class Lord : public Noble {
    public:
        Lord(const string& name);
        void fire(Protector& old_protector, bool flee);
        void battle(Noble& opponent);
        void hires(Protector& new_recruit);
        double get_Strength();
        void battleCry();
    };

    class PersonWithStrenghtoFight : public Noble {
    public:
        PersonWithStrenghtoFight(const string& name,double strength);
        void set_strength(double strength_factor);
        void battle(Noble& opponent);
        double get_Strength();
        void battleCry();
    private:
        double strength;
    };
}
#endif /* Noble_h */
