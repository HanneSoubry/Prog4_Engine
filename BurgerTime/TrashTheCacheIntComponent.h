#pragma once
#include "imgui_plot.h"
#include "BaseComponent.h"
#include <vector>

namespace dae
{
	class TrashTheCacheIntComponent final : public BaseComponent
	{
	public:
		TrashTheCacheIntComponent(GameObject* pOwner);
		virtual ~TrashTheCacheIntComponent() override = default;
		TrashTheCacheIntComponent(const TrashTheCacheIntComponent& other) = delete;
		TrashTheCacheIntComponent(TrashTheCacheIntComponent&& other) = delete;
		TrashTheCacheIntComponent& operator=(const TrashTheCacheIntComponent& other) = delete;
		TrashTheCacheIntComponent& operator=(TrashTheCacheIntComponent&& other) = delete;

		void RenderImGui() override;

	private:
		int m_NrSamples{ 10 };

		std::vector<float> m_PlotValues{};
		ImGui::PlotConfig m_PlotConfig{};

		void StartCalculation();
		float GetAverageTime(int stepSize, int* array, int arrayLength);
	};
}