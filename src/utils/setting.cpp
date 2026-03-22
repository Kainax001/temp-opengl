#include "setting.h"

#include <rapidjson/document.h>
#include <rapidjson/prettywriter.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/istreamwrapper.h>
#include <rapidjson/ostreamwrapper.h>
#include <iostream>
#include <fstream>

bool isFileExists(std::string path) {
    std::ifstream file(path.c_str());
    return file.good();
}

Setting::Setting() : zNear(0.1f), zFar(100.0f), viewAngle(45.0f), SCR_WIDTH(1600), SCR_HEIGHT(900), reSizable(GL_FALSE) 
{
    // Initialize config
}

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

void Setting::loadConfig() {
    if (isFileExists("assets/config.json")) {
        std::ifstream ifs("assets/config.json");
        rapidjson::IStreamWrapper isw(ifs);

        rapidjson::Document d;
        d.ParseStream(isw);

        if (!d.HasParseError()) {
            if (d.HasMember("zNear") && d["zNear"].IsFloat()) zNear = d["zNear"].GetFloat();
            if (d.HasMember("zFar") && d["zFar"].IsFloat()) zFar = d["zFar"].GetFloat();
            if (d.HasMember("viewAngle") && d["viewAngle"].IsFloat()) viewAngle = d["viewAngle"].GetFloat();
            if (d.HasMember("SCR_WIDTH") && d["SCR_WIDTH"].IsInt()) SCR_WIDTH = d["SCR_WIDTH"].GetInt();
            if (d.HasMember("SCR_HEIGHT") && d["SCR_HEIGHT"].IsInt()) SCR_HEIGHT = d["SCR_HEIGHT"].GetInt();
            if (d.HasMember("reSizable") && d["reSizable"].IsInt()) reSizable = d["reSizable"].GetInt();

            std::cout << "[Setting] config.json load complete!\n";
        } else {
            std::cout << "[Setting] config.json parse error, initializing.\n";
            saveConfig();
        }
    } else {
        std::cout << "[Setting] config.json doesn't exist. Create new config.json\n";
        saveConfig();
    }
}

void Setting::saveConfig() {
    rapidjson::Document d;
    d.SetObject();
    rapidjson::Document::AllocatorType& allocator = d.GetAllocator();

    d.AddMember("zNear", zNear, allocator);
    d.AddMember("zFar", zFar, allocator);
    d.AddMember("viewAngle", viewAngle, allocator);
    d.AddMember("SCR_WIDTH", SCR_WIDTH, allocator);
    d.AddMember("SCR_HEIGHT", SCR_HEIGHT, allocator);
    d.AddMember("reSizable", reSizable, allocator);

    std::ofstream ofs("assets/config.json");
    if (ofs.is_open()) {
        rapidjson::OStreamWrapper osw(ofs);
        rapidjson::PrettyWriter<rapidjson::OStreamWrapper> writer(osw);

        writer.SetIndent(' ', 4); 
        d.Accept(writer);

        std::cout << "[Setting] config.json saved!\n";
    } else {
        std::cout << "[ERROR] Can't save config.json. Check folder existence.\n";
    }
}

float Setting::getAspect() { return (float)SCR_WIDTH / (float)SCR_HEIGHT; }
float Setting::getRadian() { return glm::radians(viewAngle); }
float Setting::getZNear() { return zNear; }
float Setting::getZFar() { return zFar; }
int Setting::getWindowWidth() { return SCR_WIDTH; }
int Setting::getWindowHeight() { return SCR_HEIGHT; }
int Setting::canResize() { return reSizable; }