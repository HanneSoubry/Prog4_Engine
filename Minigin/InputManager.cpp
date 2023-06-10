#include <SDL.h>
#include "InputManager.h"
#include <backends/imgui_impl_sdl2.h>

bool dae::InputManager::ProcessInput()
{
	m_KeysDownThisFrame.clear();
	m_KeysUpThisFrame.clear();
	m_KeysPressed = SDL_GetKeyboardState(NULL);
	
	// Keyboard events
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			return false;
		}
		if (e.type == SDL_KEYDOWN) {
			m_KeysDownThisFrame.emplace(e.key.keysym.scancode);
		}
		if (e.type == SDL_KEYUP) {
			m_KeysUpThisFrame.emplace(e.key.keysym.scancode);
		}
		if (e.type == SDL_MOUSEBUTTONDOWN) {
			m_KeysDownThisFrame.emplace(e.key.keysym.scancode);
		}
		if (e.type == SDL_MOUSEBUTTONUP) {
			m_KeysUpThisFrame.emplace(e.key.keysym.scancode);
		}

		//process event for IMGUI
		ImGui_ImplSDL2_ProcessEvent(&e);
	}
	
	// Update controllers
	for (const auto& controller : m_pControllers)
	{
		controller->Update();
	}

	// Check commands
	for (const auto& command : m_pBaseCommands)
	{
		bool shouldExecute{ false };

		if (command.first.id == -1) // using keyboard
		{
			switch (command.first.action)
			{
			case InputAction::Pressed:
				shouldExecute = (m_KeysPressed[command.first.buttons[0]] == 1);
				break;
			case InputAction::Down:
				shouldExecute = m_KeysDownThisFrame.contains(command.first.buttons[0]);
				break;

			case InputAction::Up:
				shouldExecute = m_KeysUpThisFrame.contains(command.first.buttons[0]);
				break;
			}
		}
		else // using controller
		{
			switch (command.first.action)
			{
			case InputAction::Pressed:
				shouldExecute = m_pControllers[command.first.id]->IsPressed(command.first.buttons[0]);
				break;

			case InputAction::Down:
				shouldExecute = m_pControllers[command.first.id]->IsDown(command.first.buttons[0]);
				break;

			case InputAction::Up:
				shouldExecute = m_pControllers[command.first.id]->IsUp(command.first.buttons[0]);
				break;
			}
		}
		
		if (shouldExecute)
		{
			command.second->Execute();
		}
	}

	for (const auto& command : m_p1DValueCommands)
	{
		bool shouldExecute{ false };
		float axisValue{ 0 };

		if (command.first.id == -1) // using keyboard
		{
			switch (command.first.action)
			{
			case InputAction::Digital1DAxis:
				if (m_KeysPressed[command.first.buttons[0]] == 1) // left pressed
				{
					axisValue -= 1;
				}
				if (m_KeysPressed[command.first.buttons[1]] == 1) // right pressed
				{
					axisValue += 1;
				}

				shouldExecute = (axisValue != 0);	// should execute if not 0
				break;
			}
		}
		else // using controller
		{
			switch (command.first.action)
			{
			case InputAction::Analog1DAxis:
				axisValue = m_pControllers[command.first.id]->GetAxis(command.first.buttons[0]);
				shouldExecute = (axisValue != 0);	// should execute if not 0
				break;

			case InputAction::Digital1DAxis:
				if (m_pControllers[command.first.id]->IsPressed(command.first.buttons[0])) // left pressed
				{
					axisValue -= 1;
				}
				if (m_pControllers[command.first.id]->IsPressed(command.first.buttons[1])) // right pressed
				{
					axisValue += 1;
				}

				shouldExecute = (axisValue != 0);	// should execute if any input on x, or y, or both
				break;
			}
		}

		if (shouldExecute)
		{
			command.second->Execute(axisValue);
		}
	}

	for (const auto& command : m_p2DValueCommands)
	{
		bool shouldExecute{ false };
		glm::vec2 axisValue{0, 0};

		if (command.first.id == -1) // using keyboard
		{
			switch (command.first.action)
			{
			case InputAction::Digital2DAxis:
				if (m_KeysPressed[command.first.buttons[0]] == 1) // left pressed
				{
					axisValue.x -= 1;
				}
				if (m_KeysPressed[command.first.buttons[1]] == 1) // right pressed
				{
					axisValue.x += 1;
				}
				if (m_KeysPressed[command.first.buttons[2]] == 1) // up pressed
				{
					axisValue.y += 1;
				}
				if (m_KeysPressed[command.first.buttons[3]] == 1) // down pressed
				{
					axisValue.y -= 1;
				}

				shouldExecute = (axisValue.x != 0 || axisValue.y != 0);	// should execute if any input on x, or y, or both
				break;
				// case analog action: does not exist on keyboard
			}
		}
		else // using controller
		{
			switch (command.first.action)
			{
			case InputAction::Analog2DAxis:
				axisValue = m_pControllers[command.first.id]->Get2DAxis(command.first.buttons[0]);
				shouldExecute = (axisValue.x != 0 || axisValue.y != 0);	// should execute if any input on x, or y, or both
				break;

			case InputAction::Digital2DAxis:
				if (m_pControllers[command.first.id]->IsPressed(command.first.buttons[0])) // left pressed
				{
					axisValue.x -= 1;
				}
				if (m_pControllers[command.first.id]->IsPressed(command.first.buttons[1])) // right pressed
				{
					axisValue.x += 1;
				}
				if (m_pControllers[command.first.id]->IsPressed(command.first.buttons[2])) // up pressed
				{
					axisValue.y += 1;
				}
				if (m_pControllers[command.first.id]->IsPressed(command.first.buttons[3])) // down pressed
				{
					axisValue.y -= 1;
				}

				shouldExecute = (axisValue.x != 0 || axisValue.y != 0);	// should execute if any input on x, or y, or both
				break;
			}
		}

		if (shouldExecute)
		{
			command.second->Execute(axisValue);
		}
	}

	return true;
}

void dae::InputManager::BindCommand(const std::vector<unsigned int>& buttons, InputAction action, std::unique_ptr<BaseCommand> pCommand, int id)
{
	InputKey key{};
	if (GetInputKey(key, buttons, action, id))
	{
		m_pBaseCommands.emplace(key, std::move(pCommand));
	}
}

void dae::InputManager::BindCommand(const std::vector<unsigned int>& buttons, InputAction action, std::unique_ptr<Command<float>> pCommand, int id)
{
	InputKey key{};
	if (GetInputKey(key, buttons, action, id))
	{
		m_p1DValueCommands.emplace(key, std::move(pCommand));
	}	
}

void dae::InputManager::BindCommand(const std::vector<unsigned int>& buttons, InputAction action, std::unique_ptr<Command<glm::vec2>> pCommand, int id)
{
	InputKey key{};
	if (GetInputKey(key, buttons, action, id))
	{
		m_p2DValueCommands.emplace(key, std::move(pCommand));
	}
}

void dae::InputManager::BindCommand(unsigned int button, InputAction action, std::unique_ptr<BaseCommand> pCommand, int id)
{
	std::vector<unsigned int> vector{};
	vector.push_back(button);

	BindCommand(vector, action, std::move(pCommand), id);
}

void dae::InputManager::BindCommand(unsigned int button, InputAction action, std::unique_ptr<Command<float>> pCommand, int id)
{
	std::vector<unsigned int> vector{};
	vector.push_back(button);

	BindCommand(vector, action, std::move(pCommand), id);
}

void dae::InputManager::BindCommand(unsigned int button, InputAction action, std::unique_ptr<Command<glm::vec2>> pCommand, int id)
{
	std::vector<unsigned int> vector{};
	vector.push_back(button);

	BindCommand(vector, action, std::move(pCommand), id);
}

bool dae::InputManager::GetInputKey(InputKey& outKey, const std::vector<unsigned int>& buttons, InputAction action, int id)
{
	if (id < -1 || id > 4)	// invalid id, -1 = keyboard, 0 - 3 = up to 4 controllers
		return false;

	if (static_cast<int>(buttons.size()) > 4)
		return false; // cannot have 4+ buttons on one command

	else if ((action == InputAction::Up ||
		action == InputAction::Down ||
		action == InputAction::Pressed) && buttons.size() > 1)
	{
		// not axis value -> only one button
		return false;
	}

	else if ((action != InputAction::Digital2DAxis && action != InputAction::Analog2DAxis) && static_cast<int>(buttons.size()) > 2)
		return false; // only 4 button 2D can have 2+ button, all others should be only one or two button(s)

	while (id >= static_cast<int>(m_pControllers.size()))
	{
		// if not enough controllers, add one
		m_pControllers.push_back(std::make_unique<XBoxController>(static_cast<int>(m_pControllers.size())));
	}

	InputKey key{};
	key.action = action;
	key.buttons = buttons;
	key.id = id;

	outKey = key;

	return true;
}