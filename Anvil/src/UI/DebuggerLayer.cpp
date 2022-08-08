#include "DebuggerLayer.hpp"

// --- RLE ---
#include <ImGui/imgui.h>



void anvil::DebuggerLayer::onEnter()
{

}

void anvil::DebuggerLayer::onExit()
{

}

void anvil::DebuggerLayer::onUpdate(const rle::time::step_ms delta)
{
	// Increment the timer
	m_Timer += delta;

	// Increment our frame counter
	if (!m_FramePlotPaused)
	{
		m_FrameTimeCounter.push_back(static_cast<float>(delta.count()));

		if (m_FrameTimeCounter.size() > 300)
			m_FrameTimeCounter.erase(m_FrameTimeCounter.begin());
	}

	// TEMP: rle::time::step_sec(1.0) could eventually be turned into a constant
	if (m_Timer >= rle::time::step_sec(1.0))
	{
		for (const auto time : m_FrameTimeCounter)
			m_AverageFrameTime += time;
		m_AverageFrameTime /= static_cast<float>(m_FrameTimeCounter.size());

		m_Timer -= rle::time::step_sec(1.0);
	}
}

void anvil::DebuggerLayer::onRender(rle::Renderer& renderer) const
{
	if (ImGui::Begin("Debugger", &m_Open))
	{
		ImGui::Text("Frame Info:");
		ImGui::BulletText("Average Frame Time: %f", m_AverageFrameTime);
		ImGui::BulletText("Average FPS: %i", static_cast<std::uint32_t>(1000.0f / m_AverageFrameTime));
		ImGui::PlotLines(
			"Frame Times",
			m_FrameTimeCounter.data(),
			static_cast<float>(m_FrameTimeCounter.size()),
			0,
			nullptr,
			0.0f,
			10.0f,
			ImVec2(0.0f, 40.0f));
		ImGui::Checkbox("Paused", &m_FramePlotPaused);

		// This here so its ready for scene debugging info
		//ImGui::Separator();

		//ImGui::Text("Scene:");

		ImGui::End();
	}
}
