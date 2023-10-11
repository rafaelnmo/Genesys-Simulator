QT += core gui
QT += printsupport
QT += designer
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
CONFIG += c++14

QMAKE_CXXFLAGS += -pedantic -Wno-unused -Wmissing-field-initializers

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
	../../../../kernel/simulator/Attribute.cpp \
	../../../../kernel/simulator/ComponentManager.cpp \
	../../../../kernel/simulator/ConnectionManager.cpp \
	../../../../kernel/simulator/Counter.cpp \
	../../../../kernel/simulator/CppSerializer.cpp \
	../../../../kernel/simulator/Entity.cpp \
	../../../../kernel/simulator/EntityType.cpp \
	../../../../kernel/simulator/Event.cpp \
	../../../../kernel/simulator/ExperimentManager.cpp \
	../../../../kernel/simulator/ExperimentManagerDefaultImpl1.cpp \
	../../../../kernel/simulator/GenSerializer.cpp \
	../../../../kernel/simulator/JsonSerializer.cpp \
	../../../../kernel/simulator/LicenceManager.cpp \
	../../../../kernel/simulator/Model.cpp \
	../../../../kernel/simulator/ModelCheckerDefaultImpl1.cpp \
	../../../../kernel/simulator/ModelComponent.cpp \
	../../../../kernel/simulator/ModelDataDefinition.cpp \
	../../../../kernel/simulator/ModelDataManager.cpp \
	../../../../kernel/simulator/ModelInfo.cpp \
	../../../../kernel/simulator/ModelManager.cpp \
	../../../../kernel/simulator/ModelPersistenceDefaultImpl2.cpp \
	../../../../kernel/simulator/ModelSerializer.cpp \
	../../../../kernel/simulator/ModelSimulation.cpp \
	../../../../kernel/simulator/OnEventManager.cpp \
	../../../../kernel/simulator/ParserChangesInformation.cpp \
	../../../../kernel/simulator/ParserDefaultImpl1.cpp \
	../../../../kernel/simulator/ParserDefaultImpl2.cpp \
	../../../../kernel/simulator/ParserManager.cpp \
	../../../../kernel/simulator/Persistence.cpp \
	../../../../kernel/simulator/Plugin.cpp \
	../../../../kernel/simulator/PluginConnectorDummyImpl1.cpp \
	../../../../kernel/simulator/PluginInformation.cpp \
	../../../../kernel/simulator/PluginManager.cpp \
	../../../../kernel/simulator/SimulationExperiment.cpp \
	../../../../kernel/simulator/SimulationReporterDefaultImpl1.cpp \
	../../../../kernel/simulator/SimulationScenario.cpp \
	../../../../kernel/simulator/Simulator.cpp \
	../../../../kernel/simulator/SinkModelComponent.cpp \
	../../../../kernel/simulator/SourceModelComponent.cpp \
	../../../../kernel/simulator/StatisticsCollector.cpp \
	../../../../kernel/simulator/TraceManager.cpp \
	../../../../kernel/simulator/XmlSerializer.cpp \
	../../../../kernel/statistics/CollectorDatafileDefaultImpl1.cpp \
	../../../../kernel/statistics/CollectorDefaultImpl1.cpp \
	../../../../kernel/statistics/SamplerBoostImpl.cpp \
	../../../../kernel/statistics/SamplerDefaultImpl1.cpp \
	../../../../kernel/statistics/SorttFile.cpp \
	../../../../kernel/statistics/StatisticsDataFileDefaultImpl.cpp \
	../../../../kernel/statistics/StatisticsDefaultImpl1.cpp \
	../../../../kernel/util/Util.cpp \
	../../../../parser/Genesys++-driver.cpp \
	../../../../parser/Genesys++-scanner.cpp \
	../../../../parser/GenesysParser.cpp \
	../../../../parser/obj_t.cpp \
	../../../../plugins/components/Access.cpp \
	../../../../plugins/components/Assign.cpp \
	../../../../plugins/components/Batch.cpp \
	../../../../plugins/components/Buffer.cpp \
	../../../../plugins/components/CellularAutomata.cpp \
	../../../../plugins/components/Clone.cpp \
	../../../../plugins/components/CppForG.cpp \
	../../../../plugins/components/Create.cpp \
	../../../../plugins/components/Decide.cpp \
	../../../../plugins/components/Delay.cpp \
	../../../../plugins/components/DiffEquations.cpp \
	../../../../plugins/components/Dispose.cpp \
	../../../../plugins/components/DropOff.cpp \
	../../../../plugins/components/DummyComponent.cpp \
	../../../../plugins/components/Enter.cpp \
	../../../../plugins/components/Exit.cpp \
	../../../../plugins/components/FiniteStateMachine.cpp \
    ../../../../plugins/components/ExtendedFinishStateMachine.cpp \
	../../../../plugins/components/PickableStationItem.cpp \
	../../../../plugins/components/Wait.cpp \
	../../../../plugins/components/LSODE.cpp \
	../../../../plugins/components/Leave.cpp \
	../../../../plugins/components/MarkovChain.cpp \
	../../../../plugins/components/Match.cpp \
	../../../../plugins/components/OLD_ODEelement.cpp \
	../../../../plugins/components/PickStation.cpp \
	../../../../plugins/components/PickUp.cpp \
	../../../../plugins/components/Process.cpp \
	../../../../plugins/components/QueueableItem.cpp \
	../../../../plugins/components/Record.cpp \
	../../../../plugins/components/Release.cpp \
	../../../../plugins/components/Remove.cpp \
	../../../../plugins/components/Route.cpp \
	../../../../plugins/components/Search.cpp \
	../../../../plugins/components/SeizableItem.cpp \
	../../../../plugins/components/Seize.cpp \
	../../../../plugins/components/Separate.cpp \
	../../../../plugins/components/Signal.cpp \
	../../../../plugins/components/Start.cpp \
	../../../../plugins/components/Stop.cpp \
	../../../../plugins/components/Store.cpp \
	../../../../plugins/components/Submodel.cpp \
	../../../../plugins/components/Unstore.cpp \
	../../../../plugins/components/Write.cpp \
	../../../../plugins/data/AssignmentItem.cpp \
	../../../../plugins/data/CppCompiler.cpp \
	../../../../plugins/data/DummyElement.cpp \
	../../../../plugins/data/EFSM.cpp \
	../../../../plugins/data/EntityGroup.cpp \
	../../../../plugins/data/Failure.cpp \
	../../../../plugins/data/File.cpp \
	../../../../plugins/data/Formula.cpp \
	../../../../plugins/data/Label.cpp \
	../../../../plugins/data/Queue.cpp \
	../../../../plugins/data/Resource.cpp \
	../../../../plugins/data/Schedule.cpp \
	../../../../plugins/data/Sequence.cpp \
	../../../../plugins/data/Set.cpp \
	../../../../plugins/data/SignalData.cpp \
	../../../../plugins/data/Station.cpp \
	../../../../plugins/data/Storage.cpp \
	../../../../plugins/data/Variable.cpp \
	../../../../tools/FitterDummyImpl.cpp \
	../../../../tools/HypothesisTesterDefaultImpl1.cpp \
	../../../../tools/ProbabilityDistribution.cpp \
	../../../../tools/ProbabilityDistributionBase.cpp \
	../../../../tools/SolverDefaultImpl1.cpp \
	../../../BaseGenesysTerminalApplication.cpp \
	../../../terminal/GenesysShell/GenesysShell.cpp \
	../../../terminal/examples/arenaExamples/AirportSecurityExample.cpp \
	../../../terminal/examples/arenaExamples/AirportSecurityExampleExtended.cpp \
	../../../terminal/examples/arenaExamples/Airport_Extended1.cpp \
	../../../terminal/examples/arenaExamples/Assembly_Line.cpp \
	../../../terminal/examples/arenaExamples/Banking_Transactions.cpp \
	../../../terminal/examples/arenaExamples/Example_BasicOrderShipping.cpp \
	../../../terminal/examples/arenaExamples/Example_PortModel.cpp \
	../../../terminal/examples/arenaExamples/Example_PublicTransport.cpp \
	../../../terminal/examples/arenaSmarts/Smart_AddingResource.cpp \
	../../../terminal/examples/arenaSmarts/Smart_AlternatingEntityCreation.cpp \
	../../../terminal/examples/arenaSmarts/Smart_ArrivalsElementStopsEntitiesArrivingAfterASetTime.cpp \
	../../../terminal/examples/arenaSmarts/Smart_ArrivalsEntityTypeVsAttribute.cpp \
	../../../terminal/examples/arenaSmarts/Smart_AssignExample.cpp \
	../../../terminal/examples/arenaSmarts/Smart_AutomaticStatisticsCollection.cpp \
	../../../terminal/examples/arenaSmarts/Smart_BasicModeling.cpp \
	../../../terminal/examples/arenaSmarts/Smart_BatchAndSeparate.cpp \
	../../../terminal/examples/arenaSmarts/Smart_ContinuousFlowEntities.cpp \
	../../../terminal/examples/arenaSmarts/Smart_Create.cpp \
	../../../terminal/examples/arenaSmarts/Smart_DecideNWayByChance.cpp \
	../../../terminal/examples/arenaSmarts/Smart_DefiningAttributesAsStrings.cpp \
	../../../terminal/examples/arenaSmarts/Smart_DefiningControlLogic.cpp \
	../../../terminal/examples/arenaSmarts/Smart_DefiningResourceCapacity.cpp \
	../../../terminal/examples/arenaSmarts/Smart_DelayBasedOnReplication.cpp \
	../../../terminal/examples/arenaSmarts/Smart_EntitiesProcessedByPriority.cpp \
	../../../terminal/examples/arenaSmarts/Smart_EvaluatingConditionsBeforeEnteringQueue.cpp \
	../../../terminal/examples/arenaSmarts/Smart_Expression.cpp \
	../../../terminal/examples/arenaSmarts/Smart_InventoryAndHoldingCosts.cpp \
	../../../terminal/examples/arenaSmarts/Smart_MaxArrivalsField.cpp \
	../../../terminal/examples/arenaSmarts/Smart_ModelRunUntil1000Parts.cpp \
	../../../terminal/examples/arenaSmarts/Smart_ModuleDisplayVariables.cpp \
	../../../terminal/examples/arenaSmarts/Smart_OverlappingResources.cpp \
	../../../terminal/examples/arenaSmarts/Smart_ParallelProcessingOfEntities.cpp \
	../../../terminal/examples/arenaSmarts/Smart_PlacingEntitiesInQueueSets.cpp \
	../../../terminal/examples/arenaSmarts/Smart_PriorityExample.cpp \
	../../../terminal/examples/arenaSmarts/Smart_ProcessArena.cpp \
	../../../terminal/examples/arenaSmarts/Smart_Record_Arena.cpp \
	../../../terminal/examples/arenaSmarts/Smart_RemovingAndReorderingEntitiesInAQueue.cpp \
	../../../terminal/examples/arenaSmarts/Smart_ResourceCosting.cpp \
	../../../terminal/examples/arenaSmarts/Smart_ResourceScheduleCosting.cpp \
	../../../terminal/examples/arenaSmarts/Smart_ResourceSets.cpp \
	../../../terminal/examples/arenaSmarts/Smart_SeizingMultipleSimultaneosly.cpp \
	../../../terminal/examples/arenaSmarts/Smart_SelectingRouteBasedOnProbability.cpp \
	../../../terminal/examples/arenaSmarts/Smart_SelectingShorterQueue.cpp \
	../../../terminal/examples/arenaSmarts/Smart_SynchronizingParallelEntities.cpp \
	../../../terminal/examples/arenaSmarts/Smart_ValueAdded.cpp \
	../../../terminal/examples/arenaSmarts/Smart_WaitForSignal.cpp \
	../../../terminal/examples/book/Book_Cap02_Example01.cpp \
	../../../terminal/examples/smarts/Smart_AssignWriteSeizes.cpp \
	../../../terminal/examples/smarts/Smart_BatchSeparate.cpp \
	../../../terminal/examples/smarts/Smart_Buffer.cpp \
    ../../../terminal/examples/smarts/Smart_ExtendedFSM.cpp \
    ../../../terminal/examples/smarts/Smart_FiniteStateMachine.cpp \
	../../../terminal/examples/smarts/Smart_CellularAutomata1.cpp \
	../../../terminal/examples/smarts/Smart_CppForG.cpp \
	../../../terminal/examples/smarts/Smart_Delay.cpp \
	../../../terminal/examples/smarts/Smart_Dummy.cpp \
	../../../terminal/examples/smarts/Smart_Failures.cpp \
	../../../terminal/examples/smarts/Smart_LSODE.cpp \
	../../../terminal/examples/smarts/Smart_Record.cpp \
    ../../../terminal/examples/smarts/Smart_SimulationControlResponse.cpp \
	../../../terminal/examples/smarts/Smart_WaitScanCondition.cpp \
	../../../terminal/examples/smarts/Smart_WaitSignal.cpp \
	../../../terminal/examples/smarts/Smart_ModelInfoModelSimulation.cpp \
	../../../terminal/examples/smarts/Smart_OnEvent.cpp \
	../../../terminal/examples/smarts/Smart_Parser.cpp \
	../../../terminal/examples/smarts/Smart_ParserModelFunctions.cpp \
	../../../terminal/examples/smarts/Smart_Plugin.cpp \
	../../../terminal/examples/smarts/Smart_Process.cpp \
	../../../terminal/examples/smarts/Smart_ProcessSet.cpp \
	../../../terminal/examples/smarts/Smart_RouteStation.cpp \
	../../../terminal/examples/smarts/Smart_SeizeDelayRelease.cpp \
	../../../terminal/examples/smarts/Smart_SeizeDelayReleaseMany.cpp \
	../../../terminal/examples/smarts/Smart_Sequence.cpp \
	../../../terminal/examples/teaching/AnElectronicAssemblyAndTestSystem.cpp \
#	../../../terminal/examples/teaching/ContinuousModel.cpp \
	../../../terminal/examples/teaching/FullSimulationOfComplexModel.cpp \
	../../../terminal/examples/teaching/OperatingSystem02.cpp \
	../../../terminal/examples/teaching/OperatingSystem03.cpp \
	../../../terminal/underDevelopment/TestingTerminalApp.cpp \
#	BaseMVController.cpp \
	CodeEditor.cpp \
	ModelGraphicsScene.cpp \
	ModelGraphicsView.cpp \
	ObjectPropertyBrowser.cpp \
	PropertyEditor.cpp \
	dialogs/Dialogmodelinformation.cpp \
	dialogs/dialogBreakpoint.cpp \
	dialogs/dialogpluginmanager.cpp \
	dialogs/dialogsimulationconfigure.cpp \
	dialogs/dialogsystempreferences.cpp \
    QPropertyBrowser/qtbuttonpropertybrowser.cpp \
    QPropertyBrowser/qteditorfactory.cpp \
    QPropertyBrowser/qtgroupboxpropertybrowser.cpp \
    QPropertyBrowser/qtpropertybrowser.cpp \
    QPropertyBrowser/qtpropertybrowserutils.cpp \
    QPropertyBrowser/qtpropertymanager.cpp \
    QPropertyBrowser/qttreepropertybrowser.cpp \
    QPropertyBrowser/qtvariantproperty.cpp \
	graphicals/GraphicalAnimateExpression.cpp \
	graphicals/GraphicalAssociation.cpp \
	graphicals/GraphicalComponentPort.cpp \
	graphicals/GraphicalConnection.cpp \
	graphicals/GraphicalModelComponent.cpp \
	graphicals/GraphicalModelDataDefinition.cpp \
	main.cpp \
	mainwindow.cpp \
	qcustomplot.cpp

HEADERS += \
	../../../../kernel/TraitsKernel.h \
	../../../../kernel/simulator/Attribute.h \
	../../../../kernel/simulator/ComponentManager.h \
	../../../../kernel/simulator/ConnectionManager.h \
	../../../../kernel/simulator/Counter.h \
	../../../../kernel/simulator/CppSerializer.h \
	../../../../kernel/simulator/DefineGetterSetter.h \
	../../../../kernel/simulator/Entity.h \
	../../../../kernel/simulator/EntityType.h \
	../../../../kernel/simulator/Event.h \
	../../../../kernel/simulator/ExperimentManager.h \
	../../../../kernel/simulator/ExperimentManagerDefaultImpl1.h \
	../../../../kernel/simulator/ExperimetManager_if.h \
	../../../../kernel/simulator/GenSerializer.h \
	../../../../kernel/simulator/JsonSerializer.h \
	../../../../kernel/simulator/LicenceManager.h \
	../../../../kernel/simulator/Model.h \
	../../../../kernel/simulator/ModelCheckerDefaultImpl1.h \
	../../../../kernel/simulator/ModelChecker_if.h \
	../../../../kernel/simulator/ModelComponent.h \
	../../../../kernel/simulator/ModelDataDefinition.h \
	../../../../kernel/simulator/ModelDataManager.h \
	../../../../kernel/simulator/ModelInfo.h \
	../../../../kernel/simulator/ModelManager.h \
	../../../../kernel/simulator/ModelPersistenceDefaultImpl2.h \
	../../../../kernel/simulator/ModelSerializer.h \
	../../../../kernel/simulator/ModelSimulation.h \
	../../../../kernel/simulator/OnEventManager.h \
	../../../../kernel/simulator/ParserChangesInformation.h \
	../../../../kernel/simulator/ParserDefaultImpl1.h \
	../../../../kernel/simulator/ParserDefaultImpl2.h \
	../../../../kernel/simulator/ParserManager.h \
	../../../../kernel/simulator/Parser_if.h \
	../../../../kernel/simulator/Persistence.h \
	../../../../kernel/simulator/Plugin.h \
	../../../../kernel/simulator/PluginConnectorDummyImpl1.h \
	../../../../kernel/simulator/PluginConnector_if.h \
	../../../../kernel/simulator/PluginInformation.h \
	../../../../kernel/simulator/PluginManager.h \
        ../../../../kernel/simulator/PropertyGenesys.h \
	../../../../kernel/simulator/ScenarioExperiment_if.h \
	../../../../kernel/simulator/SimulationControlAndResponse.h \
	../../../../kernel/simulator/SimulationExperiment.h \
	../../../../kernel/simulator/SimulationReporterDefaultImpl1.h \
	../../../../kernel/simulator/SimulationReporter_if.h \
	../../../../kernel/simulator/SimulationScenario.h \
	../../../../kernel/simulator/Simulator.h \
	../../../../kernel/simulator/SinkModelComponent.h \
	../../../../kernel/simulator/SourceModelComponent.h \
	../../../../kernel/simulator/StatisticsCollector.h \
	../../../../kernel/simulator/TraceManager.h \
	../../../../kernel/simulator/XmlSerializer.h \
	../../../../kernel/statistics/CollectorDatafileDefaultImpl1.h \
	../../../../kernel/statistics/CollectorDatafile_if.h \
	../../../../kernel/statistics/CollectorDefaultImpl1.h \
	../../../../kernel/statistics/Collector_if.h \
	../../../../kernel/statistics/SamplerBoostImpl.h \
	../../../../kernel/statistics/SamplerDefaultImpl1.h \
	../../../../kernel/statistics/Sampler_if.h \
	../../../../kernel/statistics/SorttFile.h \
	../../../../kernel/statistics/StatisticsDataFileDefaultImpl.h \
	../../../../kernel/statistics/StatisticsDataFile_if.h \
	../../../../kernel/statistics/StatisticsDefaultImpl1.h \
	../../../../kernel/statistics/Statistics_if.h \
	../../../../kernel/util/Exact.h \
	../../../../kernel/util/List.h \
	../../../../kernel/util/ListObservable.h \
	../../../../kernel/util/Util.h \
	../../../../parser/Genesys++-driver.h \
	../../../../parser/GenesysParser.h \
	../../../../parser/location.hh \
	../../../../parser/obj_t.h \
	../../../../parser/parserBisonFlex/bisonparser.yy \
	../../../../parser/parserBisonFlex/lexerparser.ll \
	../../../../parser/position.hh \
	../../../../parser/stack.hh \
	../../../../plugins/components/Access.h \
	../../../../plugins/components/Assign.h \
	../../../../plugins/components/Batch.h \
	../../../../plugins/components/Buffer.h \
	../../../../plugins/components/CellularAutomata.h \
	../../../../plugins/components/Clone.h \
	../../../../plugins/components/CppForG.h \
	../../../../plugins/components/Create.h \
	../../../../plugins/components/Decide.h \
	../../../../plugins/components/Delay.h \
	../../../../plugins/components/DiffEquations.h \
	../../../../plugins/components/Dispose.h \
	../../../../plugins/components/DropOff.h \
	../../../../plugins/components/DummyComponent.h \
	../../../../plugins/components/Enter.h \
	../../../../plugins/components/Exit.h \
	../../../../plugins/components/FiniteStateMachine.h \
    ../../../../plugins/components/ExtendedFinishStateMachine.h \
	../../../../plugins/components/PickableStationItem.h \
	../../../../plugins/components/Wait.h \
	../../../../plugins/components/LSODE.h \
	../../../../plugins/components/Leave.h \
	../../../../plugins/components/MarkovChain.h \
	../../../../plugins/components/Match.h \
	../../../../plugins/components/OLD_ODEelement.h \
	../../../../plugins/components/PickStation.h \
	../../../../plugins/components/PickUp.h \
	../../../../plugins/components/Process.h \
	../../../../plugins/components/QueueableItem.h \
	../../../../plugins/components/Record.h \
	../../../../plugins/components/Release.h \
	../../../../plugins/components/Remove.h \
	../../../../plugins/components/Route.h \
	../../../../plugins/components/Search.h \
	../../../../plugins/components/SeizableItem.h \
	../../../../plugins/components/Seize.h \
	../../../../plugins/components/Separate.h \
	../../../../plugins/components/Signal.h \
	../../../../plugins/components/Start.h \
	../../../../plugins/components/Stop.h \
	../../../../plugins/components/Store.h \
	../../../../plugins/components/Submodel.h \
	../../../../plugins/components/Unstore.h \
	../../../../plugins/components/Write.h \
	../../../../plugins/data/AssignmentItem.h \
	../../../../plugins/data/CppCompiler.h \
	../../../../plugins/data/DummyElement.h \
	../../../../plugins/data/EFSM.h \
        ../../../../plugins/data/State.h \
        ../../../../plugins/data/Transition.h \
	../../../../plugins/data/EntityGroup.h \
	../../../../plugins/data/Failure.h \
	../../../../plugins/data/File.h \
	../../../../plugins/data/Formula.h \
	../../../../plugins/data/Label.h \
	../../../../plugins/data/Queue.h \
	../../../../plugins/data/Resource.h \
	../../../../plugins/data/Schedule.h \
	../../../../plugins/data/Sequence.h \
	../../../../plugins/data/Set.h \
	../../../../plugins/data/SignalData.h \
	../../../../plugins/data/Station.h \
	../../../../plugins/data/Storage.h \
	../../../../plugins/data/Variable.h \
	../../../../tools/DataAnalyser_if.h \
	../../../../tools/FitterDummyImpl.h \
	../../../../tools/Fitter_if.h \
	../../../../tools/HypothesisTesterDefaultImpl1.h \
	../../../../tools/HypothesisTester_if.h \
	../../../../tools/ProbabilityDistribution.h \
	../../../../tools/ProbabilityDistributionBase.h \
	../../../../tools/SolverDefaultImpl1.h \
	../../../../tools/Solver_if.h \
	../../../../tools/TraitsTools.h \
	../../../BaseGenesysTerminalApplication.h \
	../../../GenesysApplication_if.h \
	../../../TraitsApp.h \
	../../../terminal/GenesysShell/GenesysShell.h \
	../../../terminal/GenesysShell/GenesysShell_if.h \
#	../../../terminal/TraitsTerminalApp.h \
	../../../terminal/examples/arenaExamples/AirportSecurityExample.h \
	../../../terminal/examples/arenaExamples/AirportSecurityExampleExtended.h \
	../../../terminal/examples/arenaExamples/Airport_Extended1.h \
	../../../terminal/examples/arenaExamples/Assembly_Line.h \
	../../../terminal/examples/arenaExamples/Banking_Transactions.h \
	../../../terminal/examples/arenaExamples/Example_BasicOrderShipping.h \
	../../../terminal/examples/arenaExamples/Example_PortModel.h \
	../../../terminal/examples/arenaExamples/Example_PublicTransport.h \
	../../../terminal/examples/arenaSmarts/Smart_AddingResource.h \
	../../../terminal/examples/arenaSmarts/Smart_AlternatingEntityCreation.h \
	../../../terminal/examples/arenaSmarts/Smart_ArrivalsElementStopsEntitiesArrivingAfterASetTime.h \
	../../../terminal/examples/arenaSmarts/Smart_ArrivalsEntityTypeVsAttribute.h \
	../../../terminal/examples/arenaSmarts/Smart_AssignExample.h \
	../../../terminal/examples/arenaSmarts/Smart_AutomaticStatisticsCollection.h \
	../../../terminal/examples/arenaSmarts/Smart_BasicModeling.h \
	../../../terminal/examples/arenaSmarts/Smart_BatchAndSeparate.h \
	../../../terminal/examples/arenaSmarts/Smart_ContinuousFlowEntities.h \
	../../../terminal/examples/arenaSmarts/Smart_Create.h \
	../../../terminal/examples/arenaSmarts/Smart_DecideNWayByChance.h \
	../../../terminal/examples/arenaSmarts/Smart_DefiningAttributesAsStrings.h \
	../../../terminal/examples/arenaSmarts/Smart_DefiningControlLogic.h \
	../../../terminal/examples/arenaSmarts/Smart_DefiningResourceCapacity.h \
	../../../terminal/examples/arenaSmarts/Smart_DelayBasedOnReplication.h \
	../../../terminal/examples/arenaSmarts/Smart_EntitiesProcessedByPriority.h \
	../../../terminal/examples/arenaSmarts/Smart_EvaluatingConditionsBeforeEnteringQueue.h \
	../../../terminal/examples/arenaSmarts/Smart_Expression.h \
	../../../terminal/examples/arenaSmarts/Smart_InventoryAndHoldingCosts.h \
	../../../terminal/examples/arenaSmarts/Smart_MaxArrivalsField.h \
	../../../terminal/examples/arenaSmarts/Smart_ModelRunUntil1000Parts.h \
	../../../terminal/examples/arenaSmarts/Smart_ModuleDisplayVariables.h \
	../../../terminal/examples/arenaSmarts/Smart_OverlappingResources.h \
	../../../terminal/examples/arenaSmarts/Smart_ParallelProcessingOfEntities.h \
	../../../terminal/examples/arenaSmarts/Smart_PlacingEntitiesInQueueSets.h \
	../../../terminal/examples/arenaSmarts/Smart_PriorityExample.h \
	../../../terminal/examples/arenaSmarts/Smart_ProcessArena.h \
	../../../terminal/examples/arenaSmarts/Smart_Record_Arena.h \
	../../../terminal/examples/arenaSmarts/Smart_RemovingAndReorderingEntitiesInAQueue.h \
	../../../terminal/examples/arenaSmarts/Smart_ResourceCosting.h \
	../../../terminal/examples/arenaSmarts/Smart_ResourceScheduleCosting.h \
	../../../terminal/examples/arenaSmarts/Smart_ResourceSets.h \
	../../../terminal/examples/arenaSmarts/Smart_SeizingMultipleSimultaneosly.h \
	../../../terminal/examples/arenaSmarts/Smart_SelectingRouteBasedOnProbability.h \
	../../../terminal/examples/arenaSmarts/Smart_SelectingShorterQueue.h \
	../../../terminal/examples/arenaSmarts/Smart_SynchronizingParallelEntities.h \
	../../../terminal/examples/arenaSmarts/Smart_ValueAdded.h \
	../../../terminal/examples/arenaSmarts/Smart_WaitForSignal.h \
	../../../terminal/examples/book/Book_Cap02_Example01.h \
	../../../terminal/examples/smarts/Smart_AssignWriteSeizes.h \
	../../../terminal/examples/smarts/Smart_BatchSeparate.h \
	../../../terminal/examples/smarts/Smart_Buffer.h \
    ../../../terminal/examples/smarts/Smart_ExtendedFSM.h \
	../../../terminal/examples/smarts/Smart_FiniteStateMachine.h \
	../../../terminal/examples/smarts/Smart_CellularAutomata1.h \
	../../../terminal/examples/smarts/Smart_CppForG.h \
	../../../terminal/examples/smarts/Smart_Delay.h \
	../../../terminal/examples/smarts/Smart_Dummy.h \
	../../../terminal/examples/smarts/Smart_Failures.h \
	../../../terminal/examples/smarts/Smart_LSODE.h \
	../../../terminal/examples/smarts/Smart_Record.h \
    ../../../terminal/examples/smarts/Smart_SimulationControlResponse.h \
	../../../terminal/examples/smarts/Smart_WaitScanCondition.h \
	../../../terminal/examples/smarts/Smart_WaitSignal.h \
	../../../terminal/examples/smarts/Smart_ModelInfoModelSimulation.h \
	../../../terminal/examples/smarts/Smart_OnEvent.h \
	../../../terminal/examples/smarts/Smart_Parser.h \
	../../../terminal/examples/smarts/Smart_ParserModelFunctions.h \
	../../../terminal/examples/smarts/Smart_Plugin.h \
	../../../terminal/examples/smarts/Smart_Process.h \
	../../../terminal/examples/smarts/Smart_ProcessSet.h \
	../../../terminal/examples/smarts/Smart_RouteStation.h \
	../../../terminal/examples/smarts/Smart_SeizeDelayRelease.h \
	../../../terminal/examples/smarts/Smart_SeizeDelayReleaseMany.h \
	../../../terminal/examples/smarts/Smart_Sequence.h \
	../../../terminal/examples/teaching/AnElectronicAssemblyAndTestSystem.h \
	../../../terminal/examples/teaching/BufferFIFO.h \
# 	../../../terminal/examples/teaching/ContinuousModel.h \
	../../../terminal/examples/teaching/FullSimulationOfComplexModel.h \
	../../../terminal/examples/teaching/OperatingSystem02.h \
	../../../terminal/examples/teaching/OperatingSystem03.h \
	../../../terminal/underDevelopment/TestingTerminalApp.h \
#	BaseMVController.h \
	CodeEditor.h \
	LineNumberArea.h \
	ModelGraphicsScene.h \
	ModelGraphicsView.h \
	ObjectPropertyBrowser.h \
	PropertyEditor.h \
    QPropertyBrowser/qtbuttonpropertybrowser.h \
    QPropertyBrowser/qteditorfactory.h \
    QPropertyBrowser/qtgroupboxpropertybrowser.h \
    QPropertyBrowser/qtpropertybrowser.h \
    QPropertyBrowser/qtpropertybrowserutils_p.h \
    QPropertyBrowser/qtpropertymanager.h \
    QPropertyBrowser/qttreepropertybrowser.h \
    QPropertyBrowser/qtvariantproperty.h \
    TraitsGUI.h \
    UtilGUI.h \
	dialogs/Dialogmodelinformation.h \
	dialogs/dialogBreakpoint.h \
	dialogs/dialogpluginmanager.h \
	dialogs/dialogsimulationconfigure.h \
	dialogs/dialogsystempreferences.h \
	graphicals/GraphicalAnimateExpression.h \
	graphicals/GraphicalAssociation.h \
	graphicals/GraphicalComponentPort.h \
	graphicals/GraphicalConnection.h \
	graphicals/GraphicalModelComponent.h \
	graphicals/GraphicalModelDataDefinition.h \
	mainwindow.h \
	qcustomplot.h

FORMS += \
	dialogs/Dialogmodelinformation.ui \
	dialogs/dialogBreakpoint.ui \
	dialogs/dialogpluginmanager.ui \
	dialogs/dialogsimulationconfigure.ui \
	dialogs/dialogsystempreferences.ui \
	mainwindow.ui

TRANSLATIONS += \
	GenesysQtGUI_en_US.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
	../../../../../autoloadplugins.txt \
	QPropertyBrowser/CMakeLists.txt \
	QPropertyBrowser/images/cursor-arrow.png \
	QPropertyBrowser/images/cursor-busy.png \
	QPropertyBrowser/images/cursor-closedhand.png \
	QPropertyBrowser/images/cursor-cross.png \
	QPropertyBrowser/images/cursor-forbidden.png \
	QPropertyBrowser/images/cursor-hand.png \
	QPropertyBrowser/images/cursor-hsplit.png \
	QPropertyBrowser/images/cursor-ibeam.png \
	QPropertyBrowser/images/cursor-openhand.png \
	QPropertyBrowser/images/cursor-sizeall.png \
	QPropertyBrowser/images/cursor-sizeb.png \
	QPropertyBrowser/images/cursor-sizef.png \
	QPropertyBrowser/images/cursor-sizeh.png \
	QPropertyBrowser/images/cursor-sizev.png \
	QPropertyBrowser/images/cursor-uparrow.png \
	QPropertyBrowser/images/cursor-vsplit.png \
	QPropertyBrowser/images/cursor-wait.png \
	QPropertyBrowser/images/cursor-whatsthis.png \
	QPropertyBrowser/qtpropertybrowser.pri

RESOURCES += \
	GenesysQtGUI_resources.qrc \
	QPropertyBrowser/qtpropertybrowser.qrc
