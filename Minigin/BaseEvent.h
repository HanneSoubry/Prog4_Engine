#pragma once
namespace dae
{
	// Inherit from this to create new types of events
	class Event
	{
	public:
		virtual ~Event() = default;

		// add whatever data you need in the derived events
	};
}