#include "SelectableListMenu.h"

SelectableListMenu::SelectableListMenu(Gtk::Window& window, ClientProtocol&& protocol, std::string&& name):
	MenuView(window, std::move(protocol)), player_name(std::move(name)){}

SelectableListMenu::~SelectableListMenu(){}

void SelectableListMenu::configure(int quantity){
	try{
		for (int i = 0; i < quantity; i++){
			std::string field = this->protocol.receiveString();
			this->addField(field);
		}
	}catch (const SocketException& e){
		this->error->set_label("Ocurrio un error");
        this->showError();
	}

	for (auto it = this->fields.begin(); it != this->fields.end(); ++it){
		this->games->pack_start(it->getContainer());
	}
	this->games->show();
}

void SelectableListMenu::addField(const std::string& field_name){
	GameMenuField field(field_name);
	this->fields.push_back(std::move(field));
	this->fields.back().getButton().signal_clicked().connect(sigc::bind<Glib::ustring>(sigc::mem_fun(*this,
                                                                                                   &SelectableListMenu::selectButtonPressed), field_name));
}


bool SelectableListMenu::createPlayer(){
	this->player = std::unique_ptr<Player>(new Player(std::move(this->protocol), this->player_name, this->window));
	return false;
}
