#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <format>
#include <memory>
#include <ranges>
#include <msl/scoped_shared_ptr.h>

struct Sauce
{
	std::string name;
};

class SaucePot
{
public:
	SaucePot(std::string name)
	{
		m_sauce = std::make_shared<Sauce>();
		m_sauce->name = name;
	}
	scoped_shared_ptr<Sauce> GetSauce() { return scoped_shared_ptr<Sauce>(m_sauce); }

private:
	std::shared_ptr<Sauce> m_sauce;
};

void ScopedRef(scoped_shared_ptr<Sauce> & sauce, const std::string_view name)
{
	sauce->name = name;
	std::cout << std::format("sauce pot named {} here\n", sauce->name); // ok
}

void TestScopedSharedPtr()
{
	std::cout << __FUNCTION__ << " test starting" << '\n';

	SaucePot pot("Torta");
	Sauce * bad_sauce{};
	std::shared_ptr<Sauce> bad_sauce2{};
	std::vector<std::shared_ptr<Sauce>> bad_sausages;

	{
		const auto sauce = pot.GetSauce(); // ok
		std::cout << std::format("sauce pot named {} here\n", sauce->name); // ok
		// bad_sauce = sauce.get(); // compile-error get disabled
		// bad_sauce = *sauce; // compile-error dereference disabled
		// scoped_shared_ptr<Sauce> bad_scoped_sauce1(sauce); // compile-error copy disabled 1
		// scoped_shared_ptr<Sauce> bad_scoped_sauce2 = sauce; // compile-error copy disabled 2
		// scoped_shared_ptr<Sauce> bad_scoped_sauce3; // compile-error default constructor disabled
		// sauce = pot.GetSauce(); // compile-error assignment disabled
	}

	{
		auto sauce2 = pot.GetSauce(); // ok
		sauce2->name = "Tortillas"; // ok if non const
		std::cout << std::format("sauce pot named {} here\n", sauce2->name); // ok
		sauce2->name = "Tortiglione"; // ok if non const
	}
	std::cout << std::format("sauce pot named {} here\n", pot.GetSauce()->name); // ok

	{
		auto sauce = pot.GetSauce(); // ok
		// bad_sauce2(sauce); // compile-error private base constructor 1
		// bad_sauce2 = sauce; // compile-error private base constructor 2
		// bad_sausages.emplace_back(sauce); // compile-error private base constructor
		// bad_sausages.push_back(sauce); // compile-error private base constructor
		ScopedRef(sauce, "Tortellino"); // ok
	}

	{
		auto sauce = pot.GetSauce(); // ok
		// std::shared_ptr<Sauce> sauce2 = std::static_pointer_cast<Sauce>(sauce); // compile-error private base constructor
		// auto shared = static_cast<std::shared_ptr<Sauce>>(sauce); // compile-error private base constructor

		auto sauce2 = sauce.operator->(); // ok - unsafe
		sauce.~scoped_shared_ptr(); // ok - unsafe
	}
	std::cout << "All tests passed." << '\n';

	std::cout << std::endl << "Press enter to continue..." << std::endl;
	std::ignore = getchar();
	std::ignore = getchar();
}
