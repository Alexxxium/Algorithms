#include <iostream>



namespace algs
{
	class ProductAlpha
	{
	public:
		virtual ~ProductAlpha() = default;
		virtual void printAlphaProductName() const = 0;
	};

	class ProductBetta
	{
	public:
		virtual ~ProductBetta() = default;
		virtual void printBettaProductName() const = 0;
	};

	class ProductGamma
	{
	public:
		virtual ~ProductGamma() = default;
		virtual void printGammaProductName() const = 0;
	};


	class Factory
	{
	public:
		virtual ~Factory() = default;
		virtual ProductAlpha* factoryMethodAlpha() const = 0;
		virtual ProductBetta* factoryMethodBetta() const = 0;
		virtual ProductGamma* factoryMethodGamma() const = 0;
	};
}