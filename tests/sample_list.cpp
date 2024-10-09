

#include "../src/fuzzy.hpp"
#include <iostream>

#include <string>

int
main(void)
{
  {
    std::cout << "Rough finding for 'cat'" << std::endl;
    std::string to_find = "cat";
    std::vector<std::string> vec;
    vec.push_back("dogs");
    vec.push_back("unicorns");
    vec.push_back("table");
    vec.push_back("planets");
    vec.push_back("cats");
    vec.push_back("ostrich");
    vec.push_back("shouting");
    vec.push_back("promenade");
    vec.push_back("running");
    vec.push_back("clandestine");
    vec.push_back("at");
    vec.push_back("cat");
    vec.push_back("musical");
    vec.push_back("45g0-");
    auto rec = fuzzy::rough_find(to_find, vec);
    for ( const auto &n : rec )
      std::cout << "\"" << vec[n.index] << "\": " << n.res << std::endl;
  }

  {
    std::cout << "Precise finding for 'cat'" << std::endl;
    std::string to_find = "cat";
    std::vector<std::string> vec;
    vec.push_back("dogs");
    vec.push_back("unicorns");
    vec.push_back("table");
    vec.push_back("planets");
    vec.push_back("cats");
    vec.push_back("ostrich");
    vec.push_back("shouting");
    vec.push_back("promenade");
    vec.push_back("running");
    vec.push_back("clandestine");
    vec.push_back("at");
    vec.push_back("cat");
    vec.push_back("musical");
    vec.push_back("45g0-");
    auto rec = fuzzy::precise_find(to_find, vec);
    for ( const auto &n : rec )
      std::cout << "\"" << vec[n.index] << "\": " << n.res << std::endl;
  }
  {
    std::string to_find = "brier";
    std::vector<std::string> vec = {
      "aardvark",   "abacus",       "abyss",      "acorn",       "adamant",      "adhesive",  "aeroplane", "algebra",
      "allege",     "alloy",        "almanac",    "aloft",       "ambush",       "amulet",    "anchor",    "anomaly",
      "antenna",    "anthem",       "apex",       "apogee",      "arable",       "archway",   "armistice", "aroma",
      "arson",      "artifact",     "artisan",    "asphalt",     "astute",       "asylum",    "atlas",     "atom",
      "attire",     "auburn",       "aurora",     "autumn",      "avalanche",    "avatar",    "avian",     "axiom",
      "azure",      "backlog",      "balustrade", "bamboo",      "baritone",     "basilisk",  "bastion",   "beacon",
      "behemoth",   "bellwether",   "benchmark",  "berserk",     "bibliography", "binary",    "bitumen",   "blizzard",
      "blueprint",  "bohemian",     "borough",    "botany",      "bravado",      "briar",     "brittle",   "broker",
      "buccaneer",  "bullion",      "bungalow",   "bureaucracy", "burlesque",    "burlap",    "byline",    "cabaret",
      "cadenza",    "calculus",     "calypso",    "cameo",       "canopy",       "capsize",   "caravan",   "cartridge",
      "cascade",    "catalyst",     "cathedral",  "cauldron",    "cavalier",     "celestial", "censure",   "chameleon",
      "charisma",   "chasm",        "chassis",    "chateau",     "chisel",       "chronic",   "citadel",   "clarion",
      "clemency",   "cloister",     "coalesce",   "colossus",    "concave",      "conduit",   "confetti",  "conifer",
      "consortium", "contraband",   "corridor",   "cortex",      "courier",      "covalent",  "coyote",    "cranium",
      "crescendo",  "cryptic",      "curvature",  "cynic",       "daffodil",     "dalliance", "damask",    "dauntless",
      "debacle",    "deciduous",    "decipher",   "decompose",   "decree",       "defector",  "defiance",  "demagogue",
      "deluge",     "demeanor",     "derelict",   "desideratum", "detonate",     "dexterity", "diadem",    "digress",
      "domicile",   "doppelgänger", "dormant",    "dowager",     "dowry",        "dynamo",    "echelon",   "eclectic",
      "eclipse",    "edifice",      "effigy",     "egress",      "enclave",      "ensign",    "entourage", "ephemeral",
      "equinox",    "erratic",      "estuary",    "etymology",   "euphoria",     "evasive",   "exalt",     "exodus",
      "exorcist",   "facade",       "falcon",     "fathom",      "fervor",       "festoon",   "fissure",   "flannel",
      "flotilla",   "flux",         "foyer",      "franchise",   "frenzy",       "fulcrum",   "galaxy",    "galleon",
      "gamut",      "garrison",     "gazebo",     "gelatin",     "geyser",       "gnome",     "gossamer",  "gradient",
      "grotto",     "gumption",     "gyroscope"
    };
    {
      auto rec = fuzzy::rough_find(to_find, vec, 10);
      std::cout << "Ten closest matches for 'brier' were..." << std::endl;
      for ( const auto &n : rec ) {
        std::cout << "\"" << vec[n.index] << "\": " << n.res << std::endl;
      }
    }
    {
      std::cout << "Using rough finding" << std::endl;
      to_find = "exorc";
      auto rec = fuzzy::rough_find(to_find, vec, 10);
      std::cout << "Ten closest matches for 'exorc' were..." << std::endl;
      for ( const auto &n : rec ) {
        std::cout << "\"" << vec[n.index] << "\": " << n.res << std::endl;
      }
      // as you can see rough find is find but not too accurate
    }
    {
      std::cout << "Using precise finding" << std::endl;
      to_find = "exorc";
      auto rec = fuzzy::precise_find(to_find, vec, 10);
      std::cout << "Ten closest matches for 'exorc' were..." << std::endl;
      for ( const auto &n : rec ) {
        std::cout << "\"" << vec[n.index] << "\": " << n.res << std::endl;
      }
    }
  }

  return 0;
};
