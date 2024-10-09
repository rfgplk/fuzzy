

#include "../src/fuzzy.hpp"
#include <iostream>

#include <string>

int
main(void)
{
  std::string to_find = "carevn";
  std::vector<std::string> words = {
    "aardvark",     "abacus",         "abyss",       "acorn",         "adamant",      "adhesive",      "aeroplane",
    "algebra",      "allegro",        "allemand",    "aloe",          "alpaca",       "alsjeblieft",   "altitude",
    "altruismo",    "amaretto",       "amber",       "ambush",        "amicizia",     "amulet",        "anatomie",
    "ancora",       "andante",        "anomaly",     "antenna",       "anthem",       "antiquité",     "apex",
    "apogeo",       "apoplexie",      "arable",      "arcane",        "archipel",     "archway",       "argent",
    "argilla",      "aristocratie",   "aroma",       "arrividerci",   "arson",        "artifact",      "artisan",
    "asphalt",      "astuto",         "asylum",      "atlas",         "atleta",       "atom",          "attente",
    "attire",       "auburn",         "aurora",      "autocorrectie", "autumn",       "avalanche",     "avatar",
    "avversario",   "aviation",       "axiom",       "azote",         "azure",        "bachata",       "backlog",
    "ballerino",    "balustrade",     "bambino",     "bamboo",        "baritone",     "basilisk",      "bastion",
    "beacon",       "behemoth",       "bellwether",  "benchmark",     "berserk",      "bibliografía",  "bibliothèque",
    "binary",       "bitume",         "blizzard",    "boîte",         "bohemian",     "bomboniera",    "bonheur",
    "bonnet",       "bordeaux",       "borough",     "botany",        "boulangerie",  "bravado",       "briar",
    "brillante",    "brittle",        "broker",      "buccaneer",     "bulbo",        "bullion",       "bungalow",
    "bureaucracy",  "burlesque",      "burlap",      "buurt",         "butterfly",    "cabaret",       "cadenza",
    "café",         "calculus",       "calice",      "calypso",       "camouflage",   "canapé",        "candelabra",
    "canopy",       "capsize",        "caravan",     "carotte",       "cartridge",    "cascade",       "castello",
    "catalyst",     "cathédrale",     "cauldron",    "cavalier",      "celestial",    "censure",       "cerveza",
    "chameleon",    "charisma",       "château",     "chasm",         "chassis",      "chef",          "chisel",
    "chronic",      "citadel",        "clarion",     "clémence",      "cloister",     "coalesce",      "colosseo",
    "commando",     "concave",        "conduit",     "confetti",      "conifer",      "consortio",     "consortium",
    "contraband",   "corridor",       "corte",       "courier",       "covent",       "coyote",        "crescendo",
    "cryptic",      "curvature",      "cynic",       "cytologie",     "daffodil",     "dalliance",     "damask",
    "dama",         "danseur",        "dauntless",   "debacle",       "deciduous",    "decipher",      "décomposer",
    "decree",       "defiance",       "demagogue",   "déluge",        "demeanor",     "derelict",      "désiré",
    "détour",       "dexterity",      "diadem",      "digress",       "dirigeant",    "disordine",     "doppelgänger",
    "dormant",      "doudou",         "dowager",     "dynamisme",     "eau",          "eclectic",      "eclipse",
    "effervescent", "effigy",         "egress",      "einheit",       "elaborate",    "éléphant",      "ellipse",
    "ember",        "embrace",        "enclave",     "energie",       "ensemble",     "entrée",        "entourage",
    "éphemère",     "equinox",        "erratic",     "estuaire",      "étude",        "euphoria",      "evasive",
    "exalt",        "exodus",         "exorcist",    "extravagance",  "facade",       "falcon",        "fantôme",
    "fathom",       "ferme",          "fervor",      "festino",       "fissure",      "flotilla",      "fluctuation",
    "foyer",        "franchise",      "fresque",     "fulcrum",       "fureur",       "galaxy",        "galère",
    "galleon",      "gamme",          "gauche",      "gazebo",        "gemini",       "geyser",        "gladiateur",
    "gnome",        "gossamer",       "gourmet",     "gradient",      "grotte",       "guerilla",      "gumption",
    "gyroscope",    "habitat",        "haiku",       "hallucination", "hammock",      "harmonie",      "harpe",
    "havoc",        "héritage",       "hexagon",     "hibernation",   "highlander",   "hoopla",        "horizon",
    "hôtel",        "humilité",       "hypnose",     "idée",          "idylle",       "igloo",         "illusion",
    "immortel",     "impasse",        "imperatore",  "incantation",   "incognito",    "ineffable",     "infini",
    "ingénieur",    "inimitié",       "innocuo",     "interlude",     "intrépide",    "inverno",       "invictus",
    "ironie",       "isola",          "ivresse",     "jacuzzi",       "jalousie",     "jardin",        "jeune",
    "jovial",       "jubilation",     "jungle",      "jusqu'à",       "juxtapose",    "kaleidoscope",  "karma",
    "ketchup",      "kiosque",        "knight",      "labyrinthe",    "lacuna",       "lampadaire",    "lapis",
    "lassitude",    "latente",        "léger",       "léthargie",     "liberté",      "limousine",     "logique",
    "lueur",        "lumière",        "macabre",     "magnanimité",   "mainsail",     "majordome",     "mannequin",
    "marauder",     "marmalade",      "martien",     "mascarade",     "matador",      "mécanisme",     "méduse",
    "mélodie",      "mémoire",        "ménage",      "menthe",        "mesure",       "métaphore",     "metaphysique",
    "métier",       "miettes",        "migración",   "milieu",        "minuit",       "mirage",        "mise",
    "misère",       "mistral",        "mitologia",   "mobilière",     "modesto",      "molécule",      "momentum",
    "montagne",     "morose",         "mosaïque",    "motif",         "mousse",       "mystique",      "naissance",
    "narrateur",    "néant",          "neige",       "néophyte",      "nervure",      "nidification",  "nocturne",
    "nomenclature", "nozze",          "nuage",       "nuovo",         "obélisque",    "obscurité",     "océan",
    "octet",        "oiseau",         "ombrage",     "onde",          "ongle",        "opus",          "orgueil",
    "orée",         "ornithologie",   "oscillation", "ossature",      "ostinato",     "panorama",      "parabole",
    "paradiso",     "parallèle",      "parasol",     "pénombre",      "persuader",    "phare",         "phénix",
    "phénomène",    "phosphorescent", "piège",       "pirogue",       "pirouette",    "plaque",        "planète",
    "politesse",    "portée",         "portico",     "posture",       "pragmatique",  "précieux",      "prélude",
    "prisme",       "prologue",       "promenade",   "propagation",   "prophète",     "prospérité",    "protagoniste",
    "provenance",   "proximité",      "pseudonyme",  "purge",         "quasar",       "quatuor",       "quintessence",
    "quixotic",     "radieux",        "rafale",      "réalité",       "rébellion",    "recette",       "redemption",
    "relique",      "résilience",     "résistance",  "retouche",      "reverie",      "ricochet",      "rivière",
    "rhapsodie",    "rituel",         "rivage",      "rocaille",      "rôle",         "romarin",       "ronron",
    "roseau",       "safari",         "sagittaire",  "salsa",         "sanglier",     "sarcasmo",      "satire",
    "sculpture",    "séance",         "sépulcre",    "séraphin",      "serenità",     "serpentine",    "sérénade",
    "sérieux",      "signe",          "sirène",      "sismique",      "solennel",     "solstice",      "sphère",
    "spirale",      "spore",          "stalactite",  "statuette",     "stratosphère", "strudel",       "subito",
    "succinct",     "supernova",      "syllogisme",  "symbole",       "symphonie",    "synchronicité", "tabernacle",
    "talisman",     "tapisserie",     "tempête",     "tenor",         "ténacité",     "terrazzo",      "thème",
    "timbre",       "tissage",        "toison",      "tournoi",       "tremble",      "trompe",        "troisième",
    "tulipe",       "turbulence",     "ultimatum",   "ultra",         "univers",      "uruguayen",     "usanza",
    "utile",        "vacanza",        "valeur",      "valise",        "vannerie",     "vautour",       "vedette",
    "veille",       "velours",        "ventilateur", "verdict",       "vibrato",      "violette",      "vitesse",
    "vocation",     "voile",          "volant",      "volcan",        "vortex",       "vraiment",      "waltz",
    "wanderlust",   "whisky",         "xenon",       "xylophone",     "yacht",        "yeux",          "zeste",
    "zodiaco",      "zoologie",       "zucchero"
  };     // 521 random words
  auto f = fuzzy::fuzzy_find(to_find, words, 20);     // top 20 hits
  std::cout << "Twenty closest matches for '" << to_find << "' were..." << std::endl;
  for(size_t i = 0; i < f.results.size(); i++)  
    std::cout << "\"" << f.strings[f.results[i].index] << "\": " << f.results[i].res << std::endl;
  std::string to_confirm = "whisky";
  std::cout << "'whisky' appears in the list: " << fuzzy::fuzzy_exists(to_confirm, words) << std::endl;;
  return 0;
};
