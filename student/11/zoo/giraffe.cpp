#include "giraffe.hh"

Giraffe::Giraffe(): Mammal()
{
}

void Giraffe::suckle(std::ostream &output) const
{
    output << "Ori ori ori!" << std::endl;
}
