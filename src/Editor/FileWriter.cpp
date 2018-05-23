
#include <yaml.h>
#include <iostream>
#include <WeaponNames.h>
#include <ConfigFields.h>
#include "FileWriter.h"
#include "MapObject.h"

FileWriter::FileWriter(const std::string &filename)
        : File(filename, std::fstream::out | std::ios_base::trunc) {}


void FileWriter::save(const std::vector<int>& weapons,
                std::vector<std::vector<double>>& worms,
                std::vector<std::vector<double>>& girders) {
    YAML::Emitter out;

    out << YAML::BeginMap;

    out << YAML::Key << WORMS_LIFE;
    out << YAML::Value << 200;

    //armas
    out << YAML::Key << WEAPON_AMMO;
    out << YAML::Value << YAML::BeginMap;
    out << YAML::Key << BAZOOKA_NAME;
    out << YAML::Value << weapons[0];
    out << YAML::Key << MORTAR_NAME;
    out << YAML::Value << weapons[1];
    out << YAML::Key << GREEN_GRENADE_NAME;
    out << YAML::Value << weapons[2];
    out << YAML::Key << RED_GRENADE_NAME;
    out << YAML::Value << weapons[3];
    out << YAML::Key << BANANA_NAME;
    out << YAML::Value << weapons[4];
    out << YAML::Key << HOLY_GRENADE_NAME;
    out << YAML::Value << weapons[9];
    out << YAML::Key << DYNAMITE_NAME;
    out << YAML::Value << weapons[8];
    out << YAML::Key << BAT_NAME;
    out << YAML::Value << weapons[6];
    out << YAML::Key << AIR_ATTACK_NAME;
    out << YAML::Value << weapons[5];
    out << YAML::Key << TELEPORT_NAME;
    out << YAML::Value << weapons[7];

    out << YAML::EndMap;

    //posicion de gusanos
    out << YAML::Key << WORMS_DATA;
    out << worms;

    out << YAML::Key << GIRDERS_DATA;
    out << girders;


    out << YAML::EndMap;

    std::cout << "Here's the output YAML:\n\n\n" << out.c_str()<<std::endl;

    file << out.c_str();
}