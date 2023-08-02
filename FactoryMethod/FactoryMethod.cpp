#include <iostream>
#include <vector>
#include "FactoryMethod.h"


class ProductAlpha: public algs::Product
{
public:
	ProductAlpha() = default;
	~ProductAlpha() = default;

	void printProductName() override {
		std::cout << "Product name:\t\'Alpha\'\n";
	}
};

class ProductBetta: public algs::Product
{
public:
	ProductBetta() = default;
	~ProductBetta() = default;

	void printProductName() override {
		std::cout << "Product name:\t\'Betta\'\n";
	}

};

class ProductGamma: public algs::Product
{
public:
	ProductGamma() = default;
	~ProductGamma() = default;

	void printProductName() override {
		std::cout << "Product name:\t\'Gamma\'\n";
	}
};




class FactoryAlpha: public algs::Factory
{
public:
	FactoryAlpha() = default;
	~FactoryAlpha() = default;
	
	algs::Product* factoryMethod() const override {
		return new ProductAlpha;
	}
};

class FactoryBetta: public algs::Factory
{
public:
	FactoryBetta() = default;
	~FactoryBetta() = default;

	algs::Product* factoryMethod() const override {
		return new ProductBetta;
	}
};

class FactoryGamma: public algs::Factory
{
public:
	FactoryGamma() = default;
	~FactoryGamma() = default;

	algs::Product* factoryMethod() const override {
		return new ProductGamma;
	}
};




int main()
{
	FactoryAlpha alpha;
	FactoryBetta betta;
	FactoryGamma gamma;
	std::vector<algs::Product*> products;

	for (int i = 0; i < 3; ++i) {
		products.push_back(alpha.factoryMethod());
	}
	for (int i = 0; i < 5; ++i) {
		products.push_back(betta.factoryMethod());
	}
	for (int i = 0; i < 7; ++i) {
		products.push_back(gamma.factoryMethod());
	}
	for (const auto &ptr: products) {
		ptr->printProductName();
	}

	return 0;
}