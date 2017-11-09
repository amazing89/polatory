// Copyright (c) 2016, GSI and The Polatory Authors.

#pragma once

#include <cstdlib>
#include <exception>
#include <iostream>
#include <string>

#include <boost/program_options.hpp>

struct options {
  std::string in_file;
  double bin_width;
  int n_bins;
  double psill;
  double range;
  double nugget;
};

options parse_options(int argc, const char *argv[]) {
  namespace po = boost::program_options;

  options opts;

  po::options_description opts_desc("");
  opts_desc.add_options()
    ("in", po::value<std::string>(&opts.in_file)->required(),
     "input file")
    ("bin-width", po::value<double>(&opts.bin_width)->required(),
     "bin width of empirical variogram")
    ("n-bins", po::value<int>(&opts.n_bins)->default_value(15),
     "number of bins of empirical variogram")
    ("psill", po::value<double>(&opts.psill)->required(),
     "initial value for the partial sill")
    ("range", po::value<double>(&opts.range)->required(),
     "initial value for the range")
    ("nugget", po::value<double>(&opts.nugget)->default_value(0),
     "initial value for the nugget");

  po::variables_map vm;
  try {
    po::store(po::parse_command_line(argc, argv, opts_desc, po::command_line_style::unix_style ^ po::command_line_style::allow_short), vm);
    po::notify(vm);
  } catch (std::exception& e) {
    std::cout << e.what() << std::endl
              << "Usage: " << argv[0] << " [OPTION]..." << std::endl
              << opts_desc;
    std::exit(1);
  }

  return opts;
}