#include <memory>

namespace algs 
{
	class Product 
	{
	public:
		virtual ~Product() = default;
		virtual void printProductName() = 0;
	};

	class Factory
	{
	public:
		virtual ~Factory() = default;
		virtual Product* factoryMethod() const = 0;
	};
}