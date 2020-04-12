//
// Created by tal on 12.12.2019.
//

#include <mutex>
#include "ConnectControlClientCommand.h"
#include <string>
std::mutex mutex_lock1;
void SendAndGetMassages(int client_socket) {
  string information;
  while (Variables::getInstance()->threadFlag) {
    mutex_lock1.try_lock();
    while (!Variables::getInstance()->queOfVarsToPushToTheServer.empty()) {
      information = "set " + Variables::getInstance()->queOfVarsToPushToTheServer.front()->GetSim().substr(1) + " " +
          to_string(Variables::getInstance()->queOfVarsToPushToTheServer.front()->GetValue()) + "\r\n";
      int is_sent = send(client_socket, information.c_str(), information.length(), MSG_NOSIGNAL);
//      int is_sent = send(client_socket, information.c_str(), information.length(), 0);
      if (is_sent < 0) {
        std::cout << "Error sending message" << std::endl;
      }
      //////////////////must check if the delete works good.!
      delete Variables::getInstance()->queOfVarsToPushToTheServer.front();
      Variables::getInstance()->queOfVarsToPushToTheServer.pop();
      information = "";
    }
    mutex_lock1.unlock();
  }
  close(client_socket);
}
int ConnectControlClientCommand::execute(vector<string> vector, int index) {
  {
    //create socket
    int client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1) {
      //error
      std::cerr << "Could not create a socket" << std::endl;
      return -1;
    }

    //We need to create a sockaddr obj to hold address of server
    sockaddr_in address; //in means IP4
    address.sin_family = AF_INET;//IP4
    string localHostAdd = vector[index + 1].substr(1, vector[index + 1].size() - 2);
    address.sin_addr.s_addr = inet_addr(localHostAdd.c_str());  //the localhost address
    address.sin_port = htons(Variables::getInstance()->doShuntingYard(vector[index + 2]));
    //we need to convert our number (both port & localhost)
    // to a number that the network understands.

    // Requesting a connection with the server on local host with port 8081
    int is_connect = connect(client_socket, (struct sockaddr *) &address, sizeof(address));
    if (is_connect == -1) {
      std::cerr << "Could not connect to host server" << std::endl;
      return -2;
    } else {
      //std::cout << "Client is now connected to server" << std::endl;
    }

    //if here we made a connection
    Variables::getInstance()->thr2 = thread(SendAndGetMassages, client_socket);
    return 3;
  }
}