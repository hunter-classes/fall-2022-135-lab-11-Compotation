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

TEST_CASE("task c: follow") {
  Network nw;
  // add three users
  nw.addUser("mario", "Mario");
  nw.addUser("luigi", "Luigi");
  nw.addUser("yoshi", "Yoshi");

  // make them follow each other
  nw.follow("mario", "luigi");
  nw.follow("mario", "yoshi");
  nw.follow("luigi", "mario");
  nw.follow("luigi", "yoshi");
  nw.follow("yoshi", "mario");
  nw.follow("yoshi", "luigi");

  CHECK_FALSE(nw.isFollowing("mario", "mario"));
  CHECK(nw.isFollowing("mario", "luigi"));
  CHECK(nw.isFollowing("mario", "yoshi"));

  CHECK_FALSE(nw.isFollowing("luigi", "luigi"));
  CHECK(nw.isFollowing("luigi", "mario"));
  CHECK(nw.isFollowing("luigi", "yoshi"));

  CHECK_FALSE(nw.isFollowing("yoshi", "yoshi"));
  CHECK(nw.isFollowing("yoshi", "mario"));
  CHECK(nw.isFollowing("yoshi", "luigi"));

  // add a user who does not follow others
  nw.addUser("wario", "Wario");
  for (auto user: {"mario", "luigi", "yoshi", "wario"}) {
    CHECK_FALSE(nw.isFollowing("wario", user));
  }
}

TEST_CASE("task d") {
  Network nw;
  // add three users
  nw.addUser("mario", "Mario");
  nw.addUser("luigi", "Luigi");
  nw.addUser("yoshi", "Yoshi");

  nw.follow("mario", "luigi");
  nw.follow("luigi", "mario");
  nw.follow("luigi", "yoshi");
  nw.follow("yoshi", "mario");

  // write some posts
  nw.writePost("mario", "It's a-me, Mario!");
  nw.writePost("luigi", "Hey hey!");
  nw.writePost("mario", "Hi Luigi!");
  nw.writePost("yoshi", "Test 1");
  nw.writePost("yoshi", "Test 2");
  nw.writePost("luigi", "I just hope this crazy plan of yours works!");
  nw.writePost("mario", "My crazy plans always work!");
  nw.writePost("yoshi", "Test 3");
  nw.writePost("yoshi", "Test 4");
  nw.writePost("yoshi", "Test 5");

  CHECK_EQ(nw.getTimeline("mario"), "Mario (@mario): My crazy plans always work!\n"
                                    "Luigi (@luigi): I just hope this crazy plan of yours works!\n"
                                    "Mario (@mario): Hi Luigi!\n"
                                    "Luigi (@luigi): Hey hey!\n"
                                    "Mario (@mario): It's a-me, Mario!\n");
  CHECK_EQ(nw.getTimeline("yoshi"),
           "Yoshi (@yoshi): Test 5\n"
           "Yoshi (@yoshi): Test 4\n"
           "Yoshi (@yoshi): Test 3\n"
           "Mario (@mario): My crazy plans always work!\n"
           "Yoshi (@yoshi): Test 2\n"
           "Yoshi (@yoshi): Test 1\n"
           "Mario (@mario): Hi Luigi!\n"
           "Mario (@mario): It's a-me, Mario!\n");
}