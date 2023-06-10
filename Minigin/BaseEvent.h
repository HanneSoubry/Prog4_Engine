#pragma once
namespace dae
{
	// Inherit from this to create new types of events
	class Event
	{
	public:
		explicit Event() = default;
		virtual ~Event() = default;

		Event(const Event& other) = delete;
		Event(Event&& other) = delete;
		Event& operator=(const Event& other) = delete;
		Event& operator=(Event&& other) = delete;

		// add whatever data you need in the derived events
	};
}