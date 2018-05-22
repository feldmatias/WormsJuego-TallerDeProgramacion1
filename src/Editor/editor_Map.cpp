
#include <iostream>
#include <fstream>
#include "yaml-cpp/yaml.h"
#include "editor_Map.h"

Map::Map(BaseObjectType *cobject, const Glib::RefPtr<Gtk::Builder> &builder)
        : Gtk::Layout(cobject),
          m_builder(builder) {
    add_events(Gdk::BUTTON_PRESS_MASK);
    signal_button_press_event().connect(
            sigc::mem_fun(*this, &Map::on_button_clicked));
    pallete.emplace_back("resources/images/right_worm.png");
    for (int i = 0; i < 180; i = i + 10) {
        pallete.emplace_back(
                "resources/images/Girder/girder_3_" + std::to_string(i) +
                ".png");
    }
    for (int i = 0; i < 180; i = i + 10) {
        pallete.emplace_back(
                "resources/images/Girder/girder_6_" + std::to_string(i) +
                ".png");
    }
}


void Map::add(unsigned int id, double x, double y) {
    Gtk::Image new_image(pallete[id - 1]);
    const Glib::RefPtr<Gdk::Pixbuf> &img = new_image.get_pixbuf();
    put(new_image, x-img->get_width()/2,y-img->get_height()/2);
    new_image.show();
    objects.push_back(std::move(new_image));
}

void Map::moveLast(double x, double y) {
    Gtk::Image &actual_object = objects.back();
    move(actual_object,x-actual_object.get_width()/2,y-actual_object.get_height()/2);
    actual_object.show();
}

void Map::turnLast(int angle) {
    objects.pop_back();
    Gtk::Image new_image(pallete[(angle % 180) / 10 + 1]);
    //TODO: como obtengo la posicion nueva??
    put(new_image, 100, 100);
    new_image.show();
    objects.push_back(std::move(new_image));
}


//VIEJO
void Map::turn_signal() {
    /*/
    MapObject &object = objects.back().second;

    Gtk::Image new_image(pallete[(object.turn() % 180) / 10 + 1]);
    const Glib::RefPtr<Gdk::Pixbuf> &pixb = object.getImagePixbuf();
    const Pos &pos = object.getPos();


    put(new_image, object.getPrintableWidth(),
        object.getPrintableHeight());
    objects.pop_back();
    new_image.show();
    MapObject new_obj(std::move(new_image), std::move(pos));
    objects.emplace_back(std::make_pair(button_id, std::move(new_obj)));

     /*/
}

bool Map::on_button_clicked(GdkEventButton *button_event) {
    controller->mapClickedSignal(button_event);
    /*/
    if (action == 0) { //nuevo
        Gtk::Image new_image(pallete[button_id - 1]);
        Pos pos(button_event->x, button_event->y);

        const Glib::RefPtr<Gdk::Pixbuf> &img = new_image.get_pixbuf();

        put(new_image, pos.getPrintableWidth(img->get_width()),
            pos.getPrintableHeigth(img->get_height()));
        new_image.show();
        MapObject object(std::move(new_image), pos);
        objects.emplace_back(std::make_pair(button_id, std::move(object)));


    } else if (action == 1) { //mover

        MapObject &object = objects.back().second;
        const Glib::RefPtr<Gdk::Pixbuf> &img = object.getImagePixbuf();
        Gtk::Image *image = object.getImageWidget();
        object.updatePos(button_event->x, button_event->y);

        move(*image, object.getPrintableWidth(),
             object.getPrintableHeight());

        action = 0;
    }
     /*/
    return true;

}

void Map::undo() {
    objects.pop_back();
}

void Map::clean() {
    objects.clear();
}

void Map::save_signal() {
    /*/
    //gusanos
    std::vector<std::vector<double>> worms;
    std::vector<std::vector<double>> girders;
    for (auto &object : objects) {
        const Pos &pos = object.second.getPos();
        if (object.first == 1) {//worm
            std::vector<double> position;
            position.push_back(pos.getX()); //pos x
            position.push_back(pos.getY()); //pos_y
            worms.push_back(position);
        } else if (object.first == 2) { //viga corta
            std::vector<double> data;
            data.push_back(3); //len
            data.push_back(pos.getX()); //pos_x
            data.push_back(pos.getY()); //pos_y
            data.push_back(pos.getAngle()); //rotation
            girders.push_back(data);
        }
    }

    YAML::Emitter out;

    out << YAML::BeginMap;

    out << YAML::Key << "worms_life";
    out << YAML::Value << 200;

    //armas
    out << YAML::Key << "weapon_ammo";
    out << YAML::Value << YAML::BeginMap;
    out << YAML::Key << "Bazooka";
    out << YAML::Value << 99999;
    out << YAML::Key << "Mortar";
    out << YAML::Value << 10;
    out << YAML::Key << "GreenGrenade";
    out << YAML::Value << 99999;
    out << YAML::Key << "RedGrenade";
    out << YAML::Value << 10;
    out << YAML::Key << "Banana";
    out << YAML::Value << 5;
    out << YAML::Key << "HolyGrenade";
    out << YAML::Value << 2;
    out << YAML::Key << "Dynamite";
    out << YAML::Value << 5;
    out << YAML::Key << "Bat";
    out << YAML::Value << 99999;
    out << YAML::Key << "AirAttack";
    out << YAML::Value << 2;
    out << YAML::Key << "Teleportation";
    out << YAML::Value << 99999;

    out << YAML::EndMap;

    //posicion de gusanos
    out << YAML::Key << "worms";
    out << worms;

    out << YAML::Key << "girders";
    out << girders;

    /*//*/out << YAML::Value << YAML::BeginSeq;

    out << YAML::Value << YAML::BeginSeq << 50 << 100 << YAML::EndSeq;
    out << YAML::Value << YAML::BeginSeq << 60 << 100 << YAML::EndSeq;
    out << YAML::Value << YAML::BeginSeq << 70 << 100 << YAML::EndSeq;

    out << YAML::EndSeq;/*//*/


    out << YAML::EndMap;

    //std::cout << "Here's the output YAML:\n\n\n" << out.c_str()<<std::endl;

    std::ofstream file("config_editor.yaml");
    file << out.c_str();
    /*/

}

void Map::load_signal() {
    /*/
    clean();
    YAML::Node config = YAML::LoadFile("config_editor.yaml");
/*//*/
    int worms_life = config["worms_life"].as<int>();
    std::cout << "worms_life: " << worms_life << std::endl;

    //convierto directamente a map
    std::map<std::string, int> ammo = config["weapon_ammo"].as<std::map<std::string, int>>();

    std::cout << "En el map: ammo bazooka: " << ammo["Bazooka"] << std::endl;
    std::cout << "ammo dynamite: " << ammo["Dynamite"]<< std::endl;

/*//*/
    //carga de  worms
    std::vector<std::vector<float>> worms = config["worms"].as<std::vector<std::vector<float>>>();

    //std::cout <<"\nworms:\n\n";
    for (auto &worm : worms) {
        MapObject new_worm(Gtk::Image(pallete.front()), Pos(worm[0], worm[1]));
        Gtk::Image *new_image = new_worm.getImageWidget();
        put(*new_image, new_worm.getPrintableWidth(),
            new_worm.getPrintableHeight());
        new_image->show();
        objects.emplace_back(std::make_pair(1, std::move(new_worm)));
        //std::cout << "pos_x: " << worm[0] << " pos_y: " << worm[1] << std::endl;

    }

    //carga de vigas
    std::vector<std::vector<float>> girders = config["girders"].as<std::vector<std::vector<float>>>();

    //std::cout <<"\nGirders:\n\n";
    for (auto &girder : girders) {
        MapObject new_girder(Gtk::Image(pallete[1]),
                             Pos(girder[1], girder[2], girder[3]));
        objects.emplace_back(std::make_pair(2, std::move(new_girder)));
        //std::cout << "len: " << girder[0] <<"  pos_x: " << girder[1] << " pos_y: " << girder[2] << "  rotation: "<< girder[3] << std::endl;
    }
    /*/
}

void Map::linkController(MapController *pController) {
    this->controller = pController;
}






