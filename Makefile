
build/opencaffea: build/core/opencaffea.o build/simulation/simulation.o
	g++ -I src build/core/opencaffea.o build/simulation/simulation.o -o build/opencaffea



build/core/opencaffea.o: src/*
	@if not exist build\core mkdir build\core
	g++ -I src -c src/core/opencaffea.cpp -o build/core/opencaffea.o

build/simulation/simulation.o: src/simulation/*
	@if not exist build\simulation mkdir build\simulation
	g++ -I src -c src/simulation/simulation.cpp -o build/simulation/simulation.o

clear:
	@if exist build rmdir /s /q build
	@echo done
