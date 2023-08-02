#include <vector>
#include <string>
#include <memory>


std::vector<std::string> read_bmf_file(const std::string filepath);
std::vector<std::string> extract_hex_strings(const std::vector<std::string>& lines);
std::unique_ptr<uint8_t[]> transform_hex_strings(const std::vector<std::string>& hex_strings, size_t& buffer_size);
