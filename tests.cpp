#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "profile.h"

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
