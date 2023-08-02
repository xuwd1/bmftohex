#include <iostream>
#include <argparse/argparse.hpp>
#include <string>
#include <memory>
#include <bmfconvert.hpp>

// a tool dedicated for bmf embedded in iasl decompiled acpi table

void write_buffer_to_file(std::string filename, const std::unique_ptr<uint8_t[]>& buffer, const size_t buffer_size){
    std::FILE* outfile =  std::fopen(filename.c_str(),"w");
    fwrite(buffer.get(), buffer_size , 1, outfile);
    std::fclose(outfile);
}

int main(int argc, char** argv){
    argparse::ArgumentParser parser("bmftohex","0.1",argparse::default_arguments::all,true);
    parser.add_argument("inpath").help("path to bmf text file").metavar("<INPATH>");
    parser.add_argument("outpath").help("path to output binary file").metavar("<OUTPATH>");
    try {
        parser.parse_args(argc,argv);
    } 
    catch(const std::runtime_error& err) {
        std::cerr << err.what() << std::endl;
        std::cerr << parser;
        return 1;
    }
    try {
        auto file_path = parser.get<std::string>("inpath");
        auto out_path = parser.get<std::string>("outpath");
        auto lines = read_bmf_file(file_path);
        lines = extract_hex_strings(lines);
        size_t value_buffer_size;
        std::unique_ptr<uint8_t[]> value_buffer = transform_hex_strings(lines,value_buffer_size);
        write_buffer_to_file(out_path, value_buffer, value_buffer_size);
    } 
    catch (const std::exception& e) {
        std::cerr<<"Exception occured: "<< e.what()<<std::endl;
        return 1;
    }
    return 0;
}