CXX=g++

INC_DIR=./include
SRC_DIR=./src
TESTSRC_DIR=./testsrc
BIN_DIR=./bin
OBJ_DIR=./obj
TEST_TMP_DIR=./testtmp


CXXFLAG=-std=gnu++17 -I $(INC_DIR)
LDFLAGS=-L /opt/local/lib -lgtest -lgtest_main -lpthread -lexpat

all: directories runtest

runtest:	run_teststrutils \
			run_teststrdatasource \
			run_teststrdatasink \
			run_testfiledatass \
			run_testdsv \
			run_testxml \
			run_testcsvbs \
			run_testosm \
			run_testdpr \
			run_testcsvbsi \
			run_testtp \
			run_testtpcl

run_teststrutils: $(BIN_DIR)/teststrutils
	$(BIN_DIR)/teststrutils --gtest_output=xml:$(TEST_TMP_DIR)/run_teststrutils
	mv $(TEST_TMP_DIR)/run_teststrutils run_teststrutils

run_teststrdatasource: $(BIN_DIR)/srctest
	$(BIN_DIR)/srctest --gtest_output=xml:$(TEST_TMP_DIR)/run_teststrdatasource
	mv $(TEST_TMP_DIR)/run_teststrdatasource run_teststrdatasource

run_teststrdatasink: $(BIN_DIR)/sinktest
	$(BIN_DIR)/sinktest --gtest_output=xml:$(TEST_TMP_DIR)/run_teststrdatasink
	mv $(TEST_TMP_DIR)/run_teststrdatasink run_teststrdatasink

run_testfiledatass: $(BIN_DIR)/testfiledatass
	$(BIN_DIR)/testfiledatass --gtest_output=xml:$(TEST_TMP_DIR)/run_testfiledatass
	mv $(TEST_TMP_DIR)/run_testfiledatass run_testfiledatass

run_testdsv: $(BIN_DIR)/dsvtest
	$(BIN_DIR)/dsvtest --gtest_output=xml:$(TEST_TMP_DIR)/run_testdsv
	mv $(TEST_TMP_DIR)/run_testdsv run_testdsv

run_testxml: $(BIN_DIR)/xmltest
	$(BIN_DIR)/xmltest --gtest_output=xml:$(TEST_TMP_DIR)/run_testxml
	mv $(TEST_TMP_DIR)/run_testxml run_testxml

run_testkml:$(BIN_DIR)/testkml
	$(BIN_DIR)/testkml --gtest_output=xml:$(TEST_TMP_DIR)/run_testkml
	mv $(TEST_TMP_DIR)/run_testkml /run_testkml

run_testcsvbs: $(BIN_DIR)/testcsvbs
	$(BIN_DIR)/testcsvbs --gtest_output=xml:$(TEST_TMP_DIR)/run_testcsvbs
	mv $(TEST_TMP_DIR)/run_testcsvbs run_testcsvbs

run_testosm: $(BIN_DIR)/osmtest
	$(BIN_DIR)/osmtest --gtest_output=xml:$(TEST_TMP_DIR)/run_testosm
	mv $(TEST_TMP_DIR)/run_testosm run_testosm

run_testdpr: $(BIN_DIR)/testdpr
	$(BIN_DIR)/testdpr --gtest_output=xml:$(TEST_TMP_DIR)/run_testdpr
	mv $(TEST_TMP_DIR)/run_testdpr /run_testdpr

run_testcsvbsi: $(BIN_DIR)/testcsvbsi
	$(BIN_DIR)/testcsvbsi --gtest_output=xml:$(TEST_TMP_DIR)/run_testcsvbsi
	mv $(TEST_TMP_DIR)/run_testcsvbsi run_testcsvbsi

run_testtp: $(BIN_DIR)/testtp
	$(BIN_DIR)/testtp --gtest_output=xml:$(TEST_TMP_DIR)/run_testtp
	mv $(TEST_TMP_DIR)/run_testtp run_testtp

run_testtpcl: $(BIN_DIR)/testtpcl
	$(BIN_DIR)/testtpcl --gtest_output=xml:$(TEST_TMP_DIR)/run_testtpcl
	mv $(TEST_TMP_DIR)/run_testtpcl run_testtpcl

teststrutils: $(BIN_DIR)/teststrutils
	$(BIN_DIR)/teststrutils

$(BIN_DIR)/teststrutils: $(OBJ_DIR)/StringUtilsTest.o $(OBJ_DIR)/StringUtils.o
	$(CXX) -o $(BIN_DIR)/teststrutils $(OBJ_DIR)/StringUtilsTest.o $(OBJ_DIR)/StringUtils.o $(LDFLAGS)

$(OBJ_DIR)/StringUtilsTest.o: $(TESTSRC_DIR)/StringUtilsTest.cpp $(INC_DIR)/StringUtils.h
	$(CXX) -o $(OBJ_DIR)/StringUtilsTest.o $(CXXFLAG) -c $(TESTSRC_DIR)/StringUtilsTest.cpp

$(OBJ_DIR)/StringUtils.o: $(SRC_DIR)/StringUtils.cpp $(INC_DIR)/StringUtils.h
	$(CXX) -o $(OBJ_DIR)/StringUtils.o $(CXXFLAG) -c $(SRC_DIR)/StringUtils.cpp

srctest: $(BIN_DIR)/srctest
	$(BIN_DIR)/srctest

$(BIN_DIR)/srctest: $(OBJ_DIR)/StringDataSourceTest.o $(OBJ_DIR)/StringDataSource.o
	$(CXX) -o $(BIN_DIR)/srctest $(OBJ_DIR)/StringDataSourceTest.o $(OBJ_DIR)/StringDataSource.o $(LDFLAGS)

$(OBJ_DIR)/StringDataSourceTest.o: $(TESTSRC_DIR)/StringDataSourceTest.cpp $(INC_DIR)/StringDataSource.h $(INC_DIR)/DataSource.h
	$(CXX) -o $(OBJ_DIR)/StringDataSourceTest.o $(CXXFLAG) -c ${TESTSRC_DIR}/StringDataSourceTest.cpp

$(OBJ_DIR)/StringDataSource.o: $(SRC_DIR)/StringDataSource.cpp $(INC_DIR)/StringDataSource.h $(INC_DIR)/DataSource.h
	$(CXX) -o $(OBJ_DIR)/StringDataSource.o $(CXXFLAG) -c $(SRC_DIR)/StringDataSource.cpp

sinktest: $(BIN_DIR)/sinktest
	$(BIN_DIR)/sinktest

$(BIN_DIR)/sinktest: $(OBJ_DIR)/StringDataSinkTest.o $(OBJ_DIR)/StringDataSink.o
	$(CXX) -o $(BIN_DIR)/sinktest $(OBJ_DIR)/StringDataSinkTest.o $(OBJ_DIR)/StringDataSink.o $(LDFLAGS)

$(OBJ_DIR)/StringDataSinkTest.o: $(TESTSRC_DIR)/StringDataSinkTest.cpp $(INC_DIR)/StringDataSink.h $(INC_DIR)/DataSink.h
	$(CXX) -o $(OBJ_DIR)/StringDataSinkTest.o $(CXXFLAG) -c $(TESTSRC_DIR)/StringDataSinkTest.cpp

$(OBJ_DIR)/StringDataSink.o: $(SRC_DIR)/StringDataSink.cpp $(INC_DIR)/StringDataSink.h $(INC_DIR)/DataSink.h
	$(CXX) -o $(OBJ_DIR)/StringDataSink.o $(CXXFLAG) -c $(SRC_DIR)/StringDataSink.cpp

testfiledatass: $(BIN_DIR)/testfiledatass
	$(BIN_DIR)/testfiledatass

$(BIN_DIR)/testfiledatass: $(OBJ_DIR)/FileDataSource.o $(OBJ_DIR)/FileDataSink.o $(OBJ_DIR)/FileDataFactory.o $(OBJ_DIR)/FileDataSSTest.o
	$(CXX) -o $(BIN_DIR)/testfiledatass $(OBJ_DIR)/FileDataSource.o $(OBJ_DIR)/FileDataSink.o $(OBJ_DIR)/FileDataFactory.o $(OBJ_DIR)/FileDataSSTest.o $(LDFLAGS)

$(OBJ_DIR)/FileDataSSTest.o: $(TESTSRC_DIR)/FileDataSSTest.cpp $(INC_DIR)/FileDataFactory.h $(INC_DIR)/FileDataSink.h $(INC_DIR)/FileDataSource.h
	$(CXX) -o $(OBJ_DIR)/FileDataSSTest.o $(CXXFLAG) -c $(TESTSRC_DIR)/FileDataSSTest.cpp

$(OBJ_DIR)/FileDataSource.o: $(SRC_DIR)/FileDataSource.cpp $(INC_DIR)/FileDataSource.h $(INC_DIR)/DataSource.h
	$(CXX) -o $(OBJ_DIR)/FileDataSource.o $(CXXFLAG) -c $(SRC_DIR)/FileDataSource.cpp

$(OBJ_DIR)/FileDataSink.o: $(SRC_DIR)/FileDataSink.cpp $(INC_DIR)/FileDataSink.h $(INC_DIR)/DataSink.h
	$(CXX) -o $(OBJ_DIR)/FileDataSink.o $(CXXFLAG) -c $(SRC_DIR)/FileDataSink.cpp

$(OBJ_DIR)/FileDataFactory.o: $(SRC_DIR)/FileDataFactory.cpp $(INC_DIR)/FileDataFactory.h $(INC_DIR)/FileDataSource.h $(INC_DIR)/FileDataSink.h
	$(CXX) -o $(OBJ_DIR)/FileDataFactory.o $(CXXFLAG) -c $(SRC_DIR)/FileDataFactory.cpp

dsvtest: $(BIN_DIR)/dsvtest
	$(BIN_DIR)/dsvtest

$(BIN_DIR)/dsvtest: $(OBJ_DIR)/DSVTest.o $(OBJ_DIR)/DSVWriter.o $(OBJ_DIR)/StringDataSink.o $(OBJ_DIR)/DSVReader.o $(OBJ_DIR)/StringDataSource.o $(OBJ_DIR)/StringUtils.o
	$(CXX) -o $(BIN_DIR)/dsvtest $(OBJ_DIR)/DSVTest.o $(OBJ_DIR)/DSVWriter.o $(OBJ_DIR)/StringDataSink.o $(OBJ_DIR)/DSVReader.o $(OBJ_DIR)/StringDataSource.o $(OBJ_DIR)/StringUtils.o $(LDFLAGS) 

$(OBJ_DIR)/DSVTest.o: $(TESTSRC_DIR)/DSVTest.cpp $(SRC_DIR)/StringDataSink.cpp $(SRC_DIR)/StringDataSource.cpp
	$(CXX) -o $(OBJ_DIR)/DSVTest.o $(CXXFLAG) -c $(TESTSRC_DIR)/DSVTest.cpp

$(OBJ_DIR)/DSVWriter.o: $(SRC_DIR)/DSVWriter.cpp $(INC_DIR)/DSVWriter.h
	$(CXX) -o $(OBJ_DIR)/DSVWriter.o $(CXXFLAG) -c $(SRC_DIR)/DSVWriter.cpp

$(OBJ_DIR)/DSVReader.o: $(SRC_DIR)/DSVReader.cpp $(INC_DIR)/DSVReader.h
	$(CXX) -o $(OBJ_DIR)/DSVReader.o $(CXXFLAG) -c $(SRC_DIR)/DSVReader.cpp

$(OBJ_DIR)/StringUtils.o: $(SRC_DIR)/StringUtils.cpp $(INC_DIR)/StringUtils.h
	$(CXX) -o $(OBJ_DIR)/StringUtils.o $(CXXFLAG) -c $(SRC_DIR)/StringUtils.cpp

xmltest: $(BIN_DIR)/xmltest
	$(BIN_DIR)/xmltest

$(BIN_DIR)/xmltest: $(OBJ_DIR)/XMLTest.o $(OBJ_DIR)/XMLWriter.o $(OBJ_DIR)/StringDataSink.o $(OBJ_DIR)/XMLReader.o $(OBJ_DIR)/StringDataSource.o
	$(CXX) -o $(BIN_DIR)/xmltest $(OBJ_DIR)/XMLTest.o $(OBJ_DIR)/XMLWriter.o $(OBJ_DIR)/StringDataSink.o $(OBJ_DIR)/XMLReader.o $(OBJ_DIR)/StringDataSource.o $(LDFLAGS) 

$(OBJ_DIR)/XMLTest.o: $(TESTSRC_DIR)/XMLTest.cpp $(SRC_DIR)/StringDataSink.cpp $(SRC_DIR)/StringDataSource.cpp
	$(CXX) -o $(OBJ_DIR)/XMLTest.o $(CXXFLAG) -c $(TESTSRC_DIR)/XMLTest.cpp

$(OBJ_DIR)/XMLWriter.o: $(SRC_DIR)/XMLWriter.cpp $(INC_DIR)/XMLWriter.h
	$(CXX) -o $(OBJ_DIR)/XMLWriter.o $(CXXFLAG) -c $(SRC_DIR)/XMLWriter.cpp

$(OBJ_DIR)/XMLReader.o: $(SRC_DIR)/XMLReader.cpp $(INC_DIR)/XMLReader.h
	$(CXX) -o $(OBJ_DIR)/XMLReader.o $(CXXFLAG) -c $(SRC_DIR)/XMLReader.cpp

testcsvbs: $(BIN_DIR)/testcsvbs
	$(BIN_DIR)/testcsvbs

$(BIN_DIR)/testcsvbs: $(OBJ_DIR)/CSVBusSystemTest.o $(OBJ_DIR)/CSVBusSystem.o $(OBJ_DIR)/DSVReader.o $(OBJ_DIR)/StringDataSource.o $(OBJ_DIR)/StringUtils.o
	$(CXX) -o $(BIN_DIR)/testcsvbs $(OBJ_DIR)/CSVBusSystemTest.o $(OBJ_DIR)/CSVBusSystem.o $(OBJ_DIR)/DSVReader.o $(OBJ_DIR)/StringDataSource.o $(OBJ_DIR)/StringUtils.o $(LDFLAGS)

$(OBJ_DIR)/CSVBusSystemTest.o: $(TESTSRC_DIR)/CSVBusSystemTest.cpp $(SRC_DIR)/StringDataSource.cpp
	$(CXX) -o $(OBJ_DIR)/CSVBusSystemTest.o $(CXXFLAG) -c $(TESTSRC_DIR)/CSVBusSystemTest.cpp

$(OBJ_DIR)/CSVBusSystem.o: $(SRC_DIR)/CSVBusSystem.cpp $(INC_DIR)/CSVBusSystem.h $(INC_DIR)/StringUtils.h
	$(CXX) -o $(OBJ_DIR)/CSVBusSystem.o $(CXXFLAG) -c $(SRC_DIR)/CSVBusSystem.cpp

osmtest: $(BIN_DIR)/osmtest
	$(BIN_DIR)/osmtest

$(BIN_DIR)/osmtest: $(OBJ_DIR)/OSMTest.o $(OBJ_DIR)/COpenStreetMap.o $(OBJ_DIR)/XMLReader.o $(OBJ_DIR)/StringDataSource.o
	$(CXX) -o $(BIN_DIR)/osmtest $(OBJ_DIR)/OSMTest.o $(OBJ_DIR)/COpenStreetMap.o $(OBJ_DIR)/XMLReader.o $(OBJ_DIR)/StringDataSource.o $(LDFLAGS)

$(OBJ_DIR)/OSMTest.o: $(TESTSRC_DIR)/OSMTest.cpp $(SRC_DIR)/StringDataSource.cpp
	$(CXX) -o $(OBJ_DIR)/OSMTest.o $(CXXFLAG) -c $(TESTSRC_DIR)/OSMTest.cpp

$(OBJ_DIR)/COpenStreetMap.o: $(SRC_DIR)/COpenStreetMap.cpp $(INC_DIR)/OpenStreetMap.h $(INC_DIR)/StringUtils.h
	$(CXX) -o $(OBJ_DIR)/COpenStreetMap.o $(CXXFLAG) -c $(SRC_DIR)/COpenStreetMap.cpp

testdpr: $(BIN_DIR)/testdpr
	$(BIN_DIR)/testdpr

$(BIN_DIR)/testdpr: $(OBJ_DIR)/DijkstraPathRouter.o $(OBJ_DIR)/DijkstraTest.o
	$(CXX) -o $(BIN_DIR)/testdpr $(CXXFLAG) $(OBJ_DIR)/DijkstraPathRouter.o $(OBJ_DIR)/DijkstraTest.o $(LDFLAGS)

$(OBJ_DIR)/DijkstraTest.o: $(TESTSRC_DIR)/DijkstraTest.cpp $(SRC_DIR)/DijkstraPathRouter.cpp
	$(CXX) -o $(OBJ_DIR)/DijkstraTest.o $(CXXFLAG) -c $(TESTSRC_DIR)/DijkstraTest.cpp

$(OBJ_DIR)/DijkstraPathRouter.o: $(SRC_DIR)/DijkstraPathRouter.cpp $(INC_DIR)/DijkstraPathRouter.h $(INC_DIR)/PathRouter.h
	$(CXX) -o $(OBJ_DIR)/DijkstraPathRouter.o $(CXXFLAG) -c $(SRC_DIR)/DijkstraPathRouter.cpp

$(OBJ_DIR)/DijkstraTransportationPlanner.o: $(SRC_DIR)/DijkstraTransportationPlanner.cpp $(INC_DIR)/DijkstraTransportationPlanner.h $(INC_DIR)/DijkstraPathRouter.h $(INC_DIR)/PathRouter.h
	$(CXX) -o $(OBJ_DIR)/DijkstraTransportationPlanner.o $(CXXFLAG) -c $(SRC_DIR)/DijkstraTransportationPlanner.cpp

testcsvbsi:
$(BIN_DIR)/testcsvbsi: $(OBJ_DIR)/BusSystemIndexer.o $(OBJ_DIR)/CSVBusSystemIndexerTest.o $(OBJ_DIR)/CSVBusSystem.o $(OBJ_DIR)/StringDataSource.o $(OBJ_DIR)/DSVReader.o $(OBJ_DIR)/StringUtils.o
	$(CXX) -o $(BIN_DIR)/testcsvbsi $(CXXFLAG) $(OBJ_DIR)/BusSystemIndexer.o $(OBJ_DIR)/CSVBusSystemIndexerTest.o $(OBJ_DIR)/CSVBusSystem.o $(OBJ_DIR)/StringDataSource.o $(OBJ_DIR)/DSVReader.o $(OBJ_DIR)/StringUtils.o $(LDFLAGS)

$(OBJ_DIR)/BusSystemIndexer.o: $(SRC_DIR)/BusSystemIndexer.cpp $(INC_DIR)/BusSystemIndexer.h
	$(CXX) -o $(OBJ_DIR)/BusSystemIndexer.o $(CXXFLAG) -c $(SRC_DIR)/BusSystemIndexer.cpp

$(OBJ_DIR)/CSVBusSystemIndexerTest.o: $(TESTSRC_DIR)/CSVBusSystemIndexerTest.cpp $(INC_DIR)/StringDataSource.h
	$(CXX) -o $(OBJ_DIR)/CSVBusSystemIndexerTest.o $(CXXFLAG) -c $(TESTSRC_DIR)/CSVBusSystemIndexerTest.cpp

testtpcl:
$(BIN_DIR)/testtpcl: $(OBJ_DIR)/TransportationPlannerCommandLine.o $(OBJ_DIR)/TPCommandLineTest.o 
	$(CXX) -o $(BIN_DIR)/testtpcl $(CXXFLAG) $(OBJ_DIR)/TransportationPlannerCommandLine.o $(OBJ_DIR)/TPCommandLineTest.o $(LDFLAGS)

$(OBJ_DIR)/TPCommandLineTest.o: $(TESTSRC_DIR)/TPCommandLineTest.cpp $(INC_DIR)/TransportationPlannerCommandLine.h $(INC_DIR)/StringDataSink.h $(INC_DIR)/StringDataSource.h 
	$(CXX) -o $(OBJ_DIR)/TPCommandLineTest.o $(CXXFLAG) -c $(TESTSRC_DIR)/TPCommandLineTest.cpp

$(OBJ_DIR)/transplanner.o: $(SRC_DIR)/transplanner.cpp $(INC_DIR)/TransportationPlanner.h
	$(CXX) -o $(OBJ_DIR)/transplanner.o $(CXXFLAG) -c $(SRC_DIR)/transplanner.cpp

$(OBJ_DIR)/TPCommandLineTest.o: $(TESTSRC_DIR)/TPCommandLineTest.cpp $(INC_DIR)/TransportationPlannerCommandLine.h $(INC_DIR)/StringDataSink.h $(INC_DIR)/StringDataSource.h 
	$(CXX) -o $(OBJ_DIR)/TPCommandLineTest.o $(CXXFLAG) -c $(TESTSRC_DIR)/TPCommandLineTest.cpp

testtp:
$(BIN_DIR)/testtp: $(OBJ_DIR)/DijkstraTransportationPlanner.o $(OBJ_DIR)/CSVOSMTransportationPlannerTest.o 
	$(CXX) -o $(BIN_DIR)/testtp $(CXXFLAG) $(OBJ_DIR)/DijkstraTransportationPlanner.o $(OBJ_DIR)/CSVOSMTransportationPlannerTest.o $(LDFLAGS)

$(OBJ_DIR)/CSVOSMTransportationPlannerTest.o: $(TESTSRC_DIR)/CSVOSMTransportationPlannerTest.cpp $(INC_DIR)/TransportationPlanner.h 
	$(CXX) -o $(OBJ_DIR)/CSVOSMTransportationPlannerTest.o $(CXXFLAG) -c $(TESTSRC_DIR)/CSVOSMTransportationPlannerTest.cpp

$(OBJ_DIR)/DijkstraTransportationPlanner.o: $(SRC_DIR)/DijkstraTransportationPlanner.cpp $(INC_DIR)/DijkstraTransportationPlanner.h
	$(CXX) -o $(OBJ_DIR)/DijkstraTransportationPlanner.o $(CXXFLAG) -c $(SRC_DIR)/DijkstraTransportationPlanner.cpp

testkml:
$(BIN_DIR)/testkml: $(OBJ_DIR)/KMLWriter.o $(OBJ_DIR)/KMLTest.o  $(OBJ_DIR)/kmlout.o
	$(CXX) -o $(BIN_DIR)/testkml $(CXXFLAG) $(OBJ_DIR)/KMLWriter.o $(OBJ_DIR)/KMLTest.o $(OBJ_DIR)/kmlout.o $(LDFLAGS)

$(OBJ_DIR)/KMLTest.o: $(TESTSRC_DIR)/KMLTest.cpp $(INC_DIR)/KMLWriter.h $(INC_DIR)/StringDataSink.h $(INC_DIR)/StringDataSource.h $(INC_DIR)/StringUtils.h 
	$(CXX) -o $(OBJ_DIR)/KMLTest.o -c $(CXXFLAG) $(TESTSRC_DIR)/KMLTest.cpp

$(OBJ_DIR)/kmlout.o: $(SRC_DIR)/kmlout.cpp $(INC_DIR)/KMLWriter.h $(INC_DIR)/OpenStreetMap.h $(INC_DIR)/CSVBusSystem.h $(INC_DIR)/DSVReader.h $(INC_DIR)/DSVWriter.h $(INC_DIR)/FileDataFactory.h $(INC_DIR)/FileDataSink.h $(INC_DIR)/FileDataSource.h $(INC_DIR)/StandardDataSink.h $(INC_DIR)/StandardDataSource.h $(INC_DIR)/StandardErrorDataSink.h $(INC_DIR)/StringUtils.h
	$(CXX) -o $(OBJ_DIR)/kmlout.o -c $(CXXFLAG) $(SRC_DIR)/kmlout.cpp

$(OBJ_DIR)/KMLWriter.o: $(SRC_DIR)/KMLWriter.cpp $(INC_DIR)/KMLWriter.h $(INC_DIR)/XMLWriter.h $(INC_DIR)/StringUtils.h
	$(CXX) -o $(OBJ_DIR)/KMLWriter.o -c $(CXXFLAG) $(SRC_DIR)/KMLWriter.cpp

$(OBJ_DIR)/StandardDataSink.o: $(SRC_DIR)/StandardDataSink.cpp $(INC_DIR)/DataSink.h
	$(CXX) -o $(OBJ_DIR)/StandardDataSink.o -c $(CXXFLAG) $(SRC_DIR)/StandardDataSink.cpp

$(OBJ_DIR)/StandardDataSource.o: $(SRC_DIR)/StandardDataSource.cpp $(INC_DIR)/DataSource.h
	$(CXX) -o $(OBJ_DIR)/StandardDataSource.o -c $(CXXFLAG) $(SRC_DIR)/StandardDataSource.cpp

$(OBJ_DIR)/StandardErrorDataSink.o: $(SRC_DIR)/StandardErrorDataSink.cpp $(INC_DIR)/DataSink.h
	$(CXX) -o $(OBJ_DIR)/StandardErrorDataSink.o -c $(CXXFLAG) $(SRC_DIR)/StandardErrorDataSink.cpp

directories:
	mkdir -p $(BIN_DIR)
	mkdir -p $(OBJ_DIR)
	mkdir -p $(TEST_TMP_DIR)

.PHONY: clean

clean:
	rm -rf $(BIN_DIR) $(OBJ_DIR) $(TEST_TMP_DIR)
	rm -f run_*

