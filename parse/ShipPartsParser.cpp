#define PHOENIX_LIMIT 11
#define BOOST_RESULT_OF_NUM_ARGS PHOENIX_LIMIT

#include "Parse.h"

#include "ParseImpl.h"
#include "EnumParser.h"
#include "ValueRefParser.h"
#include "ConditionParserImpl.h"
#include "CommonParamsParser.h"

#include "../universe/ShipDesign.h"
#include "../universe/Condition.h"
#include "../universe/ValueRef.h"

#include <tuple>
#include <boost/spirit/include/phoenix.hpp>
//TODO: replace with std::make_unique when transitioning to C++14
#include <boost/smart_ptr/make_unique.hpp>

#define DEBUG_PARSERS 0

#if DEBUG_PARSERS
namespace std {
    inline ostream& operator<<(ostream& os, const std::vector<ShipSlotType>&) { return os; }
    inline ostream& operator<<(ostream& os, const parse::effects_group_payload&) { return os; }
    inline ostream& operator<<(ostream& os, const std::map<std::string, std::unique_ptr<PartType>>&) { return os; }
    inline ostream& operator<<(ostream& os, const std::pair<const std::string, std::unique_ptr<PartType>>&) { return os; }
}
#endif

namespace {
    const boost::phoenix::function<parse::detail::is_unique> is_unique_;

    struct Stats {
        Stats() :
            stat1(0.0), stat2(0.0), stat3(0.0)
        {}
        Stats(boost::optional<double> stat1_,
                    boost::optional<double> stat2_,
                    boost::optional<double> stat3_) :
            stat1(stat1_), stat2(stat2_), stat3(stat3_)
        {}
        boost::optional<double> stat1 = boost::optional<double>(0.0);
        boost::optional<double> stat2 = boost::optional<double>(0.0);
        boost::optional<double> stat3 = boost::optional<double>(0.0);
    };

    void insert_parttype(std::map<std::string, std::unique_ptr<PartType>>& part_types,
                         ShipPartClass part_class,
                         const Stats& stats,
                         const parse::detail::MovableEnvelope<CommonParams>& common_params,
                         const MoreCommonParams& more_common_params,
                         boost::optional<std::vector<ShipSlotType>> mountable_slot_types,
                         const std::string& icon,
                         bool no_default_capacity_effect,
                         bool& pass)
    {
        auto part_type = boost::make_unique<PartType>(
            part_class,
            (stats.stat1 ? *(stats.stat1) : 0.0),
            (stats.stat2 ? *(stats.stat2) : 1.0),
            (stats.stat3 ? *(stats.stat3) : 1.0),
            *common_params.OpenEnvelope(pass), more_common_params,
            (mountable_slot_types ? *mountable_slot_types : std::vector<ShipSlotType>()),
            icon,
            !no_default_capacity_effect);

        part_types.insert(std::make_pair(part_type->Name(), std::move(part_type)));
    }

    BOOST_PHOENIX_ADAPT_FUNCTION(void, insert_parttype_, insert_parttype, 9)

    using start_rule_payload = std::map<std::string, std::unique_ptr<PartType>>;
    using start_rule_signature = void(start_rule_payload&);

    struct grammar : public parse::detail::grammar<start_rule_signature> {
        grammar(const parse::lexer& tok, const std::string& filename,
                const parse::text_iterator& first, const parse::text_iterator& last) :
            grammar::base_type(start),
            condition_parser(tok, label),
            string_grammar(tok, label, condition_parser),
            tags_parser(tok, label),
            common_rules(tok, label, condition_parser, string_grammar, tags_parser),
            ship_slot_type_enum(tok),
            ship_part_class_enum(tok),
            double_rule(tok),
            one_or_more_slots(ship_slot_type_enum)
        {
            namespace phoenix = boost::phoenix;
            namespace qi = boost::spirit::qi;

            using phoenix::construct;

            qi::_1_type _1;
            qi::_2_type _2;
            qi::_3_type _3;
            qi::_4_type _4;
            qi::_5_type _5;
            qi::_6_type _6;
            qi::_7_type _7;
            qi::_8_type _8;
            qi::_pass_type _pass;
            qi::_val_type _val;
            qi::_r1_type _r1;
            qi::matches_type matches_;

            stats
                = (
                  -(  (label(tok.Capacity_)  > double_rule)
                   | (label(tok.Damage_)    > double_rule)
                   )
                > -(  (label(tok.Damage_)    > double_rule )   // damage is secondary for fighters
                   | (label(tok.Shots_)     > double_rule )   // shots is secondary for direct fire weapons
                   )
                > -(  (label(tok.Noisiness_)> double_rule )   // noisiness for weapons / fighter bays
                   )
                ) [ _val = construct<Stats>(_1, _2, _3) ];

            part_type
                = ( tok.Part_
                >   common_rules.more_common
                >   label(tok.Class_)       > ship_part_class_enum
                >  stats
                > matches_[tok.NoDefaultCapacityEffect_]
                > -(label(tok.MountableSlotTypes_) > one_or_more_slots)
                >   common_rules.common
                >   label(tok.Icon_)        > tok.string 
                  ) [ _pass = is_unique_(_r1, _1, phoenix::bind(&MoreCommonParams::name, _2)),
                      insert_parttype_(_r1, _3, _4, _7, _2, _6, _8, _5, _pass) ]
                ;

            start
                =   +part_type(_r1)
                ;

            part_type.name("Part");

#if DEBUG_PARSERS
            debug(part_type);
#endif

            qi::on_error<qi::fail>(start, parse::report_error(filename, first, last, _1, _2, _3, _4));
        }

        using  stats_rule = parse::detail::rule<Stats ()>;
        using  part_type_rule = parse::detail::rule<void (start_rule_payload&)>;

        using start_rule = parse::detail::rule<start_rule_signature>;

        parse::detail::Labeller                                                  label;
        const parse::conditions_parser_grammar                                   condition_parser;
        const parse::string_parser_grammar                                       string_grammar;
        parse::detail::tags_grammar                                              tags_parser;
        parse::detail::common_params_rules                                       common_rules;
        parse::ship_slot_enum_grammar                                            ship_slot_type_enum;
        parse::ship_part_class_enum_grammar                                      ship_part_class_enum;
        parse::detail::double_grammar                                            double_rule;
        parse::detail::single_or_bracketed_repeat<parse::ship_slot_enum_grammar> one_or_more_slots;
        part_type_rule                                                           part_type;
        stats_rule                                                               stats;;
        start_rule                                                               start;
    };

}

namespace parse {
    start_rule_payload ship_parts(const boost::filesystem::path& path) {
        const lexer lexer;
        start_rule_payload parts;

        for (const auto& file : ListScripts(path)) {
            /*auto success =*/ detail::parse_file<grammar, start_rule_payload>(lexer, file, parts);
        }

        return parts;
    }
}
