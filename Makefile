build/simulation.o: src/*
	g++ -o build/openCaffea src/core/opencaffea.cpp
clear:
	rm -r build/*
