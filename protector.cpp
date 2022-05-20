//
//  protector.cpp
//  hw07
//
//  Created by Noah LaPoint on 4/14/22.
//

#include "Noble.h"
#include "Protector.h"
#include <string>
#include <vector>

using namespace std;
namespace WarriorCraft{

    Protector::Protector(const string& protector_name, double strength) : protector_name(protector_name), strength(strength), employer(nullptr) {}
    void Protector::new_hire(Lord* new_employer) { employer = new_employer; }
    void Protector::fired() { employer = nullptr; }
    void Protector::set_strength(double dec_strength) { strength = dec_strength * strength; }
    void Protector::runaway()
    {
        if (employer != nullptr)
        {
            employer->fire(*this, true);
            employer = nullptr;
        }
    }
    double Protector::get_strength() const { return strength; }
    const string& Protector::get_name() const { return protector_name; }
    bool Protector::isHired() const { return (employer != nullptr); }
    const string& Protector::employer_name() const { return employer->getName(); }

    Archer::Archer(const string& name, double strength) : Protector(name, strength) {}
    void Archer::battleCry(){cout << "TWANG! " << get_name() << " says: Take that in the name of my lord, " << employer_name();}

    Swordsman::Swordsman(const string& name, double strength) : Protector(name, strength){}
    void Swordsman::battleCry(){cout << "CLANG! " << get_name() << " says: Take that in the name of my lord, " << employer_name();}
    Wizard::Wizard(const string& name, double strength) : Protector(name, strength){}
    void Wizard::battleCry(){cout << "POOF!";}

}
