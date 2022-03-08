#include <iostream>
#include <string>

#include "utils/format.h"
#include "config.h"

namespace po = boost::program_options;
po::variables_map kVariablesMap;

void ParseArgs(int argc, char **argv) {
    for (int i = 0; i < argc; ++i) {
        auto arg = std::string(argv[i]);
    }

    po::options_description gen_desc("Generic options");
    gen_desc.add_options()
        ("help,h", "Show commandline options.")
        ("filename,f", po::value<std::string>(), "The input file name.");

    // Set all visible options.
    po::options_description visible;
    visible.add(gen_desc);

    // Collect all options.
    po::options_description all;
    all.add(visible);

    po::positional_options_description p_desc;
    p_desc.add("arguments", -1);

    try {
        po::store(po::command_line_parser(argc, argv)
                      .options(all)
                      .positional(p_desc)
                      .run(),
                  kVariablesMap);
        po::notify(kVariablesMap);
    } catch (const boost::program_options::error& e) {
        printf("ERROR: %s\n", e.what());
        std::cout << visible << std::endl;
        exit(EXIT_FAILURE);
    }

    if (kVariablesMap.count("help") ||
            kVariablesMap.count("arguments")) {
        auto ev = EXIT_SUCCESS;
        // The user specified an argument. We don't accept any, so explain
        // our usage.
        if (kVariablesMap.count("arguments")) {
            for (auto& arg : kVariablesMap["arguments"].as<std::vector<std::string>>()) {
                std::cout << "Unrecognized argument: " << arg << std::endl;
            }
            ev = EXIT_FAILURE;
        }
        std::cout << visible << std::endl;
        exit(ev);
    }
}
