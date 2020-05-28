#include <string>

namespace b64 {
    static const std::string base64_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                                            "abcdefghijklmnopqrstuvwxyz"
                                            "0123456789+/";

    // static inline bool is_base64(unsigned char);
    std::string encode(const std::string &);
    std::string decode(const std::string &);
} // namespace b64