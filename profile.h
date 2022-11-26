#pragma once
#include <string>
class Profile {
private:
  std::string username;
  std::string displayname;

public:
  Profile(std::string usrn, std::string dspn);

  Profile();

  // Return username
  std::string getUsername();

  // Return name in the format: "displayname (@username)"
  std::string getFullName();

  void setDisplayName(std::string dspn);
};
