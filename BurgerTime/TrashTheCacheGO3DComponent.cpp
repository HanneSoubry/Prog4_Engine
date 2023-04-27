#include "TrashTheCacheGO3DComponent.h"
#include <numeric>
#include <algorithm>
#include <chrono>

dae::TrashTheCacheGO3DComponent::TrashTheCacheGO3DComponent(std::shared_ptr<GameObject> pOwner)
	: BaseComponent(pOwner)
{
	// plot 1
	m_PlotConfigGO.grid_y.show = true;
	m_PlotConfigGO.frame_size = ImVec2(200, 100);
	m_PlotConfigGO.line_thickness = 2;
	m_PlotConfigGO.values.color = m_Colors[0];

	// plot 2
	m_PlotConfigGOAlt.grid_y.show = true;
	m_PlotConfigGOAlt.frame_size = ImVec2(200, 100);
	m_PlotConfigGOAlt.line_thickness = 2;
	m_PlotConfigGOAlt.values.color = m_Colors[1];

	// combined
	m_PlotConfigCombined.grid_y.show = true;
	m_PlotConfigCombined.values.ys_count = 2;
	m_PlotConfigCombined.frame_size = ImVec2(200, 100);
	m_PlotConfigCombined.line_thickness = 2;

	m_PlotConfigCombined.tooltip.show = true;
	m_PlotConfigCombined.tooltip.format = "x=%.2f, y=%.2f";

	m_PlotConfigCombined.values.colors = m_Colors;
}

dae::TrashTheCacheGO3DComponent::~TrashTheCacheGO3DComponent()
{
	if (m_PlotValuesCombined)
		delete[] m_PlotValuesCombined;
}

void dae::TrashTheCacheGO3DComponent::RenderImGui()
{
	ImGui::Begin("Excercise 2 - GameObject3D");
	ImGui::InputInt("# samples", &m_NrSamples);

	// plot 1
	if (ImGui::Button("Trash the cache with GameObject3D") && m_NrSamples >= 3)
	{
		StartCalculationGO();
	}
	ImGui::Plot("Trash the cache - GameObject3D", m_PlotConfigGO);

	// plot 2 
	if (ImGui::Button("Trash the cache with GameObject3DAlt") && m_NrSamples >= 3)
	{
		StartCalculationGOAlt();
	}
	ImGui::Plot("Trash the cache - GameObject3DAlt", m_PlotConfigGOAlt);

	// combined
	if (m_PlotConfigCombined.values.ys_list)
	{
		ImGui::Text("Combined: ");
		ImGui::Plot("Trash the cache - combined", m_PlotConfigCombined);
	}

	ImGui::End();
}

void dae::TrashTheCacheGO3DComponent::StartCalculationGO()
{
	// clear data
	m_PlotValuesGO.clear();

	// create array
	const int arraySize{ 10'000'000 };
	GameObject3D* array = new GameObject3D[arraySize];

	for (int i = 1; i <= 1024; i *= 2)	// double step
	{
		m_PlotValuesGO.push_back(GetAverageTime(i, array, arraySize));
	}

	// delete array
	delete[] array;

	float plotMax = *std::max_element(m_PlotValuesGO.begin(), m_PlotValuesGO.end());

	// set the plot data
	m_PlotConfigGO.scale.max = plotMax;
	m_PlotConfigGO.grid_y.size = plotMax / 10;

	m_PlotConfigGO.values.ys = m_PlotValuesGO.data();
	m_PlotConfigGO.values.count = static_cast<int>(m_PlotValuesGO.size());

	// if both graphs exist, update combined
	if (!m_PlotValuesGO.empty() && !m_PlotValuesGOAlt.empty())
	{
		float otherPlotMax = *std::max_element(m_PlotValuesGOAlt.begin(), m_PlotValuesGOAlt.end());

		plotMax = std::max(plotMax, otherPlotMax);

		m_PlotConfigCombined.values.count = static_cast<int>(m_PlotValuesGO.size());
		m_PlotConfigCombined.scale.max = plotMax;
		m_PlotConfigCombined.grid_y.size = plotMax / 10;

		m_PlotValuesCombined = new const float* [] { m_PlotValuesGO.data(), m_PlotValuesGOAlt.data() };
		m_PlotConfigCombined.values.ys_list = m_PlotValuesCombined;
	}
}

void dae::TrashTheCacheGO3DComponent::StartCalculationGOAlt()
{
	// clear data
	m_PlotValuesGOAlt.clear();

	// create array
	const int arraySize{ 10'000'000 };
	GameObject3DAlt* array = new GameObject3DAlt[arraySize];

	for (int i = 1; i <= 1024; i *= 2)	// double step
	{
		m_PlotValuesGOAlt.push_back(GetAverageTime(i, array, arraySize));
	}

	// delete array
	delete[] array;

	float plotMax = *std::max_element(m_PlotValuesGOAlt.begin(), m_PlotValuesGOAlt.end());

	// set the plot data
	m_PlotConfigGOAlt.scale.max = plotMax;
	m_PlotConfigGOAlt.grid_y.size = plotMax / 10;

	m_PlotConfigGOAlt.values.ys = m_PlotValuesGOAlt.data();
	m_PlotConfigGOAlt.values.count = static_cast<int>(m_PlotValuesGOAlt.size());

	// if both graphs exist, update combined
	if (!m_PlotValuesGO.empty() && !m_PlotValuesGOAlt.empty())
	{
		float otherPlotMax = *std::max_element(m_PlotValuesGO.begin(), m_PlotValuesGO.end());

		plotMax = std::max(plotMax, otherPlotMax);

		m_PlotConfigCombined.values.count = static_cast<int>(m_PlotValuesGOAlt.size());
		m_PlotConfigCombined.scale.max = plotMax;
		m_PlotConfigCombined.grid_y.size = plotMax / 10;

		m_PlotValuesCombined = new const float* [] { m_PlotValuesGO.data(), m_PlotValuesGOAlt.data() };
		m_PlotConfigCombined.values.ys_list = m_PlotValuesCombined;
	}
}

float dae::TrashTheCacheGO3DComponent::GetAverageTime(int stepSize, GameObject3D* array, int arrayLength)
{
	// take samples
	std::vector<long long> elapsedTimes{};

	for (int i{}; i < m_NrSamples; ++i)
	{
		const auto start = std::chrono::high_resolution_clock::now();

		for (int j{}; j < arrayLength; j += stepSize)
		{
			array[j].ID += 1;
		}

		const auto end = std::chrono::high_resolution_clock::now();
		const long long elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
		elapsedTimes.push_back(elapsedTime);
	}

	// remove minimum and maximum
	elapsedTimes.erase(std::min_element(elapsedTimes.begin(), elapsedTimes.end()));
	elapsedTimes.erase(std::max_element(elapsedTimes.begin(), elapsedTimes.end()));

	// get average of remaining values
	const float average{ std::accumulate(elapsedTimes.begin(), elapsedTimes.end(), 0.0f) / elapsedTimes.size() };

	return average;
}

float dae::TrashTheCacheGO3DComponent::GetAverageTime(int stepSize, GameObject3DAlt* array, int arrayLength)
{
	// take samples
	std::vector<long long> elapsedTimes{};

	for (int i{}; i < m_NrSamples; ++i)
	{
		const auto start = std::chrono::high_resolution_clock::now();

		for (int j{}; j < arrayLength; j += stepSize)
		{
			array[j].ID += 1;
		}

		const auto end = std::chrono::high_resolution_clock::now();
		const long long elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
		elapsedTimes.push_back(elapsedTime);
	}

	// remove minimum and maximum
	elapsedTimes.erase(std::min_element(elapsedTimes.begin(), elapsedTimes.end()));
	elapsedTimes.erase(std::max_element(elapsedTimes.begin(), elapsedTimes.end()));

	// get average of remaining values
	const float average{ std::accumulate(elapsedTimes.begin(), elapsedTimes.end(), 0.0f) / elapsedTimes.size() };

	return average;
}
