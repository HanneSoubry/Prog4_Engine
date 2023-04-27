#include "TrashTheCacheIntComponent.h"
#include <numeric>
#include <algorithm>
#include <chrono>

dae::TrashTheCacheIntComponent::TrashTheCacheIntComponent(std::shared_ptr<GameObject> pOwner)
	: BaseComponent(pOwner)
{
	m_PlotConfig.grid_y.show = true;
	m_PlotConfig.frame_size = ImVec2(200, 100);
	m_PlotConfig.line_thickness = 2;
	m_PlotConfig.values.color = ImColor(255, 125, 0);
}

void dae::TrashTheCacheIntComponent::RenderImGui()
{
	ImGui::Begin("Excercise 1 - Integers");
	ImGui::InputInt("# samples", &m_NrSamples);

	if (ImGui::Button("Trash the cache") && m_NrSamples >= 3)
	{
		StartCalculation();
	}

	ImGui::Plot("Trash the cache - integers", m_PlotConfig);
	ImGui::End();
}

void dae::TrashTheCacheIntComponent::StartCalculation()
{
	// clear data
	m_PlotValues.clear();

	// create array
	const int arraySize{ 10'000'000 };
	int* array = new int[arraySize];

	for (int i = 1; i <= 1024; i *= 2)	// double step
	{
		m_PlotValues.push_back(GetAverageTime(i, array, arraySize));
	}

	// delete array
	delete[] array;

	float plotMax = *std::max_element(m_PlotValues.begin(), m_PlotValues.end());

	// set the plot data
	m_PlotConfig.scale.max = plotMax;
	m_PlotConfig.grid_y.size = plotMax / 10;

	m_PlotConfig.values.ys = m_PlotValues.data();
	m_PlotConfig.values.count = static_cast<int>(m_PlotValues.size());
}

float dae::TrashTheCacheIntComponent::GetAverageTime(int stepSize, int* array, int arrayLength)
{
	// take samples
	std::vector<long long> elapsedTimes{};

	for (int i{}; i < m_NrSamples; ++i)
	{
		const auto start = std::chrono::high_resolution_clock::now();

		for (int j{}; j < arrayLength; j += stepSize)
		{
			array[j] += 1;
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
