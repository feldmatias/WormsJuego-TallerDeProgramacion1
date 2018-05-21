#ifndef __HANDLERS__H__
#define __HANDLERS__H__

#include "client_Timer.h"
#include <gdk/gdk.h>

class Player;
class ViewsList;
class WeaponList;
class WorldView;

/* Clase que se encarga de definir los handlers del teclado y 
   del mouse. */
class Handlers{
	private:
		Player& player;
		ViewsList& view_list;
		WeaponList& weapons;
		WorldView& world;

		bool has_shoot;
		int current_angle;
		int weapons_time;

		std::unique_ptr<Timer> timer;


	public:
		/* Constructor */
		Handlers(Player& player, ViewsList& view_list, WeaponList& weapons, WorldView& world);

		/* Destructor */
		~Handlers();

		/* Handler de movimiento. Establece cuales son teclas de movimiento */
		bool movement_key_press_handler(GdkEventKey* key_event);

		/* Handler completo para el presionado de teclas. Indica
		   los pasos que se deben realizar al presionar una tecla
		   especifica */
		bool complete_key_press_handler(GdkEventKey* key_event);

		/* Handler completo para la liberación de teclas. Indica
		   los pasos que se deben realizar al liberar una tecla
		   especifica */
		bool complete_key_release_handler(GdkEventKey* key_event);

		/* Handler del mouse. Indica los pasos que se deben realizar
		   al utilizar el mouse */
		bool on_button_press_event(GdkEventButton* event);

		/* Handler inactivo de las teclas. Indica que no se debe
		   realizar ninguna accion al producirse un evento */
		bool inactive_key_handler(GdkEventKey* key_event);

		/* Handler inactivo del mouse. Indica que no se debe
		   realizar ninguna accion al producirse un evento */
		bool inactive_button_handler(GdkEventButton *event);

		/* Habilita todos los handlers */
		void enable_all();

		/* Deshabilita todos los handlers */
		void disable_all();

		/* Deshabilita los handlers de ataque */
		void disable_attack_handlers();

		/* Realiza el shoot del player */
		void timerStopped(int power);

		/* Devuelve el angulo actual del scope */
		int getCurrentAngle() const;
};

#endif
