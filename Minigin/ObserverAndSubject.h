#pragma once
#include "BaseEvent.h"
#include <vector>
#include "GameObject.h"

namespace dae
{
	class Observer
	{
	public:
		virtual ~Observer() = default;
		virtual void Notify(std::shared_ptr<Event> event) = 0;
	};

	class Subject
	{
	public:
		void AddObserver(Observer* observer)
		{
			m_pObservers.push_back(observer);
		}

		void RemoveObserver(Observer* observer)
		{
			for (int i{ 0 }; i < static_cast<int>(m_pObservers.size()); ++i)
			{
				if (m_pObservers[i] == observer)
				{
					m_pObservers.erase(std::remove(m_pObservers.begin(), m_pObservers.end(), m_pObservers[i]));
				}
			}
		}

	protected:
		void Notify(std::shared_ptr<Event> event)
		{
			for (Observer* observer : m_pObservers)
			{
				observer->Notify(event);
			}
		}

	private:
		std::vector<Observer*> m_pObservers{};
	};

}