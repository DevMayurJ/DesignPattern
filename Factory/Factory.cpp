// Factory.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
using namespace std;

/*=================ACTUAL Product START============================================================================*/
/**
 * The Product interface declares the operations that all concrete products must
 * implement.
 */

class CBroker
{
public:
	virtual ~CBroker() {}
	virtual std::string ParseFixMessage() const = 0;
};

/**
 * Concrete Products provide various implementations of the Product interface.
 */
class CHSBC : public CBroker
{
public:
	std::string ParseFixMessage() const override
	{
		return "{Result of the CHSBC}";
	}
};

class CAxis : public CBroker
{
public:
	std::string ParseFixMessage() const override
	{
		return "{Result of the CAxis}";
	}
};

/*=================ACTUAL Product END============================================================================*/



/*=================Creator START============================================================================*/
/**
 * The Creator class declares the factory method that is supposed to return an
 * object of a Product class. The Creator's subclasses usually provide the
 * implementation of this method.
 */
class Creator
{
	/**
	 * Note that the Creator may also provide some default implementation of the
	 * factory method.
	 */
public:
	virtual ~Creator() {};
	virtual CBroker* FactoryMethod() const = 0;
	/**
	 * Also note that, despite its name, the Creator's primary responsibility is
	 * not creating products. Usually, it contains some core business logic that
	 * relies on Product objects, returned by the factory method. Subclasses can
	 * indirectly change that business logic by overriding the factory method and
	 * returning a different type of product from it.
	 */

	std::string ParseFixMessage() const
	{
		// Call the factory method to create a Product object.
		CBroker* broker = this->FactoryMethod();
		// Now, use the product.
		std::string result = "Creator: The same creator's code has just worked with " + broker->ParseFixMessage();
		delete broker;
		return result;
	}
};

/**
 * Concrete Creators override the factory method in order to change the
 * resulting product's type.
 */
class ConcreteCreatorHSBC : public Creator 
{
	/**
	 * Note that the signature of the method still uses the abstract product type,
	 * even though the concrete product is actually returned from the method. This
	 * way the Creator can stay independent of concrete product classes.
	 */
public:
	CBroker* FactoryMethod() const override
	{
		return new CHSBC();
	}
};

class ConcreteCreatorAxis : public Creator
{
public:
	CBroker* FactoryMethod() const override
	{
		return new CAxis();
	}
};
/*=================Creator END============================================================================*/

/**
 * The client code works with an instance of a concrete creator, albeit through
 * its base interface. As long as the client keeps working with the creator via
 * the base interface, you can pass it any creator's subclass.
 */
void ClientCode(const Creator& creator) 
{
	// ...
	std::cout << "Client: I'm not aware of the creator's class, but it still works.\n";
	cout << creator.ParseFixMessage().c_str() << std::endl;
	// ...
}


/**
 * The Application picks a creator's type depending on the configuration or
 * environment.
 */

int main()
{

	bool bExit = false;
	while (!bExit)
	{
		int iChoice;
		cout << "1 HSBC\n2 Axix\n0 Exit\n";
		cout << "Enter your choice:\n";
		cin >> iChoice;
		Creator* creator = nullptr;
		switch (iChoice)
		{
			//scope issue, case: doesn't introduce new scope till break, so you have to use {} if we want to declare variable inside case
			case 1:
			{
				std::cout << "App: Launched with the ConcreteCreator1.\n";
				creator = new ConcreteCreatorHSBC();
			}
			break;
			case 2:
			{
				std::cout << std::endl;
				std::cout << "App: Launched with the ConcreteCreator2.\n";
				creator = new ConcreteCreatorAxis();
			}
			break;
			case 0:
				std::cout << "Exiting.\n";
				bExit = true;
				break;
			default:
				std::cout << "Invalid choice.\n";
		}

		if (nullptr != creator)
		{
			ClientCode(*creator);
			delete creator;
		}
	}//while

	return 0;
}

/*
1 HSBC
2 Axix
0 Exit
Enter your choice:
1
App: Launched with the ConcreteCreator1.
Client: I'm not aware of the creator's class, but it still works.
Creator: The same creator's code has just worked with {Result of the CHSBC}
1 HSBC
2 Axix
0 Exit
Enter your choice:
2

App: Launched with the ConcreteCreator2.
Client: I'm not aware of the creator's class, but it still works.
Creator: The same creator's code has just worked with {Result of the CAxis}
1 HSBC
2 Axix
0 Exit
Enter your choice:
0
Exiting.
*/