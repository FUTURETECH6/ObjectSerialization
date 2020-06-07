#ifndef BIN_SER_H
#define BIN_SER_H

#include "Serializer.h"
#include <string>
#include <type_traits>

/*serialize*/
class Bin_Ser {
public:
	template<typename Type> typename std::enable_if<std::is_arithmetic<Type>::value>::type serialize(Type &obj, std::string path);
	template<typename Type> typename std::enable_if<std::is_pointer<Type>::value>::type serialize(Type &obj, std::string path);//?
	template<typename Type>	void serialize(Type obj, std::string path, std::size_t len);
	template<typename Type> void serialize(std::unique_ptr<Type> &obj, std::string path);
	template<typename Type> void serialize(std::shared_ptr<Type> &obj, std::string path);
	template<typename Type> void serialize(std::vector<Type> &obj, std::string path);
	template<typename Type> void serialize(std::list<Type> &obj, std::string path);
	template<typename Type> void serialize(std::set<Type> &obj, std::string path);
	template<typename Type>	void serialize(std::unique_ptr<Type[]> &obj, std::string path, std::size_t len);
	template<typename Type>	void serialize(std::shared_ptr<Type[]> &obj, std::string path, std::size_t len);
	template<typename Type1, typename Type2> void serialize(std::pair<Type1, Type2> &obj, std::string path);
	template<typename Type1, typename Type2> void serialize(std::map<Type1, Type2> &obj, std::string path);
};

template <typename Type>
typename std::enable_if<std::is_arithmetic<Type>::value>::type 
Bin_Ser::serialize(Type &obj, std::string path) {
	std::ofstream os(path);
	ser::ser_ari<Type>(obj, os);
};

template<typename Type>
typename std::enable_if<std::is_pointer<Type>::value>::type 
Bin_Ser::serialize(Type &obj, std::string path) {
	std::ofstream os(path);
	ser::ser_ptr<Type>(obj, os);
};

template<typename Type>
void Bin_Ser::serialize(Type obj, std::string path, std::size_t len) {
	std::ofstream os(path);
	ser::ser_ptra<Type>(obj, len, os);
};

template <typename Type1, typename Type2>
void Bin_Ser::serialize(std::pair<Type1, Type2> &obj, std::string path) {
	//std::ofstream os(path);
	serialize(obj.first, path);
	serialize(obj.second, path);
	//ser::ser_pair<Type1, Type2>(obj, os);
};

template <typename Type>
void Bin_Ser::serialize(std::unique_ptr<Type> &obj, std::string path) {
	std::ofstream os(path);
	ser::ser_uptr<Type>(obj, os);
	//serialize(*obj, path);
};

template<typename Type>
void Bin_Ser::serialize(std::unique_ptr<Type[]> &obj, std::string path, std::size_t len) {
	std::ofstream os(path);
	ser::ser_uptra<Type[]>(obj, len, os);
	//serialize(*obj, path);//?
};

template <typename Type>
void Bin_Ser::serialize(std::shared_ptr<Type> &obj, std::string path) {
	std::ofstream os(path);
	ser::ser_sptr<Type>(obj, os);
	//serialize(*obj, path);
};

template<typename Type>
void Bin_Ser::serialize(std::shared_ptr<Type[]> &obj, std::string path, std::size_t len) {
	std::ofstream os(path);
	ser::ser_sptra<Type[]>(obj, len, os);
};

template <typename Type>
void Bin_Ser::serialize(std::vector<Type> &obj, std::string path) {
	//std::ofstream os(path);
	//ser::ser_vec<Type>(obj, os);
	serialize(obj.size(), path);
	for (auto &elem : obj) {
		serialize(elem, path);
	}
};

template <typename Type>
void Bin_Ser::serialize(std::list<Type> &obj, std::string path) {
	//std::ofstream os(path);
	//ser::ser_list<Type>(obj, os);
	serialize(obj.size(), path);
	for (auto &elem : obj) {
		serialize(elem, path);
	}
};

template <typename Type>
void Bin_Ser::serialize(std::set<Type> &obj, std::string path) {
	//std::ofstream os(path);
	//ser::ser_set<Type>(obj, os);
	serialize(obj.size(), path);
	for (auto &elem : obj) {
		serialize(elem, path);
	}
};

template <typename Type1, typename Type2>
void Bin_Ser::serialize(std::map<Type1, Type2> &obj, std::string path) {
	//std::ofstream os(path);
	//ser::ser_map<Type1, Type2>(obj, os);
	serialize(obj.size(), path);
	for (auto &elem : obj) {
		serialize(elem, path);
	}
};
/*------------------------------------------------------------*/
/*deserialize*/
class Bin_Des {
public://typename std::enable_if<std::is_arithmetic<Type>::value>::type
	template<typename Type> typename std::enable_if<std::is_arithmetic<Type>::value>::type deserialize(Type &obj, std::string path);
	template<typename Type> typename std::enable_if<std::is_pointer<Type>::value>::type deserialize(Type &obj, std::string path);
	template<typename Type> void deserialize(Type &obj, std::string path, std::size_t len);
	template<typename Type> void deserialize(std::unique_ptr<Type> &obj, std::string path);
	template<typename Type> void deserialize(std::shared_ptr<Type> &obj, std::string path);
	template<typename Type> void deserialize(std::vector<Type> &obj, std::string path);
	template<typename Type> void deserialize(std::list<Type> &obj, std::string path);
	template<typename Type> void deserialize(std::set<Type> &obj, std::string path);
	template<typename Type>	void deserialize(std::unique_ptr<Type[]> &obj, std::string path, std::size_t len);
	template<typename Type>	void deserialize(std::shared_ptr<Type[]> &obj, std::string path, std::size_t len);
	template<typename Type1, typename Type2> void deserialize(std::pair<Type1, Type2> &obj, std::string path);
	template<typename Type1, typename Type2> void deserialize(std::map<Type1, Type2> &obj, std::string path);
};

template <typename Type >
typename std::enable_if<std::is_arithmetic<Type>::value>::type 
Bin_Des::deserialize(Type &obj, std::string path) {
		std::ifstream is(path);
		des::des_ari<Type>(obj, is);
	};

template <typename Type>
typename std::enable_if<std::is_pointer<Type>::value>::type 
Bin_Des::deserialize(Type &obj, std::string path) {
	std::ifstream is(path);
	des::des_ptr<Type>(obj, is);
};

template <typename Type>
void Bin_Des::deserialize(Type &obj, std::string path, std::size_t len) {
	std::ifstream is(path);
	des::des_ptra(obj, is);
};

template <typename Type1, typename Type2>
void Bin_Des::deserialize(std::pair<Type1, Type2> &obj, std::string path) {
	std::ifstream is(path);
	deserialize(obj.first, path);
	deserialize(obj.second, path);
	//des::des_pair<Type1, Type2>(obj, is);
};

template <typename Type>
void Bin_Des::deserialize(std::unique_ptr<Type> &obj, std::string path) {
	std::ifstream is(path);
	des::des_uptr<Type>(obj, is);
	//deserialize(*obj, path);
};

template<typename Type>
void Bin_Des::deserialize(std::unique_ptr<Type[]> &obj, std::string path, std::size_t len) {
	std::ifstream is(path);
	des::des_uptra<Type[]>(obj, len, is);
};

template <typename Type>
void Bin_Des::deserialize(std::shared_ptr<Type> &obj, std::string path) {
	std::ifstream is(path);
	des::des_sptr<Type>(obj, is);
};

template<typename Type>
void Bin_Des::deserialize(std::shared_ptr<Type[]> &obj, std::string path, std::size_t len) {
	std::ifstream is(path);
	des::des_sptra<Type[]>(obj, len, is);
};

template <typename Type>
void Bin_Des::deserialize(std::vector<Type> &obj, std::string path) {
	//std::ifstream is(path);
	//des::des_vec<Type>(obj, is);
	deserialize(obj.size(), path);
	for (auto &elem : obj) {
		deserialize(elem, path);
	}
};

template <typename Type>
void Bin_Des::deserialize(std::list<Type> &obj, std::string path) {
	//std::ifstream is(path);
	//des::des_list<Type>(obj, is);
	deserialize(obj.size(), path);
	for (auto &elem : obj) {
		deserialize(elem, path);
	}
};

template <typename Type>
void Bin_Des::deserialize(std::set<Type> &obj, std::string path) {
	//std::ifstream is(path);
	//des::des_set<Type>(obj, is);
	deserialize(obj.size(), path);
	for (auto &elem : obj) {
		deserialize(elem, path);
	}
};

template <typename Type1, typename Type2>
void Bin_Des::deserialize(std::map<Type1, Type2> &obj, std::string path) {
	//std::ifstream is(path);
	//des::des_map<Type1, Type2>(obj, is);
	deserialize(obj.size(), path);
	for (auto &elem : obj) {
		deserialize(elem, path);
	}
};

#endif