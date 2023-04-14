#include <SDL.h>
#include "InputManager.h"
#include <backends/imgui_impl_sdl2.h>

bool dae::InputManager::ProcessInput()
{
	m_KeysDownThisFrame.clear();
	m_KeysUpThisFrame.clear();

	// Keyboard events
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			return false;
		}
		if (e.type == SDL_KEYDOWN) {
			m_KeysDownThisFrame.emplace(e.key.keysym.sym);
			m_KeysPressed.emplace(e.key.keysym.sym);		// the set will remove duplicates
		}
		if (e.type == SDL_KEYUP) {
			m_KeysUpThisFrame.emplace(e.key.keysym.sym);
			m_KeysPressed.erase(e.key.keysym.sym);		
		}
		if (e.type == SDL_MOUSEBUTTONDOWN) {
			m_KeysDownThisFrame.emplace(e.key.keysym.sym);
			m_KeysPressed.emplace(e.key.keysym.sym);	
		}
		if (e.type == SDL_MOUSEBUTTONUP) {
			m_KeysUpThisFrame.emplace(e.key.keysym.sym);
			m_KeysPressed.erase(e.key.keysym.sym);		
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
	for (const auto& command : m_pCommands)
	{
		bool shouldExecute{ false };

		if (command.first.id == -1) // using keyboard
		{
			switch (command.first.action)
			{
			case InputAction::Pressed:
				shouldExecute = m_KeysPressed.contains(command.first.buttons[0]);
				break;

			case InputAction::Down:
				shouldExecute = m_KeysDownThisFrame.contains(command.first.buttons[0]);
				break;

			case InputAction::Up:
				shouldExecute = m_KeysUpThisFrame.contains(command.first.buttons[0]);
				break;

			case InputAction::Digital2DAxis:
				if (m_KeysPressed.contains(command.first.buttons[0])) // left pressed
				{
					m_2DAxisValue.x -= 1;
				}
				if (m_KeysPressed.contains(command.first.buttons[1])) // right pressed
				{
					m_2DAxisValue.x += 1;
				}
				if (m_KeysPressed.contains(command.first.buttons[2])) // up pressed
				{
					m_2DAxisValue.y += 1;
				}
				if (m_KeysPressed.contains(command.first.buttons[3])) // down pressed
				{
					m_2DAxisValue.y -= 1;
				}

				shouldExecute = (m_2DAxisValue.x != 0 || m_2DAxisValue.y != 0);	// should execute if any input on x, or y, or both
				break;
			// case analog action: does not exist on keyboard
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

			case InputAction::Analog1DAxis:
				m_1DAxisValue = m_pControllers[command.first.id]->GetAxis(command.first.buttons[0]);
				shouldExecute = (m_1DAxisValue > 0);	// should execute if any input
				break;

			case InputAction::Analog2DAxis:
				m_2DAxisValue = m_pControllers[command.first.id]->Get2DAxis(command.first.buttons[0]);
				shouldExecute = (m_2DAxisValue.x != 0 || m_2DAxisValue.y != 0);	// should execute if any input on x, or y, or both
				break;

			case InputAction::Digital2DAxis:
				if (m_pControllers[command.first.id]->IsPressed(command.first.buttons[0])) // left pressed
				{
					m_2DAxisValue.x -= 1;
				}
				if (m_pControllers[command.first.id]->IsPressed(command.first.buttons[1])) // right pressed
				{
					m_2DAxisValue.x += 1;
				}
				if (m_pControllers[command.first.id]->IsPressed(command.first.buttons[2])) // up pressed
				{
					m_2DAxisValue.y += 1;
				}
				if (m_pControllers[command.first.id]->IsPressed(command.first.buttons[3])) // down pressed
				{
					m_2DAxisValue.y -= 1;
				}

				shouldExecute = (m_2DAxisValue.x != 0 || m_2DAxisValue.y != 0);	// should execute if any input on x, or y, or both
				break;
			}
		}
		
		if (shouldExecute)
		{
			command.second->Execute();
		}

		// reset values for next command
		m_1DAxisValue = 0;
		m_2DAxisValue = { 0, 0 };
	}

	return true;
}

void dae::InputManager::BindCommand(const std::vector<unsigned int>& buttons, InputAction action, std::unique_ptr<Command> pCommand, int id)
{
	if (id < -1 || id > 4)	// invalid id, -1 = keyboard, 0 - 3 = up to 4 controllers
		return;

	if (static_cast<int>(buttons.size()) > 4)
		return; // cannot have 4+ buttons on one command

	else if (action != InputAction::Digital2DAxis && static_cast<int>(buttons.size()) > 1)
		return; // only 4 button 2D can have 1+ button, all others should be only one button

	while (id >= static_cast<int>(m_pControllers.size()))
	{
		// if not enough controllers, add one
		m_pControllers.push_back(std::make_unique<XBoxController>(static_cast<int>(m_pControllers.size())));
	}

	InputKey key{};
	key.action = action;
	key.buttons = buttons;
	key.id = id;

	m_pCommands.emplace(key, std::move(pCommand));
}

void dae::InputManager::BindCommand(unsigned int button, InputAction action, std::unique_ptr<Command> pCommand, int id)
{
	std::vector<unsigned int> vector{};
	vector.push_back(button);

	BindCommand(vector, action, std::move(pCommand), id);
}
