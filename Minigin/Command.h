#pragma once

namespace dae
{
	class GameObject;

	class BaseCommand
	{
	public:
		explicit BaseCommand() = default;
		virtual ~BaseCommand() = default;
		virtual void Execute() = 0;
	};

	template <typename T>
	class Command : public BaseCommand
	{
	public:
		explicit Command() = default;
		virtual ~Command() = default;
		virtual void Execute() override {};
		virtual void Execute(const T& commandInfo) = 0;
	};
}
