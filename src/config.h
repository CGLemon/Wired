#pragma once

#include <boost/program_options.hpp>

static constexpr int kChipHeight = 500;
static constexpr int kChipWidth = 500;
static constexpr int kNumVertices = (kChipHeight+2) * (kChipWidth+2);

void ParseArgs(int argc, char **argv);

extern boost::program_options::variables_map kVariablesMap;
