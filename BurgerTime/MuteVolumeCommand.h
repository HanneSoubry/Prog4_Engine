#pragma once
#include "Command.h"

namespace dae
{
	class MuteVolumeCommand final : public BaseCommand
	{
	public:
		MuteVolumeCommand(bool isMusicPlaying);
		~MuteVolumeCommand() = default;

		virtual void Execute() override;
	private: 
		bool m_IsMuted{};
	};

}