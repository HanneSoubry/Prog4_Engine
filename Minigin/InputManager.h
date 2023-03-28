#pragma once
#include "Singleton.h"
#include <vector>
#include "XBoxController.h"
#include <map>
#include <memory>
#include "Command.h"

namespace dae
{
	class InputManager final : public Singleton<InputManager>
	{
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

		struct ControllerKey
		{
			int controllerIndex;
			std::vector<unsigned int> buttons;
			InputAction action;

			// required to emplace something in a map
			bool operator<(const ControllerKey& other) const { return other.controllerIndex < controllerIndex; }
		};

		bool ProcessInput();

		void BindCommand(const std::vector<unsigned int>& buttons, InputAction action, std::unique_ptr<Command> pCommand, int id = 0);
		void BindCommand(unsigned int button, InputAction action, std::unique_ptr<Command> pCommand, int id = 0);

		// command may ask the value
		// processInput will set these and then fire the command
		float Get1DAxisValue() const { return m_1DAxisValue; }
		const glm::vec2& Get2DAxisValue() const { return m_2DAxisValue; }

	private:
		std::vector<std::unique_ptr<XBoxController>> m_pControllers{};
		std::multimap<ControllerKey, std::unique_ptr<Command>> m_pCommands{};

		float m_1DAxisValue{};
		glm::vec2 m_2DAxisValue{};
	};

}
