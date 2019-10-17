
#include <tuple>
#include <map>
#include <iostream>
#include "parse.h"
#include "dataModel.h"
#ifdef ANDROID
#include <android/log.h>
#define TAG "mainTest"
#define printf(...) __android_log_print(ANDROID_LOG_DEBUG,TAG,__VA_ARGS__);
#define printe(...) __android_log_print(ANDROID_LOG_ERROR,TAG,__VA_ARGS__);
#endif



int main() {
    animal::Dog dog;

    dog.color = "green";
    dog.barkType = "whaf";
    dog.weight = 30;
    

    Json::Value jsonDog = Parse::toJson(dog); // produces {"color":"green", "barkType":"whaf", "weight": 30}
    
    animal::Cat cat;
    cat.name = "adf";
    // Json::Value jsonCat = Parse::toJson(cat);
    // printf("%s\n",jsonCat.getString().c_str());

    printf("%s",jsonDog.getString().c_str());

    std::string abc = "abc";
    //printf("%s", abc.c_str());
    //std::cout << std::boolalpha << (dog == dog2) << std::endl; // pass the test, both dog are equal!
    
    return 0;
}