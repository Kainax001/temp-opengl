#include "setting.h"

#include <nlohmann/json.hpp>
#include <iostream>
#include <fstream>

//Helper method
bool isFileExists(std::string path) {
    std::ifstream file(path.c_str());
    return file.good(); 
}

Setting::Setting() : zNear(0.1f), zFar(100.0f), viewAngle(45.0f), SCR_WIDTH(1600), SCR_HEIGHT(900)
{
    // initialize
}

// edit config value
void Setting::setRenderdistance(float newzNear, float newzFar)
{
    zNear = newzNear;
    zFar = newzFar;
}

void Setting::setViewAngle(float newviewAngle)
{
    viewAngle = newviewAngle;
}

void Setting::setWindowsize(int newSCR_WIDTH, int newSCR_HEIGHT)
{
    SCR_WIDTH = newSCR_WIDTH;
    SCR_HEIGHT = newSCR_HEIGHT;
}

// edit and load config.json
void Setting::loadConfig()
{
    if (isFileExists("assets/config.json")) {
        std::ifstream file("assets/config.json");
        nlohmann::json jsonData;

        try {
            file >> jsonData;
            
            zNear      = jsonData.value("zNear", 0.1f);
            zFar       = jsonData.value("zFar", 100.0f);
            viewAngle  = jsonData.value("viewAngle", 45.0f);
            SCR_WIDTH  = jsonData.value("SCR_WIDTH", 1600);
            SCR_HEIGHT = jsonData.value("SCR_HEIGHT", 900);
            
            std::cout << "[Setting] config.json load complete!\n";
        } 
        catch (nlohmann::json::parse_error& e) {
            std::cout << "[Setting] config.json has been spoiled, intialize setting.\n";
            
            setConfig(); 
        }

        file.close();
    } 
    else {
        std::cout << "[Setting] config.json doesn't exist. Create new config.json\n";
        setConfig(); 
    }
}

void Setting::setConfig()
{
    nlohmann::json jsonData;
    
    jsonData["zNear"]      = zNear;
    jsonData["zFar"]       = zFar;
    jsonData["viewAngle"]  = viewAngle;
    jsonData["SCR_WIDTH"]  = SCR_WIDTH;
    jsonData["SCR_HEIGHT"] = SCR_HEIGHT;

    std::ofstream file("assets/config.json");
    if (file.is_open()) {
        file << jsonData.dump(4);
        file.close();
        std::cout << "[Setting] config.json saved!\n";
    } else {
        std::cout << "[EROOR] Can't save config.json. Check asset folder does exist.\n";
    }
}

float Setting::getAspect(){ return (float)SCR_WIDTH / (float)SCR_HEIGHT; }
float Setting::getRadian() { return glm::radians(viewAngle); }
float Setting::getZNear() { return zNear; }
float Setting::getZFar() { return zFar; }
int Setting::getWindowWidth() { return SCR_WIDTH; }
int Setting::getWindowHeight() { return SCR_HEIGHT; }