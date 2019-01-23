#include <bits/stdc++.h>

#include "tinyxml2.h"

typedef long long llong;

using namespace std;

double distSq(double lat1, double lon1, double lat2, double lon2) {
	return pow(lat1-lat2,2)+pow(lon1-lon2,2);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

//cout.precision(20);

	tinyxml2::XMLDocument runDoc;
	tinyxml2::XMLError res = runDoc.LoadFile("/home/daren/Downloads/Morning_Run_20190121.gpx");

	assert(res == tinyxml2::XML_SUCCESS);

	tinyxml2::XMLNode *gpx = runDoc.FirstChildElement("gpx");
	assert(gpx);

	tinyxml2::XMLElement *metadata = gpx->FirstChildElement("metadata");
	assert(metadata);
	tinyxml2::XMLElement *timeEle = metadata->FirstChildElement("time");
	assert(timeEle);

	tinyxml2::XMLElement *trk = gpx->FirstChildElement("trk");
	assert(trk);
	tinyxml2::XMLElement *name = trk->FirstChildElement("name");
	assert(name);
	tinyxml2::XMLElement *type = trk->FirstChildElement("type");
	assert(type);
	tinyxml2::XMLElement *trkseg = trk->FirstChildElement("trkseg");
	assert(trkseg);

	tinyxml2::XMLElement *runTrkseg = trkseg;


	vector<double> runLat, runLon;
	vector<string> runEle, runTimes;

	for (tinyxml2::XMLElement *trkpt = trkseg->FirstChildElement("trkpt"); trkpt; trkpt = trkpt->NextSiblingElement("trkpt"))
	{
		double lat,lon;
		res = trkpt->QueryDoubleAttribute("lat", &lat);
		assert(res == tinyxml2::XML_SUCCESS);
		res = trkpt->QueryDoubleAttribute("lon", &lon);
		assert(res == tinyxml2::XML_SUCCESS);
//cout << lat << " " << lon << endl;

		runLat.push_back(lat);
		runLon.push_back(lon);


		tinyxml2::XMLElement *ele = trkpt->FirstChildElement("ele");
		assert(ele);
		string elePt(ele->GetText());

		tinyxml2::XMLElement *timePt = trkpt->FirstChildElement("time");
		assert(timePt);
		string timeStr(timePt->GetText());

//cout << elePt << " " << timeStr << endl;

		runEle.push_back(elePt);
		runTimes.push_back(timeStr);

	}


	tinyxml2::XMLDocument doc;
	res = doc.LoadFile("/home/daren/Downloads/Hill_Run.gpx");
	assert(res == tinyxml2::XML_SUCCESS);

	gpx = doc.FirstChildElement("gpx");
	assert(gpx);
	trk = gpx->FirstChildElement("trk");
	assert(trk);
	trkseg = trk->FirstChildElement("trkseg");
	assert(trkseg);

	vector<double> routeLat, routeLon;
	vector<string> routeEle, routeTimes;

	for(tinyxml2::XMLElement *trkpt = trkseg->FirstChildElement("trkpt"); trkpt; trkpt = trkpt->NextSiblingElement("trkpt"))
    {
        double lat,lon;
        res = trkpt->QueryDoubleAttribute("lat", &lat);
        assert(res == tinyxml2::XML_SUCCESS);
        res = trkpt->QueryDoubleAttribute("lon", &lon);
        assert(res == tinyxml2::XML_SUCCESS);
//cout << lat << " " << lon << endl;

        routeLat.push_back(lat);
        routeLon.push_back(lon);


        tinyxml2::XMLElement *ele = trkpt->FirstChildElement("ele");
        assert(ele);
		string elePt(ele->GetText());
		
/*
        tinyxml2::XMLElement *timePt = trkpt->FirstChildElement("time");
        assert(timePt);
        string timeStr(timePt->GetText());
*/
//cout << elePt << endl;

        routeEle.push_back(elePt);

    }

	
	int runIdx=0;


	double CLOSE_ENOUGH = .0001;

	
	vector<int> interpRouteIdx;



	for(int routeIdx=0; routeIdx<routeLat.size(); ++routeIdx) {
		int startingIdx=runIdx;
		double startingDistSq = distSq(runLat[runIdx], runLon[runIdx], routeLat[routeIdx], routeLon[routeIdx]);

		int closestIdx = startingIdx;
		double closestDistSq = startingDistSq;

		for(int idx = startingIdx+1; idx<runLat.size(); ++idx) {
			double tmpDistSq = distSq(runLat[idx], runLon[idx], routeLat[routeIdx], routeLon[routeIdx]);

			if(tmpDistSq > 2*startingDistSq)
				break;
			
			
			if(tmpDistSq < closestDistSq) {
				closestIdx = idx;
				closestDistSq = tmpDistSq;
			}
		}

		routeTimes.push_back(runTimes[closestIdx]);

		runIdx = closestIdx;

//cout << routeLat[routeIdx] << " " << routeLon[routeIdx] << " " << routeEle[routeIdx] << " " << routeTimes[routeIdx] << endl;
	}

	runTrkseg->DeleteChildren();

	for(int i=0; i<routeLat.size(); ++i) {
		tinyxml2::XMLElement *runTrkpt = runDoc.NewElement("trkpt");
		runTrkpt->SetAttribute("lat", routeLat[i]);
		runTrkpt->SetAttribute("lon", routeLon[i]);
		tinyxml2::XMLElement *runEle = runDoc.NewElement("ele");
		runEle->SetText(routeEle[i].c_str());
		tinyxml2::XMLElement *runTime = runDoc.NewElement("time");
		runTime->SetText(routeTimes[i].c_str());
		runTrkpt->InsertEndChild(runEle);
		runTrkpt->InsertEndChild(runTime);
		runTrkseg->InsertEndChild(runTrkpt);
	}

	tinyxml2::XMLPrinter printer;
	runDoc.Print(&printer);
	cout << printer.CStr() << endl;



	int a = 1;
	return a;
}
