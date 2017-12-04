//
// Created by Cristobal Mendoza on 12/3/17.
//

#include "magSlideTransitionFactory.h"

/*
 *
 *
 *
class Base {};

class DerivedA : public Base {};
class DerivedB : public Base {};
class DerivedC : public Base {};

Base* create(const std::string& type)
{
    static std::map<std::string, std::function<Base*()>> type_creator_map =
    {
        {"DerivedA", [](){return new DerivedA();}},
        {"DerivedB", [](){return new DerivedB();}},
        {"DerivedC", [](){return new DerivedC();}}
    };

    auto it = type_creator_map.find(type);
    if(it != type_creator_map.end())
    {
        return it->second();
    }

    return nullptr;
}
 */

magSlideTransitionFactory* magSlideTransitionFactory::_instance = 0;

magSlideTransitionFactory::magSlideTransitionFactory()
{
	magSlideTransition voidTransition;
	magFadeInTransition fadeIn;

	registerTransition<magSlideTransition>(voidTransition);
	registerTransition<magFadeInTransition>(fadeIn);
}

magSlideTransitionFactory* magSlideTransitionFactory::instance()
{
	if (_instance == 0)
	{
		_instance = new magSlideTransitionFactory();
	}

	return _instance;
}

std::shared_ptr<magSlideTransition>
magSlideTransitionFactory::createTransition(std::string transitionName, std::shared_ptr<magSlide> slide,
											ofParameterGroup &settings, u_int64_t duration)
{
	std::shared_ptr<magSlideTransition> transition;

	if (transitionsMap.count(transitionName) > 0)
	{
		transition = transitionsMap[transitionName]();
	}
	else
	{
		transition = transitionsMap[transition->getName()]();
	}

	transition->slide = slide;
	transition->duration = duration;
	transition->loadSettings(settings);
	return transition;
}
