#include "network.h"
#include <regex>
#include <iostream>

int Network::findID(const std::string &usrn) {
  for (int i = 0; i < numUsers; i++) {
    if (profiles[i].getUsername() == usrn) {
      return i;
    }
  }
  return -1;
}

Network::Network() {
  numUsers = 0;
  numPosts = 0;
  for (auto & m : following) {
    for (bool & n : m) {
      n = false;
    }
  }
}

bool Network::addUser(const std::string &usrn, const std::string &dspn) {
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
  std::cout << "digraph {\n";
  for (int i = 0; i < numUsers; i++) {
    std::cout << "  \"@" << profiles[i].getUsername() << "\"\n";
  }
  std::cout << "\n";
  for (int m = 0; m < numUsers; m++) {
    for (int n = 0; n < numUsers; n++) {
      if (following[m][n]) {
        std::cout << "  \"@" << profiles[m].getUsername() << "\" -> " << "\"@" << profiles[n].getUsername() << "\"\n";
      }
    }
  }
  std::cout << "}";
}

bool Network::isFollowing(const std::string &usrn1, const std::string &usrn2) {
  if (findID(usrn1) != -1 && findID(usrn2) != -1) {
    return following[findID(usrn1)][findID(usrn2)];
  }
  return false;
}

bool Network::writePost(const std::string &usrn, const std::string &msg) {
  if (findID(usrn) != -1 && numPosts < MAX_POSTS) {
    posts[numPosts] = {usrn, msg};
    numPosts++;
    return true;
  }
  return false;
}

bool Network::printTimeline(const std::string &usrn) {
  std::cout << getTimeline(usrn);
  return !getTimeline(usrn).empty();
}

std::string Network::getTimeline(const std::string &usrn) {
  std::string res;
  for (int i = numPosts - 1; i > -1; i--) {
    Post &post = posts[i];
    if (post.username == usrn || isFollowing(usrn, post.username)) {
      res += profiles[findID(post.username)].getFullName() + ": " + post.message + "\n";
    }
  }
  return res;
}
