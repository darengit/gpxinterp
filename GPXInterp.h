#include <bits/stdc++.h>

#include "Config.h"
#include "GPXExtract.h"

using namespace std;

namespace gpxinterp {
class GPXInterp {
	static constexpr double earthRadiusM = 6371000;

	// This function converts decimal degrees to radians
	static double deg2rad(double deg) {
  		return (deg * M_PI / 180);
	}

	//  This function converts radians to decimal degrees
	static double rad2deg(double rad) {
  		return (rad * 180 / M_PI);
	}

	/**
	 * Returns the distance between two points on the Earth.
	 * Direct translation from http://en.wikipedia.org/wiki/Haversine_formula
	 * @param lat1d Latitude of the first point in degrees
	 * @param lon1d Longitude of the first point in degrees
	 * @param lat2d Latitude of the second point in degrees
	 * @param lon2d Longitude of the second point in degrees
	 * @return The distance between the two points in kilometers
	 */
	static double distanceEarth(double lat1d, double lon1d, double lat2d, double lon2d) {
		double lat1r, lon1r, lat2r, lon2r, u, v;
		lat1r = deg2rad(lat1d);
		lon1r = deg2rad(lon1d);
		lat2r = deg2rad(lat2d);
		lon2r = deg2rad(lon2d);
		u = sin((lat2r - lat1r)/2);
		v = sin((lon2r - lon1r)/2);
		return 2.0 * earthRadiusM * asin(sqrt(u * u + cos(lat1r) * cos(lat2r) * v * v));
	}

public:
	static void interp(GPXExtract& runExtract, GPXExtract& routeExtract) {
		size_t runIdx = 0;

		int interpCnt=0;
		vector<double> interpDists;
		double totalInterpDist=0;

		for(size_t routeIdx=0; routeIdx<routeExtract.lats.size(); ++routeIdx) {
			size_t closestIdx=UINT_MAX;
			double closestDist = DBL_MAX;//distanceEarth(routeExtract.lats[routeIdx], routeExtract.lons[routeIdx],
				//runExtract.lats[startingIdx], runExtract.lons[startingIdx]);


			double currRouteDist = 10;
			if(routeIdx)
				currRouteDist = GPXInterp::distanceEarth(routeExtract.lats[routeIdx], routeExtract.lons[routeIdx],
					routeExtract.lats[routeIdx-1], routeExtract.lons[routeIdx-1]);

			for(size_t idx=runIdx; idx<runExtract.lats.size(); ++idx) {
				double runRouteDist = distanceEarth(routeExtract.lats[routeIdx],
                                            routeExtract.lons[routeIdx],
                                            runExtract.lats[idx],
                                            runExtract.lons[idx]);
				
				if(runRouteDist > 2.0*(totalInterpDist+currRouteDist) && idx-runIdx > CHECK_MIN_PTS)
					break;

				if(routeIdx && routeIdx<routeExtract.lats.size()-1) {
					if(runRouteDist > ACCURACY)
						continue;

					double speed = (currRouteDist+totalInterpDist) /
						(double)(runExtract.times[idx]-routeExtract.times[routeIdx-interpCnt-1]);
					
					if(speed<MIN_SPEED_M_S || speed>MAX_SPEED_M_S)
						continue;
				}

				if(runRouteDist < closestDist) {
					closestDist = runRouteDist;
					closestIdx = idx;
				}
			}

			// assert we found points for 1st and last points
			assert((routeIdx||routeIdx<routeExtract.lats.size()-1) || closestIdx!=UINT_MAX);

			if(closestIdx==UINT_MAX) {
				++interpCnt;
				interpDists.push_back(currRouteDist);
				totalInterpDist += currRouteDist;
			} else {
				if(interpCnt) {
					time_t interpTime = runExtract.times[closestIdx] - routeExtract.times[routeIdx-interpCnt-1];
				
					double runningDist=0;
					for(int i=0; i<interpCnt; ++i) {
						runningDist += interpDists[i];
						routeExtract.times.push_back(routeExtract.times[routeIdx-interpCnt-1] + (time_t)((double)interpTime*runningDist/(totalInterpDist+currRouteDist)));
					}
				}

				routeExtract.times.push_back(runExtract.times[closestIdx]);
				interpCnt=0;
				interpDists.clear();
				totalInterpDist=0;

				runIdx=closestIdx+1;
				// assert that runIdx doesn't run to the end before the last point
				assert(routeIdx==routeExtract.lats.size()-1 || runIdx<runExtract.lats.size());

				closestIdx=UINT_MAX;
				closestDist=DBL_MAX;
			}

		}
/*	
		routeExtract.lats.push_back(routeExtract.lats.back());
		routeExtract.lons.push_back(routeExtract.lons.back());
		routeExtract.times.push_back(routeExtract.times.back());
		if(routeExtract.extractEles)
			routeExtract.elevations.push_back(routeExtract.elevations.back());
*/

		return;
	}
};
}
