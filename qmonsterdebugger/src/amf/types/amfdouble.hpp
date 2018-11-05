#pragma once
#ifndef AMFDOUBLE_HPP
#define AMFDOUBLE_HPP

#include "types/amfitem.hpp"
#include "types/amfnumber.hpp"

namespace amf {

class SerializationContext;

class AmfDouble : public AmfNumber {
public:
	AmfDouble() : value(0) { }
	AmfDouble(double v) : value(v) { }
    operator double() const override { return value; }
    operator int() const override { return static_cast<int>(value); }
    u8 marker() const override { return AMF_DOUBLE; }

	bool operator==(const AmfItem& other) const;
	std::vector<u8> serialize(SerializationContext&) const;
	static AmfDouble deserialize(v8::const_iterator& it, v8::const_iterator end, SerializationContext&);

	double value;
};

} // namespace amf

#endif
