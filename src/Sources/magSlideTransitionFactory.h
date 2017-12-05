//
// Created by Cristobal Mendoza on 12/3/17.
//

#ifndef MAGSLIDETRANSITIONFACTORY_H
#define MAGSLIDETRANSITIONFACTORY_H

#include "magSlide.h"
#include "magSlideTransition.h"

/**
 * Factory class to register and instantiate transitions.
 */
class magSlideTransitionFactory
{
public:
	static magSlideTransitionFactory* instance();

	std::shared_ptr<magSlideTransition> createTransition(string transitionName,
														 std::shared_ptr<magSlide> slide,
														 ofParameterGroup &group,
														 u_int64_t duration);
	template<typename T>
	void registerTransition(T transition)
	{
		if (transitionsMap.count(transition.getName()) == 0)
		{
			transitionsMap[transition.getName()] = [](){
				return std::make_shared<T>();
			};
		}
	}

protected:
	std::unordered_map<std::string, std::function<std::shared_ptr<magSlideTransition>()>> transitionsMap;
private:
	static magSlideTransitionFactory* _instance;
	magSlideTransitionFactory();
};

#endif //MAGSLIDETRANSITIONFACTORY_H
