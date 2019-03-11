#include <bits/stdc++.h>

#include "GPXExtract.h"
#include "GPXInterp.h"
#include "GPXConstruct.h"
#include "Config.h"

using namespace std;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);


	if(gpxinterp::INTERP_ROUTE_ALL) {
		gpxinterp::GPXExtract routeExtract(gpxinterp::ROUTE_FILE_FULL_PATH, gpxinterp::REPEAT);
		routeExtract.extractEles = true;
		routeExtract.extract();

		gpxinterp::GPXInterp::interp(routeExtract, gpxinterp::TIME_START, gpxinterp::TIME_END);

		gpxinterp::GPXConstruct::construct(routeExtract, routeExtract);

		tinyxml2::XMLPrinter printer;
		routeExtract.doc.Print(&printer);
		cout << printer.CStr() << endl;


		return 0;
	}




	gpxinterp::GPXExtract runExtract(gpxinterp::RUN_FILE_FULL_PATH);
	runExtract.extractTimes = true;
	runExtract.extractEles = true;
	runExtract.extract();

	gpxinterp::GPXExtract routeExtract(gpxinterp::ROUTE_FILE_FULL_PATH);
	routeExtract.extractEles = true;
	routeExtract.extract();

	gpxinterp::GPXInterp::interp(runExtract, routeExtract);
	gpxinterp::GPXConstruct::construct(runExtract, routeExtract);

	tinyxml2::XMLPrinter printer;
	runExtract.doc.Print(&printer);
	cout << printer.CStr() << endl;

	return 0;
}
