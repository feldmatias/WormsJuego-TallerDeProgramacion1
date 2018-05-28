#ifndef __SERVER_H__
#define __SERVER_H__

#include <string>
#include <list>
#include <memory>
#include "Socket.h"
#include "Thread.h"
#include "GamesList.h"

class Server: public Thread{
	private:
		Socket socket;
		std::list<std::unique_ptr<Thread>> clients;
		GamesList games_list;

		void check();

	public:
		//Crea el server y lo asocia al puerto indicado
		Server(const std::string& service);

		//Desconecta el server
		~Server();

		//Ejecuta el server
		void run();

		//Avisa al server que debe dejar de ejecutarse
		void stop();
};

#endif