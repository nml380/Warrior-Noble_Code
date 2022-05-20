//
//  noble.cpp
//  hw07
//
//  Created by Noah LaPoint on 4/14/22.
//

#include "Noble.h"
#include "Protector.h"
#include <string>
#include <vector>

using namespace std;
namespace WarriorCraft
{
    ostream& operator<<(ostream& os, Lord& curr_noble) // determines output operator for Warriors
    {
        cout << "here" << endl;
        for(size_t y = 0; y < curr_noble.getArmy().size(); y++)
        {
            Protector* protect = curr_noble.getArmy()[y];
            protect->battleCry();
            cout << endl;
        }
        return os;
    }

    ostream& operator<<(ostream& os, PersonWithStrenghtoFight& person) // determines output operator for Warriors
    {
        os << "Ugh!" << endl;
        return os;
    }
    Noble::Noble(const string& name) : noble_name(name), Alive(true), Army(){}
    const string& Noble::getName() { return noble_name; }
    bool Noble::healthStatus() { return Alive; }
    void Noble::died() { Alive = false; }
    vector<Protector*>& Noble::getArmy() { return Army;}


    Lord::Lord(const string& name) : Noble(name){}
    void Lord::battleCry() {cout << (*this);}
    void Lord::fire(Protector& old_protector, bool flee)
    {
        for (size_t x = 0; x < getArmy().size(); x++) // searches for warrior in Army and fires warrior
        {
            if ((getArmy()[x]->get_name()) == old_protector.get_name())
            {
                for (size_t y = x; y < getArmy().size() - 1; y++) // shifts elements in the list one to the left of the found warrior
                {
                    getArmy()[y] = getArmy()[y + 1];
                }
                if (flee == false)
                {
                    cout << "You dont work for me anymore " << old_protector.get_name() << "! -- King Arthur." << endl;
                }
                else
                {
                    cout << old_protector.get_name() << " flees i`n terror, abondoning his lord, " << getName() << endl;
                }
                getArmy()[getArmy().size() - 1] = nullptr;
                getArmy().pop_back();
                old_protector.fired();
                x = getArmy().size();
            }
        }
    }
    void Lord::battle(Noble& opponent)
    {
        cout << getName() << " battles " << opponent.getName() << endl;
        if ((!healthStatus()) || (!opponent.healthStatus())) // tests and outputs correct staments if at least one of the Nobles is dead
        {
            if (healthStatus() == true)
            {
                battleCry();
                cout << "He's dead, " << getName() << endl;
            }
            else if (opponent.healthStatus() == true)
            {
                opponent.battleCry();
                cout << "He's dead, " << opponent.getName() << endl;
            }
            else
            {
                cout << "Oh, NO! They're both dead! Yuck!" << endl;
            }
        }
        else // outputs correct statements based on each Nobles army strength
        {
            battleCry();
            opponent.battleCry();
            double opponent_1_str = get_Strength();
            double opponent_2_str = opponent.get_Strength();
            if (opponent_1_str > opponent_2_str)
            {
                double strength_decrease = opponent_2_str / opponent_1_str;
                for (size_t x = 0; x < getArmy().size(); x++) { getArmy()[x]->set_strength(1 - strength_decrease); } // decreases each warriors strength
                for (size_t y = 0; y < opponent.getArmy().size(); y++) { opponent.getArmy()[y]->set_strength(0); } // sets warriors strength to 0
                opponent.died();
                cout << getName() << " defeats " << opponent.getName() << endl;

            }
            else if (opponent_2_str > opponent_1_str)
            {
                double strength_decrease = opponent_1_str / opponent_2_str;
                for (size_t x = 0; x < opponent.getArmy().size(); x++) { opponent.getArmy()[x]->set_strength(1 - strength_decrease); } // decreases each warriors strength
                for (size_t y = 0; y < getArmy().size(); y++) { getArmy()[y]->set_strength(0); } // sets warriors strength to 0
                died();
                cout << opponent.getName() << " defeats " << getName() << endl;
            }
            else
            {
                for (size_t y = 0; y < getArmy().size(); y++) { getArmy()[y]->set_strength(0); } // sets warriors stength to 0
                for (size_t y = 0; y < opponent.getArmy().size(); y++) { opponent.getArmy()[y]->set_strength(0); } // sets warriors strength to 0
                died();
                opponent.died();
                cout << "Mutual Annihilation: Arthur and Lancelot die at each other's hands" << endl;
            }
        }
    }
    void Lord::hires(Protector& new_recruit) // hires warrior if not already hired
    {
        if ((!new_recruit.isHired()) and (new_recruit.get_strength() != 0))
        {
            Protector* protector_pointer = &new_recruit;
            getArmy().push_back(protector_pointer);
            new_recruit.new_hire(this);
        }
    }
    double Lord::get_Strength()
    {
        double strength = 0;
        for (size_t x = 0; x < getArmy().size(); x++) // loops through first army and determines its total strength
        {
            strength += getArmy()[x]->get_strength();
        }
        return strength;
    }

    PersonWithStrenghtoFight::PersonWithStrenghtoFight(const string& name,double strength) : Noble(name),strength(strength) {}
    void PersonWithStrenghtoFight::battleCry() {cout << (*this); }
    void PersonWithStrenghtoFight::set_strength(double strength_factor) { strength = strength * strength_factor; }
    void PersonWithStrenghtoFight::battle(Noble& opponent)
    {
        cout << getName() << " battles " << opponent.getName() << endl;
        if ((!healthStatus()) || (!opponent.healthStatus())) // tests and outputs correct staments if at least one of the Nobles is dead
        {
            if (healthStatus() == true)
            {
                cout << "He's dead, " << getName() << endl;
            }
            else if (opponent.healthStatus() == true)
            {
                cout << "He's dead, " << opponent.getName() << endl;
            }
            else
            {
                cout << "Oh, NO! They're both dead! Yuck!" << endl;
            }
        }
        else // outputs correct statements based on each Nobles army strength
        {
            battleCry();
            opponent.battleCry();
            double opponent_1_str = strength;
            double opponent_2_str = 0;
            for (size_t y = 0; y < opponent.getArmy().size(); y++) // loops through seconda army and determines its total stength
            {
                opponent_2_str += opponent.getArmy()[y]->get_strength();
            }
            if (opponent_1_str > opponent_2_str)
            {
                double strength_decrease = opponent_2_str / opponent_1_str;
                set_strength(1 - strength_decrease); // decreases each warriors strength
                for (size_t y = 0; y < opponent.getArmy().size(); y++) { opponent.getArmy()[y]->set_strength(0); } // sets warriors strength to 0
                opponent.died();
                cout << getName() << " defeats " << opponent.getName() << endl;

            }
            else if (opponent_2_str > opponent_1_str)
            {
                double strength_decrease = opponent_1_str / opponent_2_str;
                for (size_t x = 0; x < opponent.getArmy().size(); x++) { opponent.getArmy()[x]->set_strength(1 - strength_decrease); } // decreases each warriors strength
                set_strength(0); // sets warriors strength to 0
                died();
                cout << opponent.getName() << " defeats " << getName() << endl;
            }
            else
            {
                set_strength(0); // sets warriors stength to 0
                for (size_t y = 0; y < opponent.getArmy().size(); y++) { opponent.getArmy()[y]->set_strength(0); } // sets warriors strength to 0
                died();
                opponent.died();
                cout << "Mutual Annihilation: Arthur and Lancelot die at each other's hands" << endl;
            }
        }
    }
    double PersonWithStrenghtoFight::get_Strength()
    {
        return strength;
    }
}
