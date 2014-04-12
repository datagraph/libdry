/* This is free and unencumbered software released into the public domain. */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "catch.hpp"

#include <dry/bitset.h>
#include <dry/bitset/empty_bitset.h>
#include <dry/bitset/small_bitset.h>
#include <dry/bitset/uniform_bitset.h>

////////////////////////////////////////////////////////////////////////////////
/* dry::bitset */

using bitset = dry::empty_bitset;

TEST_CASE("bitset::npos") {
  REQUIRE(bitset::npos > 0);
}

TEST_CASE("bitset::word_size") {
  REQUIRE(bitset::word_size > 0);
}

////////////////////////////////////////////////////////////////////////////////
/* dry::empty_bitset */

using empty_bitset = dry::empty_bitset;

TEST_CASE("empty_bitset#size") {
  REQUIRE(empty_bitset{}.size() == 0);
}

TEST_CASE("empty_bitset#count") {
  REQUIRE(empty_bitset{}.count(true) == 0);
  REQUIRE(empty_bitset{}.count(false) == 0);
}

TEST_CASE("empty_bitset#all") {
  REQUIRE(empty_bitset{}.all() == false);
}

TEST_CASE("empty_bitset#any") {
  REQUIRE(empty_bitset{}.any() == false);
}

TEST_CASE("empty_bitset#none") {
  REQUIRE(empty_bitset{}.none() == true);
}

TEST_CASE("empty_bitset#flip") {
  REQUIRE_NOTHROW(empty_bitset{}.flip());
}

////////////////////////////////////////////////////////////////////////////////
/* dry::small_bitset */

using small_bitset = dry::small_bitset<16>;

TEST_CASE("small_bitset#size") {
  REQUIRE(small_bitset{}.size() == 0);
  REQUIRE(small_bitset{1}.size() == 1);
  REQUIRE(small_bitset{100}.size() == 100);
  REQUIRE_THROWS_AS(small_bitset{1ULL<<33}.size(), std::out_of_range);
}

TEST_CASE("small_bitset#count") {
  REQUIRE(small_bitset{}.count(true) == 0);
  REQUIRE(small_bitset{}.count(false) == 0);
  REQUIRE(small_bitset{1}.count(true) == 0);
  REQUIRE(small_bitset{1}.count(false) == 1);
}

TEST_CASE("small_bitset#all") {
  REQUIRE(small_bitset{}.all() == false);
  REQUIRE(small_bitset{1}.all() == false);
  //REQUIRE(small_bitset{1}.flip().all() == true);
}

TEST_CASE("small_bitset#any") {
  REQUIRE(small_bitset{}.any() == false);
  REQUIRE(small_bitset{1}.any() == false);
  //REQUIRE(small_bitset{1}.flip().any() == true);
}

TEST_CASE("small_bitset#none") {
  REQUIRE(small_bitset{}.none() == true);
  REQUIRE(small_bitset{1}.none() == true);
  //REQUIRE(small_bitset{1}.flip().none() == false);
}

TEST_CASE("small_bitset#flip") {} /* not supported */

////////////////////////////////////////////////////////////////////////////////
/* dry::uniform_bitset */

using uniform_bitset = dry::uniform_bitset;

TEST_CASE("uniform_bitset#size") {
  REQUIRE(uniform_bitset{}.size() == 0);
}

TEST_CASE("uniform_bitset#count") {
  REQUIRE(uniform_bitset{}.count(true) == 0);
  REQUIRE(uniform_bitset{}.count(false) == 0);
  REQUIRE(uniform_bitset{1}.count(true) == 0);
  REQUIRE(uniform_bitset{1}.count(false) == 1);
}

TEST_CASE("uniform_bitset#all") {
  REQUIRE(uniform_bitset{}.all() == false);
  REQUIRE(uniform_bitset(1, false).all() == false);
  REQUIRE(uniform_bitset(1, true).all() == true);
}

TEST_CASE("uniform_bitset#any") {
  REQUIRE(uniform_bitset{}.any() == false);
  REQUIRE(uniform_bitset(1, false).any() == false);
  REQUIRE(uniform_bitset(1, true).any() == true);
}

TEST_CASE("uniform_bitset#none") {
  REQUIRE(uniform_bitset{}.none() == true);
  REQUIRE(uniform_bitset(1, false).none() == true);
  REQUIRE(uniform_bitset(1, true).none() == false);
}

TEST_CASE("uniform_bitset#flip") {
  REQUIRE_NOTHROW(uniform_bitset{}.flip());
  REQUIRE(uniform_bitset{}.value() == false);
  REQUIRE(uniform_bitset{}.flip().value() == true);
}
