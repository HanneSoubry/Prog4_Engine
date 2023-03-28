#pragma once
#include "glm/glm.hpp"

namespace dae
{
	class XBoxController final
	{
		class XBoxControllerImpl;

	public:
		explicit XBoxController(int controllerIndex);
		~XBoxController();

		XBoxController(const XBoxController& other) = delete;
		XBoxController(XBoxController&& other) = delete;
		XBoxController& operator=(const XBoxController& other) = delete;
		XBoxController& operator=(XBoxController&& other) = delete;

		enum ControllerButton
		{
			DPadUp = 0x0001,
			DPadDown = 0x0002,
			DPadLeft = 0x0004,
			DPadRight = 0x0008,
			Start = 0x0010,
			Back = 0x0020,
			LeftThumb = 0x0040,
			RightThumb = 0x0080,
			LeftShoulder = 0x0100,
			RightShoulder = 0x0200,
			LeftTrigger = 0x0400,
			RightTrigger = 0x0800,
			ButtonA = 0x1000,
			ButtonB = 0x2000,
			ButtonX = 0x4000,
			ButtonY = 0x8000
		};

		void Update();

		bool IsDown(unsigned int button) const;
		bool IsUp(unsigned int  button) const;
		bool IsPressed(unsigned int  button) const;

		float GetAxis(unsigned int button) const;	// triggers
		glm::vec2 Get2DAxis(unsigned int button) const;	// thumbsticks

	private:
		XBoxControllerImpl* pImpl;
	};
}


