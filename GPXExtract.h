#pragma once

#include <bits/stdc++.h>

#include "tinyxml2.h"

using namespace std;

namespace gpxinterp {

class GPXExtract {
public:
	GPXExtract(const char *fileFullPath, size_t rep=1):xmlFileFullPath(fileFullPath), repeat(rep){}

	string xmlFileFullPath;
	tinyxml2::XMLDocument doc;

	tinyxml2::XMLNode *gpx = nullptr;
	tinyxml2::XMLNode *trk = nullptr;
	tinyxml2::XMLNode *trkseg = nullptr;

	vector<double> lats;
	vector<double> lons;

	vector<time_t> times;
	bool extractTimes = false;
	vector<double> elevations;
	bool extractEles = false;

	size_t repeat;

	void extract() {
		tinyxml2::XMLError res = doc.LoadFile(xmlFileFullPath.c_str());
		assert(res == tinyxml2::XML_SUCCESS);

		gpx = doc.FirstChildElement("gpx");
		assert(gpx);

		trk = gpx->FirstChildElement("trk");
		assert(trk);

		trkseg = trk->FirstChildElement("trkseg");
		assert(trkseg);

		for (tinyxml2::XMLElement *trkpt = trkseg->FirstChildElement("trkpt"); trkpt; trkpt = trkpt->NextSiblingElement("trkpt")) {
        	double lat,lon;
        	res = trkpt->QueryDoubleAttribute("lat", &lat);
        	assert(res == tinyxml2::XML_SUCCESS);
        	res = trkpt->QueryDoubleAttribute("lon", &lon);
        	assert(res == tinyxml2::XML_SUCCESS);

			lats.push_back(lat);
			lons.push_back(lon);

			if(extractEles) {
				tinyxml2::XMLElement *ele = trkpt->FirstChildElement("ele");
				assert(ele);

				double num;
				res = ele->QueryDoubleText(&num);
				assert(res == tinyxml2::XML_SUCCESS);

				elevations.push_back(num);
			}

			if(extractTimes) {
				tinyxml2::XMLElement *timePt = trkpt->FirstChildElement("time");
				assert(timePt);

				struct tm t1;
				char *res = strptime(timePt->GetText(), "%FT%T%z", &t1);
				assert(res);

				time_t t2 = timegm(&t1);
				assert(t2!=-1);

				times.push_back(t2);
			}	
		}

		// doesn't make sense to repeat a loop from extracted times
		assert(!extractTimes || repeat==1);

		auto tmpLats = lats;
		auto tmpLons = lons;
		auto tmpElevations = elevations;
		for(size_t i=1; i<repeat; ++i) {
			for(size_t j=1; j<tmpLats.size(); ++j) {
				lats.push_back(tmpLats[j]);
				lons.push_back(tmpLons[j]);
				if(extractEles) elevations.push_back(tmpElevations[j]);
			}
		}
    }
};

}
