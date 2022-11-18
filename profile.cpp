#include "profile.h"

#include <utility>

Profile::Profile(std::string usrn, std::string dspn): username(std::move(usrn)), displayname(std::move(dspn)) {

}

Profile::Profile() = default;

std::string Profile::getUsername() {
  return username;
}

std::string Profile::getFullName() {
  return displayname + " (@" + username + ")";
}

void Profile::setDisplayName(std::string dspn) {
  displayname = std::move(dspn);
}
