
#ifndef _PARSE_H
#define _PARSE_H
#include <tuple>
#include <map>
#include <type_traits>
#include <initializer_list>
#include <iostream>
#include "json.h"
#include <functional>
#include "integer_sequence.h"

#ifndef PROPERTY
#define PROPERTY(CLASS, MEMBER) Parse::property(&CLASS::MEMBER, #MEMBER)
#endif

namespace Parse{
    // sequence for


    // // sequence for
    template <typename T, T... S, typename F>
    constexpr void for_sequence(std::integer_sequence<T, S...>, F&& f) {
        using unpack_t = int[];
        (void)unpack_t{(static_cast<void>(f(std::integral_constant<T, S>{})), 0)..., 0};
    }


    template<typename Class, typename T>
    struct PropertyImpl {
        constexpr PropertyImpl(T Class::*aMember, const char* aName) : member{aMember}, name{aName} {}

        using Type = T;

        T Class::*member;
        const char* name;
    };




    // One could overload this function to accept both a getter and a setter instead of a member.
    template<typename Class, typename T>
    constexpr PropertyImpl<Class, T> property(T Class::*member, const char* name) {
        return PropertyImpl<Class, T>{member, name};
    }

    template<typename T>
    Json::Value toJson(const T& object) {
        
        Json::Value value;

        // We first get the number of properties
        constexpr auto nbProperties = std::tuple_size<decltype(T::properties)>::value;
        //constexpr auto nbProperties = 1;
        
        // We iterate on the index sequence of size `nbProperties`
        for_sequence(std::make_index_sequence<nbProperties>{}, [&](auto i){
            // get the property
            constexpr auto property = std::get<i>(T::properties);

            // set the value to the member
            value[property.name] = object.*(property.member);
        });
        
        

        return value;
    }


    // unserialize function
    // template<typename T>
    // T fromJson(const Json::Value& data) {
    //     T object;

    //     // We first get the number of properties
    //     constexpr auto nbProperties = std::tuple_size<decltype(T::properties)>::value;
        
    //     // We iterate on the index sequence of size `nbProperties`
    //     for_sequence(std::make_index_sequence<nbProperties>{}, [&](auto i){
    //         // get the property
    //         constexpr auto property = std::get<i>(T::properties);

    //         // get the type of the property
    //         using Type = typename decltype(property)::Type;

    //         // set the value to the member
    //         object.*(property.member) = Json::asAny<Type>(data[property.name]);
    //     });

    //     return object;
    // }


}
#endif