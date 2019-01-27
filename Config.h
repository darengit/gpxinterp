#pragma once

namespace gpxinterp {
	const char *RUN_FILE_FULL_PATH = "/home/daren/Downloads/Morning_Run_20190113.gpx";
	const char *ROUTE_FILE_FULL_PATH = "/home/daren/Downloads/Hill_Run.gpx";

	const double MAX_SPEED_MIN_MILE = 7;
	const double MIN_SPEED_MIN_MILE = 14;

	const double MAX_SPEED_M_S = 1600.0/60.0/MAX_SPEED_MIN_MILE;
	const double MIN_SPEED_M_S = 1600.0/60.0/MIN_SPEED_MIN_MILE;

	const int CHECK_MIN_PTS = 50;

	const double ACCURACY = 10; // in meters
}
