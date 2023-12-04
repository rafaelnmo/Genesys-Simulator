#include "Smart_EFSM1.h"
#include <map>

// you have to included need libs

// GEnSyS Simulator
#include "../../../../kernel/simulator/EntityType.h"
#include "../../../../kernel/simulator/ModelSimulation.h"
#include "../../../../kernel/simulator/Simulator.h"

// Model Components
#include "../../../../plugins/components/Create.h"
#include "../../../../plugins/components/Dispose.h"
#include "../../../../plugins/components/Assign.h"
#include "../../../../plugins/data/Variable.h"
#include "../../../../plugins/data/EFSM.h"
#include "../../../../plugins/components/FSM_State.h"
#include "../../../../plugins/components/FSM_Transition.h"
#include "../../../../plugins/components/FSM_Variable.h"
#include "../../../../plugins/components/FSM_State.h"
#include "../../../../plugins/components/FSM_ModalModel.h"
#include "../../../../plugins/components/Delay.h"




//#include "../../../../plugins/components/FiniteStateMachine.h"
#include "../../../TraitsApp.h"


Smart_EFSM1::Smart_EFSM1() {
}

/**
 * This is the main function of the application. 
 * It instanciates the simulator, builds a simulation model and then simulate that model.
 */
int Smart_EFSM1::main(int argc, char** argv) {
	// instantiate simulator
	Simulator* genesys = new Simulator();
	genesys->getTracer()->setTraceLevel(TraitsApp<GenesysApplication_if>::traceLevel);
	setDefaultTraceHandlers(genesys->getTracer());
    PluginManager* plugins = genesys->getPlugins();
    plugins->autoInsertPlugins("/mnt/HD_EXTERNO/computerScience/course/14ºFASE/modSim/new/Genesys-Simulator/autoloadplugins.txt");

	// create model
	Model* model = genesys->getModels()->newModel();

    EntityType* entityType = new EntityType(model, "Person");
    Create* create1 = plugins->newInstance<Create>(model);
    create1->setDescription("Enter Garage");
    create1->setEntityType(entityType);
    create1->setTimeBetweenCreationsExpression("EXPO(5)");
    create1->setTimeUnit(Util::TimeUnit::minute);

    Assign* assign1 = new Assign(model);
    assign1->setDescription("Verify if has car");
    Assignment* assigment1 = new Assignment("hasCar", "1");
    assign1->getAssignments()->insert(assigment1);
    create1->getConnections()->insert(assign1);

	Delay* delay1 = plugins->newInstance<Delay>(model); // the default delay time is 1.0 s
    delay1->setDescription("Browse");
    delay1->setDelayExpression("tria(3, 7, 11)");
    delay1->setDelayTimeUnit(Util::TimeUnit::minute);
    assign1->getConnections()->insert(delay1);

	Variable* var1 = plugins->newInstance<Variable>(model, "carsParked");
	var1->setInitialValue(10.0, "carsParked"); 

	Variable* var2 = plugins->newInstance<Variable>(model, "maxCarsParked");
	var2->setInitialValue(20.0, "maxCarsParked"); 

    ExtendedFSM* efsm1 = plugins->newInstance<ExtendedFSM>(model, "efsm_1");
    efsm1->insertVariable(var1);
    efsm1->insertVariable(var2);
    
    efsm1->CreateInternalData(efsm1);   
    FSM_State* state1 = plugins->newInstance<FSM_State>(model, "state_1");

    FSM_Transition* transition1 = plugins->newInstance<FSM_Transition>(model, "transition_1");
    transition1->setGuardExpression("hasCar = 1 & carsParked < maxCarsParked");
    //transition1->setOriginState("Counting");
    //transition1->setDestinationState("Counting");
    transition1->setOutputActions("hasCar = 0");
    transition1->setSetActions("carsParked = carsParked + 1");
    efsm1->insertTransition(transition1);
    state1->getConnections()->insert(transition1);
    transition1->getConnections()->insert(state1);

    FSM_Transition* transition2 = plugins->newInstance<FSM_Transition>(model,"transition_2");
    transition2->setGuardExpression("hasCar = 0 & carsParked > 0");
    //transition2->setOriginState("Counting");
    //transition2->setDestinationState("Counting");
    transition2->setOutputActions("hasCar = 1");
    transition2->setSetActions("carsParked = carsParked - 1");
    efsm1->insertTransition(transition2);
    state1->getConnections()->insert(transition2);
    transition2->getConnections()->insert(state1);

    FSM_Transition* transition3 = plugins->newInstance<FSM_Transition>(model,"transition_3");
    transition3->setGuardExpression("");
    //transition3->setOriginState("Counting");
    //transition3->setDestinationState("Counting");
    transition3->setOutputActions("");
    transition3->setSetActions("");
    transition3->setDefault(true);
    efsm1->insertTransition(transition3);
    state1->getConnections()->insert(transition3);
    transition3->getConnections()->insert(state1);

    FSM_ModalModel* modalmodel1 = plugins->newInstance<FSM_ModalModel>(model, "modalmodel_1");
    modalmodel1->setEFSMData(efsm1);
    delay1->getConnections()->insert(modalmodel1);

    Dispose* dispose1 = plugins->newInstance<Dispose>(model);
    dispose1->setReportStatistics(true);
    modalmodel1->getConnections()->insert(dispose1);
	
    // set options, save and simulate
	model->getSimulation()->setNumberOfReplications(3);
	model->getSimulation()->setReplicationLength(20, Util::TimeUnit::minute);
	model->getSimulation()->setTerminatingCondition("");
	model->getSimulation()->setReplicationReportBaseTimeUnit(Util::TimeUnit::hour);
    model->save("./models/Smart_EFSM1.gen");
	model->getSimulation()->start();	
	// free memory
	delete genesys;
	
	return 0;
};
