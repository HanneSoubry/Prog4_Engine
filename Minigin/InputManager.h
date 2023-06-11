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
			Digital1DAxis,	// 2 button value : Left, Right
			Digital2DAxis	// 4 button value : Left, Right, Up, Down
		};

		struct InputKey
		{
			int inputId;
			int controllerId;
			std::vector<unsigned int> buttons;
			InputAction action;

			// required to emplace something in a map
			bool operator<(const InputKey& other) const { return other.inputId < inputId; }
		};

		bool ProcessInput();

		// returns unique inputId, needed to remove the command
		int BindCommand(const std::vector<unsigned int>& buttons, InputAction action, std::unique_ptr<BaseCommand> pCommand, int id = -1);  // use keyboard by default
		int BindCommand(const std::vector<unsigned int>& buttons, InputAction action, std::unique_ptr<Command<float>> pCommand, int id = -1);  // use keyboard by default
		int BindCommand(const std::vector<unsigned int>& buttons, InputAction action, std::unique_ptr<Command<glm::vec2>> pCommand, int id = -1);  // use keyboard by default
		int BindCommand(unsigned int button, InputAction action, std::unique_ptr<BaseCommand> pCommand, int id = -1);
		int BindCommand(unsigned int button, InputAction action, std::unique_ptr<Command<float>> pCommand, int id = -1);
		int BindCommand(unsigned int button, InputAction action, std::unique_ptr<Command<glm::vec2>> pCommand, int id = -1);

		void RemoveCommand(int inputId);

	private:
		std::vector<std::unique_ptr<XBoxController>> m_pControllers{};

		// using multimap to allow multiple commands on the same key
		bool GetInputKey(InputKey& outKey, const std::vector<unsigned int>& buttons, InputAction action, int id = -1);
		std::multimap<InputKey, std::unique_ptr<BaseCommand>> m_pBaseCommands{};
		std::multimap<InputKey, std::unique_ptr<Command<float>>> m_p1DValueCommands{};
		std::multimap<InputKey, std::unique_ptr<Command<glm::vec2>>> m_p2DValueCommands{};

		// using set to avoid duplicates, does not need to be ordered
		std::unordered_set<unsigned int> m_KeysUpThisFrame{};
		std::unordered_set<unsigned int> m_KeysDownThisFrame{};
		const Uint8* m_KeysPressed{};

		int m_MaxInputKeyId{-1};
	};

}
