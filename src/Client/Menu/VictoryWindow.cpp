#include "VictoryWindow.h"
#include <gtkmm/builder.h>
#include "Path.h"
#include <iostream>

VictoryWindow::VictoryWindow(Gtk::Window& window) :
	window(window), made_choice(false) {
	Glib::RefPtr<Gtk::Builder> builder = Gtk::Builder::create_from_file(GLADE_PATH + "victory_window.glade");

	builder->get_widget("Menu", this->my_window);

	builder->get_widget("victory_msg", victory_msg);

	builder->get_widget("Return_menu", this->return_menu);
	builder->get_widget("quit", this->quit);

	this->return_menu->signal_clicked().connect(sigc::mem_fun(*this, &VictoryWindow::returnMenuButtonPressed));

	this->quit->signal_clicked().connect(sigc::mem_fun(*this, &VictoryWindow::quitButtonPressed));
}

VictoryWindow::~VictoryWindow() {}

void VictoryWindow::returnMenuButtonPressed() {
	//this->made_choice = true;
	std::cout << "Vuelvo al menu principal" << std::endl;
	this->my_window->close();
}

void VictoryWindow::quitButtonPressed() {
	this->my_window->close();
	this->window.close();
}

void VictoryWindow::setWinner(std::string&& message) {
	this->winner_msg = message;
	this->victory_msg->set_text(this->winner_msg);
}

void VictoryWindow::show_all() {
	this->my_window->show_all();

}