/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SimulationReporterDefaultImpl1.cpp
 * Author: rafael.luiz.cancian
 * 
 * Created on 8 de Agosto de 2018, 10:59
 */

#include "SimulationReporterDefaultImpl1.h"
#include <assert.h>
#include <iomanip>
#include <iostream>

SimulationReporterDefaultImpl1::SimulationReporterDefaultImpl1(ModelSimulation* simulation, Model* model, List<ModelElement*>* statsCountersSimulation) {
    _simulation = simulation;
    _model = model;
    _statsCountersSimulation = statsCountersSimulation;
}

SimulationReporterDefaultImpl1::SimulationReporterDefaultImpl1(const SimulationReporterDefaultImpl1& orig) {
}

SimulationReporterDefaultImpl1::~SimulationReporterDefaultImpl1() {
}

void SimulationReporterDefaultImpl1::showReplicationStatistics() {
    _model->getTraceManager()->traceReport(Util::TraceLevel::report, "");
    _model->getTraceManager()->traceReport(Util::TraceLevel::report, "Begin of Report for replication " + std::to_string(_simulation->getCurrentReplicationNumber()) + " of " + std::to_string(_model->getInfos()->getNumberOfReplications()));
    const std::string UtilTypeOfStatisticsCollector = Util::TypeOf<StatisticsCollector>();
    const std::string UtilTypeOfCounter = Util::TypeOf<Counter>();
    // runs over all elements and list the statistics for each one, and then the statistics with no parent
    Util::IncIndent();
    // copy the ist of statistics and counters into a single new list
    std::list<ModelElement*>* statisticsAndCounters = new std::list<ModelElement*>(*(_model->getElementManager()->getElements(UtilTypeOfStatisticsCollector)->getList()));
    std::list<ModelElement*>* counters = new std::list<ModelElement*>(*(_model->getElementManager()->getElements(UtilTypeOfCounter)->getList()));
    statisticsAndCounters->merge(*counters);
    // organizes statistics into a map of maps
    std::map< std::string, std::map<std::string, std::list<ModelElement*>*>* >* mapMapTypeStat = new std::map<std::string, std::map<std::string, std::list<ModelElement*>*>*>();

    for (std::list<ModelElement*>::iterator it = statisticsAndCounters->begin(); it != statisticsAndCounters->end(); it++) {
	std::string parentName, parentTypename;
	ModelElement* statOrCnt = (*it);
	//std::cout << statOrCnt->getName() << ": " << statOrCnt->getTypename() << std::endl;
	if ((*it)->getTypename() == UtilTypeOfStatisticsCollector) {
	    StatisticsCollector* stat = dynamic_cast<StatisticsCollector*> (statOrCnt);
	    parentName = stat->getParent()->getName();
	    parentTypename = stat->getParent()->getTypename();
	} else {
	    if ((*it)->getTypename() == UtilTypeOfCounter) {
		Counter* cnt = dynamic_cast<Counter*> (statOrCnt);
		parentName = cnt->getParent()->getName();
		parentTypename = cnt->getParent()->getTypename();

	    }
	}
	// look for key=parentTypename
	std::map<std::string, std::map<std::string, std::list<ModelElement*>*>*>::iterator mapMapIt = mapMapTypeStat->find(parentTypename);
	if (mapMapIt == mapMapTypeStat->end()) { // parentTypename does not exists in map. Include it.
	    std::pair< std::string, std::map<std::string, std::list<ModelElement*>*>* >* newPair = new std::pair<std::string, std::map<std::string, std::list<ModelElement*>*>*>(parentTypename, new std::map<std::string, std::list<ModelElement*>*>());
	    mapMapTypeStat->insert(*newPair);
	    mapMapIt = mapMapTypeStat->find(parentTypename); // find again. Now it will.
	}
	//assert(mapMapIt != mapMapTypeStat->end());
	std::map<std::string, std::list<ModelElement*>*>* mapTypeStat = (*mapMapIt).second;
	assert(mapTypeStat != nullptr);
	// look for key=parentName
	std::map<std::string, std::list<ModelElement*>*>::iterator mapIt = mapTypeStat->find(parentName);
	if (mapIt == mapTypeStat->end()) { // parentTypename does not exists in map. Include it.
	    std::pair< std::string, std::list<ModelElement*>* >* newPair = new std::pair<std::string, std::list<ModelElement*>*>(parentName, new std::list<ModelElement*>());
	    mapTypeStat->insert(*newPair);
	    mapIt = mapTypeStat->find(parentName); // find again. Now it will.
	}
	// get the list and insert the stat in that list
	std::list<ModelElement*>* listStatAndCount = (*mapIt).second;
	assert(listStatAndCount != nullptr);
	listStatAndCount->insert(listStatAndCount->end(), statOrCnt);
	//_model->getTraceManager()->traceReport(Util::TraceLevel::report, parentTypename + " -> " + parentName + " -> " + stat->show());
    }
    // now runs over that map of maps showing the statistics
    for (auto const mapmapItem : *mapMapTypeStat) {
	_model->getTraceManager()->traceReport(Util::TraceLevel::report, "Statistis for " + mapmapItem.first + ":");
	Util::IncIndent();
	{
	    for (auto const mapItem : *(mapmapItem.second)) {
		_model->getTraceManager()->traceReport(Util::TraceLevel::report, mapItem.first + ":");
		Util::IncIndent();
		{
		    _model->getTraceManager()->traceReport(Util::TraceLevel::report, Util::SetW("name", _nameW) +
			    Util::SetW("elems", _w) + Util::SetW("min", _w) + Util::SetW("max", _w) + Util::SetW("average", _w) + Util::SetW("variance", _w) + Util::SetW("stddev", _w) + Util::SetW("varCoef", _w) + Util::SetW("confInterv", _w) + Util::SetW("confLevel", _w));
		    for (ModelElement * const item : *(mapItem.second)) {
			if (item->getTypename() == UtilTypeOfStatisticsCollector) {
			    Statistics_if* stat = dynamic_cast<StatisticsCollector*> (item)->getStatistics();
			    _model->getTraceManager()->traceReport(Util::TraceLevel::report,
				    Util::SetW(item->getName() + std::string(_nameW, '.'), _nameW - 1) + " " +
				    Util::SetW(std::to_string(stat->numElements()), _w) +
				    Util::SetW(std::to_string(stat->min()), _w) +
				    Util::SetW(std::to_string(stat->max()), _w) +
				    Util::SetW(std::to_string(stat->average()), _w) +
				    Util::SetW(std::to_string(stat->variance()), _w) +
				    Util::SetW(std::to_string(stat->stddeviation()), _w) +
				    Util::SetW(std::to_string(stat->variationCoef()), _w) +
				    Util::SetW(std::to_string(stat->halfWidthConfidenceInterval()), _w) +
				    Util::SetW(std::to_string(stat->getConfidenceLevel()), _w)
				    );
			} else {
			    if (item->getTypename() == UtilTypeOfCounter) {
				Counter* count = dynamic_cast<Counter*> (item);
				_model->getTraceManager()->traceReport(Util::TraceLevel::report,
					Util::SetW(count->getName() + std::string(_nameW, '.'), _nameW - 1) + " " +
					Util::SetW(std::to_string(count->getCountValue()), _w)
					);
			    }
			}
		    }
		}
		Util::DecIndent();
	    }
	}
	Util::DecIndent();
    }

    Util::DecIndent();
    _model->getTraceManager()->traceReport(Util::TraceLevel::report, "End of Report for replication " + std::to_string(_simulation->getCurrentReplicationNumber()) + " of " + std::to_string(_model->getInfos()->getNumberOfReplications()));
    _model->getTraceManager()->traceReport(Util::TraceLevel::report, "------------------------------");
}

void SimulationReporterDefaultImpl1::showSimulationStatistics() {//List<StatisticsCollector*>* cstatsSimulation) {
    _model->getTraceManager()->traceReport(Util::TraceLevel::report, "");
    _model->getTraceManager()->traceReport(Util::TraceLevel::report, "Begin of Report for Simulation (based on " + std::to_string(_model->getInfos()->getNumberOfReplications()) + " replications)");
    const std::string UtilTypeOfStatisticsCollector = Util::TypeOf<StatisticsCollector>();
    const std::string UtilTypeOfCounter = Util::TypeOf<Counter>();
    // runs over all elements and list the statistics for each one, and then the statistics with no parent
    Util::IncIndent();
    // COPY the list of statistics and counters into a single new list
    //std::list<ModelElement*>* statisticsAndCounters = //new std::list<ModelElement*>(*(this->_statsCountersSimulation->getList()));
    // organizes statistics into a map of maps
    std::map< std::string, std::map<std::string, std::list<ModelElement*>*>* >* mapMapTypeStat = new std::map<std::string, std::map<std::string, std::list<ModelElement*>*>*>();

    for (std::list<ModelElement*>::iterator it = _statsCountersSimulation->getList()->begin(); it != _statsCountersSimulation->getList()->end(); it++) {
	std::string parentName, parentTypename;
	ModelElement* statOrCnt = (*it);
	//std::cout << statOrCnt->getName() << ": " << statOrCnt->getTypename() << std::endl;
	if ((*it)->getTypename() == UtilTypeOfStatisticsCollector) {
	    StatisticsCollector* stat = dynamic_cast<StatisticsCollector*> (statOrCnt);
	    parentName = stat->getParent()->getName();
	    parentTypename = stat->getParent()->getTypename();
	} else {
	    if ((*it)->getTypename() == UtilTypeOfCounter) {
		Counter* cnt = dynamic_cast<Counter*> (statOrCnt);
		parentName = cnt->getParent()->getName();
		parentTypename = cnt->getParent()->getTypename();

	    }
	}
	// look for key=parentTypename
	std::map<std::string, std::map<std::string, std::list<ModelElement*>*>*>::iterator mapMapIt = mapMapTypeStat->find(parentTypename);
	if (mapMapIt == mapMapTypeStat->end()) { // parentTypename does not exists in map. Include it.
	    std::pair< std::string, std::map<std::string, std::list<ModelElement*>*>* >* newPair = new std::pair<std::string, std::map<std::string, std::list<ModelElement*>*>*>(parentTypename, new std::map<std::string, std::list<ModelElement*>*>());
	    mapMapTypeStat->insert(*newPair);
	    mapMapIt = mapMapTypeStat->find(parentTypename); // find again. Now it will.
	}
	assert(mapMapIt != mapMapTypeStat->end());
	std::map<std::string, std::list<ModelElement*>*>* mapTypeStat = (*mapMapIt).second;
	assert(mapTypeStat != nullptr);
	// look for key=parentName
	std::map<std::string, std::list<ModelElement*>*>::iterator mapIt = mapTypeStat->find(parentName);
	if (mapIt == mapTypeStat->end()) { // parentTypename does not exists in map. Include it.
	    std::pair< std::string, std::list<ModelElement*>* >* newPair = new std::pair<std::string, std::list<ModelElement*>*>(parentName, new std::list<ModelElement*>());
	    mapTypeStat->insert(*newPair);
	    mapIt = mapTypeStat->find(parentName); // find again. Now it will.
	}
	// get the list and insert the stat in that list
	std::list<ModelElement*>* listStat = (*mapIt).second;
	listStat->insert(listStat->end(), statOrCnt);
	//_model->getTraceManager()->traceReport(Util::TraceLevel::report, parentTypename + " -> " + parentName + " -> " + stat->show());
    }
    // now runs over that map of maps showing the statistics
    //int w = 12;
    for (auto const mapmapItem : *mapMapTypeStat) {
	_model->getTraceManager()->traceReport(Util::TraceLevel::report, "Statistis for " + mapmapItem.first + ":");
	Util::IncIndent();
	{
	    for (auto const mapItem : *(mapmapItem.second)) {
		_model->getTraceManager()->traceReport(Util::TraceLevel::report, mapItem.first + ":");
		Util::IncIndent();
		{
		    _model->getTraceManager()->traceReport(Util::TraceLevel::report, Util::SetW("name", _nameW) +
			    Util::SetW("elems", _w) + Util::SetW("min", _w) + Util::SetW("max", _w) + Util::SetW("average", _w) + Util::SetW("variance", _w) + Util::SetW("stddev", _w) + Util::SetW("varCoef", _w) + Util::SetW("confInterv", _w) + Util::SetW("confLevel", _w));
		    for (ModelElement * const item : *(mapItem.second)) {
			if (item->getTypename() == UtilTypeOfStatisticsCollector) {
			    Statistics_if* stat = dynamic_cast<StatisticsCollector*> (item)->getStatistics();
			    _model->getTraceManager()->traceReport(Util::TraceLevel::report,
				    Util::SetW(item->getName() + std::string(_nameW, '.'), _nameW - 1) + " " +
				    Util::SetW(std::to_string(stat->numElements()), _w) +
				    Util::SetW(std::to_string(stat->min()), _w) +
				    Util::SetW(std::to_string(stat->max()), _w) +
				    Util::SetW(std::to_string(stat->average()), _w) +
				    Util::SetW(std::to_string(stat->variance()), _w) +
				    Util::SetW(std::to_string(stat->stddeviation()), _w) +
				    Util::SetW(std::to_string(stat->variationCoef()), _w) +
				    Util::SetW(std::to_string(stat->halfWidthConfidenceInterval()), _w) +
				    Util::SetW(std::to_string(stat->getConfidenceLevel()), _w)
				    );
			} else {
			    if (item->getTypename() == UtilTypeOfCounter) {
				Counter* cnt = dynamic_cast<Counter*> (item);
				_model->getTraceManager()->traceReport(Util::TraceLevel::report,
					Util::SetW(cnt->getName() + std::string(_nameW, '.'), _nameW - 1) + " " +
					Util::SetW(std::to_string(cnt->getCountValue()), _w)
					);

			    }
			}
		    }
		}
		Util::DecIndent();
	    }
	}
	Util::DecIndent();
    }

    Util::DecIndent();
    _model->getTraceManager()->traceReport(Util::TraceLevel::report, "End of Report for Simulation");
}
