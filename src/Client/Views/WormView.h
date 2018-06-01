#ifndef __WORMVIEW_H__
#define __WORMVIEW_H__

#include <gtkmm/widget.h>
#include <gtkmm/image.h>
#include <gtkmm/grid.h>
#include <gdkmm/pixbuf.h>
#include <queue>
#include <vector>
#include "Viewable.h"
#include "WormLifeView.h"

#define DIR_RIGHT 1
#define DIR_LEFT -1

/* Clase que se encarga de controlar la vista de los worms */
class WormView: public Viewable {
	private:
		int player_id;
		int life;
		char dir;
		bool is_moving;
		std::string weapon;
		Position last_position;
		WormLifeView label;
		Gtk::Image image;
		Gtk::Grid worm;
		std::queue<Glib::RefPtr<Gdk::Pixbuf>> walk_queue;
		Glib::RefPtr<Gdk::Pixbuf> walk_image;
		std::vector<Glib::RefPtr<Gdk::Pixbuf>> scope_vector;
		Glib::RefPtr<Gdk::Pixbuf> scope_image;
		int angle;

		/* Actualiza la imagen del worm a la correspondiente segun las
		 * condiciones en las que se encuentra este */
		void setNewImage(bool dir_changed, bool colliding, bool is_current_worm, bool has_shot);

		/* Cambia la imagen actual por la del arma actual */
		void setWeaponImage();

		/* Cambia la imagen actual por la siguiente imagen del worm caminando */
		void setMovementImage(bool dir_changed);

		/* Cambia la imagen actual por la imagen del worm caminando */
		void setStaticImage(bool dir_changed);

		/* Actualiza las imagenes de las armas */
		void updateWeaponImage();

		/* Callback */
		bool batHitCallBack(std::vector<Glib::RefPtr<Gdk::Pixbuf>>::iterator& iter, const int width);

	public:
		/* Constructor */
		WormView(WorldView& worldView, int life, char dir, Position pos, int player_id);

		/* Destructor */
		~WormView();

		/* Constructor por movimiento */
		WormView(WormView&& other);


		/* Actualiza la posicion y vida del worm */
		void updateData(int new_life, char new_dir, const Position& new_pos, bool colliding, bool is_current_worm, bool has_shot);

		/* Actualiza la imagen del arma con el angulo actual */
		void updateScope(int angle);

		/* Actualiza el arma del worm y cambia la imagen */
		void changeWeapon(const std::string &weapon);

		/* Devuelve la direccion del worm */
		char getDir() const;

		/* Elimina la imagen del arma del worm */
		void removeWeaponImage();

		/* Devuelve la vida del worm */
		int getLife() const;

		/* Devuelve el id del player que controla al worm */
		int getPlayerId() const;

		/* Devuelve el contenedor donde se encuentra la vista del worm */
		Gtk::Widget& getWidget() override;

		/* Devuelve la imagen que contiene al worm */
		Gtk::Image& getImage();

		/* Cambia la imagen del worm por la animacion del worm
		 * festejando la victoria */
		void setVictory();

		/* Devuelve true si el gusano se esta moviendo */
		bool isMoving() const;

		/* Realiza la animacion del worm bateando */
		void batHit();
};


#endif
