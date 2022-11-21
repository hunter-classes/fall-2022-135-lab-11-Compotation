#include "network.h"
#include <regex>

int Network::findID(std::string usrn) {
  for (int i = 0; i < numUsers; i++) {
    if (profiles[i].getUsername() == usrn) {
      return i;
    }
  }
  return -1;
}

Network::Network() {
  numUsers = 0;
  for (auto & m : following) {
    for (bool & n : m) {
      n = false;
    }
  }
}

bool Network::addUser(std::string usrn, std::string dspn) {
  if (std::regex_match(usrn, std::regex("^[A-Za-z0-9]+$")) && findID(usrn) == -1 && numUsers < MAX_USERS) {
    profiles[numUsers] = Profile(usrn, dspn);
    numUsers++;
    return true;
  }
  return false;
}

bool Network::follow(const std::string& usrn1, const std::string& usrn2) {
  int id1 = findID(usrn1);
  int id2 = findID(usrn2);
  if (id1 != -1 && id2 != -1) {
    following[id1][id2] = true;
  }
  return false;
}

void Network::printDot() {

}
