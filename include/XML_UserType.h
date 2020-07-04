#ifndef XML_USERTYPE_H
#define XML_USERTYPE_H

#include "XML_Ser.h"
#include "tinyxml2.h"

class UserType_Ser_Xml : public xml_ser
{
public:
	UserType_Ser_Xml(const char* filepath) : xml_ser(filepath) { };
	~UserType_Ser_Xml() {};

	template<typename Type>
	void Serialize(Type &obj, std::string NodeName) {
		Serializer(obj, NodeName, root);
	};
	template<typename Type>
	void Serialize(Type &obj, std::string NodeName, size_t len) {
		Serializer(obj, NodeName, root, len);
	};
};



class UserType_Des_Xml : public xml_des
{
private:
	tinyxml2::XMLElement *Child;
public:
	UserType_Des_Xml(const char* filepath) : xml_des(filepath) { Child = root->FirstChildElement(); };
	~UserType_Des_Xml() {};
	template<typename Type>
	void Deserialize(Type &obj, std::string NodeName) {
		if (Child) {
			Deserializer(obj, NodeName, Child);
			Child = Child->NextSiblingElement();
		}
	};
	template<typename Type>
	void Deserialize(Type &obj, std::string NodeName, size_t len) {
		if (Child) {
			Deserializer(obj, NodeName, Child, len);
			Child = Child->NextSiblingElement();
		}
	};
};

#endif
