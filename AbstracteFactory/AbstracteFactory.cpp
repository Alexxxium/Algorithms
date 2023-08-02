#include "AbstracteFactory.h"
#include <vector>


class ProductAlphaX: public algs::ProductAlpha { public: void printAlphaProductName() const override { std::cout << "Product:\tFactory: \'X\'\tName: \'Alpha\'\n"; } };
class ProductAlphaY: public algs::ProductAlpha { public: void printAlphaProductName() const override { std::cout << "Product:\tFactory: \'Y\'\tName: \'Alpha\'\n"; } };
class ProductAlphaZ: public algs::ProductAlpha { public: void printAlphaProductName() const override { std::cout << "Product:\tFactory: \'Z\'\tName: \'Alpha\'\n"; } };

class ProductBettaX: public algs::ProductBetta { public: void printBettaProductName() const override { std::cout << "Product:\tFactory: \'X\'\tName: \'Betta\'\n"; } };
class ProductBettaY: public algs::ProductBetta { public: void printBettaProductName() const override { std::cout << "Product:\tFactory: \'Y\'\tName: \'Betta\'\n"; } };
class ProductBettaZ: public algs::ProductBetta { public: void printBettaProductName() const override { std::cout << "Product:\tFactory: \'Z\'\tName: \'Betta\'\n"; } };

class ProductGammaX: public algs::ProductGamma { public: void printGammaProductName() const override { std::cout << "Product:\tFactory: \'X\'\tName: \'Gamma\'\n"; } };
class ProductGammaY: public algs::ProductGamma { public: void printGammaProductName() const override { std::cout << "Product:\tFactory: \'Y\'\tName: \'Gamma\'\n"; } };
class ProductGammaZ: public algs::ProductGamma { public: void printGammaProductName() const override { std::cout << "Product:\tFactory: \'Z\'\tName: \'Gamma\'\n"; } };



class Factory_X: public algs::Factory {
public:
	algs::ProductAlpha* factoryMethodAlpha() const override { return new ProductAlphaX; }
	algs::ProductBetta* factoryMethodBetta() const override { return new ProductBettaX; }
	algs::ProductGamma* factoryMethodGamma() const override { return new ProductGammaX; }
};

class Factory_Y: public algs::Factory {
public:
	algs::ProductAlpha* factoryMethodAlpha() const override { return new ProductAlphaY; }
	algs::ProductBetta* factoryMethodBetta() const override { return new ProductBettaY; }
	algs::ProductGamma* factoryMethodGamma() const override { return new ProductGammaY; }
};

class Factory_Z: public algs::Factory {
public:
	algs::ProductAlpha* factoryMethodAlpha() const override { return new ProductAlphaZ; }
	algs::ProductBetta* factoryMethodBetta() const override { return new ProductBettaZ; }
	algs::ProductGamma* factoryMethodGamma() const override { return new ProductGammaZ; }
};



int main()
{
	Factory_X x_fact; std::vector<algs::ProductAlpha*> prod_alpha;
	Factory_Y y_fact; std::vector<algs::ProductBetta*> prod_betta;
	Factory_Z z_fact; std::vector<algs::ProductGamma*> prod_gamma;

	for (int i = 0; i < 3; ++i) {
		prod_alpha.push_back(x_fact.factoryMethodAlpha());
		prod_betta.push_back(x_fact.factoryMethodBetta());
		prod_gamma.push_back(x_fact.factoryMethodGamma());
	}
	for (int i = 0; i < 5; ++i) {
		prod_alpha.push_back(y_fact.factoryMethodAlpha());
		prod_betta.push_back(y_fact.factoryMethodBetta());
		prod_gamma.push_back(y_fact.factoryMethodGamma());
	}
	for (int i = 0; i < 7; ++i) {
		prod_alpha.push_back(z_fact.factoryMethodAlpha());
		prod_betta.push_back(z_fact.factoryMethodBetta());
		prod_gamma.push_back(z_fact.factoryMethodGamma());
	}

	std::cout << "Alpha vector:\n";
	for (const auto &i : prod_alpha) {
		i->printAlphaProductName();
	} 
	std::cout << std::endl << "\nBetta vector:\n";
	for (const auto &i : prod_betta) {
		i->printBettaProductName();
	} 
	std::cout << std::endl << "\nGamma vector:\n";
	for (const auto &i : prod_gamma) {
		i->printGammaProductName();
	} 
	std::cout << std::endl;
}