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
}

bool Network::addUser(std::string usrn, std::string dspn) {
  if (std::regex_match(usrn, std::regex("^[A-Za-z0-9]+$")) && findID(usrn) == -1 && numUsers < MAX_USERS) {
    profiles[numUsers] = Profile(usrn, dspn);
    numUsers++;
    return true;
  }
  return false;
}
