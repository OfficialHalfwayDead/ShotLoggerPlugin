#pragma once
#include "bakkesmod/plugin/bakkesmodplugin.h"
#pragma comment( lib, "bakkesmod.lib" )

class ShotLogger : public BakkesMod::Plugin::BakkesModPlugin
{
protected:
	std::shared_ptr<bool> shotMeasure;
	std::shared_ptr<float> minSpeed;
	std::vector<float> measurements;
	float old_speed_sq = -1.0f;

public:
	ShotLogger() = default;
	~ShotLogger() = default;
	void onLoad();
	void onUnload();
	void Toggle();
	void Tick();
};