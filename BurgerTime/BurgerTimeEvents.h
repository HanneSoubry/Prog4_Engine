#pragma once
#include "BaseEvent.h"

namespace dae
{
	class EventDamaged : public Event
	{
	public:
		virtual ~EventDamaged() = default;

		EventDamaged(int damage)
			: amount{damage}
		{ };

		// data (initialize at creation, only read needed for observer)
		const int amount;
	};

	class EventScoreChanged : public Event
	{
	public:
		virtual ~EventScoreChanged() = default;

		EventScoreChanged(int score, bool scoreSet = false)
			: amount{ score }, isSet{ scoreSet }
		{ };

		// data
		const int amount;
		const bool isSet;
	};
}