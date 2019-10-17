#ifndef _DATA_MODEL_H
#define _DATA_MODEL_H

#include "parse.h"
#include <tuple>
#include <map>
#include <iostream>
#include <vector>
#ifndef PROPERTY
#define PROPERTY(CLASS, MEMBER) Parse::property(&CLASS::MEMBER, #MEMBER)
#endif

namespace animal {
class JClass{};

class Cat {
    public:
    std::string name = "not_defined";
    int id = -1;

    constexpr static auto properties = std::make_tuple(
        PROPERTY(Cat, name),
        PROPERTY(Cat, name),
        PROPERTY(Cat, name),
        PROPERTY(Cat, name),
        PROPERTY(Cat, name),
        PROPERTY(Cat, id)
    );
};

class Cow {
    public:
    std::string name = "cow";
    int id = 000;
    constexpr static auto properties = std::make_tuple(
        PROPERTY(Cow, name),
        PROPERTY(Cow, name),
        PROPERTY(Cow, name),
        PROPERTY(Cow, name),
        PROPERTY(Cow, name),
        PROPERTY(Cow, id)
    );

};

class Dog {
    public:
    std::string barkType;
    std::string color;
    int weight = 0;
    int id = 1;
    std::vector<animal::Cat> cats;
    std::vector<animal::Cow> cows;
    animal::Cat catObject;
    
    Dog(){
        Cat c;
        c.name = "cat 1";
        cats.push_back(c);
        Cow cow;
        cows.push_back(cow);
    }
    bool operator==(const Dog& rhs) const {
        return barkType == rhs.barkType && color == rhs.color && weight == rhs.weight;
    }
    
    constexpr static auto properties = std::make_tuple(
        PROPERTY(Dog, barkType),
        PROPERTY(Dog, color),
        PROPERTY(Dog, weight),
        PROPERTY(Dog, cats),
        PROPERTY(Dog, cows),
        PROPERTY(Dog, catObject),
        PROPERTY(Dog, id)

    );
};

}
#endif