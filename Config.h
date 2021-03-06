#pragma once

namespace gpxinterp {
	// full path to an activity which needs smoothing and interpolation
	const char *RUN_FILE_FULL_PATH = "/home/daren/Downloads/Morning_Run_20190210.gpx";
	// full path to the route file created on strava for the actual route traveled
	const char *ROUTE_FILE_FULL_PATH = "/home/daren/Downloads/Pond_Loop.gpx";

	// a speed you did not exceed on your run
	const double MAX_SPEED_MIN_MILE = 7;
	// a speed you did not go below during your run
	const double MIN_SPEED_MIN_MILE = 14;

	const double MAX_SPEED_M_S = 1600.0/60.0/MAX_SPEED_MIN_MILE;
	const double MIN_SPEED_M_S = 1600.0/60.0/MIN_SPEED_MIN_MILE;

	// check at least CHECK_MIN_PTS from RUN_FILE_FULL_PATH for a point which matches
	// closest to a point on ROUTE_FILE_FULL_PATH
	const int CHECK_MIN_PTS = 50;

	// interpolate intermediate points if we can't find a matching point within
	// ACCURACY
	const double ACCURACY = 10; // in meters


	



	const bool INTERP_ROUTE_ALL = true;
	const char *TIME_START = "2019-03-10T18:30:00Z";
	const char *TIME_END = "2019-03-10T19:18:00Z";
	const int REPEAT = 4;




}
