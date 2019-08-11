# ShotLoggerPlugin
BakkesMod Plugin to log every shot the player makes (chat window + file).
It works by just logging the current ball speed on every physics tick where the horizontal speed of the ball has increased and the total speed is higher than the chosen **shot_log_minspeed**.

## Installation

https://bakkesplugins.com/

## Usage

**THIS PLUGIN IS OFF BY DEFAULT**

You need to use the console commands to turn it on and configure. (Console opens with F6)

**shot_log** [0|1] - Turn the plugin off/on

**shot_log_minspeed** - The minimum speed "shot" that the logger will log

**shot_log_save** - Save all the shot speeds to a file called shots.csv in the bakkesmod folder.

**shot_log_reset** - Throw away all the previous measurements. Counter starts at 0 again and **shot_log_save** won't save the previous shots.
