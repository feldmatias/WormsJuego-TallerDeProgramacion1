#ifndef __CLIENTPLAYER_H__
#define __CLIENTPLAYER_H__

#include <memory>
#include "client_Protocol.h"
#include "WorldView.h"
#include "client_Turn.h"
#include "client_Weapon.h"
#include "client_WeaponList.h"
#include "WorldView.h"
#include "client_WeaponView.h"
#include "client_ScreenView.h"
#include "ViewsList.h"
#include "Position.h"
#include "DataReceiver.h"
#include "Handlers.h"
#include "client_PlayersList.h"
#include "TurnLabel.h"

class Player {
	private:
		ClientProtocol protocol;
		std::string name;
		WeaponList weapons;
		WorldView world;
		WeaponView weapons_view;
		TurnLabel turn_label;
		ScreenView screen;
		std::unique_ptr<Turn> turn;
		ViewsList view_list;
		DataReceiver data_receiver;
		Handlers handlers;
		PlayersList players_list;
		
		void disable_attack_handlers();

	public:
		Player(ClientProtocol protocol, const std::string& name);
		~Player();

		void startTurn(int worm_id, int player_id);
		void endTurn();

		void change_weapon(std::string weapon);
		
		void shoot(int angle, int power, int time);
		void shoot(Position position);
		
		void update_weapons_view();
		
		void play_tick_time();
		
		Gtk::Container& getWindow();
		
		WorldView& getWorld();
		
		ViewsList& getViewList();

		ClientProtocol& getProtocol();
};

#endif