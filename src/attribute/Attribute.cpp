#include "Attribute.h"
#include <iostream>






size_t AttributeLayout::stride() const
{
	return _stride;
}

void AttributeLayout::print_attrs() const
{
	std::cout << "| offset | count | size |" << std::endl;
	for (const auto& el : _attributes)
	{
		std::cout << "| " << el.offset << " | " << el.component_count << " | " << el.component_size << " |\n";
	}
	std::cout << "stride: " << _stride << std::endl;
}

const std::vector<AttributeLayout::Attribute>& AttributeLayout::get_attributes() const
{
	return _attributes;
}
