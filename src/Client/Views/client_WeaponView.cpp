#include "WeaponView.h"

WeaponView::WeaponView(WorldView& worldView, std::string weapon, Position pos):
	Viewable(worldView), weapon_name(std::move(weapon)){
	this->addToWorld(pos);
}

WeaponView::~WeaponView(){}

void WeaponView::updateData(const Position& new_pos){
	this->move(new_pos);
}

void WeaponView::explode(){
	this->removeFromWorld();
	////////////////////////////////////////Hacer sonido de explosion y animacion? Si se hace animacion hay que guardar la ultima posicion del arma
}

Gtk::Widget& WeaponView::getWidget(){
	////////////////////////////////////////////Ver que hacer con la rotacion, por ahora lo dejo asi
	std::string path(IMAGES_PATH);
	path += this->weapon_name;
	path += ".png";
	this->image.set(path);
	return this->image;
}