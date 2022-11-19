#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "profile.h"
#include "network.h"

TEST_CASE("task a") {
  Profile p1("marco", "Marco");
  CHECK_EQ(p1.getUsername(), "marco");
  CHECK_EQ(p1.getFullName(), "Marco (@marco)");

  p1.setDisplayName("Marco Rossi");
  CHECK_EQ(p1.getUsername(), "marco");
  CHECK_EQ(p1.getFullName(), "Marco Rossi (@marco)");

  Profile p2("tarma1", "Tarma Roving");
  CHECK_EQ(p2.getUsername(), "tarma1");
  CHECK_EQ(p2.getFullName(), "Tarma Roving (@tarma1)");
}

TEST_CASE("task b") {
  Network nw;

  CHECK(nw.addUser("mario", "Mario"));
  CHECK(nw.addUser("luigi", "Luigi"));

  CHECK_FALSE(nw.addUser("mario", "Mario2"));
  CHECK_FALSE(nw.addUser("mario 2", "Mario2"));
  CHECK_FALSE(nw.addUser("mario-2", "Mario2"));

  for (int i = 2; i < 20; i++) {
    CHECK(nw.addUser("mario" + std::to_string(i),
                            "Mario" + std::to_string(i)));
  }

  CHECK_FALSE(nw.addUser("yoshi", "Yoshi"));
}