#include <iostream>
#include <tuple>

template<typename Class, typename T>
struct PropertyImpl {
    constexpr PropertyImpl(T Class::*aMember, const char* aName) : member{aMember}, name{aName} {}

    using Type = T;

    T Class::*member;
    const char* name;
};

template<typename Class, typename T>
constexpr auto property(T Class::*member, const char* name) {
    return PropertyImpl<Class, T>{member, name};
};


struct Dog {
    std::string barkType;
    std::string color;
    int weight = 0;

    bool operator==(const Dog& rhs) const {
        return std::tie(barkType, color, weight) == std::tie(rhs.barkType, rhs.color, rhs.weight);
    }

    constexpr static auto properties = std::make_tuple(
        property(&Dog::barkType, "barkType"),
        property(&Dog::color, "color"),
        property(&Dog::weight, "weight")
    );
};