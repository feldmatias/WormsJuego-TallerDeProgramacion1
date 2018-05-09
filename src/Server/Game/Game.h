#ifndef __GAME_H__
#define __GAME_H__

#include "server_Turn.h"
#include "GameParameters.h"
#include "Thread.h"
#include "server_Player.h"
#include "Worm.h"
#include <mutex>
#include <vector>
#include <memory>
#include "World.h"

class Player;

class Game: public Thread{
	private:
		GameParameters parameters;
		World world;
		Turn turn;
		std::mutex mutex;
		std::vector<std::unique_ptr<Thread>> threads;

		void configure();

	public:
		Game(const std::string& config_file);
		~Game();

		bool addPlayer(Player&& player);

		bool isFull();

		void run() override;

		worm_ptr getCurrentWorm();

		void endTurn();
};

#endif