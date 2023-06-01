#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <exception>
#include <fstream>
#include <ios>
#include <iostream>
#include <istream>
#include <limits>
#include <map>
#include <memory>
#include <ostream>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>
#include <chrono>


using CodeType = std::uint16_t;

namespace globals {


    const CodeType dms{ std::numeric_limits<CodeType>::max() };

}

void compress(std::istream& is, std::ostream& os)
{
    std::map<std::pair<CodeType, char>, CodeType> dictionary;


    const auto reset_dictionary = [&dictionary] {
        dictionary.clear();

        const long int minc = std::numeric_limits<char>::min();
        const long int maxc = std::numeric_limits<char>::max();

        for (long int c = minc; c <= maxc; ++c)
        {
            const CodeType dictionary_size = dictionary.size();

            dictionary[{globals::dms, static_cast<char> (c)}] = dictionary_size;
        }
    };

    reset_dictionary();

    CodeType i{ globals::dms };
    char c;

    while (is.get(c))
    {

        if (dictionary.size() == globals::dms)
            reset_dictionary();

        if (dictionary.count({ i, c }) == 0)
        {

            const CodeType dictionary_size = dictionary.size();

            dictionary[{i, c}] = dictionary_size;
            os.write(reinterpret_cast<const char*> (&i), sizeof(CodeType));
            i = dictionary.at({ globals::dms, c });
        }
        else
            i = dictionary.at({ i, c });
    }

    if (i != globals::dms)
        os.write(reinterpret_cast<const char*> (&i), sizeof(CodeType));
}

void decompress(std::istream& is, std::ostream& os)
{
    std::vector<std::pair<CodeType, char>> dictionary;


    const auto reset_dictionary = [&dictionary] {
        dictionary.clear();
        dictionary.reserve(globals::dms);

        const long int minc = std::numeric_limits<char>::min();
        const long int maxc = std::numeric_limits<char>::max();

        for (long int c = minc; c <= maxc; ++c)
            dictionary.push_back({ globals::dms, static_cast<char> (c) });
    };

    const auto rebuild_string = [&dictionary](CodeType k) -> std::vector<char> {
        std::vector<char> s;

        while (k != globals::dms)
        {
            s.push_back(dictionary.at(k).second);
            k = dictionary.at(k).first;
        }

        std::reverse(s.begin(), s.end());
        return s;
    };

    reset_dictionary();

    CodeType i{ globals::dms };
    CodeType k;

    while (is.read(reinterpret_cast<char*> (&k), sizeof(CodeType)))
    {

        if (dictionary.size() == globals::dms)
            reset_dictionary();

        if (k > dictionary.size())
            throw std::runtime_error("invalid compressed code");

        std::vector<char> s;

        if (k == dictionary.size())
        {
            dictionary.push_back({ i, rebuild_string(i).front() });
            s = rebuild_string(k);
        }
        else
        {
            s = rebuild_string(k);

            if (i != globals::dms)
                dictionary.push_back({ i, s.front() });
        }

        os.write(&s.front(), s.size());
        i = k;
    }

    if (!is.eof() || is.gcount() != 0)
        throw std::runtime_error("corrupted compressed file");
}


void print_usage(const std::string& s = "", bool su = true)
{
    if (!s.empty())
        std::cerr << "\nERROR: " << s << '\n';

    if (su)
    {
        std::cerr << "\nUsage:\n";
        std::cerr << "\tprogram -flag input_file output_file\n\n";
        std::cerr << "Where `flag' is either `c' for compressing, or `d' for decompressing, and\n";
        std::cerr << "`input_file' and `output_file' are distinct files.\n\n";
        std::cerr << "Examples:\n";
        std::cerr << "\tlzw_v3.exe -c license.txt license.lzw\n";
        std::cerr << "\tlzw_v3.exe -d license.lzw new_license.txt\n";
    }

    std::cerr << std::endl;
}


int main()
{

    enum class Mode {
        Compress,
        Decompress
    };

    Mode m;

    std::cout << "compress or decompress? (c/d): ";
    char mode;
    std::cin >> mode;
    std::cout << std::endl;

    if (mode == 'c')
        m = Mode::Compress;
    else
        if (mode == 'd')
            m = Mode::Decompress;
        else
        {
            print_usage(std::string("flag `") + mode + "' is not recognized.");
            return EXIT_FAILURE;
        }

    const std::size_t buffer_size{ 1024 * 1024 };

    const std::unique_ptr<char[]> input_buffer(new char[buffer_size]);
    const std::unique_ptr<char[]> output_buffer(new char[buffer_size]);

    std::ifstream input_file;
    std::ofstream output_file;

    std::cout << "input file path: ";
    std::string path;
    std::cin >> path;
    std::cout << std::endl;

    input_file.rdbuf()->pubsetbuf(input_buffer.get(), buffer_size);
    input_file.open(path, std::ios_base::binary);

    if (!input_file.is_open())
    {
        print_usage(std::string("input_file `") + path + "' could not be opened.");
        return EXIT_FAILURE;
    }

    std::cout << "input new file path: ";
    std::string newPath;
    std::cin >> newPath;
    std::cout << std::endl;

    output_file.rdbuf()->pubsetbuf(output_buffer.get(), buffer_size);
    output_file.open(newPath, std::ios_base::binary);

    if (!output_file.is_open())
    {
        print_usage(std::string("output_file `") + newPath + "' could not be opened.");
        return EXIT_FAILURE;
    }

    try
    {
        input_file.exceptions(std::ios_base::badbit);
        output_file.exceptions(std::ios_base::badbit | std::ios_base::failbit);
        
        typedef std::chrono::high_resolution_clock clock_;
        typedef std::chrono::milliseconds ms;
        std::chrono::time_point<std::chrono::high_resolution_clock> beg_ = clock_::now();
        auto t = clock_::now();


        if (m == Mode::Compress)
            compress(input_file, output_file);
        else
            if (m == Mode::Decompress)
                decompress(input_file, output_file);

        std::chrono::time_point<std::chrono::high_resolution_clock> end_ = clock_::now();
        std::cout << "time: " << std::chrono::duration_cast<ms>(end_ - beg_).count();
    }
    catch (const std::ios_base::failure& f)
    {
        print_usage(std::string("File input/output failure: ") + f.what() + '.', false);
        return EXIT_FAILURE;
    }
    catch (const std::exception& e)
    {
        print_usage(std::string("Caught exception: ") + e.what() + '.', false);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}