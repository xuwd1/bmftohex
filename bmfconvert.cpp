#include <fstream>
#include <regex>
#include <vector>
#include <memory>
#include <bmfconvert.hpp>

/*
    read bmf file into vector of strings. one string per line.
*/
std::vector<std::string> read_bmf_file(const std::string filepath){
    std::vector<std::string> ret;
    std::ifstream infile(filepath);
    std::string linestr;
    while(std::getline(infile,linestr)){
        ret.push_back(linestr);
    }
    return ret;
}

/*
    extract hex strings. one hex number string without any prefix per item in the returning vector
*/
const std::regex enclosed_comment_re("\\/\\*.*\\*\\/");
const std::regex open_comment_re("\\/\\/.*$");
const std::regex hex_num_re("0[xX]([0-9a-fA-F]{2})");
std::vector<std::string> extract_hex_strings(const std::vector<std::string>& lines){
    std::vector<std::string> ret;
    for (auto& line:lines){
        std::string new_line;
        new_line = std::regex_replace(line,enclosed_comment_re,"");
        new_line = std::regex_replace(new_line,open_comment_re,"");
        std::sregex_iterator iter(new_line.begin(),new_line.end(),hex_num_re);
        for (;iter!=std::sregex_iterator();iter++){
            std::smatch match;
            match = *iter;
            ret.push_back(match.str(1));
        }
    }
    return ret;
}

std::unique_ptr<uint8_t[]> transform_hex_strings(const std::vector<std::string>& hex_strings, size_t& buffer_size){
    size_t string_nums = hex_strings.size();
    buffer_size = string_nums;
    std::unique_ptr<uint8_t[]> ret_buffer(new uint8_t[string_nums]);
    for (size_t i=0; i<string_nums; i++){
        const auto& hex_string = hex_strings[i];
        uint8_t hex_value = std::stoi(hex_string,0,16);
        ret_buffer[i] = hex_value; 
    }
    return ret_buffer;
}

