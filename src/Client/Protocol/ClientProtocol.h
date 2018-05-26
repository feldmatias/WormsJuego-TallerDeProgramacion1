#ifndef __CLIENTPROTOCOL_H__
#define __CLIENTPROTOCOL_H__

#include "Socket.h"
#include "Protocol.h"
#include "Position.h"
#include "ViewsList.h"
#include "PlayersList.h"

class Player;
class WeaponList;

class ClientProtocol: public Protocol {
	public:
		/* Constructor */
		ClientProtocol(Socket&& socket);

		/* Constructor por movimiento */
		ClientProtocol(ClientProtocol&& other);

		/* Destructor */
		~ClientProtocol();

		/* Envia un mensaje que indica una accion de movimiento */
		void send_move_action(char action);

	    /* Envia un mensaje que indica que el worm dejo de moverse */
	    void send_stop_moving();

		/* Envia un mensaje que indica una accion de cambio de arma
		 * con el nombre del arma */
		void send_change_weapon(const std::string& weapon);

		/* Envia un mensaje de accion de disparo, con el angulo, la potencia
		 * y el tiempo de explosion */
		void send_weapon_shoot(int32_t angle, int32_t power, int32_t time);

		/* Envia un mensaje de accion de disparo teledirigido con
		 * la posicion del disparo */
		void send_weapon_self_directed_shoot(const Position& pos);

		/* Envia un mensaje de finalizacion de turno */
		void send_end_turn();

		/* Recibe un mensaje que le indica que accion realizar */
		void receive(Player& player, ViewsList& viewsList);

		/* Recibe los jugadores de la partida junto con su
		 * id y su nombre */
		void receivePlayers(PlayersList& players_list);

		/* Recibe la vigas presentes en el mapa junto con su tamaño,
		 * su posicion y su rotacion */
		void receiveGirders(ViewsList& viewsList);

		/* Recibe las armas presentes en el juego junto con
		 * su municion */
		void receiveWeaponsAmmo(WeaponList& weapon_list);
};

#endif
