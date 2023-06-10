#pragma once
#include "imgui_plot.h"
#include "BaseComponent.h"
#include <vector>

namespace dae
{
	struct Transform3D
	{
		float matrix[16] = {
			1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1
		};
	};

	class GameObject3D
	{
	public:
		Transform3D transform{};
		int ID{};
	};

	class GameObject3DAlt
	{
	public:
		Transform3D* transform{ nullptr };
		int ID{};
	};

	class TrashTheCacheGO3DComponent final : public BaseComponent
	{
	public:
		TrashTheCacheGO3DComponent(GameObject* pOwner);
		virtual ~TrashTheCacheGO3DComponent() override;
		TrashTheCacheGO3DComponent(const TrashTheCacheGO3DComponent& other) = delete;
		TrashTheCacheGO3DComponent(TrashTheCacheGO3DComponent&& other) = delete;
		TrashTheCacheGO3DComponent& operator=(const TrashTheCacheGO3DComponent& other) = delete;
		TrashTheCacheGO3DComponent& operator=(TrashTheCacheGO3DComponent&& other) = delete;

		void RenderImGui() override;

	private:
		int m_NrSamples{ 10 };
		ImU32 m_Colors[2] = { ImColor(0, 255, 0), ImColor(0, 255, 255) };

		std::vector<float> m_PlotValuesGO{};
		std::vector<float> m_PlotValuesGOAlt{};
		const float** m_PlotValuesCombined{};

		ImGui::PlotConfig m_PlotConfigGO{};
		ImGui::PlotConfig m_PlotConfigGOAlt{};
		ImGui::PlotConfig m_PlotConfigCombined{};

		void StartCalculationGO();
		void StartCalculationGOAlt();
		float GetAverageTime(int stepSize, GameObject3D* array, int arrayLength);
		float GetAverageTime(int stepSize, GameObject3DAlt* array, int arrayLength);
	};
}