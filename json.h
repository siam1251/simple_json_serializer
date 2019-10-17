
#ifndef _JSON_H 
#define _JSON_H

#include <tuple>
#include <map>
#include <vector>
#include <iostream>
#include <sstream>
#include <typeinfo>
#include <type_traits>


namespace Json{
    class Value;
}
namespace Parse{
        template<typename T>
        Json::Value toJson(const T& object);
};

// Sample implementation of a json-like data structure. It is only there for the example to compile and actually produce a testable output
namespace Json {
   
    const std::string quote = "\"";
    
    class ValueData {
        public:
        std::map<std::string, Value> subObject;
        std::vector<std::string> unorderedKeys;
        std::string string = "";
        int number = 0;
    };
    
    class Value {
        public:
        ValueData data;

        template<typename T>
        std::string getPrecisionStr(T value, int precision=2) {
            std::ostringstream oss;
            oss.precision(precision);
            oss << value;
            return oss.str();
        }
        
        Value& operator[](std::string name) {
            data.unorderedKeys.push_back(name);
            return data.subObject[std::move(name)];
        }
        
        const Value& operator[](std::string name) const {
            auto it = data.subObject.find(std::move(name));
            
            if (it != data.subObject.end()) {
                return it->second;
            }
            
            throw;
        }
        
        Value& operator=(std::string value) {
            data.string =  quote+value+quote;
            return *this;
        }
        
        Value& operator=(int value) {
            data.string = std::to_string(value);
            return *this;
        }
        
        Value& operator=(float value) {
            data.string = getPrecisionStr(value);
            return *this;
        }

        Value& operator=(double value) {
            data.string = getPrecisionStr(value);
            return *this;
        }

       template<typename T, typename E = void>
        struct A{ bool isClass= false;}; // undefined

        

        template<typename T>
        Value& operator=(std::vector<T> value) {
            // data.number = value;
            // data.string = std::to_string(value);
            std::string str = "[";
            for(int i = 0; i < value.size(); i++)
            {   
                
                Json::Value tmp = Parse::toJson(value[i]);
                str += tmp.getString();
                if(i < value.size()-1){
                    str += ", ";
                }
            }
            str += "]";
            data.string += str;
            return *this;
        }

       
        template<typename T2>
        Value& operator=(std::map<std::string, T2> map) {
            // data.number = value;
            // data.string = std::to_string(value);
            std::string str = "[";
            for(auto it = map.begin(); it != map.end(); it++)
            {   
                str += "{";
                //Json::Value k = Parse::toJson(it->first);
                //str += k.getString();
                str += "\""+it->first+ "\"";
                str += ":";
                Json::Value v = Parse::toJson(it->second);
                str += v.getString();
                str += "}";
                if(std::next(it) != map.end()){
                    str += ", ";
                }
            }
            str += "]";
            data.string += str;
            return *this;
        }

        

        template<typename T, typename = std::enable_if_t<std::is_class<T>::value>
        >
        Value& operator= (const T& object) {
            
            std::string str = "";
            Json::Value tmp = Parse::toJson(object);
            str += tmp.getString();
            data.string += str;
           
            return *this;
        
        }



        std::string getArrayString(){
            std::string str = "";
            int i = 0;
            for(std::string& key: data.unorderedKeys){
                str += data.subObject[key].getString();
                if(data.unorderedKeys.size()-i > 1){
                    str += ", ";
                }
                i++;
            }
            if (!data.string.empty()){
                return data.string;
            }
            return str;
        }
        std::string getString(){
            std::string str = "";
            str += "{";
            bool no_element = true;
            int i = 0;
            for(std::string& key: data.unorderedKeys){
                no_element = false;
                str += quote + key + quote;
                str += ":";
                str += data.subObject[key].getString();
                if(data.unorderedKeys.size()-i > 1){
                    str += ", ";
                }
                i++;
            }
            if (!data.string.empty()){
                return data.string;
            }
            str += "}";

            
            return str;
        }
        template<class TT>
        bool isPrimitive(std::string ss) {
            return true;
        }
        template<class TT>
        bool isPrimitive(int ss) {
            return true;
        }
        template<class TT>
        bool isPrimitive(const int& ss) {
            return true;
        }
        template<class T>
        bool isPrimitiveType() {
            return false;
        }
        
        
        
        

    };
    
    template<typename T> T& asAny(Value&);
    template<typename T> const T& asAny(const Value&);
    
    // template<>
    // int& asAny<int>(Value& value) {
    //     return value.data.number;
    // }
    
    // template<>
    // const int& asAny<int>(const Value& value) {
    //     return value.data.number;
    // }
    
    // template<>
    // const std::string& asAny<std::string>(const Value& value) {
    //     return value.data.string;
    // }
    
    // template<>
    // std::string& asAny<std::string>(Value& value) {
    //     return value.data.string;
    // }
}

#endif