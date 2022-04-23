#include <fstream>

#include "Market.h"
#include "TreePricer.h"
#include "EuropeanTrade.h"
#include "AmericanTrade.h"
#include "BarrierTrade.h"

void test1()
{
  std::ifstream fin("simpleMkt.dat");
  if (fin) {
    Market mkt;
    fin >> mkt;
    mkt.Print();
    EuropeanOption callOption1(Call, 90, Date(2016, 1, 1));
    EuropeanOption callOption2(Call, 91, Date(2016, 1, 1));
    EuroCallSpread callSpread(90, 91, Date(2016, 1, 1));

    std::cout << "callOption1 struck at 90:\t"
	      << binomialTree(mkt, callOption1, 100) << std::endl;
    std::cout << "callOption2 struck at 91:\t"
	      << binomialTree(mkt, callOption2, 100) << std::endl;
    std::cout << "callSpread 90 to 91:\t\t"
	      << binomialTree(mkt, callSpread, 100) << std::endl;
    std::cout << "callOption1 - callOption2:\t"
	      << binomialTree(mkt, callOption1, 100) - binomialTree(mkt, callOption2, 100) << std::endl;
  }
  else {
    std::cerr << "no simpleMkt.dat found" << std::endl;
  }
}

// american options
void test2()
{
  std::ifstream fin("simpleMkt.dat");
  if (fin) {
    Market mkt;
    fin >> mkt;
    mkt.Print();
    AmericanOption callOption1(Call, 90, Date(2016, 1, 1));
    AmericanOption callOption2(Call, 91, Date(2016, 1, 1));
    AmerCallSpread callSpread(90, 91, Date(2016, 1, 1));

    std::cout << "callOptionAmer1 struck at 90:\t"
	      << binomialTree(mkt, callOption1, 100) << std::endl;
    std::cout << "callOptionAmer2 struck at 91:\t"
	      << binomialTree(mkt, callOption2, 100) << std::endl;
    std::cout << "callSpreadAmer 90 to 91:\t\t"
	      << binomialTree(mkt, callSpread, 100) << std::endl;
  }
  else {
    std::cerr << "no simpleMkt.dat found" << std::endl;
  }
}

// European vs American
void testAmer()
{
  std::cout << "\n------------------------ Test American -------------------\n";
  std::ifstream fin("simpleMkt.dat");
  std::ofstream foutA1("amerCall.txt");
  std::ofstream foutE1("euroCall.txt");
  std::ofstream foutA2("amerPut.txt");
  std::ofstream foutE2("euroPut.txt");
  if (fin) {
    Market mkt;
    fin >> mkt;
    mkt.Print();
    const int treeTimeSteps = 100;
    for (int i = 0; i <= 200; i++) {
      EuropeanOption euroCall(Call, i, Date(2016, 1, 1));
      AmericanOption amerCall(Call, i, Date(2016, 1, 1));
      foutE1 << i << "\t\t\t"
	     << binomialTree(mkt, euroCall, treeTimeSteps)
	     << std::endl;
      foutA1 << i << "\t\t\t"
	    << binomialTree(mkt, amerCall, treeTimeSteps)
	     << std::endl;
    }
    for (int i = 0; i <= 200; i++) {
      EuropeanOption euroPut(Put, i, Date(2016, 1, 1));
      AmericanOption amerPut(Put, i, Date(2016, 1, 1));
      foutE2 << i << "\t\t\t"
	     << binomialTree(mkt, euroPut, treeTimeSteps)
	     << std::endl;
      foutA2 << i << "\t\t\t"
	     << binomialTree(mkt, amerPut, treeTimeSteps)
	     << std::endl;
    }
  }
  else
    std::cerr << "no simpleMkt.dat found" << std::endl;
}

void testBarrier()
{
  std::cout << "\n------------------------ Test Barrier -------------------\n";
  std::ifstream fin("simpleMkt.dat");
  if (fin) {
    Market mkt;
    fin >> mkt;
    mkt.Print();
    EuropeanOption callOption1(Call, 90, Date(2016, 1, 1));
    UpBarrier upBar(120);
    BarrierOption barOption1(upBar, callOption1);


    std::cout << "callOption1 struck at 90:\t\t\t"
	      << binomialTree(mkt, callOption1, 100) << std::endl;
    std::cout << "barrierOption1 with up barrier at 110:\t\t"
	      << binomialTree(mkt, barOption1, 100) << std::endl;

    // changing upBar
    // upBar = UpBarrier(110);
    // std::cout << "changing upBar: \t\t\t\t" << binomialTree(mkt, barOption1, 100) << std::endl;
  }
  else {
    std::cerr << "no simpleMkt.dat found" << std::endl;
  }
}

void testBarrier2()
{
  std::cout << "\n------------------------ Test Barrier2 -------------------\n";
  std::ifstream fin("simpleMkt.dat");
  std::ofstream foutE1("barrierTest_euroCall.txt");
  std::ofstream foutB1("barrierTest_bar.txt");
  if (fin) {
    Market mkt;
    fin >> mkt;
    mkt.Print();
    const int treeTimeSteps = 100;
    EuropeanOption euroCall(Call, 80, Date(2016, 1, 1));
    for (int i = 0; i <= 200; i++) {
      BarrierOption barOption1(DownBarrier(i), euroCall);
      foutE1 << i << "\t\t\t"
	     << binomialTree(mkt, euroCall, treeTimeSteps)
	     << std::endl;
      foutB1 << i << "\t\t\t"
	     << binomialTree(mkt, barOption1, treeTimeSteps)
	     << std::endl;
    }
  }
  else
    std::cerr << "no simpleMkt.dat found" << std::endl;
}

void testTreePricer()
{
  std::cout << "\n------------------------ Test TreePricer -------------------\n";
  std::ifstream fin("simpleMkt.dat");
  if (fin) {
    Market mkt;
    fin >> mkt;
    mkt.Print();
    CRRBinomialTreePricer crrBTreePricer(100); // nTimeStep = 100

    EuropeanOption euroCall(Call, 80, Date(2016, 1, 1));
    std::cout << crrBTreePricer.Price(mkt, euroCall) << std::endl;
    std::cout << binomialTree(mkt, euroCall, 100) << std::endl;


    JRRNBinomialTreePricer jrrnBTreePricer(100); // nTimeStep = 100
    std::cout << jrrnBTreePricer.Price(mkt, euroCall) << std::endl;

  }
  else
    std::cerr << "no simpleMkt.dat found" << std::endl;
}


void testDoubleBarrier()
{
    std::cout << "\n------------------------ Test DoubleBarrier -------------------\n";
    std::ifstream fin("simpleMkt.dat");
    std::ofstream foutB1("barrierTest_DownBarrier.txt");
    std::ofstream foutB2("barrierTest_UpBarrier.txt");
    std::ofstream foutB3("barrierTest_DoubleBarrier_down.txt");
    std::ofstream foutB4("barrierTest_DoubleBarrier_up.txt");
    if (fin) {
        Market mkt;
        fin >> mkt;
        mkt.Print();
        const int treeTimeSteps = 100;
        EuropeanOption euroCall(Call, 80, Date(2016, 1, 1));
        BarrierOption barOption1(DownBarrier(60), euroCall);
        BarrierOption barOption2(UpBarrier(120), euroCall);
        for (int i = 100; i <= 300; i++) {
            BarrierOption barOption3(DoubleBarrier(60, i), euroCall);
            foutB1 << i << "\t\t\t"
            << binomialTree(mkt, barOption1, treeTimeSteps)
            << std::endl;
            foutB3 << i << "\t\t\t"
            << binomialTree(mkt, barOption3, treeTimeSteps)
            << std::endl;
        }
        for (int i = 100; i > 0; i--){
            BarrierOption barOption4(DoubleBarrier(i, 120), euroCall);
            foutB2 << i << "\t\t\t"
            << binomialTree(mkt, barOption2, treeTimeSteps)
            << std::endl;
            foutB4 << i << "\t\t\t"
            << binomialTree(mkt, barOption4, treeTimeSteps)
            << std::endl;
        }
    }
    else
        std::cerr << "no simpleMkt.dat found" << std::endl;
}

//void testAdjustedTree()
//{
//    std::cout << "\n------------------------ Test AdjustedTree -------------------\n";
//    std::ifstream fin("simpleMkt.dat");
//    std::ofstream foutB1("AdjustTest.txt");
//    std::ofstream foutB2("CRRTest_UpBarrier.txt");
//    if (fin) {
//        Market mkt;
//        fin >> mkt;
//        mkt.Print();
//        //const int treeTimeSteps = 100;
//        EuropeanOption euroCall(Call, 80, Date(2016, 1, 1));
//        for (int i = 100; i <= 1000; i++) {
//            CRRBinomialTreePricer crrBTreePricer(i);
//            AdjustedBinomialTreePricer adjustBTreePricer(i);
//            foutB1 << i << "\t\t\t"
//            << crrBTreePricer.Price(mkt, euroCall)
//            << std::endl;
//            foutB2 << i << "\t\t\t"
//            << adjustBTreePricer.Price(mkt, euroCall)
//            << std::endl;
//        }
//    }
//    else
//        std::cerr << "no simpleMkt.dat found" << std::endl;
//}


int main()
{
  //test1();
  //test2();
  //testAmer();
  // testBarrier();
  // testBarrier2();

  testTreePricer();
  //testDoubleBarrier();
  //testAdjustedTree();
  return 0;
}
