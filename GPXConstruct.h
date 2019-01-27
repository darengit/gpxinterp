#include <bits/stdc++.h>

#include "GPXExtract.h"

using namespace std;

namespace gpxinterp {

class GPXConstruct {
public:
	static void construct(GPXExtract& runExtract, GPXExtract& routeExtract) {
		runExtract.trkseg->DeleteChildren();

		assert(routeExtract.times.size() == routeExtract.lats.size());

		for(size_t i=0; i<routeExtract.lats.size(); ++i) {
			tinyxml2::XMLElement *runTrkpt = runExtract.doc.NewElement("trkpt");
			runTrkpt->SetAttribute("lat", routeExtract.lats[i]);
			runTrkpt->SetAttribute("lon", routeExtract.lons[i]);

			if(routeExtract.extractEles) {
				tinyxml2::XMLElement *runEle = runExtract.doc.NewElement("ele");
				runEle->SetText(to_string(routeExtract.elevations[i]).c_str());
				runTrkpt->InsertEndChild(runEle);
			}

			struct tm *gmtm = gmtime(&routeExtract.times[i]);
			char buf[100] = {'\0'};
			size_t ret = strftime(buf, 100, "%FT%T%z", gmtm);
			assert(ret);

			tinyxml2::XMLElement *runTime = runExtract.doc.NewElement("time");
			runTime->SetText(buf);
			runTrkpt->InsertEndChild(runTime);
			runExtract.trkseg->InsertEndChild(runTrkpt);
		}

		return;
	}
};

}
