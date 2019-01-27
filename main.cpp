#include <bits/stdc++.h>

#include "GPXExtract.h"
#include "GPXInterp.h"
#include "GPXConstruct.h"
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

	gpxinterp::GPXInterp::interp(runExtract, routeExtract);
	gpxinterp::GPXConstruct::construct(runExtract, routeExtract);

	tinyxml2::XMLPrinter printer;
	runExtract.doc.Print(&printer);
	cout << printer.CStr() << endl;

	return 0;
}
