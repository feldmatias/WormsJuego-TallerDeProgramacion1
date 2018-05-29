
#include "FileBoxView.h"

FileBoxView::FileBoxView(BaseObjectType *cobject,
                         const Glib::RefPtr<Gtk::Builder> &builder)
        : Gtk::HBox(cobject) {
    builder->get_widget("btn_save", save);
    Gtk::manage(save);
    builder->get_widget("btn_load", load);
    Gtk::manage(load);
    builder->get_widget("btn_clean", new_map);
    Gtk::manage(new_map);
}

void FileBoxView::linkControler(std::shared_ptr<FileBoxController> controller) {
    this->file_box_controller = std::move(controller);
    save->signal_clicked().connect(
            sigc::mem_fun(*file_box_controller,
                          &FileBoxController::onSaveClicked));

    load->signal_clicked().connect(
            sigc::mem_fun(*file_box_controller,
                          &FileBoxController::onLoadClicked));

    new_map->signal_clicked().connect(
            sigc::mem_fun(*file_box_controller,
                          &FileBoxController::onNewClicked));
}