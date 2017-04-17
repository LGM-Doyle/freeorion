#include "../universe/Enums.h"
#include "../Empire/Diplomacy.h"
#include "../util/MultiplayerCommon.h"

#include <boost/python.hpp>

namespace FreeOrionPython {
    using boost::python::enum_;
    void WrapGameStateEnums() {
        enum_<StarType>("starType")
            .value("blue",      STAR_BLUE)
            .value("white",     STAR_WHITE)
            .value("yellow",    STAR_YELLOW)
            .value("orange",    STAR_ORANGE)
            .value("red",       STAR_RED)
            .value("neutron",   STAR_NEUTRON)
            .value("blackHole", STAR_BLACK)
            .value("noStar",    STAR_NONE)
            .value("unknown",   INVALID_STAR_TYPE)
        ;
        enum_<Visibility>("visibility")
            .value("invalid",   INVALID_VISIBILITY)
            .value("none",      VIS_NO_VISIBILITY)
            .value("basic",     VIS_BASIC_VISIBILITY)
            .value("partial",   VIS_PARTIAL_VISIBILITY)
            .value("full",      VIS_FULL_VISIBILITY)
        ;
        enum_<PlanetSize>("planetSize")
            .value("tiny",      SZ_TINY)
            .value("small",     SZ_SMALL)
            .value("medium",    SZ_MEDIUM)
            .value("large",     SZ_LARGE)
            .value("huge",      SZ_HUGE)
            .value("asteroids", SZ_ASTEROIDS)
            .value("gasGiant",  SZ_GASGIANT)
            .value("noWorld",   SZ_NOWORLD)
            .value("unknown",   INVALID_PLANET_SIZE)
        ;
        enum_<PlanetType>("planetType")
            .value("swamp",     PT_SWAMP)
            .value("radiated",  PT_RADIATED)
            .value("toxic",     PT_TOXIC)
            .value("inferno",   PT_INFERNO)
            .value("barren",    PT_BARREN)
            .value("tundra",    PT_TUNDRA)
            .value("desert",    PT_DESERT)
            .value("terran",    PT_TERRAN)
            .value("ocean",     PT_OCEAN)
            .value("asteroids", PT_ASTEROIDS)
            .value("gasGiant",  PT_GASGIANT)
            .value("unknown",   INVALID_PLANET_TYPE)
        ;
        enum_<PlanetEnvironment>("planetEnvironment")
            .value("uninhabitable", PE_UNINHABITABLE)
            .value("hostile",       PE_HOSTILE)
            .value("poor",          PE_POOR)
            .value("adequate",      PE_ADEQUATE)
            .value("good",          PE_GOOD)
        ;
        enum_<TechStatus>("techStatus")
            .value("unresearchable",    TS_UNRESEARCHABLE)
            .value("partiallyUnlocked", TS_HAS_RESEARCHED_PREREQ)
            .value("researchable",      TS_RESEARCHABLE)
            .value("complete",          TS_COMPLETE)
        ;
        enum_<BuildType>("buildType")
            .value("building",          BT_BUILDING)
            .value("ship",              BT_SHIP)
        ;
        enum_<ResourceType>("resourceType")
            .value("industry",      RE_INDUSTRY)
            .value("trade",         RE_TRADE)
            .value("research",      RE_RESEARCH)
            .value("stockpile",     RE_STOCKPILE)
        ;
        enum_<MeterType>("meterType")
            .value("targetPopulation",  METER_TARGET_POPULATION)
            .value("targetIndustry",    METER_TARGET_INDUSTRY)
            .value("targetResearch",    METER_TARGET_RESEARCH)
            .value("targetTrade",       METER_TARGET_TRADE)
            .value("targetConstruction",METER_TARGET_CONSTRUCTION)
            .value("targetHappiness",   METER_TARGET_HAPPINESS)

            .value("maxDamage",         METER_MAX_CAPACITY)
            .value("maxCapacity",       METER_MAX_CAPACITY)
            .value("maxSecondaryStat",  METER_MAX_SECONDARY_STAT)
            .value("maxNoisiness",      METER_MAX_TERTIARY_STAT)

            .value("maxFuel",           METER_MAX_FUEL)
            .value("maxShield",         METER_MAX_SHIELD)
            .value("maxStructure",      METER_MAX_STRUCTURE)
            .value("maxDefense",        METER_MAX_DEFENSE)
            .value("maxSupply",         METER_MAX_SUPPLY)
            .value("maxStockpile",      METER_MAX_STOCKPILE)
            .value("maxTroops",         METER_MAX_TROOPS)

            .value("population",        METER_POPULATION)
            .value("industry",          METER_INDUSTRY)
            .value("research",          METER_RESEARCH)
            .value("trade",             METER_TRADE)
            .value("construction",      METER_CONSTRUCTION)
            .value("happiness",         METER_HAPPINESS)

            .value("damage",            METER_CAPACITY)
            .value("capacity",          METER_CAPACITY)
            .value("secondaryStat",     METER_SECONDARY_STAT)
            .value("noisiness",         METER_TERTIARY_STAT)

            .value("fuel",              METER_FUEL)
            .value("shield",            METER_SHIELD)
            .value("structure",         METER_STRUCTURE)
            .value("defense",           METER_DEFENSE)
            .value("supply",            METER_SUPPLY)
            .value("stockpile",         METER_STOCKPILE)
            .value("troops",            METER_TROOPS)

            .value("rebels",            METER_REBEL_TROOPS)
            .value("size",              METER_SIZE)
            .value("stealth",           METER_STEALTH)
            .value("detection",         METER_DETECTION)
            .value("battleDetection",   METER_BATTLE_DETECTION)
            .value("speed",             METER_SPEED)
        ;
        enum_<DiplomaticStatus>("diplomaticStatus")
            .value("war",               DIPLO_WAR)
            .value("peace",             DIPLO_PEACE)
            .value("allied",            DIPLO_ALLIED)
        ;
        enum_<DiplomaticMessage::DiplomaticMessageType>("diplomaticMessageType")
            .value("noMessage",             DiplomaticMessage::INVALID_DIPLOMATIC_MESSAGE_TYPE)
            .value("warDeclaration",        DiplomaticMessage::WAR_DECLARATION)
            .value("peaceProposal",         DiplomaticMessage::PEACE_PROPOSAL)
            .value("acceptPeaceProposal",   DiplomaticMessage::ACCEPT_PEACE_PROPOSAL)
            .value("alliesProposal",        DiplomaticMessage::ALLIES_PROPOSAL)
            .value("acceptAlliesProposal",  DiplomaticMessage::ACCEPT_ALLIES_PROPOSAL)
            .value("endAllies",             DiplomaticMessage::END_ALLIANCE_DECLARATION)
            .value("cancelProposal",        DiplomaticMessage::CANCEL_PROPOSAL)
            .value("rejectProposal",        DiplomaticMessage::REJECT_PROPOSAL)
        ;
        enum_<CaptureResult>("captureResult")
            .value("capture",       CR_CAPTURE)
            .value("destroy",       CR_DESTROY)
            .value("retain",        CR_RETAIN)
        ;
        enum_<EffectsCauseType>("effectsCauseType")
            .value("invalid",       INVALID_EFFECTS_GROUP_CAUSE_TYPE)
            .value("unknown",       ECT_UNKNOWN_CAUSE)
            .value("inherent",      ECT_INHERENT)
            .value("tech",          ECT_TECH)
            .value("building",      ECT_BUILDING)
            .value("field",         ECT_FIELD)
            .value("special",       ECT_SPECIAL)
            .value("species",       ECT_SPECIES)
            .value("shipPart",      ECT_SHIP_PART)
            .value("shipHull",      ECT_SHIP_HULL)
        ;
        enum_<ShipSlotType>("shipSlotType")
            .value("external",      SL_EXTERNAL)
            .value("internal",      SL_INTERNAL)
            .value("core",          SL_CORE)
        ;
        enum_<ShipPartClass>("shipPartClass")
            .value("shortRange",        PC_DIRECT_WEAPON)
            .value("fighterBay",        PC_FIGHTER_BAY)
            .value("fighterHangar",     PC_FIGHTER_HANGAR)
            .value("shields",           PC_SHIELD)
            .value("armour",            PC_ARMOUR)
            .value("troops",            PC_TROOPS)
            .value("detection",         PC_DETECTION)
            .value("stealth",           PC_STEALTH)
            .value("fuel",              PC_FUEL)
            .value("colony",            PC_COLONY)
            .value("speed",             PC_SPEED)
            .value("general",           PC_GENERAL)
            .value("bombard",           PC_BOMBARD)
            .value("industry",          PC_INDUSTRY)
            .value("research",          PC_RESEARCH)
            .value("trade",             PC_TRADE)
            .value("productionLocation",PC_PRODUCTION_LOCATION)
            .value("battleScanner",     PC_BATTLE_SCANNER)
        ;
        enum_<UnlockableItemType>("unlockableItemType")
            .value("invalid",       INVALID_UNLOCKABLE_ITEM_TYPE)
            .value("building",      UIT_BUILDING)
            .value("shipPart",      UIT_SHIP_PART)
            .value("shipHull",      UIT_SHIP_HULL)
            .value("shipDesign",    UIT_SHIP_DESIGN)
            .value("tech",          UIT_TECH)
        ;
        enum_<Aggression>("aggression")
            .value("invalid",       INVALID_AGGRESSION)
            .value("beginner",      BEGINNER)
            .value("turtle",        TURTLE)
            .value("cautious",      CAUTIOUS)
            .value("typical",       TYPICAL)
            .value("aggressive",    AGGRESSIVE)
            .value("maniacal",      MANIACAL)
        ;
        enum_<GalaxySetupOption>("galaxySetupOption")
            .value("invalid",       INVALID_GALAXY_SETUP_OPTION)
            .value("none",          GALAXY_SETUP_NONE)
            .value("low",           GALAXY_SETUP_LOW)
            .value("medium",        GALAXY_SETUP_MEDIUM)
            .value("high",          GALAXY_SETUP_HIGH)
            .value("random",        GALAXY_SETUP_RANDOM)
        ;
        enum_<Shape>("galaxyShape")
            .value("invalid",       INVALID_SHAPE)
            .value("spiral2",       SPIRAL_2)
            .value("spiral3",       SPIRAL_3)
            .value("spiral4",       SPIRAL_4)
            .value("cluster",       CLUSTER)
            .value("elliptical",    ELLIPTICAL)
            .value("disc",          DISC)
            .value("box",           BOX)
            .value("irregular",     IRREGULAR)
            .value("ring",          RING)
            .value("random",        RANDOM)
        ;
        enum_<GameRules::RuleType>("ruleType")
            .value("invalid",       GameRules::INVALID_RULE_TYPE)
            .value("toggle",        GameRules::TOGGLE)
            .value("int",           GameRules::INT)
            .value("double",        GameRules::DOUBLE)
            .value("string",        GameRules::STRING)
        ;
        enum_<Networking::RoleType>("roleType")
            .value("host",                Networking::ROLE_HOST)
            .value("clientTypeModerator", Networking::ROLE_CLIENT_TYPE_MODERATOR)
            .value("clientTypePlayer",    Networking::ROLE_CLIENT_TYPE_PLAYER)
            .value("clientTypeObserver",  Networking::ROLE_CLIENT_TYPE_OBSERVER)
            .value("galaxySetup",         Networking::ROLE_GALAXY_SETUP)
        ;
    }
}
