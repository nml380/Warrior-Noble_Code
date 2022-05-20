//
//  Protector.h
//  hw07
//
//  Created by Noah LaPoint on 4/14/22.
//

#ifndef Protector_h
#define Protector_h

#include <string>
#include <vector>

namespace WarriorCraft{

    class Protector {
    public:
        Protector(const string& protector_name, double strength);
        void new_hire(Lord* new_employer);
        void fired();
        void set_strength(double dec_strength);
        void runaway();
        double get_strength() const;
        const string& get_name() const;
        bool isHired() const;
        const string& employer_name() const;
        virtual void battleCry() = 0;
    private:
        string protector_name;
        double strength;
        Lord* employer;
    };

    class Archer : public Protector {
    public:
        Archer(const string& name, double strength);
        void battleCry();
    };

    class Swordsman : public Protector {
    public:
        Swordsman(const string& name, double strength);
        void battleCry();
    };

    class Wizard : public Protector {
    public:
        Wizard(const string& name, double strength);
        void battleCry();
    };

}

#endif /* Protector_h */
