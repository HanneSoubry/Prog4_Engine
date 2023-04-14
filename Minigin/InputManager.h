#pragma once
#include "Singleton.h"
#include <vector>
#include "XBoxController.h"
#include <map>
#include <memory>
#include "Command.h"
#include <unordered_set>

namespace dae
{
	class InputManager final : public Singleton<InputManager>
	{
		// Can handle up to 4 controllers and a keyboard

	public:
		enum class InputAction
		{
			Pressed,
			Down,
			Up,
			Analog1DAxis,	// controller triggers
			Analog2DAxis,	// controller stick value
			Digital2DAxis	// 4 button value : Left, Right, Up, Down
		};

		struct InputKey
		{
			int id;
			std::vector<unsigned int> buttons;
			InputAction action;

			// required to emplace something in a map
			bool operator<(const InputKey& other) const { return other.id < id; }
		};

		bool ProcessInput();

		void BindCommand(const std::vector<unsigned int>& buttons, InputAction action, std::unique_ptr<Command> pCommand, int id = -1);  // use keyboard by default
		void BindCommand(unsigned int button, InputAction action, std::unique_ptr<Command> pCommand, int id = -1);

		// command may ask the value
		// processInput will set these and then fire the command
		float Get1DAxisValue() const { return m_1DAxisValue; }
		const glm::vec2& Get2DAxisValue() const { return m_2DAxisValue; }

	private:
		std::vector<std::unique_ptr<XBoxController>> m_pControllers{};

		// using multimap to allow multiple commands on the same key
		std::multimap<InputKey, std::unique_ptr<Command>> m_pCommands{};

		float m_1DAxisValue{};
		glm::vec2 m_2DAxisValue{};

		// using set to avoid duplicates, does not need to be ordered
		std::unordered_set<unsigned int> m_KeysUpThisFrame{};
		std::unordered_set<unsigned int> m_KeysDownThisFrame{};
		std::unordered_set<unsigned int> m_KeysPressed{};
	};

}
