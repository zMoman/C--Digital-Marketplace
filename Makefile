makeobjects = main.o Control.o View.o CuMarket.o Filter.o Listing.o Price.o Tester.o Category.o
testobjects = test.o Tester.o TestControl.o View.o CuMarket.o Filter.o Listing.o Price.o Category.o

a4: $(makeobjects)
	g++ -o a4 $(makeobjects)

a4test: $(testobjects)
	g++ -o a4test $(testobjects)

main.o: main.cc CuMarket.h
	g++ -c main.cc

test.o: test.cc
	g++ -c test.cc

Control.o: Control.h Control.cc
	g++ -c Control.cc

TestControl.o: TestControl.cc TestControl.h
	g++ -c TestControl.cc

View.o: View.h View.cc
	g++ -c View.cc

CuMarket.o: CuMarket.h CuMarket.cc
	g++ -c CuMarket.cc

Listing.o: Listing.h Listing.cc
	g++ -c Listing.cc

Filter.o: Filter.h Filter.cc
	g++ -c Filter.cc

Price.o: Price.h Price.cc
	g++ -c Price.cc

Tester.o: Tester.h Tester.cc
	g++ -c Tester.cc

Category.o: Category.h Category.cc
	g++ -c Category.cc

clean:
	rm a4 a4test *.o
