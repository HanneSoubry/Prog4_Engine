
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <Xinput.h>
#include "XBoxController.h"

using namespace dae;

class XBoxController::XBoxControllerImpl
{
public:
	XBoxControllerImpl(int controllerIndex)
		: m_ControllerIndex{ controllerIndex }
	{
		ZeroMemory(&m_PreviousState, sizeof(XINPUT_STATE));
		ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
	}

	void Update()
	{
		CopyMemory(&m_PreviousState, &m_CurrentState, sizeof(XINPUT_STATE));
		ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
		XInputGetState(m_ControllerIndex, &m_CurrentState);

		auto buttonChanges = m_CurrentState.Gamepad.wButtons ^ m_PreviousState.Gamepad.wButtons;
		m_ButtonsPressedThisFrame = buttonChanges & m_CurrentState.Gamepad.wButtons;
		m_ButtonsReleasedThisFrame = buttonChanges & (~m_CurrentState.Gamepad.wButtons);
	}

	bool IsDownThisFrame(unsigned int button) const { return m_ButtonsPressedThisFrame & button; }
	bool IsUpThisFrame(unsigned int button) const { return m_ButtonsReleasedThisFrame & button; }
	bool IsPressed(unsigned int button) const { return m_CurrentState.Gamepad.wButtons & button; }

	// return : [-1, 1]
	float GetAxis(unsigned int button)
	{
		if (button & ControllerButton::LeftTrigger)
		{
			return m_CurrentState.Gamepad.bLeftTrigger / m_MaxTriggerAxisValue;
		}
		
		if (button & ControllerButton::RightTrigger)
		{
			return m_CurrentState.Gamepad.bRightTrigger / m_MaxTriggerAxisValue;
		}

		// button without axis value
		return 0;
	}

	// return : [-1, 1] on both axes
	glm::vec2 Get2DAxis(unsigned int button) const
	{
		if (button & ControllerButton::LeftThumb)
		{
			return { ClampAxisWithDeadZone(m_CurrentState.Gamepad.sThumbLX), ClampAxisWithDeadZone(m_CurrentState.Gamepad.sThumbLY) };
		}

		if (button & ControllerButton::RightThumb)
		{
			return { ClampAxisWithDeadZone(m_CurrentState.Gamepad.sThumbRX), ClampAxisWithDeadZone(m_CurrentState.Gamepad.sThumbRY) };
		}

		// button without 2D axis value
		return { 0, 0 };
	}

private:
	XINPUT_STATE m_PreviousState{};
	XINPUT_STATE m_CurrentState{};

	WORD m_ButtonsPressedThisFrame;
	WORD m_ButtonsReleasedThisFrame;

	int m_ControllerIndex;

	const float m_MaxStickAxisValue{ 32767.0f };
	const float m_MaxTriggerAxisValue{ 255.0f };
	// Default windows deadzone value
	const int m_DeadZoneValue{ static_cast<int>(XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE) };

	float ClampAxisWithDeadZone(float value) const
	{
		if (std::abs(value) < m_DeadZoneValue) // in deadzone -> set to 0
		{
			return 0.f;
		}
		else
		{
			return value / m_MaxStickAxisValue;
		}
	}
};

XBoxController::XBoxController(int controllerIndex)
{
	pImpl = new XBoxControllerImpl(controllerIndex);
}

XBoxController::~XBoxController()
{
	delete pImpl;
}

void XBoxController::Update()
{
	pImpl->Update();
}

bool XBoxController::IsDown(unsigned int button) const
{
	return pImpl->IsDownThisFrame(button);
}

bool XBoxController::IsUp(unsigned int  button) const
{
	return pImpl->IsUpThisFrame(button);
}

bool XBoxController::IsPressed(unsigned int  button) const
{
	return pImpl->IsPressed(button);
}

float dae::XBoxController::GetAxis(unsigned int button) const
{
	return pImpl->GetAxis(button);
}

glm::vec2 dae::XBoxController::Get2DAxis(unsigned int button) const
{
	return pImpl->Get2DAxis(button);
}
