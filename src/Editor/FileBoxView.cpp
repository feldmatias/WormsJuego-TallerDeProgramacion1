
#include "FileBoxView.h"

FileBoxView::FileBoxView(BaseObjectType *cobject,
                         const Glib::RefPtr<Gtk::Builder> &builder)
        : Gtk::HBox(cobject) {
    builder->get_widget("btn_save", save);
    builder->get_widget("btn_load", load);
}

void FileBoxView::linkControler(std::shared_ptr<FileBoxController> controller) {
    this->file_box_controller = std::move(controller);
    save->signal_clicked().connect(
            sigc::mem_fun(*file_box_controller,
                          &FileBoxController::onSaveClicked));

    load->signal_clicked().connect(
            sigc::mem_fun(*file_box_controller,
                          &FileBoxController::onLoadClicked));
}