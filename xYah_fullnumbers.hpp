#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <vector>

namespace FullNumber {

typedef size_t NumericValue;

enum class NumberClass_t : char {
    VOID,
    UNITY,
    TEN,
    TEN_BEFORE_TWENTY,
    HUNDRED,
    THOUSAND,
    MILLION
};

struct Transition_t {
    bool canErode;
    bool canDisable;
    NumberClass_t next;

    Transition_t(bool cEr, bool cDis, NumberClass_t clazz)
        : next(clazz)
        , canErode(cEr)
        , canDisable(cDis)
    {
    }

    Transition_t(NumberClass_t clazz)
        : next(clazz){};
};

struct FullNumber_t {
    size_t value;
    std::string fullDescription;
    NumberClass_t tier;

    FullNumber_t(size_t value, std::string&& fullDescription, NumberClass_t tierCarrier)
        : value(value)
        , fullDescription(fullDescription)
        , tier(tierCarrier)
    {
    }
};

void __BUILD_TRANSITIONS(std::map<NumberClass_t, std::map<NumberClass_t, Transition_t>>& transitions)
{
    auto& __VOID = transitions[NumberClass_t::VOID];
    auto& __UNITY = transitions[NumberClass_t::UNITY];
    auto& __TEN_BEFORE_TWENTY = transitions[NumberClass_t::TEN_BEFORE_TWENTY];
    auto& __TEN = transitions[NumberClass_t::TEN];
    auto& __HUNDRED = transitions[NumberClass_t::HUNDRED];

    __VOID.emplace(std::piecewise_construct, std::forward_as_tuple(NumberClass_t::UNITY), std::forward_as_tuple(NumberClass_t::UNITY));
    __VOID.emplace(std::piecewise_construct, std::forward_as_tuple(NumberClass_t::TEN_BEFORE_TWENTY), std::forward_as_tuple(NumberClass_t::TEN_BEFORE_TWENTY));
    __VOID.emplace(std::piecewise_construct, std::forward_as_tuple(NumberClass_t::TEN), std::forward_as_tuple(NumberClass_t::TEN));
    __VOID.emplace(std::piecewise_construct, std::forward_as_tuple(NumberClass_t::HUNDRED), std::forward_as_tuple(NumberClass_t::HUNDRED));
    __VOID.emplace(std::piecewise_construct, std::forward_as_tuple(NumberClass_t::THOUSAND), std::forward_as_tuple(NumberClass_t::THOUSAND));
    __VOID.emplace(std::piecewise_construct, std::forward_as_tuple(NumberClass_t::MILLION), std::forward_as_tuple(NumberClass_t::MILLION));

    __UNITY.emplace(std::piecewise_construct, std::forward_as_tuple(NumberClass_t::MILLION), std::forward_as_tuple(NumberClass_t::MILLION));
    __UNITY.emplace(std::piecewise_construct, std::forward_as_tuple(NumberClass_t::THOUSAND), std::forward_as_tuple(NumberClass_t::THOUSAND));

    __TEN_BEFORE_TWENTY.emplace(std::piecewise_construct, std::forward_as_tuple(NumberClass_t::MILLION), std::forward_as_tuple(NumberClass_t::MILLION));
    __TEN_BEFORE_TWENTY.emplace(std::piecewise_construct, std::forward_as_tuple(NumberClass_t::THOUSAND), std::forward_as_tuple(NumberClass_t::THOUSAND));

    __TEN.emplace(std::piecewise_construct, std::forward_as_tuple(NumberClass_t::MILLION), std::forward_as_tuple(NumberClass_t::MILLION));
    __TEN.emplace(std::piecewise_construct, std::forward_as_tuple(NumberClass_t::THOUSAND), std::forward_as_tuple(NumberClass_t::THOUSAND));
    __TEN.emplace(std::piecewise_construct, std::forward_as_tuple(NumberClass_t::UNITY), std::forward_as_tuple(false, true, NumberClass_t::TEN));

    __HUNDRED.emplace(std::piecewise_construct, std::forward_as_tuple(NumberClass_t::MILLION), std::forward_as_tuple(NumberClass_t::MILLION));
    __HUNDRED.emplace(std::piecewise_construct, std::forward_as_tuple(NumberClass_t::THOUSAND), std::forward_as_tuple(NumberClass_t::THOUSAND));
    __HUNDRED.emplace(std::piecewise_construct, std::forward_as_tuple(NumberClass_t::UNITY), std::forward_as_tuple(false, true, NumberClass_t::HUNDRED));
    __HUNDRED.emplace(std::piecewise_construct, std::forward_as_tuple(NumberClass_t::TEN_BEFORE_TWENTY), std::forward_as_tuple(false, true, NumberClass_t::HUNDRED));
    __HUNDRED.emplace(std::piecewise_construct, std::forward_as_tuple(NumberClass_t::TEN), std::forward_as_tuple(true, false, NumberClass_t::HUNDRED));
}

void __BUILD_FULLNUMBER_MAP(std::map<std::string, FullNumber_t>& numberMap)
{
    numberMap.emplace(std::piecewise_construct, std::forward_as_tuple("um"), std::forward_as_tuple(1, "um", NumberClass_t::UNITY));
    numberMap.emplace(std::piecewise_construct, std::forward_as_tuple("uma"), std::forward_as_tuple(1, "uma", NumberClass_t::UNITY));
    numberMap.emplace(std::piecewise_construct, std::forward_as_tuple("dois"), std::forward_as_tuple(2, "dois", NumberClass_t::UNITY));
    numberMap.emplace(std::piecewise_construct, std::forward_as_tuple("duas"), std::forward_as_tuple(2, "duas", NumberClass_t::UNITY));
    numberMap.emplace(std::piecewise_construct, std::forward_as_tuple("três"), std::forward_as_tuple(3, "três", NumberClass_t::UNITY));
    numberMap.emplace(std::piecewise_construct, std::forward_as_tuple("quatro"), std::forward_as_tuple(4, "quatro", NumberClass_t::UNITY));
    numberMap.emplace(std::piecewise_construct, std::forward_as_tuple("cinco"), std::forward_as_tuple(5, "cinco", NumberClass_t::UNITY));
    numberMap.emplace(std::piecewise_construct, std::forward_as_tuple("seis"), std::forward_as_tuple(6, "seis", NumberClass_t::UNITY));
    numberMap.emplace(std::piecewise_construct, std::forward_as_tuple("sete"), std::forward_as_tuple(7, "sete", NumberClass_t::UNITY));
    numberMap.emplace(std::piecewise_construct, std::forward_as_tuple("oito"), std::forward_as_tuple(8, "oito", NumberClass_t::UNITY));
    numberMap.emplace(std::piecewise_construct, std::forward_as_tuple("nove"), std::forward_as_tuple(9, "nove", NumberClass_t::UNITY));
    numberMap.emplace(std::piecewise_construct, std::forward_as_tuple("dez"), std::forward_as_tuple(10, "dez", NumberClass_t::TEN_BEFORE_TWENTY));
    numberMap.emplace(std::piecewise_construct, std::forward_as_tuple("onze"), std::forward_as_tuple(11, "onze", NumberClass_t::TEN_BEFORE_TWENTY));
    numberMap.emplace(std::piecewise_construct, std::forward_as_tuple("doze"), std::forward_as_tuple(12, "doze", NumberClass_t::TEN_BEFORE_TWENTY));
    numberMap.emplace(std::piecewise_construct, std::forward_as_tuple("treze"), std::forward_as_tuple(13, "treze", NumberClass_t::TEN_BEFORE_TWENTY));
    numberMap.emplace(std::piecewise_construct, std::forward_as_tuple("catorze"), std::forward_as_tuple(14, "catorze", NumberClass_t::TEN_BEFORE_TWENTY));
    numberMap.emplace(std::piecewise_construct, std::forward_as_tuple("quatorze"), std::forward_as_tuple(14, "quatorze", NumberClass_t::TEN_BEFORE_TWENTY));
    numberMap.emplace(std::piecewise_construct, std::forward_as_tuple("quinze"), std::forward_as_tuple(15, "quinze", NumberClass_t::TEN_BEFORE_TWENTY));
    numberMap.emplace(std::piecewise_construct, std::forward_as_tuple("dezesseis"), std::forward_as_tuple(16, "dezesseis", NumberClass_t::TEN_BEFORE_TWENTY));
    numberMap.emplace(std::piecewise_construct, std::forward_as_tuple("dezessete"), std::forward_as_tuple(17, "dezessete", NumberClass_t::TEN_BEFORE_TWENTY));
    numberMap.emplace(std::piecewise_construct, std::forward_as_tuple("dezoito"), std::forward_as_tuple(18, "dezoito", NumberClass_t::TEN_BEFORE_TWENTY));
    numberMap.emplace(std::piecewise_construct, std::forward_as_tuple("dezenove"), std::forward_as_tuple(19, "dezenove", NumberClass_t::TEN_BEFORE_TWENTY));
    numberMap.emplace(std::piecewise_construct, std::forward_as_tuple("vinte"), std::forward_as_tuple(20, "vinte", NumberClass_t::TEN));
    numberMap.emplace(std::piecewise_construct, std::forward_as_tuple("trinta"), std::forward_as_tuple(30, "trinta", NumberClass_t::TEN));
    numberMap.emplace(std::piecewise_construct, std::forward_as_tuple("quarenta"), std::forward_as_tuple(40, "quarenta", NumberClass_t::TEN));
    numberMap.emplace(std::piecewise_construct, std::forward_as_tuple("cinquenta"), std::forward_as_tuple(50, "cinquenta", NumberClass_t::TEN));
    numberMap.emplace(std::piecewise_construct, std::forward_as_tuple("sessenta"), std::forward_as_tuple(60, "sessenta", NumberClass_t::TEN));
    numberMap.emplace(std::piecewise_construct, std::forward_as_tuple("setenta"), std::forward_as_tuple(70, "setenta", NumberClass_t::TEN));
    numberMap.emplace(std::piecewise_construct, std::forward_as_tuple("oitenta"), std::forward_as_tuple(80, "oitenta", NumberClass_t::TEN));
    numberMap.emplace(std::piecewise_construct, std::forward_as_tuple("noventa"), std::forward_as_tuple(90, "noventa", NumberClass_t::TEN));
    numberMap.emplace(std::piecewise_construct, std::forward_as_tuple("cem"), std::forward_as_tuple(100, "cem", NumberClass_t::HUNDRED));
    numberMap.emplace(std::piecewise_construct, std::forward_as_tuple("cento"), std::forward_as_tuple(100, "cento", NumberClass_t::HUNDRED));
    numberMap.emplace(std::piecewise_construct, std::forward_as_tuple("duzentos"), std::forward_as_tuple(200, "duzentos", NumberClass_t::HUNDRED));
    numberMap.emplace(std::piecewise_construct, std::forward_as_tuple("duzentas"), std::forward_as_tuple(200, "duzentas", NumberClass_t::HUNDRED));
    numberMap.emplace(std::piecewise_construct, std::forward_as_tuple("trezentos"), std::forward_as_tuple(300, "trezentos", NumberClass_t::HUNDRED));
    numberMap.emplace(std::piecewise_construct, std::forward_as_tuple("trezentas"), std::forward_as_tuple(300, "trezentas", NumberClass_t::HUNDRED));
    numberMap.emplace(std::piecewise_construct, std::forward_as_tuple("quatrocentos"), std::forward_as_tuple(400, "quatrocentos", NumberClass_t::HUNDRED));
    numberMap.emplace(std::piecewise_construct, std::forward_as_tuple("quatrocentas"), std::forward_as_tuple(400, "quatrocentas", NumberClass_t::HUNDRED));
    numberMap.emplace(std::piecewise_construct, std::forward_as_tuple("quinhentos"), std::forward_as_tuple(500, "quinhentos", NumberClass_t::HUNDRED));
    numberMap.emplace(std::piecewise_construct, std::forward_as_tuple("quinhentas"), std::forward_as_tuple(500, "quinhentas", NumberClass_t::HUNDRED));
    numberMap.emplace(std::piecewise_construct, std::forward_as_tuple("seiscentos"), std::forward_as_tuple(600, "seiscentos", NumberClass_t::HUNDRED));
    numberMap.emplace(std::piecewise_construct, std::forward_as_tuple("seiscentas"), std::forward_as_tuple(600, "seiscentas", NumberClass_t::HUNDRED));
    numberMap.emplace(std::piecewise_construct, std::forward_as_tuple("setecentos"), std::forward_as_tuple(700, "setecentos", NumberClass_t::HUNDRED));
    numberMap.emplace(std::piecewise_construct, std::forward_as_tuple("setecentas"), std::forward_as_tuple(700, "setecentas", NumberClass_t::HUNDRED));
    numberMap.emplace(std::piecewise_construct, std::forward_as_tuple("oitocentos"), std::forward_as_tuple(800, "oitocentos", NumberClass_t::HUNDRED));
    numberMap.emplace(std::piecewise_construct, std::forward_as_tuple("oitocentas"), std::forward_as_tuple(800, "oitocentas", NumberClass_t::HUNDRED));
    numberMap.emplace(std::piecewise_construct, std::forward_as_tuple("novecentos"), std::forward_as_tuple(900, "novecentos", NumberClass_t::HUNDRED));
    numberMap.emplace(std::piecewise_construct, std::forward_as_tuple("novecentas"), std::forward_as_tuple(900, "novecentas", NumberClass_t::HUNDRED));
    numberMap.emplace(std::piecewise_construct, std::forward_as_tuple("mil"), std::forward_as_tuple(1000, "mil", NumberClass_t::THOUSAND));
    numberMap.emplace(std::piecewise_construct, std::forward_as_tuple("milhão"), std::forward_as_tuple(1000000, "milhão", NumberClass_t::MILLION));
    numberMap.emplace(std::piecewise_construct, std::forward_as_tuple("milhões"), std::forward_as_tuple(1000000, "milhões", NumberClass_t::MILLION));
}

void __BUILD_FINAL_TRANSITIONS(std::map<NumberClass_t, char>& finalTransitions)
{
    finalTransitions.emplace(NumberClass_t::MILLION, 1);
    finalTransitions.emplace(NumberClass_t::THOUSAND, 2);
}

struct TransitionCarrier_t {
    NumberClass_t currentClass = NumberClass_t::VOID;

    TransitionCarrier_t() = default;

    void restart()
    {
        currentClass = NumberClass_t::VOID;
        blocked = false;
        erodedClasses.clear();
    }

    bool transit(Transition_t& transition, NumberClass_t comesFrom)
    {
        if (erodedClasses.find(transition.next) != erodedClasses.end() || (blocked && currentClass == transition.next)) {
            return false;
        }

        if (currentClass == transition.next) {
            if (transition.canErode) {
                erodedClasses.insert(comesFrom);
            }

            if (transition.canDisable) {
                this->blocked = true;
            }
        } else {
            erodedClasses.clear();
            blocked = false;
        }

        this->currentClass = transition.next;

        return true;
    }

private:
    std::set<NumberClass_t> erodedClasses;
    bool blocked = false;
};

struct FullNumberParser {

    explicit FullNumberParser()
    {
        __BUILD_FULLNUMBER_MAP(this->numberMap);
        __BUILD_TRANSITIONS(this->transitions);
        __BUILD_FINAL_TRANSITIONS(this->finalTransitions);
    }

    NumericValue parse(std::string& in)
    {
        TransitionCarrier_t carrier;
        std::string buffer;
        std::stringstream stream(in);

        size_t totalValue = 0;
        size_t currentValue = 0;
        char lastFinalTransition = 0;

        while (std::getline(stream, buffer, ' ')) {
            if (buffer.size() >= 2) {
                auto mapResponse = numberMap.find(buffer);
                if (mapResponse != numberMap.end()) {

                    auto fullNumber = mapResponse->second;

                    auto ways = transitions.find(carrier.currentClass);

                    if (ways != transitions.end()) {

                        auto realWay = ways->second.find(fullNumber.tier);

                        if (realWay != ways->second.end()) {
                            auto transitionState = finalTransitions.find(realWay->second.next);
                            if (!carrier.transit(realWay->second, realWay->first)) {
                                throw "Eroded || Disabled way";
                            } else if (transitionState == finalTransitions.end()) {
                                currentValue += fullNumber.value;
                            } else if (transitionState->second > lastFinalTransition) {
                                if (currentValue == 0) {
                                    currentValue += fullNumber.value;
                                } else {
                                    currentValue *= fullNumber.value;
                                }
                                lastFinalTransition = transitionState->second;

                                totalValue += currentValue;
                                currentValue = 0;
                                carrier.restart();
                            } else {
                                throw "Impossible combination";
                            }
                        } else {
                            throw "Impossible way";
                        }

                    } else {
                        throw "Impossible Transition";
                    }

                } else {
                    throw "Not Found";
                }
            }
        }
        return totalValue + currentValue;
    }

    NumericValue parse(std::string&& in)
    {
        return parse(in);
    }

private:
    std::map<std::string, FullNumber_t> numberMap;
    std::map<NumberClass_t, std::map<NumberClass_t, Transition_t>> transitions;
    std::map<NumberClass_t, char> finalTransitions;
};
}
