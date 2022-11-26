#pragma once
#include "profile.h"
#include "post.h"

class Network {
private:
  static const int MAX_USERS = 20; // max number of user profiles
  int numUsers;                    // number of registered users
  Profile profiles[MAX_USERS];     // user profiles array:
  bool following[MAX_USERS][MAX_USERS];

  static const int MAX_POSTS = 100;
  int numPosts;                    // number of posts
  Post posts[MAX_POSTS];           // array of all posts

  // mapping integer ID -> Profile

  // Returns user ID (index in the 'profiles' array) by their username
  // (or -1 if username is not found)
  int findID(const std::string &usrn);

public:
  // Constructor, makes an empty network (numUsers = 0)
  Network();

  // Attempts to sign up a new user with specified username and displayname
  // return true if the operation was successful, otherwise return false
  bool addUser(const std::string &usrn, const std::string &dspn);

  bool follow(const std::string &usrn1, const std::string &usrn2);

  void printDot();

  // usrn1 is following usrn2
  bool isFollowing(const std::string &usrn1, const std::string &usrn2);

  // Add a new post
  bool writePost(const std::string &usrn, const std::string &msg);

  // Print user's "timeline"
  bool printTimeline(const std::string &usrn);

  std::string getTimeline(const std::string &usrn);
};
