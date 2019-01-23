#include <bits/stdc++.h>

#include "GPXExtract.h"
#include "Config.h"

using namespace std;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	gpxinterp::GPXExtract runExtract(gpxinterp::RUN_FILE_FULL_PATH);
	runExtract.extractTimes = true;
	runExtract.extractEles = true;
	runExtract.extract();

	gpxinterp::GPXExtract routeExtract(gpxinterp::ROUTE_FILE_FULL_PATH);
	routeExtract.extractEles = true;
	routeExtract.extract();



	int a = 1;
	return a;
}
