#include "ShotLogger.h"
#include "utils/parser.h"

BAKKESMOD_PLUGIN(ShotLogger, "Shot logging plugin", "1.2", PLUGINTYPE_FREEPLAY)

void ShotLogger::onLoad()
{
	shotMeasure = std::make_shared<bool>(false);
	minSpeed = std::make_shared<float>(1000.0f);

	cvarManager->registerCvar("shot_log", "0", "Turns on the measurement.", true, true, 0.0f, true, 1.0f, false).bindTo(shotMeasure);
	cvarManager->getCvar("shot_log").addOnValueChanged([this](std::string oldValue, CVarWrapper cvar) 
	{ 
		if (cvar.getBoolValue())
		{
			gameWrapper->HookEvent("Function TAGame.Car_TA.SetVehicleInput", std::bind(&ShotLogger::Tick, this));
		}
		else
		{
			gameWrapper->UnhookEvent("Function TAGame.Car_TA.SetVehicleInput");
		}
	});

	cvarManager->registerCvar("shot_log_minspeed", "1000", "The minimum speed that is needed to trigger a log.", true, true, 0.0f, true, 6000.0f, false).bindTo(minSpeed);

	cvarManager->registerNotifier("shot_log_reset", [this](std::vector<std::string> params)
	{
		this->measurements.clear();
	}, "Reset the measurements.", PERMISSION_ALL);

	cvarManager->registerNotifier("shot_log_save", [this](std::vector<std::string> params)
	{
		std::ofstream logfile;
		logfile.open(gameWrapper->GetDataFolderW() + L"shots.csv");

		for (auto it : this->measurements)
		{
			logfile << std::to_string(it) << std::endl;
		}

		logfile.close();
	}, "Save the measurements to BakkesModFolder/data/shots.csv", PERMISSION_ALL);

}

void ShotLogger::onUnload()
{
}

void ShotLogger::Tick()
{
	if (*shotMeasure)
	{
		if (!gameWrapper->IsInFreeplay())
		{
			return;
		}

		auto server = gameWrapper->GetGameEventAsServer();
		if (server.IsNull())
		{
			return;
		}

		auto ball = server.GetBall();
		if (ball.IsNull())
			return;
		auto rb = ball.GetOldRBState();
		float new_speed_sq = rb.LinearVelocity.X * rb.LinearVelocity.X + rb.LinearVelocity.Y * rb.LinearVelocity.Y;

		if (old_speed_sq >= 0.0f)
		{
			if (new_speed_sq > old_speed_sq)
			{
				float total_speed = std::sqrt(new_speed_sq + rb.LinearVelocity.Z * rb.LinearVelocity.Z);
				if (total_speed > *minSpeed)
				{
					measurements.push_back(total_speed);
					gameWrapper->LogToChatbox(std::to_string(measurements.size()) + " Shot speed: " + to_string_with_precision(total_speed, 2));
				}
			}
		}

		old_speed_sq = new_speed_sq;

	}

}
